//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
//
//
// This file includes all of the pieces of the BST dictionary implementation
// This code was modified to meet Lab 2 requirements by Chandler Whitley and James Dorough
// Modified functions: inserthelp() and printhelp()
// New functions: printInorder() and printReverse()
// New helper functions: nextInorder() and nextReverse()
// Used provided link about doubly threaded binary trees: https://algorithms.tutorialhorizon.com/double-threaded-binary-tree-complete-implementation/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"
#include <string>

#ifndef BST_H
#define BST_H

using namespace std; 

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	BSTNode<Key, E>* root;									// Root of the BST

	int nodecount;											// Number of nodes in the BST

	// Private "helper" functions
	void clearhelp(BSTNode<Key, E>*);
	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*,			// Edited to work with doubly threaded BST
		const Key&, const E&);
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
	BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
	E* findhelp(BSTNode<Key, E>*, const Key&) const;
	void printhelp(BSTNode<Key, E>*) const;					// Edited to remove level input argument
	void vist(BSTNode<Key, E>*) const;			
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	BST() { root = NULL; nodecount = 0; }  // Constructor

	//Note from Prof Sipantzi -- I've commented out the destructor
	//since you would have to change clearhelp() to make it work with
	//doubly-threaded trees and that is not part of the assignment.
	//~BST() { clearhelp(root); }            // Destructor


	void clear()   // Reinitialize tree
	{
		clearhelp(root); root = NULL; nodecount = 0;
	}

	// Insert a record into the tree.
	// k Key value of the record.
	// e The record to insert.
	void insert(const Key& k, const E& e) {
		root = inserthelp(root, k, e);
		nodecount++;
	}

	// Remove a record from the tree.
	// k Key value of record to remove.
	// Return: The record removed, or NULL if there is none.
	E* remove(const Key& k) {
		E* temp = findhelp(root, k);   // First find it
		if (temp != NULL) {
			root = removehelp(root, k);
			nodecount--;
		}
		return temp;
	}
	// Remove and return the root node from the dictionary.
	// Return: The record removed, null if tree is empty.
	E* removeAny() {  // Delete min value
		if (root != NULL) {
			E* temp = new E;
			*temp = root->element();
			root = removehelp(root, root->key());
			nodecount--;
			return temp;
		}
		else return NULL;
	}

	// Return Record with key value k, NULL if none exist.
	// k: The key value to find. */
	// Return some record matching "k".
	// Return true if such exists, false otherwise. If
	// multiple records match "k", return an arbitrary one.
	E* find(const Key& k) const { return findhelp(root, k); }

	// Return the number of records in the dictionary.
	int size() { return nodecount; }

	void print() const { // Print the contents of the BST
		if (root == NULL) cout << "The BST is empty.\n";
		else
		{
			printhelp(root);	// Edited to remove level input argument because it is now a private data mamber of the node (BSTNode)
		}
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Inorder print out without using recursion
	void printInorder() const
	{
		BSTNode<Key, E> * current;
		current = root->left();							// Set current node to the actual root which is to the left of the dummy node

		// First go to the far left
		while (current->left_flag() == 1)				// While the node points to a child go left
		{
			current = current->left();					// Move to the left
		}

		while (current != root)
		{
			std::cout << current->element() << endl;	// Print out this value
			current = nextInorder(current);				// Find next value to print out
		}
	}

	// Helper function for printInorder()
	BSTNode<Key, E> * nextInorder(BSTNode<Key, E>* somenode) const
	{
		if (somenode->right_flag() == 0)		// This means that the right pointer points to the next one that should be printed out
		{
			return somenode->right();			// If the right flag points to inorder succesor move and print it out
		}

		somenode = somenode->right();			// If current node doesn't point to inorder succesor, Means we are at the node and need to move right one.
		while (somenode->left_flag() != 0)
		{
			somenode = somenode->left();		// Ensures left is printed out before node and right
		}
		return somenode;
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Reverse of inorder traversal print out without using recursion
	void printReverse() const
	{
		BSTNode<Key, E> * current;
		current = root->left();							// Set current node to actual root which is to the left of the dummy node

		// FIrst, go all the way to the right
		while (current->right_flag() == 1)				// While the node points to a child . . .
		{
			current = current->right();					// Move to the right
		}

		while (current != root)
		{
			std::cout << current->element() << "\n";	// Print out this value
			current = nextReverse(current);				// Find next value to print out 
		}
	}

	// Helper method for printReverse()
	BSTNode<Key, E> * nextReverse(BSTNode<Key, E>* reversenode) const
	{
		if (reversenode->left_flag() == 0)			// Means left pointer of pointer node is pointing to inorder predeccesor
		{
			return reversenode->left();				// Move to what the node points to and print it out
		}

		reversenode = reversenode->left();			// Go left one and check if it should be printed next
		while (reversenode->right_flag() == 1)		// If the right flag is a 1 we need to go right more
		{
			reversenode = reversenode->right();		// Loop ends when a node is found that points to a inorder predeccesor
		}
		return reversenode;
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
};


// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
	cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Insert help function
// This function does not use recursion and creates a double threaded BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(
	BSTNode<Key, E>* root, const Key& k, const E& it) {

	BSTNode<Key, E> * thisnode = new BSTNode<Key, E>(k, it);

	// If the tree is currently empty
	if (root == NULL)
	{
		// Set root as dummy
		root = new BSTNode<Key, E>();							// Initialize root to dummy
		root->setLeft(root);									// Make left pointer point to itself to start
		root->setRight(root);									// Set the right pointer of root to itself (dummy characteristic)
		root->set_left_flag(0);									// Set the left flag to 0 (dummy characteristic)
		root->set_right_flag(1);								// Set the right flag to 1 (dummy characteristic)


		// Make the inserted node a child of the dummy
		thisnode->setLeft(root);								// Set left pointer of new node to point to dummy
		root->setLeft(thisnode);								// Make the root/dummy point to the node being inserted
		thisnode->set_left_flag(root->left_flag());				// Take the flag of the dummy node
		root->set_left_flag(1);									// Set dummy left flag to 1 signifying it points to a child
		thisnode->setRight(root);								// Make this new node's right pointer also point to dummy
		thisnode->set_right_flag(0);
		thisnode->setlevel(0);									// Establish this node at level 0
		return root;											// Set this inserted node as the root

	}

	// If the tree has at least one node already
	else
	{
		// Start at the top . . . remember root is now a dummy node so the top node is the dummy nodes left child
		BSTNode<Key, E> * current = root->left();

		while (true)
		{
			if (current->key() > thisnode->key())					// Means place to the left
			{
				if (current->left_flag() == 0)						// Meaning is a leaf . . . the node can be inserted here
				{
					// The key is less than the current
					// Add to the left subtree
					thisnode->setLeft(current->left());				// Make the node we are inserting point to the dummy note. Since current is still pointing to the dummy, we can call this line
					current->setLeft(thisnode);						// Make the current element point to the one we are inserting
					thisnode->set_left_flag(current->left_flag());	// Take the flag of the current
					current->set_left_flag(1);
					thisnode->setRight(current);					// Make the inserted node point to inorder succesor
					thisnode->set_right_flag(0);
					thisnode->setlevel(thisnode->getlevel() + 1);	// Increment level by 1
					return root;
					break;
				}
				else
				{
					current = current->left();						// If not a leaf . . . 
					thisnode->setlevel(thisnode->getlevel() + 1);	// Increment level by 1
				}
			} 
			else
			{
				// Means the node we are inserting needs to be placed in the right sub tree
				if (current->right_flag() == 0)
				{
					// This is a child node, we can insert the new node here
					thisnode->setRight(current->right());					// Make the node we are inserting point to what its parents right node used to point to
					current->setRight(thisnode);							// Make the parent point to the node we are inserting
					thisnode->set_right_flag(current->right_flag());		// Take the flag of the parent
					current->set_right_flag(1);								// Set the right flag of the parent to 1 now because it has a child
					thisnode->setLeft(current);								// Make the left pointer of what we are inserting point to inorder successor
					thisnode->set_left_flag(0);								// Set flag accordingly
					thisnode->setlevel(thisnode->getlevel() + 1);			// Increment level by 1
					return root;
					break;
				}
				else
				{
					current = current->right();								// Not a valid place to insert . . . go right more
					thisnode->setlevel(thisnode->getlevel() + 1);			// Increment level by 1
				}
			}
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL)
		return rt;
	else return getmin(rt->left());
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL) // Found min
		return rt->right();
	else {                      // Continue left
		rt->setLeft(deletemin(rt->left()));
		return rt;
	}
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
	if (rt == NULL) return NULL;    // k is not in tree
	else if (k < rt->key())
		rt->setLeft(removehelp(rt->left(), k));
	else if (k > rt->key())
		rt->setRight(removehelp(rt->right(), k));
	else {                            // Found: remove it
		BSTNode<Key, E>* temp = rt;
		if (rt->left() == NULL) {     // Only a right child
			rt = rt->right();         //  so point to right
			delete temp;
		}
		else if (rt->right() == NULL) { // Only a left child
			rt = rt->left();          //  so point to left
			delete temp;
		}
		else {                    // Both children are non-empty
			BSTNode<Key, E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
	const Key& k) const {
	if (root == NULL) return NULL;          // Empty tree
	if (k < root->key())
		return findhelp(root->left(), k);   // Check left
	else if (k > root->key())
		return findhelp(root->right(), k);  // Check right
	else {
		E* temp = new E;
		*temp = root->element();
		return temp;  // Found it
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Print out a BST showing each nodes level
// Modified to work with double threads
template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* root) const {

	BSTNode<Key, E> * current;
	current = root->left();								// Set current node to actual root which is to the left of the dummy node
	
	// First go to the far left
	while (current->left_flag() == 1)					// While it points to a child . . .
	{
		current = current->left();						// Move to the left
	}
	
	while (current != root)
	{
		for (int i = 0; i < current->getlevel(); i++)   // Indent to level
			std::cout << "   ";
		cout << current->key() << "\n";					// Print out this value
		current = nextInorder(current);					// Find next value to print out
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif