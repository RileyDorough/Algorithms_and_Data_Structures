#ifndef LINK_H
#define	LINK_H

#include <cstdlib>

// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Singly linked list node
template <typename E> class Link {
public:
	E element;			// Value for this node
	Link *next;         // Pointer to next node in list

	int frequency;		// Added for this assignment to store the items frequency

	// Constructors - Modified to set frequency variable
	Link(const E& elemval, int f, Link* nextval = NULL)
	{
		element = elemval;  next = nextval; frequency = f;
	}
	Link(Link* nextval = NULL) { next = nextval; frequency = 0; }

};

#endif