/*
This is the console exectuable that makes use of the BullCowClass.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For Game Logic, see FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function protypes as outside of a class
void PrintIntro();
bool AskIfPlayerWantsExplanation();
void PrintExplanationIfPlayerWantsIt();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game, which we re-use across plays

//entry point for application
int main () {
	std::srand(static_cast<int32>(std::time(0))); // To seed your random generator with the std::time function
	bool bPlayAgain = false;
	bool WantsExplanation = false;
	do {
		BCGame.Reset();
		//print Introduction
		PrintIntro();
		//ask if player needs explanation
		WantsExplanation = AskIfPlayerWantsExplanation();
		if (WantsExplanation == true) {
			//print an explanation of the game
			PrintExplanationIfPlayerWantsIt();
			//print the guess prompt
			PlayGame();
			//ask to play again
			bPlayAgain = AskToPlayAgain();
		}
		else {
			//print the guess prompt
			PlayGame();
			//ask to play again
			bPlayAgain = AskToPlayAgain();
		}
		system("cls");
	} while (bPlayAgain == true);

	//exit application
	std::cout << std::endl;
	return 0;
}

void PrintIntro() {
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	FText MyHiddenWordSecondLetter = BCGame.SetHiddenWordThirdLetter();
	
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << "-letter isogram that I'm thinking of?\n";
	std::cout << "The third letter of the word is " << MyHiddenWordSecondLetter << ".";
	std::cout << std::endl;
	return;
}

bool AskIfPlayerWantsExplanation() {
	std::cout << "\nEnter 'yes' for an explanation or 'no' if you wish to skip to the game. ";
	FText RequestForExplanation = "";
	std::getline(std::cin, RequestForExplanation);
	return (RequestForExplanation[0] == 'y' || RequestForExplanation[0] == 'Y' && RequestForExplanation[1] == 'e' && RequestForExplanation[2] == 's');
	std::cout << std::endl;
}

void PrintExplanationIfPlayerWantsIt() {
	std::cout << "\nAn isogram is a word without repeating letters.\n";
	std::cout << "A bull means that one of the letters in your guess is the correct letter in the\n  correct location.\n";
	std::cout << "A cow means that one of the letters in your guess is the correct letter in the\n  incorrect location.\n\n";
	return;
}

//Plays a single game to completion
void PlayGame() {
	//create a MaxTries variable
	int32 MaxTriesForPlayGame = BCGame.GetMaxTries();

	//loop for number of turns asking for guesses while game
	//is NOT won and there are remaining tries
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTriesForPlayGame) {
		FText Guess = GetValidGuess(); 


		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls =  " << BullCowCount.Bulls << "     ";
		std::cout << "Cows =  " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

//loop infinitely until the user inputs valid guess
FText GetValidGuess() { 
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTriesInGetGuess = BCGame.GetMaxTries();
		std::cout << "\nTry " << CurrentTry << "/" << MaxTriesInGetGuess << ". Enter your guess: ";
		std::getline(std::cin, Guess);



		//only submit valid guess, and receive counts
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram, a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Word:
			std::cout << "Please enter a single word without symbols or numbers.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << "-letter isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		default: //assume valid guess
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until player enters valid guess
	return Guess;
}

void PrintGameSummary() {
	bool GameWon = BCGame.IsGameWon(); //store IsGameWon in variable
	//create MaxTry and CurrentTry variables
	int32 CurrentTryInGameSummary = BCGame.GetCurrentTry() - 1;
	int32 MaxTriesInGameSummary = BCGame.GetMaxTries();
	if (GameWon == true) { //if game is won
		std::cout << "GAME WON - WELL DONE!\n";
		std::cout << "You were on Try " << CurrentTryInGameSummary << " out of " << MaxTriesInGameSummary << ".\n";
		std::cout << "Play the game again and try to get a better score.\n";
	}
	else {
		std::cout << "You ran out of tries.\n";
		std::cout << "Better luck next time.\n";
	}
	return;
}

bool AskToPlayAgain() {
	std::cout << "\nDo you want to play again with a different word? Answer Yes or No. ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << "\n\n" << std::endl;
	return (Response[0] == 'y' || Response[0] == 'Y');
}
