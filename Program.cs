// See https://aka.ms/new-console-template for more information
using System;

namespace Cards
{
    public class Card{
        public static String[] SUITS = {"Clubs", "Diamonds", "Hearts", "Spades"};
        public static String[] RANKS = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten","Jack", "Queen", "King", "Ace"};
        public static String[] HAND = {"One pair.","Two pair.","Three of a kind.","Straight.","Flush.","Full house.","Four of a kind.","Straight flush.","Royal flush."};
        static String[] init(){
            String[] deck = new String[52];
            for (int i = 0; i < RANKS.Length; i++) {    // Setting up the deck of 52 cards
                for (int j = 0; j < SUITS.Length; j++) {
                    deck[SUITS.Length*i + j] = RANKS[i] + " of " + SUITS[j];
                } 
            }
            return deck;
        }
        static void shuffle( String [] deck){
            for (int i = 0; i < 52; i++) {
                Random rnd = new Random();
                int r = i + (rnd.Next(0,52-i)); //using random function
                String temp = deck[r];
                deck[r] = deck[i];
                deck[i] = temp;
            }
        }
        static void winner( String[] deck,int players){
            for( int i = 0; i < 5*players; i++ ){ //printing one card at a time
                if(i%5==0){
                    int player=i/5+1;
                    Console.WriteLine("Player "+ player +" has:");
                }
                Console.WriteLine(deck[i]); //displaying a random card
            }
            String[] rank= new String[players*5];
            String[] suit=new String[players*5];
            for(int i=0; i<players; i++){
                for(int j=0+(i*5);j<5+(i*5);j++){
                    String[] card=deck[j].Split(" ");       // Spliting the card into rank + of + suit
                    rank[j]=card[0];
                    suit[j]=card[2];
                }
            }
            HashSet<string> rank_set = new HashSet<string>();
            HashSet<string> suit_set = new HashSet<string>();
            int[] win=new int[players];
            int[] max=new int[players];
            for(int i=0; i<players; i++){
                max[i]=-1;
                for(int j=0+(i*5);j<5+(i*5);j++){ // Removing duplicates by moving into sets
                    rank_set.Add(rank[j]);
                    suit_set.Add(suit[j]);
                }
                if(rank_set.Count()==2){     // If rank size is 2 that means we have full house or four of a kind
                    int count=1;
                    String temp=rank[0+(i*5)];
                    for(int j=1+(i*5);j<5+(i*5);j++){
                        if(rank[j].Equals(temp))
                            count++;
                    }
                    if(count==4){
                        // This means we have four of a kind
                        Console.WriteLine("Player "+ (i+1)+" has:"+HAND[6]);
                        win[i]=6;
                    }
                    else{
                        // This means we have a full house
                        Console.WriteLine("Player "+ (i+1)+" has:"+HAND[5]);
                        win[i]=5;
                    }
                }
                else if(rank_set.Count()==3){    // if rank is 3 it means we have three of a kind or two pair
                    int count=1;
                    String temp=rank[0+(i*5)];
                    for(int j=1+(i*5);j<5+(i*5);j++){
                        if(rank[j].Equals(temp))
                            count++;
                    }
                    if(count==3){
                        // This means we have three of a kind
                        Console.WriteLine("Player "+ (i+1)+" has:"+HAND[2]);
                        win[i]=2;
                    }
                    else{
                        // This means we have two pair
                        Console.WriteLine("Player "+ (i+1)+" has:"+HAND[1]);
                        win[i]=1;
                    }
                }
                else if(rank_set.Count()==4){
                    // This means we have one pair
                    win[i]=0;
                    Console.WriteLine("Player "+ (i+1)+" has:"+HAND[0]);
                }
                else{
                    int straight_counter=0; // if the straight_counter equals 5 we have a straight
                    int min=12;
                    int ace_flag=0; // if there is an A ace_flag equals 1
                    for(int j=0+(i*5);j<5+(i*5);j++){
                        for(int k=0;k<13;k++){
                            if(rank[j].Equals(RANKS[k])){
                                if(min>k)       // Need the minimum for checking straights
                                    min=k;
                                if(max[i]<k)       // Need the maximum for high card in case of no flushes or straights
                                    max[i]=k;
                            }
                            if(rank[j].Equals(RANKS[12]))
                                ace_flag=1;     // needed for A 2 3 4 5 straight
                        }
                    }
                    if(min==0){ // if 2 is the smallest from RANKS,check for A 2 3 4 5 straight
                        for(int j=0+(i*5);j<5+(i*5);j++){
                            for(int k=0;k<4;k++){
                                if(rank[j].Equals(RANKS[k]))
                                    straight_counter++;
                            }
                        }
                        //Only here straight_counter needs to be 4 because we already checked for A
                        if(straight_counter==4 && ace_flag==1 && suit_set.Count()!=1){
                            // This means we have a straight
                            win[i]=3;
                            Console.WriteLine("Player "+ (i+1)+" has:"+HAND[3]);
                        }
                        else if(straight_counter==4 && ace_flag==1 && suit_set.Count()==1){
                            // This means we have a straight flush
                            win[i]=7;
                            Console.WriteLine("Player "+ (i+1)+" has:"+HAND[7]);
                        }
                        else if(suit_set.Count()==1){
                            // If there is no straight and we have only 1 suit we have a flush
                            win[i]=4;
                            Console.WriteLine("Player "+ (i+1)+" has:"+HAND[4]);
                        }
                        else{
                            win[i]=-1;
                            Console.WriteLine("Player "+(i+1)+" has high card:"+RANKS[max[i]]+".");
                        }
                    }
                    // Checks for all other straights 
                    else if(min<=8){
                        // Going through the ranks of the cards to see if there is a straight
                        for(int j=0+(i*5);j<5+(i*5);j++){
                            for(int k=min;k<min+5;k++){
                                if(rank[j].Equals(RANKS[k]))
                                    straight_counter++;
                            }
                        }
                        if(straight_counter==5 && suit_set.Count()!=1){
                            // This means we have a straight
                            win[i]=3;
                            Console.WriteLine("Player "+ (i+1)+" has:"+HAND[3]);
                        }
                        else if(straight_counter==5 && suit_set.Count()==1){
                            // This means we have a straight flush
                            win[i]=7;
                            Console.WriteLine("Player "+ (i+1)+" has:"+HAND[7]);
                        }
                        else if(straight_counter==5 && suit_set.Count()==1 && ace_flag==1){
                            // This means we have a royal flush
                            win[i]=8;
                            Console.WriteLine("Player "+ (i+1)+" has:"+HAND[8]);
                        }
                        else{
                            // Printing out the high card of the player
                            win[i]=-1;
                            Console.WriteLine("Player "+(i+1)+" has high card:"+RANKS[max[i]]+".");
                        }
                    }
                }
                rank_set.Clear();
                suit_set.Clear();
            }
            int winning_hand=win[0]; // Setting the winning hand to the first player
            for(int i=1;i<players;i++){
                if(win[i]>winning_hand)
                    winning_hand=win[i];        // Finding which is the winning hand
            }
            int split_pot=0; // If pot is split then split_pot equals 2 or more
            for(int i=0;i<players;i++){
                if(winning_hand==win[i]){       // Checking if there is more than one winning hand
                    split_pot++;
                    if(win[i]!=-1)
                        Console.WriteLine("Player "+(i+1)+" has won.");        // Printing which players won.
                }
            }
            if(split_pot>=2){       // Printing the outcome if there is more than one winning hand
                if(winning_hand==-1){
                    Console.WriteLine("Higher card wins else pot is split.");
                }
                else
                    Console.WriteLine("Pot is split.");
            }
        }
	static void Main(String[] args) {
        String [] deck = init();
        shuffle(deck);
        Console.WriteLine("Enter the number of players:");
#pragma warning disable CS8604 // Possible null reference argument.
        int players = int.Parse(Console.ReadLine());
#pragma warning restore CS8604 // Possible null reference argument.
        if(players>10){
           Console.WriteLine("Cannot play with that many players.");
        }
        else
            winner(deck,players);
      }
    }
}
