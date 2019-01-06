//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by 陈吉鹏 on 12/29/18.
//  Copyright © 2018 Chris. All rights reserved.
//

#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame(){
    Reset();
}

void FBullCowGame::Reset() {
    
    MyCurrentTry = 1;
    
    const FString HIDDEN_WORD = "plan";
    MyHiddenWord = HIDDEN_WORD;
    
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    } else if (!IsLowercase(Guess)) {
        return EGuessStatus::Not_Lowercase;
    } else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    } else {
        return EGuessStatus::OK;
    }
}






int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return int32(MyHiddenWord.length()); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const{
    TMap<int32, int32> WordLengthToMaxTries {{3,4}, {4,5}, {5,6}, {6,8}};
    return WordLengthToMaxTries[int(MyHiddenWord.length())];
}

//receive a VALID guess, increments
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    // increment the turn number
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    
    // loop through all letters in the guess
    for (int32 i = 0; i < MyHiddenWord.length(); i++){
        // compare letters against the hidden word
        for (int32 j = 0; j < MyHiddenWord.length(); j++) {
            // if they match
            if (MyHiddenWord[i] == Guess[j]){
                if (i == j) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }

        }
    }
    if (BullCowCount.Bulls == GetHiddenWordLength()) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    if (Word.length() <= 1) return true;
    
    TMap<char, bool> LetterSeen;
    // auto means that the compiler decides the type for us
    for (auto Letter : Word) {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
    for (auto Letter : Word) {
        if (!islower(Letter)) {return false;}
    }
    return true;
}




