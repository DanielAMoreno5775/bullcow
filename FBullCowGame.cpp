#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <map>
//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

//default constructor
FBullCowGame::FBullCowGame() { 
	Reset();
}

//FBullCowGame     int32 GetCurrentTry()
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
//FBullCowGame     int32 GetHiddenWordLength()
int32 FBullCowGame::GetHiddenWordLength() const {
	int32 HiddenWordLength = MyHiddenWord.length();
	return HiddenWordLength;
}
//FBullCowGame     bool IsGameWon();
bool FBullCowGame::IsGameWon() const {	return bGameIsWon;	}


//FBullCowGame     int32 GetMaxTries();
int32 FBullCowGame::GetMaxTries() const { 
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,16}, {8,18}, {9,20}, {10,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

//FBullCowGame     void Reset();
void FBullCowGame::Reset() {
	MyCurrentTry = 1;
	bGameIsWon = false;
	//hidden word must be an isogram
	std::vector<FString> hidden_word { "ale", "gap", "pan", "back", "bank", "bath", "daft", "dogs", "duck", "naive", "nasty", "neigh", "badge", "bench", "blimp", "crags", "tails", "tamed", "macro", "magic", "tapir", "micro", "zeal", "abduct", "acorns", "active", "adjust", "careful", "badger", "bakery"
		"bandit", "belfry", "blaze", "beacon", "decoy", "debt", "design", "fabric", "fables", "factor", "falcon", "flagon", "forged", "forget", "format", "code", "malice", "radio", "raid", "roads", "pigeon",
		"pacify", "machine", "magnets", "magnify", "arise", "bachelor", "bankrupt", "gamer", "games", "gears", "machinery", "manifesto", "laser", "gelatinous", "background", "image", "mage", "wizard", "magnitudes", "neighbor", "maser", "notepad", "moral", "realm", "monarch", "hailstone", "songbird", "tadpoles", "tendrils", "acolyte", "planet", "rages", "hacker", "helipad", "helicopter", "decryption" };
	int hidden_word_end = static_cast<int>(hidden_word.size()) - 1;
	MyHiddenWord = hidden_word[rand() % hidden_word_end];
	return;
}

FString FBullCowGame::SetHiddenWordThirdLetter() {
	MyHiddenWordThirdLetter = MyHiddenWord[2];
	return MyHiddenWordThirdLetter;
}


//FBullCowGame     bool CheckGuessValidity(FString);
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	int32 WordLength = MyHiddenWord.length();

	if (!IsWord(Guess)) { //if not a word
		return EGuessStatus::Not_Word; 
	}
	else if (!IsIsogram(Guess)) { //if not isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) { //if guess isn't all lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { //if guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else { //if none of the above
		return EGuessStatus::OK;
	}
}

//receives a VALID guess, increments turn and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				//increment bulls if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				//increment cows if not
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	//treat 0 to 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen; //set up map
	for (auto Letter : Word) {		//for all letters of the word
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) {	//if letter is in map 
			return false; //do Not have isogram
		}
		else {
			LetterSeen[Letter] = true; //add letter to map as seen
		}
	}
	return true; //for example when \0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true; //if lowercase
}

bool FBullCowGame::IsWord(FString Word) const
{
	for (auto Letter : Word) {
		if (isalpha(Letter)) { //if character is not a letter
			return true;
		}
	}
	return false;
}
