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
void MatchandReplace();
void allWords();

int main()
{
	MatchandReplace();
}

//This function compares two words that are passed to it; returning 0 if they are the same and 1 otherwise.
int checkWord(string toBeFound,string toBeChecked)
{		
	int wordFlag = 0;
	//This if block prevents words returning as equal if one word is a substring of the other.
	if(toBeFound.length()!=toBeChecked.length())
	{	
		cout <<"The words are not the same.\n";
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
		cout <<"The words are the same.\n";
		return 0;
	}
	else
	{
		cout <<"The words are not the same.\n";
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
		cout<<"Sentence File could not be opened for reading. Please try again and check your filename.\n";
	}
	else
	{
		sentenceText.seekg(sentenceStart, sentenceText.beg);
		while(sentenceText.get(c)&&c!=delimiter)
		{
			if(c>13||c==39)
			{
				sentence += c;
				charCount++;
			}
			else
			{
				sentence +=' ';
				charCount++;
			}
		}
		sentence+=char(delimiter);
		charCount++;
		cout <<sentence<<"\n";
		cout <<charCount<<"\n";
		sentenceEnd=sentenceStart +charCount;
		cout<<sentenceEnd<<"\n";
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
	while(sentence[index]!=32&&sentence[index]>14)
	{
		extractedWord +=sentence[index];
		index++;
		charCount++;
	}
	wordEnd=wordStart+charCount;
	cout<<wordEnd<<"\n";
	output =extractedWord;
	cout<<extractedWord<<"\n";
	wordNum++;
	return index;
}

//This function reads the words from words.txt into the program.
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

string editSentence(string newWord, string sentence, int startPos, int endPos)
{
	string finalSentence;
	for(int iter = 0; iter <startPos-1;iter++)
	{
		finalSentence+=sentence[iter];
	};
	finalSentence += " ";
	finalSentence += newWord;
	finalSentence += " ";
	for(int iter = endPos; iter<sentence.length(); iter++)
	{
		finalSentence+=sentence[iter];
	}
	return finalSentence;
}

void writeSentence(string sentence, const char* filename)
{
	ofstream outputFile;
	outputFile.open(filename,ios::app);
	//This if block checks whether the first character in the sentence is lowercase, and recasts it as uppercase
	if(96<sentence[0]&&sentence[0]<123) 
	{
		sentence[0]-=32;
	}
	outputFile << sentence;
	outputFile << "\n";
	outputFile.close();
}

/*This function takes in a starting and ending position by reference, so that it can tell the replacement function
where to cut and paste to swap the first word in "words.txt" for the second word.
*/
int matchWord(string wordtoFind, string wordtoAdd, string sentence, int &startPos, int &endPos, int &wordNum)
{
	cout<<sentence<<"\n";
	string word;
	int index = 0;
	int matchFlag=0;
	int wordFlag = 0;
	int wordStart = 0;
	int wordEnd = 0;
	int j = 59049; //Random huge number used for debugging in DDD; this works on the assu
	string Sentence = sentence;
	string purgedSentence;
	string moddedSentence=sentence;
	purgedSentence = punctuationPurge(sentence);
	cout<<sentence<<" q "<<purgedSentence<<"\n";	
	while(wordEnd<purgedSentence.length())
	{		
		extractWord(purgedSentence, word, wordStart, wordEnd, wordNum);
		
		cout<<word<<" "<<wordNum<<" "<<" "<<matchFlag<<"\n";
		j = checkWord(wordtoFind, word);
		if(j==0)
		{
			moddedSentence=editSentence(wordtoAdd, moddedSentence, wordStart, wordEnd);
			matchFlag++;
		}	
		word ="";
		wordStart=wordEnd+1;

	}
	cout<<j<<" "<<matchFlag<<"\n";
	cout <<wordNum<<"  Sentence processed, thanks!\n";
	if(matchFlag == 0)
	{
		cout<<"No matches.\n";
	}
	else
	{
		cout<<(matchFlag)<<" matches in sentence.\n";
		cout<<sentence<<"\n";
		writeSentence(Sentence, MATCH);
		writeSentence(moddedSentence,REPLACE);
	}
	wordNum=0;
	return matchFlag;
}

int matchAllWords(string wordtoFind, string sentence, int &startPos, int &endPos, int &wordNum)
{
	string word;
	int index = 0;
	int matchFlag=0;
	int wordFlag = 0;
	int wordStart = 0;
	int wordEnd = 0;
	int j = 59049; //Random huge number used for debugging in DDD
	string purgedSentence;
	string moddedSentence=sentence;
	purgedSentence = punctuationPurge(sentence);	
	while(wordEnd<purgedSentence.length())
	{		
		extractWord(purgedSentence, word, wordStart, wordEnd, wordNum);
		
		cout<<word<<" "<<wordNum<<" "<<" "<<matchFlag<<"\n";
		j = checkWord(wordtoFind, word);
		if(j==0)
		{
			matchFlag++;
			return matchFlag;
		}	
		word ="";
		wordStart=wordEnd+1;
		break;

	}
	return matchFlag;
}

void MatchandReplace()
{
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
	readWord(word1,word2,word3,word4,word5,word6,word7,word8);
	
	while(!sentenceText.eof())
	{
		string sentence =readSentence(sentenceStart, sentenceEnd, sentenceText, 46);
		string purgedSentence=punctuationPurge(sentence);
		matchWord(word1, word2, purgedSentence, wordStart, wordEnd, wordNum);
		matchFlag = 0;
		sentenceStart=sentenceEnd+1;		
	}
	sentenceStart = 0;
	sentenceEnd = 0;
	wordStart=0;
	wordEnd=0;
	charCount = 0;
	comparisonFlag=1;
	matchFlag = 0;
	matchFlagAll = 0;
	wordNum = 0;
	while(!sentenceText.eof())
	{
		cout<<"running.\n";
		string sentence =readSentence(sentenceStart, sentenceEnd, sentenceText, 46);
		string purgedSentence=punctuationPurge(sentence);
		matchFlagAll+=matchAllWords(word1, purgedSentence, wordStart, wordEnd, wordNum);
		matchFlagAll+=matchAllWords(word2, purgedSentence, wordStart, wordEnd, wordNum);
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
		if(matchFlagAll==8)
		{
			writeSentence(sentence, ALLWORDS);
		}
		else
		{
			cout<<"Sentence not going in allWords.\n";
		}
		matchFlagAll = 0;
		sentenceStart=sentenceEnd+1;	
	}
}


