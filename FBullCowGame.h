/*
The game logic (No code viewed or direct user interaction)
The game is a simple guess the word game based Bulls and Cows (the board game)
*/

#pragma once
#include <string>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Word,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
	public:
		FBullCowGame(); //constructor

		//getters
		int32 GetMaxTries() const;
		int32 GetCurrentTry() const;
		int32 GetHiddenWordLength() const;
		bool IsGameWon() const;
		
		EGuessStatus CheckGuessValidity(FString) const;

		void Reset();
		FString SetHiddenWordThirdLetter();
		FBullCowCount SubmitValidGuess(FString);

	private:
		//see constructor for initialisation
		int32 MyCurrentTry;
		FString MyHiddenWord;
		FString MyHiddenWordThirdLetter;
		bool bGameIsWon;

		bool IsIsogram(FString) const;
		bool IsLowercase(FString) const;
		bool IsWord(FString) const;
};