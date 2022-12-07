//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Driver for doubly threaded BST
// This assignment was complete by Chandler Whitley and James Dorough
// This driver shows the use of BST.h which creates a doubly threaded binary tree
// Sources used:
// provided link about doubly threaded binary trees: https://algorithms.tutorialhorizon.com/double-threaded-binary-tree-complete-implementation/
// The Textbook and class slides
//---------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "BST.h"

using namespace std;

int main()
{
	cout << "Programming Assignment 2 - Chandler Whitley" << endl << endl;

	// Create a BST and fill it using the insert function which calls inserthelp()
	BST<int, string> * myBST = new BST<int, string>();
	myBST->insert(77, "seventy-seven");
	myBST->insert(70, "seventy");
	myBST->insert(75, "seventy-five");
	myBST->insert(66, "sixty-six");
	myBST->insert(79, "seventy-nine");
	myBST->insert(68, "sixty-eight");
	myBST->insert(67, "sixty-seven");
	myBST->insert(69, "sixty-nine");
	myBST->insert(90, "ninety");
	myBST->insert(85, "eighty-five");
	myBST->insert(83, "eighty-three");
	myBST->insert(87, "eighty-seven");
	myBST->insert(65, "sixty-five");
	
	// Display the size
	cout << "The size of the BST is: " << myBST->size();

	// Demonstrate the print out which calls printhelp()
	cout << "Print demonstration" << endl;
	myBST->print();

	// Demonstrate the inorder traversal by calling printInoder()
	cout << endl << "Inorder demonstration" << endl;
	myBST->printInorder();
	cout << endl << endl;

	// Demonstrate the reverse inorder traversal by calling printReverse()
	cout << endl << "Reverse Inorder demonstration" << endl;
	myBST->printReverse();
	cout << endl << endl;

	system("pause");
	return 0;
}