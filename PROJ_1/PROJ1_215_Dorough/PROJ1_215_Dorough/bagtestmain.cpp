/*
* File:   bagtestmain.cpp
* Author: Prof Sipantzi -- CSIS 215 -- Programming Assignment 1 -- Bag Dictionary
*
* Created on July 14, 2012, 11:45 AM
* Updated pointers to smart pointers in ABag and BDictionary on 12/14/2018
*
* Modified by Chandler Whitley and James Dorough on 29JAN20
* Lab Parteners: Chandler Whitley and James Dorough (AKA the C-team)
*
* References:
* The Textbook for the remove function
* For smart pointers: https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
* For Polymorphism: http://www.cplusplus.com/
*/


// BDictionary objects myIntStrDict and myStrIntDict was modified to be a smart pointer


#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include "ABag.h"
#include "BDictionary.h"

using namespace std;
const size_t DICTIONARY_SIZE = 10;
void wait(); //Used to pause screen output


// Tests BDictionary with int and string objects only.
int main(int argc, char** argv) 
{
	cout << "James Riley Dorough | CSIS 215 PROJ1 | Bag Dictionary" << endl << endl;

	// myIntStrDict and myStrIntDict were modified to use a smart pointer . . . the corresponding function calls were modified 
	// using -> notation instead of . notation
	// Professor Sipantzi instruted Chandler to use smart pointers here by modifying the test driver

	unique_ptr<BDictionary<int, string>> myIntStrDict = make_unique<BDictionary<int, string>>(DICTIONARY_SIZE);
	unique_ptr<BDictionary<string, int>> myStrIntDict = make_unique<BDictionary<string, int>>(DICTIONARY_SIZE);

	// myIntStrDict tests
	// INSERT: myIntStrDict
	cout << "Testing dictionary with <int, string> KV Pair\n";
	for (int i = 1; i <= DICTIONARY_SIZE; i++) {
		stringstream sn;
		sn << "Beth " << i * 10;
		myIntStrDict->insert(i * 10, sn.str());
	}
	cout << "INSERT: Size of myIntStrDict is " << myIntStrDict->size() << endl;

	// REMOVEANY: myIntStrDict
	string strData;
	if (myIntStrDict->removeAny(strData) == true) {
		cout << "REMOVEANY: My string data is " << strData << endl;
	}
	else {
		cout << "RemoveAny() failed -- dictionary is empty.\n";
	}
	cout << "Size of myIntStrDict is " << myIntStrDict->size() << "\n";

	// FIND: test for myIntStrDict.find
	int intKey = 40;
	if (myIntStrDict->find(intKey, strData) == true) {
		cout << "FIND: My data at key==" << intKey << " is: " << strData << "\n";
		cout << "Size of myIntStrDict is " << myIntStrDict->size() << "\n";
	}
	else {
		cout << "Could not find a record at " << intKey << "\n";
	}

	// REMOVE: myIntStrDict
	intKey = 60;
	if (myIntStrDict->remove(intKey, strData) == true) {
		cout << "REMOVE: Removed key " << intKey << " which was " << strData << "\n";
	}
	else {
		cout << "Could not find key " << intKey << "\n";
	}
	cout << "Size of my dictionary is " << myIntStrDict->size() << "\n";

	// CLEAR: myIntStrDict
	myIntStrDict->clear();
	cout << "CLEAR: Size of myIntStrDict is " << myIntStrDict->size() << "\n\n";

	/* end myIntStrDict tests ---------------------------------------------*/

	// myStrIntDict tests
	// INSERT: myStrIntDict
	cout << "Testing dictionary with <string, int> KV Pair\n";
	myStrIntDict->insert("Terri", 57);
	myStrIntDict->insert("Beth", 53);
	myStrIntDict->insert("Jeremy", 19);
	myStrIntDict->insert("Nathan", 17);
	myStrIntDict->insert("Zipper", 2);
	myStrIntDict->insert("Button", 1);
	myStrIntDict->insert("Kiwi", 7);
	myStrIntDict->insert("Masoala", 10);

	cout << "INSERT: Size of myStrIntDict is " << myStrIntDict->size() << endl;

	// REMOVEANY: myStrIntDict
	int intData;
	if (myStrIntDict->removeAny(intData) == true) {
		cout << "REMOVEANY: My int data is " << intData << endl;
	}
	else {
		cout << "RemoveAny() failed -- dictionary is empty.\n";
	}
	cout << "Size of myIntStrDict is " << myStrIntDict->size() << "\n";

	// FIND: myStrIntDict.find
	string strKey = "Kiwi";
	if (myStrIntDict->find(strKey, intData) == true) {
		cout << "FIND: " << strKey << "\'s age is " << intData << endl;
		cout << "Size of myStrIntDict is " << myStrIntDict->size() << "\n";
	}
	else {
		cout << "Could not find a record at " << strKey << "\n";
	}

	// REMOVE: myStrIntDict
	strKey = "Button";
	if (myStrIntDict->remove(strKey, intData) == true) {
		cout << "REMOVE: Removed key " << strKey << " which was " << intData << "\n";
	}
	else {
		cout << "Could not find key " << strKey << "\n";
	}
	cout << "Size of my dictionary is " << myStrIntDict->size() << "\n";

	// CLEAR: myStrIntDict
	myStrIntDict->clear();
	cout << "CLEAR: Size of myStrIntDict is " << myStrIntDict->size() << "\n\n";

	/* end myStrIntDict tests ---------------------------------------------*/

	/* Demonstrate any Bag functions that were not used/demonstrated in the implemention
	of your BDictionary and ABag using a Bag of KVpairs<int, string>. */

	cout << endl << endl << "\n\nCreating a test Bag to show implementation of inspectTop function\n";
	ABag<KVpair<int, string>> myBag(DICTIONARY_SIZE); //Used to test bag functions not previously demonstrated
	KVpair<int, string> KV1(1, "Michael Scott");
	KVpair<int, string> KV2(2, "Dwight Shrute");

	// Add these KVpairs to the Bag
	myBag.addItem(KV1);
	myBag.addItem(KV2);

	// Create a third KVpair to fill with the info from inspectTop
	KVpair<int, string> KV3;
	myBag.inspectTop(KV3);
	cout << "The value at the top of the Bag is: " << KV3.value() << endl;
	cout << "The size of the Bag is: " << myBag.size() << endl;

	wait();

	return 0;
}

//Used to pause the screen wherever desired
void wait()
{
	//The following if-statement checks to see how many characters are in cin's buffer
	//If the buffer has characters in it, the clear and ignore methods get rid of them.
	if (cin.rdbuf()->in_avail() > 0) //If the buffer is empty skip clear and ignore
	{
		cin.clear();
		cin.ignore(256, '\n'); //Clear the input buffer 
	}
	char ch;
	cout << "Press the Enter key to continue ... ";
	cin.get(ch);
}