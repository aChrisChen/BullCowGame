//
//  main.cpp
//  BullCowGame
//
//  Created by 陈吉鹏 on 12/28/18.
//  Copyright © 2018 Chris. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

void Printintro ();
FString GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;


int32 main(int32 argc, const char * argv[]) {
    bool bPlayAgain = false;
    do {
        Printintro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while(bPlayAgain);
    
    return 0;
}

void Printintro () {
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
    return;
}

FString GetValidGuess() {
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FString Guess = "";
    do {
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " out of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a Isogram (a word without repeating letters).\n\n";
                break;
            default:
                break;
        }
        std::cout << std::endl;
    } while (Status != EGuessStatus::OK);
    return Guess;
}

void PlayGame() {
    BCGame.Reset();
    
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
        FString Guess = GetValidGuess(); //TODO make loop checking valid
        
        // submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        // print32 number of bulls and cows
        
        std::cout << "Bulls = " << BullCowCount.Bulls <<"; Cows = " << BullCowCount.Cows << ".\n\n";
        std::cout << std::endl;
        if (BCGame.IsGameWon()) {
            PrintGameSummary();
            std::cout << "Do you want to play again?(y/n)\n";
        }
    }
    std::cout << std::endl;
    
    return;
}

bool AskToPlayAgain() {
    FString answer = "";
    std::getline(std::cin, answer);
    return (answer[0] == 'y') || (answer[0] == 'Y');
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "Well done! You win!\n";
    } else {
        std::cout << "Better luck next time.\n";
    }
}
