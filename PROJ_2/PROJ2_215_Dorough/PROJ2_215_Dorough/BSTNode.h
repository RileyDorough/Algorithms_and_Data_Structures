//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include for access to the complete binary node
// template implementation
//
//
// Modified to be used by double-threaded binary trees for Lab 2
// Used provided file about bitfields to understand their implementation
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
	Key k;                  // The node's key
	E it;                   // The node's value
	BSTNode* lc;            // Pointer to left child
	BSTNode* rc;            // Pointer to right child
	// The left and right flags are implemented with Bit fields.
	bool leftf : 1;			// Set to 1 if this node points to a cild or 0 if it point to its inorder successor
	bool rightf : 1;		// Set to same values as left_flag depending on where the right pointer points
	int level;				// This is the level of the node in the BST

public:
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Two constructors -- with and without initial values
	// First constructer sets all pointer to NULL, flags to 0, and level to 0
	BSTNode() { lc = rc = NULL; set_left_flag(0); set_right_flag(0); setlevel(0); }

	// Second constructer sets flags and level to false / 0 respectivly if no arguments are passed in
	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL, bool thisleftflag = 0, bool thisrightflag = 0, int somelevel = 0)
	{
		k = K; it = e; lc = l; rc = r;
		level = somelevel;

		// When initiating a new node, its flags will alwyas be o
		set_left_flag(thisleftflag);
		set_right_flag(thisrightflag);
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	~BSTNode() { delete lc; delete rc; }    // Destructor deletes pointers
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Functions to set and return the value and key
	E& element() { return it; }
	void setElement(const E& e) { it = e; }
	Key& key() { return k; }
	void setKey(const Key& K) { k = K; }
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Functions to set and return the children
	inline BSTNode* left() const { return lc; }
	void setLeft(BinNode<E>* b) { lc = (BSTNode*)b; }
	inline BSTNode* right() const { return rc; }
	void setRight(BinNode<E>* b) { rc = (BSTNode*)b; }
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Functions to set and get the flags
	// Added functions for threaded binary tree
	bool left_flag() {return leftf;}
	void set_left_flag(bool lf) {leftf = lf;}
	bool right_flag() { return rightf; }
	void set_right_flag(bool rf) { rightf = rf; }
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Set and get function for level variable
	int getlevel() { return level; }
	void setlevel(int l) { level = l; }
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// Note this function is meaningless for this implementation because it can no longer be used to test if a node is a leaf to the threads
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Return true if it is a leaf, false otherwise
	bool isLeaf() { return (lc == NULL) && (rc == NULL); }
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
};
#endif