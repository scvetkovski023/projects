using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

string choicePlayer;
int randomInt;

bool play = true;

while (play)
{

    int scorePlayer = 0;
    int scorePC = 0;

    while (scorePlayer < 2 && scorePC < 2)
    {

        Console.Write("Game is played to 2.\n");
        Console.Write("Choose between ROCK, PAPER and SCISSORS:    ");
#pragma warning disable CS8600 // Converting null literal or possible null value to non-nullable type.
        choicePlayer = Console.ReadLine();
#pragma warning restore CS8600 // Converting null literal or possible null value to non-nullable type.
#pragma warning disable CS8602 // Dereference of a possibly null reference.
        choicePlayer = choicePlayer.ToUpper();
#pragma warning restore CS8602 // Dereference of a possibly null reference.

        Random rnd = new Random();

        randomInt = rnd.Next(1, 4);

        switch (randomInt)
        {
            case 1:
                Console.WriteLine("Computer chose ROCK");
                if (choicePlayer == "ROCK")
                {
                    Console.WriteLine("Draw.\n");
                }
                else if (choicePlayer == "PAPER")
                {
                    Console.WriteLine("Player wins.\n");
                    scorePlayer++;
                }
                else if (choicePlayer == "SCISSORS")
                {
                    Console.WriteLine("Computer wins.\n");
                    scorePC++;
                }
                break;
            case 2:
                Console.WriteLine("Computer chose PAPER");
                if (choicePlayer == "PAPER")
                {
                    Console.WriteLine("Draw.\n");
                }
                else if (choicePlayer == "ROCK")
                {
                    Console.WriteLine("Computer wins.\n");
                    scorePC++;
                }
                else if (choicePlayer == "SCISSORS")
                {
                    Console.WriteLine("Player wins.\n");
                    scorePlayer++;
                }
                break;
            case 3:
                Console.WriteLine("Computer chose SCISSORS");
                if (choicePlayer == "SCISSORS")
                {
                    Console.WriteLine("Draw.\n");
                }
                else if (choicePlayer == "ROCK")
                {
                    Console.WriteLine("Player wins.\n");
                    scorePlayer++;
                }
                else if (choicePlayer == "PAPER")
                {
                    Console.WriteLine("Computer wins.\n");
                    scorePC++;
                }
                break;
            default:
                Console.WriteLine("Invalid entry!");
                break;
        }

        Console.WriteLine("\n\nSCORES:\tPLAYER:\t{0}\tCPU:\t{1}", scorePlayer, scorePC);

    }

    if (scorePlayer == 2)
    {
        Console.WriteLine("Player WON!");
    }
    else if (scorePC == 2)
    {
        Console.WriteLine("Computer WON!");
    }
    else
    {

    }

    Console.WriteLine("Do you want to play again?(Y/N)");
#pragma warning disable CS8600 // Converting null literal or possible null value to non-nullable type.
    string loop = Console.ReadLine();
#pragma warning restore CS8600 // Converting null literal or possible null value to non-nullable type.
    if (loop == "Y")
    {
        play = true;
        Console.Clear();
    }
    else if (loop == "N")
    {
        play = false;
    }
    else{
        Console.WriteLine("Invalid input.\n");
    }

}
