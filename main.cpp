#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <sstream> 
#include <algorithm>
#include "definitions.h"
#include <vector>

using namespace std;

int main(int argc, char** argv){
  
  // Initialisation

	int fileNo = 0;
	while(fileNo < 100)
	{
		string inputFile = "input/input" + to_string(fileNo) + ".txt"; //argv[1]; 
		string outputFile = "output/output" + to_string(fileNo) + ".txt"; //argv[2]; 
//	const char* inputFile = argv[1];
//	const char* outputFile = argv[2];
	
	string word = "";
	int counter = 0;
	int point = 0;
	int wordCounter = 0;
	int maxFileLength = 200;
	Word *textWord[maxFileLength];
	vector<Word> w;
	vector<string> wString;
  
  
  
  // Read the input
  string inputString = readInput(inputFile);


  istringstream iss(inputString);
  
  do 
	{
		string subs;
		iss >> subs;
		
		textWord[wordCounter] = new Word(subs,counter,point);
		
		wordCounter++;
	} 
	while (iss);
  
	for (int i=0; i < wordCounter; i++) 
		{
	
				w.push_back(Word(textWord[i] -> getWord(), textWord[i] -> getCounter(), textWord[i] -> getPoint()));   		//push Words into a vector that contains each Word and their attributes
				wString.push_back((textWord[i] -> getWord()));																//push the string associated to each word into a vector
				for(int j = 0; j < w.size(); j++)
				{
					int c = 0;
					if(textWord[i] -> getWord() == w[j].getWord())																//check if string matches that of a word stored in the vector
					{
						c++;										// = 1 minimum
					}
					w[j].setCounterPP(c);
				}
	
		}
			

	
	string sw = shortestWord(w).getWord();
	string lw = longestWord(w).getWord();
	string lp = lowestPoints(w);
	string hp = highestPoints(w);
	string lf = leastFrequent(w);
	string hf = mostFrequent(w);
	string sName = studentName(w);
	int key = calculateKey(w);
	string secret = findSecret(w);
	string dSecret = caesarDecipher(secret, key);
	string mw = middleWord(w);
	string output;
	

	vector<string> countS;
	for(int i = 0; i < w.size(); i++)
	{
		countS.push_back(to_string(w[i].getCounter()) + w[i].getWord());
	} 
	sort(countS.begin(), countS.end());
	
  // Task 1:
  // 1st criterion
	if(criterion1(w))
	{
		output += "pass,";
	}
	else
	{
		output += "fail,";
	}
//  // 2nd criterion
	if(criterion2(w))
	{
		output += "pass,";
	}
	else
	{
		output += "fail,";
	}
  // 3rd criterion
	if(criterion3(w))
	{
		output += "pass,";
	}
	else
	{
		output += "fail,";
	}
  // 4th criterion
	if(criterion4(w))
	{
		output += "pass,";
	}
	else
	{
		output += "fail,";
	}
  // 5th criterion
	if(criterion5(w))
	{
		output += "pass,";
	}
	else
	{
		output += "fail,";
	}
  // 6th criterion
	if(criterion6(w))
	{
		output += "pass";
	}
	else
	{
		output += "fail";
	}
	
	
  // Add the seperator
	output += ";";
  // Task 2:
	
  // Shortest and longest
	output += sw + ",";
	output += lw + ",";
  // Lowest point and highest point
	output += lp + ",";
	output += hp + ",";
  // Less frequent and most frequent
	output += lf + ",";
	output += hf;
  // Add the seperator
	output += ";";

  // Task 3: 
  // Number of appearance for each word
  	for(int i = 0; i < countS.size(); i++)
  	{
  		output += countS[i] + ",";
	}

  // Add the seperator
	output += ";";

  // Task 4:
  // Student name, key and the secret
	output += sName + ",";
	output += to_string(key) + ",";
	output += secret + ",";
	output += dSecret;

  // Add the seperator
	output += ";";
	
  // Task 5:
  // The one in the middle
	output += mw;
	
  // Write input in the file
	writeOutput(output, outputFile);
	cout << output << endl;
	cout << fileNo << endl << endl;
	fileNo++;
}
  return 0;
}
