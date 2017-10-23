/*
Author: Adam Rodriguez
Class: CSCI 136
Instructor: Professor Gilbert Pajela
This program outputs a rectangle comprised of asterisks based on the user's given width and height inputs.
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int checkWord(string toBeFound,string toBeChecked);
string readSentence(int &startPos, int delimiter);
int ioTest();
void readWord(string &word1, string &word2, string &word3, string &word4, string &word5, string &word6, string &word7, string &word8);
int extractWord(string sentence, int &index, string &output, int &runCount);
void wordExtractionTest();
void sentenceTokenize();
void fullOperation();
void writeSentence(string Sentence, string fileName);
int matchWord(int &startPos, int &endPos);
string editSentence(string newWord, string sentence, int startPos, int endPos);
string readAllWords();
string punctuationPurge(string sentence);

int main()
{
	fullOperation();
}

int checkWord(string toBeFound,string toBeChecked)
{
	int wordFlag = 0;
	
	if(toBeFound.length()!=toBeChecked.length())
	{	
		cout <<"The words are not the same.\n";
		wordFlag++;
		return 1;
	}
	else
	{
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

void readWord(string &word1, string &word2, string &word3, string &word4, string &word5, string &word6, string &word7, string &word8)
{
	ifstream wordList;
	wordList.open("words.txt");
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

string readSentence(int &startPos,int delimiter)
{
	ifstream sentenceText;
	string sentence;
	static int charCount;
	string fileName;
	char c;
	
	sentenceText.open("sentences.txt");
	if(sentenceText.fail())
	{
		cout<<"File could not be opened for reading. Please try again and check your filename.\n";
	}
	else
	{
		sentenceText.seekg(startPos);
		while(sentenceText.get(c),c!=delimiter)
		{
			sentence += c;
			charCount++;
		}
		
		cout <<sentence<<"\n";
		cout <<charCount<<"\n";
		startPos=startPos+charCount;
	}
	return sentence;
}


int extractWord(string sentence,int &index, string &output, int &runCount)
{
	string extractedWord;
	for(index; index<sentence.length(); index++)
	{
		if(sentence[index]!=' '&& sentence[index]!='\t')
		{
			output += sentence[index];
		}
		else
		{
			return index;
		}
	}
	runCount++;
	return index;
}

void wordExtractionTest()
{
	string sentence;
	string word;
	int index = 0;
	int wordNum=0;
	cout <<"Please input the sentence you want me to pull words from.\n";
	getline(cin, sentence);
	for(int k=0; k<sentence.length();k++)
	{		
		index += extractWord(sentence, k, word, wordNum);
		
		cout<<word<<" "<<k<<" "<<"\n";
		word ="";
	}
	cout <<"Sentence processed, thanks!\n";
}


void sentenceTokenize()
{ 
	string sentence;
	string word;
	int index = 0;
	int wordNum=0;
	cout <<"Please input the sentence you want me to pull words from.\n";
	getline(cin, sentence);
	while(index <sentence.length())
	{
		index += extractWord(sentence, index, word, wordNum);
		cout<<word<<"\n";
	}
}

void writeSentence(string sentence, string filename)
{
	ofstream outputFile;
	outputFile.open(filename.c_str(),ios::app);
	outputFile << sentence;
	outputFile <<"."<< "\n";
	outputFile.close();
}

	
string modifySentence(string sentence, string wordToAdd, string wordtoReplace)
{
	int i;
}


/*This function takes in a starting and ending position by reference, so that it can tell the replacement function
where to cut and paste to swap the first word in "words.txt" for the second word.
*/
int matchWord(int &startPos, int &endPos)
{
	string sentence;
	string word;
	string wordtoFind;
	int index = 0;
	int matchFlag=0;
	int wordFlag = 0;
	int wordNum = 0;
	int q = 0;
	cout <<"Please input the sentence you want me to check.\n";
	getline(cin, sentence);
	string purgedSentence = punctuationPurge(sentence);
	cout<<"Please input the word you want me to look for.\n";
	cin >> wordtoFind;
	static int k;	
	for(k=0; k<purgedSentence.length();k++)
	{		
		index += extractWord(purgedSentence, k, word, wordNum);
		
		cout<<word<<" "<<k<<" "<<" "<<q<<" "<<matchFlag<<"\n";
		matchFlag += checkWord(wordtoFind, word);		
		word ="";
		q++;
	}
	cout <<"Sentence processed, thanks!\n";
	if(matchFlag == k)
	{
		cout<<"No matches.\n";
	}
	else
	{
		cout<<(q-matchFlag)<<" matches in sentence.\n";
	}
	return matchFlag;
}

int wordCount(string sentence)
{
	int wordCount=0;
	for(int iter = 0; iter<sentence.length(); iter++)
	{
		if(sentence[iter]==10||sentence.length()>0)
		{
		
		}
	}
}

						
string editSentence(string newWord, string sentence, int startPos, int endPos)
{
	string finalSentence;
	for(int iter = 0; iter <startPos;iter++)
	{
		finalSentence+=sentence[iter];
	}
	finalSentence += " ";
	finalSentence += newWord;
	for(int iter = endPos; iter<sentence.length(); iter++)
	{
		finalSentence[iter]=sentence[iter];
	}
}

string punctuationPurge(string sentence)
{
	string purgedSentence;
	for(int k=0; k<sentence.length(); k++)writes
	{
		if((sentence[k]>64&&sentence[k]<91)||(sentence[k]>96&&sentence[k]<123)||sentence[k]==32)
		{
			purgedSentence += sentence[k];
		}
	}
	return purgedSentence;
}

string readAllWords()
{
	
	string allWords;
	int j=0;
	for(int k=0; k<5000;k++)
	{
		allWords+=readSentence(j,46);
		cout<<allWords<<"\n";
	}
	cout << allWords;
}



void fullOperation()
{
	string sentence;
	string wordtoFind;
	string word;
	int sentenceStart = 0;
	int wordStart = 0;
	int wordNum = 0;
	int endPos = 0;
	int newStartPos = 0;
	string word1;
	string word2;
	string word3;
	string word4;
	string word5;
	string word6;
	string word7;
	string word8;
	sentence = readSentence(sentenceStart,46);
	string purgedSentence = punctuationPurge(sentence);
	string moddedSentence;
	readWord(word1,word2,word3,word4,word5,word6,word7,word8);
	int q=0;
	int b=0;
	while(q<purgedSentence.length())
	{
		for(int k=endPos; k<sentence.length();k++)
		{		
			extractWord(purgedSentence, k, word, wordNum);
		
			cout<<word<<" "<<k<<" "<<" "<<wordNum<<" "<<"\n";
			int j = checkWord(word1, word);
			q++;
			word="";
			if(j == 0)
			{
				newStartPos = k;
				endPos = k + wordtoFind.length();
				writeSentence(sentence, "match.txt");
				cout<<word2<<"\n";
				string moddedSentence = editSentence(word2, sentence, newStartPos, endPos);
				cout<<moddedSentence<<"\n";
				writeSentence(moddedSentence, "replace.txt");
				break;
				
			}		
		}
		break;
		sentence = readSentence(sentenceStart,46);
	}
}


