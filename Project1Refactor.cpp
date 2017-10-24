/*
Author: Adam Rodriguez
Class: CSCI 135
Instructor: Professor Gilbert Pajela
This program implements Project 1.
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//These five global constants are used for initializing streams.
const char* WORDS = "words.txt";
const char* SENTENCES = "sentences.txt";
const char* MATCH = "match.txt";
const char* REPLACE = "replace.txt";
const char* ALLWORDS = "allwords.txt";

int checkWord(string toBeFound, string toBeChecked);
string readSentence( int &sentenceStart, int &sentenceEnd, ifstream &sentenceText, int delimiter);
string punctuationPurge(string sentence);
int extractWord(string sentence, string &output, int &wordStart, int&wordEnd, int &wordNum);
void readWord(string &word1, string &word2, string &word3, string &word4, string &word5, string &word6, string &word7, string &word8);
string editSentence(string newWord, string sentence, int startPos, int endPos);
void writeSentence(string sentence, const char* filename);
int matchWord(string wordtoFind, string wordtoAdd, string sentence, int &startPos, int &endPos, int &wordNum);
int matchAllWords(string wordtoFind, string sentence, int &startPos, int &endPos, int &wordNum);
void Match_Replace_allWords();
void allWords();

int main()
{
	Match_Replace_allWords();
}

//This function compares two words that are passed to it; returning 0 if they are the same and 1 otherwise.
int checkWord(string toBeFound,string toBeChecked)
{		
	int wordFlag = 0;
	//This if block prevents words returning as equal if one word is a substring of the other.
	if(toBeFound.length()!=toBeChecked.length())
	{	
		wordFlag++;
		return 1;
	}
	else
	{
		/*This for loop iterates through the characters of the two words, checking for equality. If the characters are not equal
		then the loop uses additional conditions to check for a case mismatch, and logs the characters as equal if they are
		equivalent but of different cases.*/
		
		for(int i=0; i<toBeFound.length(); i++)
		{
			if(toBeFound[i]!=toBeChecked[i]&&toBeChecked[i]!=10)
			{
				if(toBeFound[i]>64&&toBeFound[i]<91&&toBeFound[i]!=toBeChecked[i]-32)
				{
					wordFlag++;
				}
				else if(toBeFound[i]>96&&toBeFound[i]<123&&toBeFound[i]!=toBeChecked[i]+32)
				{
					wordFlag++;
				}
			}
		}
	}
	if(wordFlag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//This function takes in a starting location, an ifstream, and an ASCII table value. 
//It reads from the start of the file to the first character matching the value it is passed.
//It then returns the sentence in a string and writes the file end location to sentenceEnd.
string readSentence(int &sentenceStart, int &sentenceEnd, ifstream &sentenceText, int delimiter)
{
	string sentence;
	int charCount=0;
	char c;
	sentenceText.open(SENTENCES);
	if(sentenceText.fail())
	{
		cout<<"Sentence File could not be opened for reading. Please try again and check your filename.\n"; //Error message output if the file doesn't open.
	}
	else
	{
		sentenceText.seekg(sentenceStart, sentenceText.beg); //File pointer offset, so the function can keep track of where it is in the file as it reads.
		while(sentenceText.get(c)&&c!=delimiter)
		{
			if(c>13||c==39||(c>32&&c<64)) //Excludes whitespace, specifically includes punctuation;
			{
				sentence += c;
				charCount++;
			}
			else //Converts non-space whitespace characters
			{
				sentence +=' ';
				charCount++;
			}
		}
		sentence+=char(delimiter);
		charCount++;
		sentenceEnd=sentenceStart +charCount;
	}
	sentenceText.close();
	return sentence;
}


//This function purges non-alphanumeric characters from the sentence, and converts all whitespace characters to spaces.
string punctuationPurge(string sentence)
{
	string purgedSentence;
	for(int k=0; k<sentence.length(); k++)
	{
		if((sentence[k]>64&&sentence[k]<91)||(sentence[k]>96&&sentence[k]<123)||(sentence[k]>47&&sentence[k]>58)||sentence[k]==39)
		{
			purgedSentence += sentence[k];
		}
		else if(sentence[k]<<14||sentence[k]==32)
		{
			purgedSentence +=' ';
		}
	}
	return purgedSentence;
}

//This function reads through a provided sentence, and returns the first word beginning at wordStart.
//It remembers where it left off with the value written to wordEnd;
int extractWord(string sentence, string &output, int &wordStart, int&wordEnd, int &wordNum)
{
	int charCount=0;
	int index=wordStart;
	string extractedWord;
	while(sentence[index]!=32&&sentence[index]>14) //This loop runs until a space or a special whitespace character is encountered.
	{
		extractedWord +=sentence[index];
		index++;
		charCount++;
	}
	wordEnd=wordStart+charCount;
	output =extractedWord;
	wordNum++;
	return wordNum;
}

//This function reads the words from words.txt into the program. It can be this simple because we have a hard upper bound of eight words to read in. 
//All words are passed by reference because we are not allowed to build a vector of words.
void readWord(string &word1, string &word2, string &word3, string &word4, string &word5, string &word6, string &word7, string &word8)
{
	ifstream wordList;
	wordList.open(WORDS);
	if(wordList.fail())
	{
		cout<<"File could not be opened for reading. Please try again and check your filename.\n";
	}
	else
	{
		wordList >> word1 >> word2 >> word3 >> word4 >> word5 >> word6 >> word7 >> word8;
	}
	wordList.close();
}

//This function edits a sentence passed into by removing the chars with indices between startPos and endPos, inclusive and swapping newWord into the gap.
string editSentence(string newWord, string sentence, int startPos, int endPos)
{
	string finalSentence;
	//This for loop copies characters from sentence into the final sentence until startPos is reached.
	for(int iter = 0; iter <startPos-1;iter++)
	{
		finalSentence+=sentence[iter];
	}
	
	//These three lines add newWord into the sentence.
	finalSentence += " ";
	finalSentence += newWord;
	finalSentence += " ";
	
	//This for loop copies characters from endPos onward to the end of sentence into finalSentence.
	for(int iter = endPos; iter<sentence.length(); iter++)
	{
		finalSentence+=sentence[iter];
	}
	return finalSentence;
}

void writeSentence(string sentence, const char* filename)
{
	ofstream outputFile;
	outputFile.open(filename, ios::app);
	//This if block checks whether the first character in the sentence is lowercase, and recasts it as uppercase.
	if(96<sentence[0]&&sentence[0]<123) 
	{
		sentence[0]-=32;
	}
	//These lines write the sentence into the file.
	outputFile << sentence;
	outputFile << "\n";
	outputFile.close();
}

/*This function takes in a starting and ending position by reference, so that it can tell the replacement function
where to cut and paste to swap the first word in "words.txt" for the second word.
*/
int matchWord(string wordtoFind, string wordtoAdd, string sentence, int &startPos, int &endPos, int &wordNum)
{
	string word;
	int index = 0;
	int matchFlag=0;
	int wordFlag = 0;
	int wordStart = 0;
	int wordEnd = 0;
	int j = 59049; //Random huge number used for debugging in DDD; this makes it easy to spot bugs if j isn't initialized properly.
	string Sentence = sentence;
	string purgedSentence;
	string moddedSentence=sentence;
	purgedSentence = punctuationPurge(sentence);
	
	//This while loop calls the extractWord function until extractWord runs out of words in the sentence.
	while(wordEnd<purgedSentence.length())
	{		
		extractWord(purgedSentence, word, wordStart, wordEnd, wordNum);
		
		j = checkWord(wordtoFind, word);	//Checks the newly extracted word against the word we're looking for. If found, j returns zero.
		if(j==0)
		{
			moddedSentence=editSentence(wordtoAdd, moddedSentence, wordStart, wordEnd); //Edits a copy of the sentence to include the second word in words in lieu of the first.
			matchFlag++;
		}	
		word ="";
		wordStart=wordEnd+1;

	}

	if(matchFlag == 0)
	{

	}
	//This else block writes the sentence out to match and replace if there are matches found.
	else
	{
		writeSentence(Sentence, MATCH);
		writeSentence(moddedSentence,REPLACE);
	}
	return matchFlag;
}


//This function is basically a modified version of matchWord above, with the replace functionality stripped out.
int matchAllWords(string wordtoFind, string sentence, int &startPos, int &endPos, int &wordNum)
{
	string word;
	int index = 0;
	int matchFlag=0;
	int wordFlag = 0;
	int wordStart = 0;
	int wordEnd = 0;
	int j = 59049; //Random huge number used for debugging in DDD; I set this high so that if j was not initialized correctly it would be obvious.
	string purgedSentence;
	string moddedSentence=sentence;
	purgedSentence = punctuationPurge(sentence);	
	while(wordEnd<purgedSentence.length()) //This is the same while loop as in matchWord.
	{		
		wordNum=extractWord(purgedSentence, word, wordStart, wordEnd, wordNum);
		
		j = checkWord(wordtoFind, word);
		if(j==0)
		{
			matchFlag++;
			return matchFlag;
		}	
		word ="";
		wordStart=wordEnd+1; //Advances the beginning character by the word length
	}
	return matchFlag; //This value is returned because the allwords part of the project uses it to determine whether all words are found.
}

//This function sequentially executes all of the steps in the project, beginning with match and replace and concluding with allwords.
void Match_Replace_allWords()
{
	//variables are initialized here.
	ifstream sentenceText;
	int sentenceStart = 0;
	int sentenceEnd = 0;
	int wordStart=0;
	int wordEnd=0;
	int charCount = 0;
	int comparisonFlag=1;
	int matchFlag = 0;
	int matchFlagAll = 0;
	int wordNum = 0;
	int maxLength = 0;
	int secondLength = 0;
	int allWordsCount = 0;
	int goodSentenceNum = 0;

	string word;
	string wordToFind;
	string word1;
	string word2;
	string word3;
	string word4;
	string word5;
	string word6;
	string word7;
	string word8;
	
	readWord(word1,word2,word3,word4,word5,word6,word7,word8); //Read in the words.
	
	while(!sentenceText.eof()) //This while loop works through the entire sentence file.
	{
		string sentence =readSentence(sentenceStart, sentenceEnd, sentenceText, 46);
		string purgedSentence=punctuationPurge(sentence);
		matchFlag+= matchWord(word1, word2, purgedSentence, wordStart, wordEnd, wordNum);
		wordNum -= 1;
		if(matchFlag!=0)
		{
			goodSentenceNum++;    //Counter of how many sentences with at least one hit have been found.
			if(wordNum>maxLength)
			{
				maxLength=wordNum;
			}
			else if(wordNum>secondLength)
			{
				secondLength = wordNum;
			}
		}
		wordNum=0;
		matchFlag=0;
		sentenceStart=sentenceEnd+1;		//Advances the read position of the file by the length of the sentence.
	}
	sentenceText.close();		//closes the filestream out.
	cout<<goodSentenceNum<<" sentences that match the first word saved in file match.\n";
	cout<<"The longest sentence matching the first word has "<<maxLength<<" words, and the second longest has "<<secondLength<<" words.\n";
	
	//This reinitializes all the relevant variables to their zero values to take a second pass through the file.
	sentenceStart = 0;
	sentenceEnd = 0;
	wordStart=0;
	wordEnd=0;
	charCount = 0;
	comparisonFlag=1;
	matchFlag = 0;
	matchFlagAll = 0;	
	wordNum = 0;
	
	sentenceText.open(SENTENCES);  //Reopens the filestream
	
	//The while loop below loops through all of the sentences in the stream, testing them against all eight words.
		
	while(!sentenceText.eof())
	{
		string sentence =readSentence(sentenceStart, sentenceEnd, sentenceText, 46);
		string purgedSentence=punctuationPurge(sentence);
		matchFlagAll+=matchAllWords(word1, purgedSentence, wordStart, wordEnd, wordNum);
		matchFlagAll+=matchAllWords(word2, purgedSentence, wordStart, wordEnd, wordNum);
		
		//Since the input file may have as few as two words, this section checks whether all eight words exist.
		//It also ensures that sentences are not spuriously failed from allwords testing if there are only six words.
		
		if(word3 =="")
		{
			matchFlagAll++;
		}	
		else
		{
			matchFlagAll+=matchAllWords(word3, purgedSentence, wordStart, wordEnd, wordNum);
		}
		if(word4 =="")
		{
			matchFlagAll++;
		}	
		else
		{
			matchFlagAll+=matchAllWords(word4, purgedSentence, wordStart, wordEnd, wordNum);
		}
		if(word5 =="")
		{
			matchFlagAll++;
		}	
		else
		{
			matchFlagAll+=matchAllWords(word5, purgedSentence, wordStart, wordEnd, wordNum);
		}
		if(word6 =="")
		{
			matchFlagAll++;
		}	
		else
		{
			matchFlagAll+=matchAllWords(word6, purgedSentence, wordStart, wordEnd, wordNum);
		}
		if(word7 =="")
		{
			matchFlagAll++;
		}	
		else
		{
			matchFlagAll+=matchAllWords(word7, purgedSentence, wordStart, wordEnd, wordNum);
		}
		if(word8 =="")
		{
			matchFlagAll++;
		}	
		else
		{
			matchFlagAll+=matchAllWords(word8, purgedSentence, wordStart, wordEnd, wordNum);
		}
		//This checks to see if the sentence in question is flagged as containing all available words.
		if(matchFlagAll==8)
		{
			writeSentence(sentence, ALLWORDS);
			allWordsCount++; //count used for final cout.
		}
		matchFlagAll = 0;
		sentenceStart=sentenceEnd+1;	//Advances through the file by a sentence.
	}
	cout<<allWordsCount<<" sentences that match every word saved in file allwords.\n";
}


