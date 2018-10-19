/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class.
*/
#pragma once
#include<iostream>
#include<string>
#include "FBullCowGame.h"

// making syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instatiate a new game, which we re-use across plays

int main()
{	
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain()==true);
	
	return 0;
}


void PrintIntro() 
{
	std::cout << "\n\nWelcome to the Bulls and Cows game!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	//loop for the number of turns asking for guesses
	
	while(! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess(); 	

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);


		std::cout << "Bulls= " << BullCowCount.Bulls << ". Cows= " << BullCowCount.Cows << ".\n"<< std::endl;
	}
	PrintGameSummary();

}

FText GetValidGuess()
{
	FText Guess = "";
	// get a guess from the player
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentGuessNumber = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentGuessNumber << " of " << BCGame.GetMaxTries() <<".";
		std::cout << " - What is your guess: ";
		getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating leters.\n\n";
			break;
		case EGuessStatus::Symbols_Used:
			std::cout << "Please do not use any symbols.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
				// assume the guess is valid
			break;
		}

	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you wanna play again with the same hidden word?(y/n): ";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
	
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done, you win!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
