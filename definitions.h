#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <sstream> 
#include <algorithm>
#include <vector>

using namespace std;



void writeOutput (string out, string fileName)
{
	ofstream file (fileName);
	file << out;
	file.close();
}

string readInput (string fileName)
{
  
	string myText;
	string text;
	
	ifstream MyReadFile(fileName);
	
	while (getline(MyReadFile,myText)) 
	{
		text = myText;
	}
		
	MyReadFile.close();
	
  	return text;
  	
}

// Definition of the struct
struct letter 
{
	char ch;     //Letter
	int points;  //Number of points per letter
	bool isVowel;  //is it of type V?

};

int calPoints(string);


// Definition of the Class 
class Word
{
	private:
		string word;
		int counter; // number of occurances of the word in the text
		int point;

	public:
		Word (string word1, int counter1, int point1) 
		{
			word = word1;
			counter = counter1;
			point = point1;
		}
		void setWord (string word1) 
		{
			word = word1;
		}
		const string getWord () const 
		{
			return word;
		}
		const int getLength () const 
		{
			return word.length();
		}
		void setCounter (int counter1) 
		{
			counter = counter1;
		}
		void setCounterPP (int x)
		{
			if(x == 1)
			{
				counter++;    //increases the counter by however many occurances there are of a word
			}
		}
		const int getCounter () const 
		{
			return counter;
		}
		void setPoint (int point1) 
		{
			point = point1;
		}
		const int getPoint () const 
		{
			return calPoints(word);
		}
		bool operator<(Word& word2)
		{
			return point < word2.point;
		}
		
};
vector<Word> w;


// Created an array of the letter struct 
letter letters [26];


//initialised letter array with the attributes of each letter (table 1)
void createTable()
{
		letters [0] = {'a', 10, 1};
		letters [1] = {'b', 21, 0}; 
		letters [2] = {'c', 7, 0};
		letters [3] = {'d', 2, 0}; 
		letters [4] = {'e', 19, 1}; 
		letters [5] = {'f', 18, 0}; 
		letters [6] = {'g', 4, 0}; 
		letters [7] = {'h', 8, 0}; 
		letters [8] = {'i', 6, 1}; 
		letters [9] = {'j', 11, 0}; 
		letters [10] = {'k', 14, 0};
		letters [11] = {'l', 3, 0};
		letters [12] = {'m', 9, 0};
		letters [13] = {'n', 22, 0};
		letters [14] = {'o', 1, 1};
		letters [15] = {'p', 23, 0};
		letters [16] = {'q', 17, 0};
		letters [17] = {'r', 5, 0};
		letters [18] = {'s', 25, 0};
		letters [19] = {'t', 13, 0};
		letters [20] = {'u', 12, 1};
		letters [21] = {'v', 26, 0};
		letters [22] = {'w', 24, 0};
		letters [23] = {'x', 16, 0};
		letters [24] = {'y', 20, 0};
		letters [25] = {'z', 15, 0};	
}

// Calculating points for a word
int calPoints (string str)
	{
		createTable();     //using create table
		int ans;
		for(int i = 0; i < str.length(); i++)    // for the length of a given string
    	{
    		for(int j = 0; j < 26; j++)			//nested for loop
    		{
    			if(str[i] == letters[j].ch)		//for each of the letters in the string find them in the table
				{
					ans += letters[j].points;	//answer = the total of the points of letters in the string 
				}
			}
		}
		return ans;
	}
	

// Calculting number of vowels in each word. 
int vCount(string str)
{
	createTable();
	int vc;
	for(int i = 0; i < str.length(); i++) 	//for the length of a given string
	{
		for(int j = 0; j < 26; j++)
		{	
			if(str[i] == letters[j].ch)		//if a letter in the string is a vowel 
			{
				vc += letters[j].isVowel;
			}
		}
	}
	return vc;
}

// Check if a word is palindrome
bool isPalindrome (string str)
	{
		for (int i = 0; i < str.length() / 2; i++)  //for half the length of the string. For strings of odd length e.g. 5 - int 2.5 = 2. The 3rd character (that isnt checked), is the same for front and back so method works in all cases.
		{
			if (str[i] != str[str.length() - i - 1]) //compare front of string with rear of string in reverse. (-1 for null value at the end of string array) 
			{
				return 0; // return 0 if front and rear dont match
				break;
			}		
		}
		return 1; // return 1 if front half = rear half reversed (palindrome)
	}

//find student name	
string studentName(vector<Word> w)
{
	Word name = w[9];      //student name is the 10th word so element 9 in the vector
	string sn = name.getWord();
	
	return sn;
}

//calculate key 
int calculateKey(vector<Word> w)
	{	
		int nameScore = w[9].getPoint();      //get the point related to student name
		int key = nameScore % 26;				// mod 26
		
		return key;							// return the answer
	}



//find the secret
string findSecret(vector<Word> w)
{
	Word s = w.back(); //finding the last word
	vector<string> fS;	//creating new vector to store the words that meet the criteria
	string secret;
	
	for(int i = 0; i < w.size(); i++)	//for each word in the Word vector
	{
		if(w[i].getPoint() >= 90 && w[i].getPoint() <= 110)		//does it meet the criteria?
		{
			fS.push_back(w[i].getWord());		//add to the new vector if they do
		}
	}
	if(fS.size() < 2)				//if there arent 2 words that meet the criteria
	{
		secret = s.getWord();		//the secret is the last word
	}
	else
	{
		secret = fS[1];    //if there are 2 words that meet the criteria, 2nd element in the vector is the secret 
	}

	return secret;
}

// Implementing Caesar cipher system (only decipher function)
string caesarDecipher(string secret, int key) 
{
	char ch;
	int i;
	string dSecret;
	for(i = 0; secret[i] != '\0'; i++) 		//for the length of the word - up to the null value at the end of the string
	{
		ch = secret[i];
		ch = ch - key;				//deciphered ch is og ch - key.
		if(ch < 'a')				// if the character is below a in the ascii table (\^ZY etc) 
		{
			ch = ch + 'z' - 'a' + 1; //loop round so a - 1 = z for example
		}
	
	secret[i] = ch;					//the new ch are now the secret 
	}
	dSecret = secret;
	return dSecret;
}


//Least frequent
string leastFrequent(vector<Word> w)
{
	Word lFrequent = w[0];
	for(int i = 0; i < w.size(); i++)
	{
		if((w[i].getCounter() < lFrequent.getCounter()) && (w[i].getLength() > 0))
		{
			lFrequent = w[i];
		}
	}
	return lFrequent.getWord();
}

//Most frequent 
string mostFrequent(vector<Word> w)
{
	Word mFrequent = w[0];
	for(int i = 0; i < w.size(); i++)
	{
		if((w[i].getCounter() > mFrequent.getCounter()) && (w[i].getLength() > 0))
		{
			mFrequent = w[i];
		}
	}
	return mFrequent.getWord();
}

//Function calculating the word with the lowest points
string lowestPoints (vector<Word> w)
{
	Word lowestP = w[0]; //lowest point is the first word in the vector
	for(int i = 0; i < w.size(); i++) 	//for each word in the vector 
	{
		if((w[i].getPoint() < lowestP.getPoint()) && (w[i].getLength() > 0)) //is it of lower points to the current lowest word in the iteration
		{
			lowestP = w[i];		//then it becomes the new lowest point
		}
	}
	return lowestP.getWord();	//after iterating through the entire vector return the lowest word
}

//function calculating the word with the highest points
string highestPoints (vector<Word> w)
{
	Word highestP = w[0];
	for(int i = 0; i < w.size(); i++)
	{
		if(w[i].getPoint() > highestP.getPoint())		//same as above but >
		{
			highestP = w[i];
		}
	}
	return highestP.getWord();
}

//function calculating the shortest word - definition for shortest word is the word with the fewest number of characters with at least 2 characters. If there are more than one of the same length it will take the first word to appear.
Word shortestWord (vector<Word> w)
{
	Word shortWord = w[0];				 
	
	for(int i = 0; i < w.size(); i++)
	{
		if(w[i].getLength() > 1)	//making sure minWord is initially set to a word > 1 character.
		{
			shortWord = w[i];
		}
	}

	for(int i = 0; i < w.size(); i++)
	{
		if((w[i].getLength() < shortWord.getLength()) && (w[i].getLength() > 1)) // //iterating through the words selecting the shortest word that is the FIRST of its length.
		{
			shortWord = w[i];
		}
	}

	return shortWord;
}

//function calculating the longest word.
Word longestWord (vector<Word> w)
{
	Word longWord = w[0];
	for(int i = 0; i < w.size(); i++)			
	{
		if(w[i].getLength() > longWord.getLength())
		{
			longWord = w[i];
		}
	}
	return longWord;
}

//sorting by points and finding the middle word
string middleWord (vector<Word> w)
{
//	w.pop_back();
	sort(w.begin(), w.end());  //sorting the Words based on the boolean oporator in its class - by points
	string mw;
	int middleValue = ((w.size() - 1) / 2);  //if the number of words is odd, the middle INDEX is the the size -1 / 2.
	int middleValue1 = (w.size() / 2);		// if the number of words is even, the 1st middle INDEX is the size / 2
	string middleWord1 = w[middleValue1].getWord();
	int middleValue2 = ((w.size() - 2) / 2);  //if the number of words is even, the 2nd middle INDEX is the size - 2 / 2
	string middleWord2 = w[middleValue2].getWord();
	
	if(w.size() % 2 == 0) 			//if the vector size is even 
	{
		mw = middleWord1 + middleWord2; 	//the middle word is the 2 middle words combined
	}
	else
	{
		mw = w[middleValue].getWord();		//if the vector size is odd 
	}
	return mw;
}

// Criterion1
bool criterion1 (vector<Word> w)
{
	Word minWord = shortestWord(w);
	
	if (minWord.getPoint() >= 10 && minWord.getPoint() <= 50) //check whether it fits the parameters
	{
		return 1;		//if so return true
	}
	else
	{
		return 0;	
	}
}

// Criterion2
bool criterion2 (vector<Word> w)

{
Word maxWord = longestWord(w);

	if (maxWord.getPoint() >= 200 && maxWord.getPoint() <= 250)
	{
		return 1;
	}
	else
	{
		return 0;	
	}
	
}

// Criterion3
bool criterion3 (vector<Word> w)
{
	int palindromeCounter = 0;
	
	for(int i = 0; i < w.size(); i++)	//for each of the words in the vector
	{
		if (isPalindrome(w[i].getWord()))	//check if palindrome 
		{
			palindromeCounter++; 		//if so ++ 
		}
	}
	if (palindromeCounter > 4)			
	{
		return 1;						//if more than 4 return true
	}
	else
	{
		return 0;
	}

}

// Criterion4
bool criterion4 (vector<Word> w)
{
	if (w.size() >= 50 && w.size() <= 100)	//if between 50 and 100 words
	{
		return 1;					//return true 
	}
	else
	{
		return 0;
	}  

}

// Criterion5
bool criterion5 (vector<Word> w)
{
	int lengthTotal;
	double lengthAvg;
	int pointTotal;
	double pointAvg;
	
	for(int i = 0; i < w.size(); i++)		//for every word in the the vector find
	{
		lengthTotal += w[i].getLength();	//total length combined
		pointTotal += w[i].getPoint();		//total points combined
	}
	
	lengthAvg = lengthTotal / w.size();		//average length
	pointAvg = pointTotal / w.size();		// average points 
	
	if(lengthAvg > 4 && lengthAvg < 8 && pointAvg > 20 && pointAvg < 60)	//if it satisfies criteria
	{
		return 1;		//return true
	}
	else
	{
		return 0;
	}	

}

// Criterion6
bool criterion6 (vector<Word> w)
{
	for(int i = 0; i < w.size(); i++)
	{
		if(vCount(w[i].getWord()) > 4)	//call to vCount function. - if more than 4 vowels 
		{
			return 0;		//return false
			break;
		}

	}
	return 1;

}

