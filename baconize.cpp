/*
Author: Ruze

Date: 10/21/22

Description: The code will take an input file containing either English (or BACON code)
and translate it to BACON code (or English) and ouput it into another file.

Usage: <exe> <input file> <-bc|-e> <output file> [-v]
*/

#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

const char* englishToBaconCode(char);
char baconCodeToEnglish (const char*);
const char* lowerCaseBC (const char*);
void translateToBacon(int,char**);
void translateToEnglish(int,char**);

int main(int argc, char** argv)
{
  //Checking for proper usage
  if(argc < 4 || argc > 5)   //There needs to be 4 or 5 command line items 
  {
    printf("Error -- usage: <exe> <input file> <-bc|-e> <output file> [-v]\n");
    return 0;
  }
  else
  {
    if(strcmp(argv[2],"-bc") != 0 && strcmp(argv[2],"-e") != 0) //if any other inputs other than -bc or -e are selected it will error
    {
        printf("Error -- usage: <exe> <input file> <-bc|-e> <output file> [-v]\n");
	      return 0;
    }
    if(argc == 5 && strcmp(argv[4],"-v") != 0) //if there are 5 command line items, then 5th must be -v
    {
      printf("Error -- usage: <exe> <input file> <-bc|-e> <output file> [-v]\n");
      return 0;
    }
  } //End of checking for proper usage

  if(strcmp(argv[2],"-bc") == 0) //Translating from English to BACON code
    translateToBacon(argc, argv);
  else if(strcmp(argv[2], "-e") == 0) //Translating from BACON code to English
    translateToEnglish(argc, argv);

  printf("\n\n%s file completed.\n",argv[3]);
  return 0; 
} //End of main

//Translate from English to BACON code and output into a file
void translateToBacon(int argc, char** argv) 
{
  ifstream inFile;
  ofstream outFile;
  inFile.open(argv[1]);  //Opens the input file 
  outFile.open(argv[3]); //Creates the output file
  const int SIZE = 256;  //Line max is 255 characters plus the '\0' character for C-style strings
  char line[SIZE];
  printf("Translating %s to BACON code\n",argv[1]);

  while (!inFile.eof())  //Will loop until it reaches the end of the input file
  {
      inFile.getline(line, SIZE); //Gets a line from the input file
      if (inFile.fail() && !inFile.eof()) //If a line exceeds the char limit it will error
      {
	      printf("\nError -- Length of a line translating from English to BACON Code must be 1 - %d characters long\n",SIZE-1);
	      printf("The lines (if there were any) before the line that caused the error have been translated into BACON code.\n");
	      return;
      }

      for(long unsigned int i = 0; i < strlen(line); i++) //Loop through the line and convert english into BACON by calling englishToBaconCode
      {                                                   //and passing the line into it and then outputing the result into the output file
	 if (i == (strlen(line) - 1) )                     
	   outFile << englishToBaconCode(line[i]) << endl; //This makes sure the sentence structure is the same in the input file
	 else                                              
	   outFile << englishToBaconCode(line[i]) << "|";
      }

      if(argc == 5 && strcmp(argv[4],"-v") == 0) //OPTIONAL: Will output what was read and written if -v is used
      {
        if(strcmp(line,"") != 0)
        {
          cout << "\nREAD:: " << line;
          cout << "\nWROTE:: ";
        }
        for(long unsigned int i = 0; i < strlen(line); i++) 
        {                                            
	   if (i == (strlen(line) - 1) )                     
	     cout << englishToBaconCode(line[i]);
	   else                                              
	     cout << englishToBaconCode(line[i]) << "|";
        }
      }

  } //End of while loop that reads file
  inFile.close();
  outFile.close();
} //End of translateToBacon method

//Translate from BACON code to English and output into a file
void translateToEnglish(int argc, char** argv)
{
  ifstream inFile;
  ofstream outFile;
  inFile.open(argv[1]);  //Opens the input file 
  outFile.open(argv[3]); //Creates the output file
  const int SIZE = 1601; //Line max is 1600 characters plus the '\0' character for C-style strings
  char line[SIZE];
  printf("Translating %s to English\n",argv[1]);

  while (!inFile.eof())  //Will loop it reaches the end of the file
  {
     inFile.getline(line, SIZE); //Gets a line from input file
     if (inFile.fail() && !inFile.eof()) //If a line exceeds the char limit it will error
     {
        printf("\nError -- Length of a line translating from BACON Code to English must be 1 - %d characters long\n",SIZE-1);
	      printf("The lines (if there were any) before the line that caused the error have been translated into English.\n");
        return;
     }

    if(argc == 5 && strcmp(argv[4],"-v") == 0) //OPTIONAL: Will output what was read if -v is used
    {
       if(strcmp(line,"") != 0)
       {
          cout << "\nREAD:: " << line;
          cout << "\nWROTE:: ";
       }
    }
    char* token;
    token = strtok(line, "|\n\r"); //Will tokenize the current line by delimiting on | and \n
    while(token != NULL)         //Loop that will continue to tokenize until it reaches NULL aka the end of the line
    {
       outFile << baconCodeToEnglish(token); //Call baconCodeToEnglish on that token and translate it into english and output it
	    
       if(argc == 5 && strcmp(argv[4],"-v") == 0) //OPTIONAL: Will output what was written if -v is used
          cout << baconCodeToEnglish(token);

       token = strtok(NULL, "|\n");
     }
     outFile << endl; //This endl makes sure the sentence structure is the same as input file

  } //End of while loop that reads file
  inFile.close();
  outFile.close();
} //End of translatingToEnglish method
  
const char* englishToBaconCode(char letter)
{
  const char* code;
  if(int(letter) >= 65 && int(letter) <= 90) //Finds the ASCII value of letter and if it's between 65 and 90 it's between A-Z
     letter += 32;                           //adding 32 to letter will convert the uppercase letter to it's lowercase form.

  switch(letter) //Switch statement that will match the letter to it's corresponding BACON code
  {
    case 'a': code = "aaaaa";
      break;
    case 'b': code = "aaaab";
      break;
    case 'c': code = "aaaba";
      break;
    case 'd': code = "aaabb";
      break;
    case 'e': code = "aabaa";
      break;
    case 'f': code = "aabab";
      break;
    case 'g': code = "aabba";
      break;
    case 'h': code = "aabbb";
      break;
    case 'i': code = "abaaa";
      break;
    case 'j': code = "abaab";
      break;
    case 'k': code = "ababa";
      break;
    case 'l': code = "ababb";
      break;
    case 'm': code = "abbaa";
      break;
    case 'n': code = "abbab";
      break;
    case 'o': code = "abbba";
      break;
    case 'p': code = "abbbb";
      break;
    case 'q': code = "baaaa";
      break;
    case 'r': code = "baaab";
      break;
    case 's': code = "baaba";
      break;
    case 't': code = "baabb";
      break;
    case 'u': code = "babaa";
      break;
    case 'v': code = "babab";
      break;
    case 'w': code = "babba";
      break;
    case 'x': code = "babbb";
      break;
    case 'y': code = "bbaaa";
      break;
    case 'z': code = "bbaab";
      break;
    case ' ': code = "/";
      break;
    default: code = "!!!!!";
  }
  return code;
} //End of englishToBaconCode method

char baconCodeToEnglish(const char* code)
{
  char letter;
  
  //If else chain that compares the BACON code passed by using strcmp and returning the corresponding letter
  if(strcmp(code, "aaaaa") == 0)   
    letter = 'A';
  else if(strcmp(code, "aaaab") == 0)
    letter = 'B';
  else if(strcmp(code, "aaaba") == 0)
    letter = 'C';
  else if(strcmp(code, "aaabb") == 0)
    letter = 'D';
  else if(strcmp(code, "aabaa") == 0)
    letter = 'E';
  else if(strcmp(code, "aabab") == 0)
    letter = 'F';
  else if(strcmp(code, "aabba") == 0)
    letter = 'G';
  else if(strcmp(code, "aabbb") == 0)
    letter = 'H';
  else if(strcmp(code, "abaaa") == 0)
    letter = 'I';
  else if(strcmp(code, "abaab") == 0)
    letter = 'J';
  else if(strcmp(code, "ababa") == 0)
    letter = 'K';
  else if(strcmp(code, "ababb") == 0)
    letter = 'L';
  else if(strcmp(code, "abbaa") == 0)
    letter = 'M';
  else if(strcmp(code, "abbab") == 0)
    letter = 'N';
  else if(strcmp(code, "abbba") == 0)
    letter = 'O';
  else if(strcmp(code, "abbbb") == 0)
    letter = 'P';
  else if(strcmp(code, "baaaa") == 0)
    letter = 'Q';
  else if(strcmp(code, "baaab") == 0)
    letter = 'R';
  else if(strcmp(code, "baaba") == 0)
    letter = 'S';
  else if(strcmp(code, "baabb") == 0)
    letter = 'T';
  else if(strcmp(code, "babaa") == 0)
    letter = 'U';
  else if(strcmp(code, "babab") == 0)
    letter = 'V';
  else if(strcmp(code, "babba") == 0)
    letter = 'W';
  else if(strcmp(code, "babbb") == 0)
    letter = 'X';
  else if(strcmp(code, "bbaaa") == 0)
    letter = 'Y';
  else if(strcmp(code, "bbaab") == 0)
    letter = 'Z';
  else if(strcmp(code, "/") == 0)
    letter = ' ';
  else if(strcmp(code, "!!!!!") == 0)
    letter = '#';
  else
    letter = '%';
  return letter;
} //End of baconCodeToEnglish method
