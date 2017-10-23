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
void readWord(string &word1, string &word2, string &word3, string &word4, string &word5, string &word6, string &word7, string &word8);
int extractWord(string sentence, int &index, string &output, int &runCount);
int sentenceTokenize(string sentence);
int MatchandReplace();
void writeSentence(string Sentence, string fileName);
int matchWord(int &startPos, int &endPos);
string editSentence(string newWord, string sentence, int startPos, int endPos);
string punctuationPurge(string sentence);

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

//This function reads the words from words.txt into the program.
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

//This function reads in an arbitrary character sequence in from sentences.txt, stopping only when the delimiter is reached.
//Delimiters are selected by their ASCII value; this is typically called as 46 to break on period input.
string readSentence(int &startPos,int delimiter)
{
	string sentence;
	static int charCount;
	string fileName;
	char c;
	ifstream sentenceText;
	sentenceText.open("sentences.txt");
	if(sentenceText.fail())
	{
		cout<<"Sentence File could not be opened for reading. Please try again and check your filename.\n";
	}
	else
	{
		sentenceText.seekg(startPos, sentenceText.beg);
		while(sentenceText.get(c)&&c!=delimiter)
		{
			if(c>13)
			{
				sentence += c;
				charCount++;
			}
			else
			{
				sentence +=' ';
				charCount++;
			}
			cout<<"1 \n";
		}
		sentence+=char(delimiter);
		charCount++;
		cout <<sentence<<"\n";
		cout <<charCount<<"\n";
		startPos=startPos+charCount;
	}
	sentenceText.close();
	return sentence;
}


int extractWord(string sentence,int &index, string &output, int &runCount)
{
	string extractedWord;
	for(index; index<sentence.length(); index++)
	{
		if(sentence[index]!=' '/*&& sentence[index]!='\t'&&sentence[index]!='\n'*/)
		{
			output += sentence[index];
		}
		else
		{
			return index;
		}
		cout<<index<<"\n";
	}
	runCount++;
	return index;
}


//This function returns the number of words in a sentence passed to it.
int sentenceTokenize(string sentence)
{ 
	int index;
	string word;
	int wordNum=0;
	int j=0;
	int k=0;
	while(index <sentence.length())
	{
		cout<<sentence.length()<<"\n";
		k= extractWord(sentence, index, word, wordNum);
		index+=k;
		cout<<index<<" "<<sentence.length()<<"\n";
		cout<<word<<"\n";
		word="";
		j++;
		cout<<"2 \n";
	}
	return j;
}

//This function takes in a sentence and a filename, and appends the sentence to the named file.
void writeSentence(string sentence, string filename)
{
	ofstream outputFile;
	outputFile.open(filename.c_str(),ios::app);
	//This if block check whether the first character in the sentence is lowercase, and recasts it as uppercase
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


int periodCount()
{
	char c;
	int periodCount=0;
	ifstream sentenceText;
	sentenceText.open("sentences.txt");
	if(sentenceText.fail())
	{
		cout<<"File open failed.\n";
	}
	else
	{
		while(sentenceText.get(c))
		{
			if(c==46)
			{
				periodCount++;
			}
			cout<<"3 \n";
		}
	}
	return periodCount;
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

string punctuationPurge(string sentence)
{
	string purgedSentence;
	for(int k=0; k<sentence.length(); k++)
	{
		if((sentence[k]>64&&sentence[k]<91)||(sentence[k]>96&&sentence[k]<123)||sentence[k]==32)
		{
			purgedSentence += sentence[k];
		}
	}
	return purgedSentence;
}


int MatchandReplace()
{
	string sentence;
	string wordtoFind;
	string word;
	ifstream sentenceText;
	int sentenceStart = 0;
	int wordStart = 0;
	int wordNum = 0;
	int endPos = 0;
	int startPos=0;
	int newStartPos = 0;
	int matchLog=0;
	int delimiter=46;
	int charCount=0;
	int periodCt=0;
	char c;
	string word1;
	string word2;
	string word3;
	string word4;
	string word5;
	string word6;
	string word7;
	string word8;
	string moddedSentence;
	string purgedSentence;
	string tempString;
	
	readWord(word1,word2,word3,word4,word5,word6,word7,word8);
	
	sentenceText.open("sentences.txt");
	if(sentenceText.fail()==true)
	{
		cout<<"File open failed. Please try another filename.\n";
		return 1;
	}
	else
	{
		periodCt = periodCount();
		cout<<periodCt<<"\n";
		
		for(int j=0;j<periodCt;j++)
		{
			cout<<j<<"\n";
			sentence = readSentence(startPos, 46);
			string purgedSentence = punctuationPurge(sentence);
		
			int q=0;
			int b=0; 	
	
			b=sentenceTokenize(sentence);
			moddedSentence = sentence;
		
			for(int i=0;i<=b;i++)
			{
				for(int k=endPos; k<sentence.length();k++)
				{		
					extractWord(purgedSentence, k, word, wordNum);
			
					cout<<word<<" "<<k<<" "<<" "<<wordNum<<" "<<"\n";
					int j = checkWord(word1, word);
					q++;
					if(j == 0)
					{
						cout<<word<<"\n";
						newStartPos = k-word.length();
						endPos = k;
						cout<<word2<<" "<<newStartPos<<" "<<endPos<<" "<<"\n";
						moddedSentence = editSentence(word2, moddedSentence, newStartPos, endPos);
						cout<<moddedSentence<<"\n";
						matchLog++;
						cout<<i<<"\n";
						
					}	
					word="";
				}
			}	
			if(matchLog !=0)
			{
				writeSentence(sentence, "match.txt");
				writeSentence(moddedSentence,"replace.txt");
			}
			
		}
	}
}


