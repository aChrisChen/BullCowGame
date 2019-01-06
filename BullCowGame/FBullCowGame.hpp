//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by 陈吉鹏 on 12/29/18.
//  Copyright © 2018 Chris. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

// all values initialized to 0
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    bool IsGameWon() const;
    int32 GetHiddenWordLength() const;
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
    
    void Reset(); // TODO Make a more rich return value.
    EGuessStatus CheckGuessValidity(FString) const; // TODO Make a more rich return value
    FBullCowCount SubmitValidGuess(FString);
    
// Please try and ignore this and focus on the int32erface above
private:
    // see constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
};

#endif /* FBullCowGame_hpp */
