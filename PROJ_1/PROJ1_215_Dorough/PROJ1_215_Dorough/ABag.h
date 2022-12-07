// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Bag implementation following the guidlines of bagADT.h
* Written by James Dorough and Chandler Whitley
* Uses an Array based Bag
* Bag ~ a stack with access to any of its elements
*/
// ---------------------------------------------------------------------------------------------------------------------------

#pragma once
#include "bagADT.h"

template <typename E>

class ABag: public Bag<E>
{
private:
	int Bagcapacity;		// Capacity of the bag
	int Bagposition;		// The current size of the bag . . . not the capacity
	E* ThisBag;				// Pointer of typename E to hold elements of the Bag

public:
	ABag() {}					// base constructor

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	ABag(size_t size)
	{
		Bagcapacity = size;		// Constructer to set the bag capacity and start position at 0
		emptyBag();				// empty bag to start with a blank slate
		ThisBag = new E[size];	// Make ThisBag point to a dynamic array of the passed in size
	} 
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	~ABag()
	{ 
		delete[] ThisBag;		// base destructor
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Insert a new item into the bag -- return false if fails and true if
	// successful
	bool addItem(const E& item)
	{
		bool result = false;

		// First ensure the bag has room left
		if (Bagposition < bagCapacity())
		{
			ThisBag[Bagposition] = item;	// Insert the item at the current position
			++Bagposition;					// Increment the position
			result = true;					//Indicate the operation sucesfully completed
		}

		return result;
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Looks for 'item' in the bag and if found updates 'item' with the 
	// bag value and returns true.  Otherwise 'item' is left unchanged
	// and the method returns false.
	bool remove(E& item)
	{
		int temp_pos;			// Variable to store the "items" position
		bool result = false;

		for (int i = (Bagposition - 1); i >= 0; --i)	// Start at the top and work down the Bag
		{
			if (ThisBag[i] == item)						// Check if the key's are equal because of how KVpair is defined
			{
				item = ThisBag[i];						// Set the passed in variable item to the value at position of the key
				temp_pos = i;
				result = true;							// Indicate the value was found
				break;									// Exit the loop
			}
		}	

		// Shift all the elements above the found item to shift down one
		// This code was used / modified from figure 4.2 in the textbook
		if (result) 
		{
			// Take all elements above the item removed (temp_pos)
			for (int j = temp_pos; j < (Bagposition - 1); j++)
			{
				ThisBag[j] = ThisBag[j + 1];			// Shift all elements down by one
			}
			Bagposition--;								// Decrement bag position by 1
		}
		
		

		return result;
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Removes the top record from the bag, puts it in returnValue, and
	// returns true if the bag is not empty.  If the bag is empty the 
	// function returns false and returnValue remains unchanged.
	bool removeTop(E& returnValue)
	{
		bool result;
		// Ensure the Bag is not empty
		if (Bagposition == 0)
		{
			result = false;
		}
		else
		{
			// Get the value off the top and decrement size by one
			returnValue = ThisBag[Bagposition-1];
			--Bagposition;
			result = true;
		}
		return result;
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Finds the record using returnValue and if the record is found updates
	// returnValue based on the contents of the bag and returns true.  If the
	// record is not found the function returns false.  Works just like remove()
	// except that the found record is not removed from the bag.
	bool find(E& returnValue) const
	{
		bool result = false;
		for(int i = (Bagposition - 1); i > 0; i--)	// Start at the top and work down the Bag
		{
			if (ThisBag[i] == returnValue)			// Check if the key's are equal not KVpair is defined to check just the key
			{
				returnValue = ThisBag[i];			// Assign the thing in the Bags position to the returnValue
				result = true;						// Indicate the value was found
				break;								// Exit the loop
			}
		}

		return result;
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Inspect the top of the bag.  If the bag is empty return
	// false and leave 'item' unchanged; otherwise, return true and update 
	// 'item' with the contents of the bag.
	bool inspectTop(E& item) const
	{
		// In the consturcter, every element was set to nullptr with the emptybag() funciton
		// Checks to see if the position is 0 meaning the bag is empty

		bool result;
		if (Bagposition == 0)
		{
			result = false;					 // If the bag is empty return false
		}
		else
		{
			item = ThisBag[Bagposition-1];	 // Assign item to the thing in the top of the bag
			result = true;					 // indicate the operatiron was succesful
		}
		return result;
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// empties the bag
	void emptyBag()
	{
		// Logically empties the bag
		// The Dectructer deletes the array when the program terminates
		Bagposition = 0; // Reset current position
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// use the += operator to add an item to the bag
	bool operator+=(const E& addend)
	{
		// Make a call to addItem and pass in a item of type E
		return addItem(addend);
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// get the size of the bag A.K.A the Bagposition
	int size() const
	{
		return Bagposition;
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// get the capacity of the bag
	int bagCapacity() const
	{
		return Bagcapacity;
	}
	// ---------------------------------------------------------------------------------------------------------------------------
};  