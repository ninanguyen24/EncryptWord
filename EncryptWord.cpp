// Author: Nina Nguyen
// Filename: EncryptWord.cpp
// Date: (10/18/2017 version 3) (10/9/2017 version 2) (9/30/2017 version 1)
// Version: 3


/*
Data stucture used: Array to iterate through alphabet
Ultility Function: srand and rand used to generate shift key
Dependencies: Relies on client program to validate legal inputs
Design: the String "word" must remain unchanged for the state to hold true. 
		Copies will be made for the encryption. transform() used to alter requested word to all lower case.
Error response: queryShift(int) will return true or false if shift key equal or invalid integer is passed. 
				Uses lowGuess, highGuess, averageValue, and numOfGuesses to generate stats. Defensive programming is 
				used in queryShift() just for safety precaution.
Modification: 
Assumptions: array used to declare ALPHABET and const int ALPHABET_INDEX should not change. Field averageValue
and numOfGuesses drives the average value of guesses and will only calculate if numOfGuess > 0. Errors are handled
by the client. Stat() is dependent on queryShift(). decode() can only be called in an on state. reset() will be called
when object is initialize, reset can be toggled by the user after the encryption. getShiftValue() is for testing purposes
only, should not be used by client.
*/

#include "EncryptWord.h"
#include "stdlib.h" // srand, rand
#include "time.h" //time
#include<string>
#include <iostream> //cout and cin
#include <cctype> //transform
#include <algorithm> //transfrom
using namespace std;

const int EncryptWord::ALPHABET_INDEX = 26;

const string EncryptWord::ALPHABET = { "abcdefghijklmnopqrstuvwxyz" };


EncryptWord::EncryptWord() {
	reset();
}

string EncryptWord::startEncrypt(string wordToLower) {//change word to lower case
	std::transform(wordToLower.begin(), wordToLower.end(), wordToLower.begin(), ::tolower);
	return wordToLower;
}

string EncryptWord::shift(string wordToShift) { //doing the actual shift

	srand(time(NULL));
	shiftValue = rand() % 26 + 1; // should generate a number between 1 to 26

	word = wordToShift;
	string temp = startEncrypt(wordToShift); //shift word to lowercase
	for (unsigned int i = 0; i <= temp.size(); i++) {
		for (int j = 0; j < ALPHABET_INDEX; j++) {
			if (temp[i] == ALPHABET[j]) {
				temp[i] = ALPHABET[(j + shiftValue) % 26]; //the actual encrypting
				break;//need it to break "if" loop after finding match
			}
		}
	}
	state = true;
	return temp;
}

bool EncryptWord::queryShift(int guess) {
	//if guess does not equal the random number used to shift the alphabet, return false
	if (guess == -1) { //doesn't increase number of guesses
		cout << "Thank you for playing." << endl;
		return true;
	}
	if (highGuess == 0 && lowGuess == 0) { //set initial highGuess and lowGuess value to first guess value
		highGuess = guess;
		lowGuess = guess;
	}

	if (guess == shiftValue) {
		cout << "You guessed the shift key!" << endl;
		if (highGuess < guess) {
			highGuess = guess;
		}
		else if (lowGuess > guess) {
			lowGuess = guess;
		}
		averageValue += guess;
		numOfGuesses++;
		return true;
	}
	else  {//(guess != shiftValue)
		if (highGuess < guess) {
			highGuess = guess;
		}
		else if (lowGuess > guess) {
			lowGuess = guess;
		}
		averageValue += guess;
		numOfGuesses++;
		return false;
	}
}

void EncryptWord::stat() {
	if(numOfGuesses != 0) {
		cout << "Correct shift key is: " << shiftValue << endl;
		cout << "Highest guess is: " << highGuess << endl;
		cout << "Lowest guess is: " << lowGuess << endl;
		cout << "Average shift value guess rounded is: " << averageValue / numOfGuesses << endl;
	}
}

//For testing purposes only
int EncryptWord::getShiftValue() const {
	return shiftValue;
}


string EncryptWord::decode() {
	state = false;
	return word;
}

void EncryptWord::reset() {
	word = "";
	lowGuess = 0;
	highGuess = 0;
	averageValue = 0;
	numOfGuesses = 0;
	shiftValue = 0;
	state = false;
}

bool EncryptWord::isOn()
{
	return state;
}
