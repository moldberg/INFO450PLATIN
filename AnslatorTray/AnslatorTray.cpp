// AnslatorTray.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
using namespace std;

const int MAX_INPUT = 501;
const int MAX_OUTPUT = 1001;

int translateToPigLatin(char *word, char pigSentence[MAX_OUTPUT]);

int main()
{
	char answer;
	cout << "Welcome to the Igpay AtinizerLay" << endl << endl;

	do //Runs and repeats the program until the console user exits
	{
		char resultPhrase[MAX_OUTPUT] = "";
		char inputPhrase[MAX_INPUT];
		bool erroneous = true;

		cout << "Enter a word or sentence in English, then press enter:\n";
		cin.getline(inputPhrase, MAX_INPUT);
		int inLength = (int)strlen(inputPhrase);

		//Loop parses, translates, and concatenates a word to the final phrase
		for (int begin = 0; begin < inLength; begin++)
		{
			int end;
			if (inputPhrase[begin] == ' ')
				continue; //Positioning the head of the word for after a space
			erroneous = false;
			for (end = begin; end < inLength; end++)
			{
				if (inputPhrase[end] == ' ')
				{
					inputPhrase[end] = '\0'; //Setting space as the delimiter
					break;
				}
			}
			char *parsedWord = inputPhrase + begin;
			if (translateToPigLatin(parsedWord, resultPhrase) < 0) //-1=error
			{
				erroneous = true;
				break;
			}
			begin = end; //Next word begins after this word ends
		}

		//Displaying results and asking to go again
		if (erroneous)
		{
			cout << "Bad input! Remember to enunciate into the translator.";
		}
		else
		{
			cout << "\nIn Pig Latin:\n" << resultPhrase;
		}
		cout << "\n\nHow about another go then? ";
		cout << "'Y' for yes, anything else to exit: ";
		cin >> answer;
		cout << endl << endl;
		cin.ignore(MAX_INPUT, '\n');
		cin.clear();
	} while (answer == 'Y' || answer == 'y');

	return 0;
}

//Translates the word that is passed as a parameter to the function
//into Pig Latin, checks errors, and concatenates to the translation
int translateToPigLatin(char *word, char pigSentence[MAX_OUTPUT])
{
	if ((char)*word > 47 && (char)*word < 58) //Range of ASCII digits 0-9
	{
		return -1; //ERROR for a number when a word-header is expected
	}
	if ((int)strlen(word) == 0)
	{
		return -1; //ERROR for a parsing that found no non-space characters
	}

	//Translation Rules...
	bool addingAy = true;
	bool transplantingHead = true;

	//Two letter-words remain the same
	if ((int)strlen(word) == 2)
	{
		addingAy = false;
		transplantingHead = false;
	}

	//Special words remain the same
	else if (!(strcmp(word, "the") && strcmp(word, "a")
		&& strcmp(word, "and") && strcmp(word, "but") && strcmp(word, "for")
		&& strcmp(word, "nor") && strcmp(word, "yet")))
	{
		addingAy = false;
		transplantingHead = false;
	}

	//Vowel-headed words have no word-head transplant
	else if ((*word == 'a') || (*word == 'e') || (*word == 'i')
		|| (*word == 'o') || (*word == 'u'))
	{
		transplantingHead = false;
	}

	//Applying rules and concatenating translation
	if (transplantingHead)
	{
		strcat(pigSentence, ++word); //Adding letters 2-end
		*(word--) = '\0';
		strcat(pigSentence, word); //Adding letter 1
	}
	else
	{
		strcat(pigSentence, word);
	}
	if (addingAy)
	{
		strcat(pigSentence, "ay");
	}
	strcat(pigSentence, " ");

	return 0;
}