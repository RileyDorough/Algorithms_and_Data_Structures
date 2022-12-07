// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Implementation of SelfOrderedListADT using the move-to-front heruistics
// Written collaborativly by Chandler Whitley and James Dorough
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#include "SelfOrderedListADT.h"
#include "llist.h"

template <typename E>
class MTF_SOL : public SelfOrderedListADT<E> {
private:
	LList<E> * OrderedList;		// List to store items, self-organized by specified heruistic
	int compares;				// Number of compares that is used for this list

public:
	//Default constructor/destructor
	// Initializes the linked list
	MTF_SOL() { OrderedList = new LList<E>(); }
	~MTF_SOL() { delete OrderedList; }
	
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//Look for 'it'.  If found return true and execute the self-ordering
	//heuristic used for ordering the list: count, move-to-front, or transpose.
	//Increments the compare instance variable every time it compares 'it' to
	//other members of the list. Returns true if 'it' is found.
	bool find(const E& it)
	{
		bool result = false;
		int position = 0;		// position of it

		// Start at the beginning of the list
		OrderedList->moveToStart();

		// Sequentially search for the value
		for (int i = 0; i < size(); i++)
		{
			compares++;
			// Check the list to find if the value already exists
			if (OrderedList->getValue() == it)
			{
				position = i;
				result = true;

				// Increment frequency
				OrderedList->setfrequency(OrderedList->getfrequency() + 1);

				break;
			}
			OrderedList->next();
		}

		if (!result)
		{
			add(it);
			position = (size() - 1);
		}

		// Call reorder for self-organization
		reorder(position);
		return result;
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//Called by find if 'it' is not in the list. Adds the new 'it' to the list
	//Can also be called independently when initially loading the list with
	//unique values and when you want to load the list in the order 'it' is 
	//read without your re-order method being called (or the number of compares
	//being incremented.
	void add(const E& it)				//Add new 'it' to the list
	{
		OrderedList->append(it, 0);
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int getCompares() const				//Returns the number of accumulated compares
	{
		return compares;
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int size() const					//Returns the size of the list
	{
		return OrderedList->length();
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//Print the list
	//In order print of the list.  printlist() prints the entire list
	//whereas printlist(n) prints n nodes.
	void printlist()
	{
		OrderedList->moveToStart();
		for (int i = 0; i < size(); i++)
		{
			std::cout << OrderedList->getValue() << "-" << OrderedList->getfrequency() << " ";
			OrderedList->next();
		}
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	void printlist(int n)
	{
		OrderedList->moveToStart();
		for (int i = 0; i < n; i++)
		{
			std::cout << OrderedList->getValue() << "-" << OrderedList->getfrequency() << " ";
			OrderedList->next();
		}
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Reorder function that implements the count self-ordereing list heruistic
	// variable pos is the position of the element that was changed
	void reorder(int pos)
	{
		// Start at the position of the item that was just found or added
		OrderedList->moveToPos(pos);

		if (OrderedList->currPos() != 0)
		{
			// Copy values of the accessed node
			int tempf = OrderedList->getfrequency();
			E tempval = OrderedList->getValue();
			OrderedList->remove(); // Remove the item from the list

			// Place item at the beginning
			OrderedList->moveToStart();
			OrderedList->insert(tempval, tempf);

		}
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
};
