// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Driver for the three self-ogranized lists
// Written collaborativly by Chandler Whitley and James Dorough
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <string>
#include <fstream>
#include "Count_SOL.h"
#include "MTF_SOL.h"
#include "Transpose_SOL.h"
using namespace std;

int main()
{
	
	cout << "PROJ-4 James Riley Dorough\n";
	
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	cout << "\nFirst Test!!!\n\n";
	// First Test: Uses the add, find, and printlist, getcompares, and size functions of the three self-0rganizing lists
	// Part 1 - Count
	Count_SOL<char> myCSOL;
	myCSOL.add('A');
	myCSOL.add('B');
	myCSOL.add('C');
	myCSOL.add('D');
	myCSOL.add('E');
	myCSOL.add('F');
	myCSOL.add('G');
	myCSOL.add('H');

	// Print out the beginning list . . . before calling finds
	cout << "Starting List: " << endl;
	myCSOL.printlist();

	myCSOL.find('F');
	myCSOL.find('D');
	myCSOL.find('F');
	myCSOL.find('G');
	myCSOL.find('E');
	myCSOL.find('G');
	myCSOL.find('F');
	myCSOL.find('A');
	myCSOL.find('D');
	myCSOL.find('F');
	myCSOL.find('G');
	myCSOL.find('E');
	myCSOL.find('H');
	myCSOL.find('I');
	cout << "\n\nCount Heuristic: " << endl;
	cout << "Number of compares: " << myCSOL.getCompares() << endl;
	cout << "Final list structure with frequencies: " << endl;
	myCSOL.printlist();
	cout << "\nMy list size: " << myCSOL.size() << endl;

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Part 2 - Move to front
	MTF_SOL<char> myMTF;
	myMTF.add('A');
	myMTF.add('B');
	myMTF.add('C');
	myMTF.add('D');
	myMTF.add('E');
	myMTF.add('F');
	myMTF.add('G');
	myMTF.add('H');

	myMTF.find('F');
	myMTF.find('D');
	myMTF.find('F');
	myMTF.find('G');
	myMTF.find('E');
	myMTF.find('G');
	myMTF.find('F');
	myMTF.find('A');
	myMTF.find('D');
	myMTF.find('F');
	myMTF.find('G');
	myMTF.find('E');
	myMTF.find('H');
	myMTF.find('I');
	cout << "\n\nCount Heuristic: " << endl;
	cout << "Number of compares: " << myMTF.getCompares() << endl;
	cout << "Final list structure with frequencies: " << endl;
	myMTF.printlist();
	cout << "\nMy list size: " << myMTF.size() << endl;

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Part 3 - Transpose
	Transpose_SOL<char> myTSOL;
	myTSOL.add('A');
	myTSOL.add('B');
	myTSOL.add('C');
	myTSOL.add('D');
	myTSOL.add('E');
	myTSOL.add('F');
	myTSOL.add('G');
	myTSOL.add('H');

	myTSOL.find('F');
	myTSOL.find('D');
	myTSOL.find('F');
	myTSOL.find('G');
	myTSOL.find('E');
	myTSOL.find('G');
	myTSOL.find('F');
	myTSOL.find('A');
	myTSOL.find('D');
	myTSOL.find('F');
	myTSOL.find('G');
	myTSOL.find('E');
	myTSOL.find('H');
	myTSOL.find('I');
	cout << "\n\nCount Heuristic: " << endl;
	cout << "Number of compares: " << myTSOL.getCompares() << endl;
	cout << "Final list structure with frequencies: " << endl;
	myTSOL.printlist();
	cout << "\nMy list size: " << myTSOL.size() << endl;
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Second test: uses a text file as input and the self-organizing lists handle finding each word
	// Part 1 - Count
	cout << endl << "Second Test!!!" << endl;
	ifstream input_file; // Input file
	input_file.open("test.txt");
	if (!input_file)
		cout << "file failed to load\n";

	
	Count_SOL<string> sCSOL;
	string some_string; // input string

	while (input_file >> some_string)
	{
		sCSOL.find(some_string);
	}
	cout << "\n\nCount Heuristic: " << endl;
	cout << "Total number of words: " << sCSOL.size() << endl;
	cout << "Total number of compares: " << sCSOL.getCompares() << endl;
	cout << "Final list structure with frequencies: " << endl;
	sCSOL.printlist(10);
	cout << endl;

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Part 2 - Move to front
	ifstream input_file2; // Input file
	input_file2.open("test.txt");
	if (!input_file2)
		cout << "file failed to load\n";
	MTF_SOL<string> sMTF;
	string string2;
	
	while (input_file2 >> string2)
	{
		sMTF.find(string2);
	}
	cout << "\nMove to front Heuristic: " << endl;
	cout << "Total number of words: " << sMTF.size() << endl;
	cout << "Total number of compares: " << sMTF.getCompares() << endl;
	cout << "Final list structure with frequencies: " << endl;
	sMTF.printlist(10);
	cout << endl;

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Part 3 - Transpose
	ifstream input_file3; // Input file
	input_file3.open("test.txt");
	if (!input_file3)
		cout << "file failed to load\n";
	Transpose_SOL<string> sTranspose;
	string string3;

	while (input_file3 >> string3)
	{
		sTranspose.find(string3);
	}
	cout << "\n\nTranspose Heuristic: " << endl;
	cout << "Total number of words: " << sTranspose.size() << endl;
	cout << "Total number of compares: " << sTranspose.getCompares() << endl;
	cout << "Final list structure with frequencies: " << endl;
	sTranspose.printlist(10);
	cout << endl;
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++v

	system("pause");
	return 0;
}