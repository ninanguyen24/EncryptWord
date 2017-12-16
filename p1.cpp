/*
// Author: Nina Nguyen
// Filename: p1.cpp
// Date: (10/18/2017 version 3) (10/9/2017 version 2) (9/30/2017 version 1)
// Version: 

/*Description and anticipated use: This program ask the user for a word and generate a random shift key to encrypt the word.
The user can choose to guess what the shift key was or not. Statistics will be generated if they chose to guess.
The user can then choose to decode (return original word), reset (clear the object and stats), encrypt a new word,
or quit the encryption program.

Data Stucture used: Vector for EncryptWord objects and Array for string comparison
Class used: Encryptword 

Assumptions: Program is used to encrypt a valid word by ultilizing the encapsulated EncryptWord class.
User input through cin should be entered as asked even with defensive programming in placed. For valid word
size of string has to be more than 4, does not include spaces or punctuations. For responses, "yes" or "no" should be
entered, case sensitive. And input integers when asked.
Public functions that are explicitly called by the driver are shift(), queryShift(), stat(), reset(), and decode()
Can have many objects added to vector, no size limit.
*/



#include "EncryptWord.h"
#include<string>
#include <iostream> //cout and cin
#include <vector> //allow vector
using namespace std;

//Prints out a short description of how the encryption program works.
void intro() {
	cout << "Welcome to the encrypter! The machine will choose a key from 1-26 to encrypt " <<
		"the word of your choice. \nPlease input a single word without spaces or punctuations " <<
		"that is at least 4 letters." << endl;
	cout << "You'll have the option to guess what the shift key was that was used to encrypt your word." << endl;
	cout << "You also have the option to reset the encryption or decode to get your original word back." << endl;
	cout << "You can encrypt as many words as you like. Let's Begin!" << endl;
	cout << endl;
}

/*validWord()************************************************************************
Input (cin): Ask user for a word to encrypt. Assuming the word is 4 letters or more with no
spaces or punctuations. Uses defensive programming to ask user for another word
if it doesn't meet requirements.
Output: return a string if word passes all requirements.
Design: Uses string methods to check for validity of word. */
string validWord() {
	string userWord;

	cout << "What word would you like to encrypt? (Close program to quit): ";
	getline(cin, userWord);
	int i = 0;

	while (userWord.size() < 4) {
		cout << "Please input a word with at least 4 characters: ";
		getline(cin, userWord);
	}

	while (userWord[i]) {
		if (ispunct(userWord[i]) || isspace(userWord[i])) {
			cout << "Please don't include punctuations or spaces. Try again: ";
			getline(cin, userWord);
			i = 0;
		}
		i++;
	}
	return userWord;
}


/*main***************************************************************************
Will initialize EncryptWord object with constructor. A valid word will call the shift function for encryption.
Main does not throw any exceptions for invalid inputs, but uses defensive program (cout and cin) 
to try and stop the program from crashing. 

User can guess the Shift Key used to encrypt, and the user input will be passed to queryShift(int)
to collect data and return that statistics at the end of the program if necessary. Program
will accept any positive integer.

Vector was used to create new EncryptWord objects and remove it after the while loop, and will
allow the user encrypt a new word by adding a new object to the vector.
*/


int main() { 
	intro();
	vector<EncryptWord> encryptWord;

	int i = 0;
	bool keepPlaying = true;
	while(keepPlaying){
		encryptWord.push_back(EncryptWord());
		string wordToEncrypt = validWord();
		//********testing, remove after
		cout << "state: " << encryptWord[i].isOn() << endl;
		cout << "The encrypted word is: ";
		cout << encryptWord[i].shift(wordToEncrypt) << endl;
		//*******testing, remove after
		cout << "state: " << encryptWord[i].isOn() << endl;
		//cout << "Shift Value: " << encryptWord[i].getShiftValue() << endl; //For testing only
		string userResponse;

		cout << "Do you you want to guess what the key value that was " <<
			"used in the shift? (Enter \"yes\" or \"no\"): ";
		cin >> userResponse;

		if (userResponse == "yes" || userResponse == "Yes") {
			if (encryptWord[i].isOn()) { //if the state is "on"
				int guessValue;
				cout << "What do you think the shift value is?" << endl;
				cout << "Hint, it's between 1-26. (input -1 to quit): ";
				while (!(cin >> guessValue) || guessValue < 0 && guessValue != -1) {//make sure the user input an integer
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a postive integer: ";
				}
				while (!encryptWord[i].queryShift(guessValue)) {
					cout << "It's wrong, please try again (input -1 to quit): ";
					cin >> guessValue;
				}
				encryptWord[i].stat();
			}
			else { //if the state is "off"
				cout << "There are no stats to report." << endl;
			}
		}
		else if (userResponse == "no" || userResponse == "No") {
			cout << "Okay, that's fine." << endl;
			encryptWord[i].stat();
		}
		else {
			cout << "Invalid response. The program will continue without guessing." << endl;
			encryptWord[i].stat();
		}

		cout << "Do you want to decode or reset?" << endl;
		cout << "Enter \"1\" for decode, \"2\" for reset or \"3\" to create a new encrypt word." << endl;
		cout << "Enter anything else to quit." << endl;
		cin >> userResponse;
		if (userResponse == "1") {
			cout << "The decode word is: " << encryptWord[i].decode() << endl;
		}
		else if (userResponse == "2") {
			cout << "Reset has been triggered." << endl;
			encryptWord[i].reset(); 
			encryptWord[i].stat();//to show that stats were also reset
		}
		else if (userResponse == "3") {
			cout << "Let's start over and create a new word." << endl;
		}
		else {
			keepPlaying = false;
		}
		i++;
		cout << endl;
	}
}


