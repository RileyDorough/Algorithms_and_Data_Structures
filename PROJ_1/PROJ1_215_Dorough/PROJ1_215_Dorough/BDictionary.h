// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Dictionary implementation following the guidlines of dictionaryADT.h
* Written by James Dorough and Chandler Whitley
* Uses a Bag data structure defined in bagADT.h and implemented in ABag.h
* Used Key-Value pairs to store items in the bag 
*/
// ---------------------------------------------------------------------------------------------------------------------------

#pragma once
#include "dictionaryADT.h"
#include "ABag.h"
#include "kvpair.h"

template <typename Key, typename E>
class  BDictionary: public Dictionary<Key, E> 
{
private:
	// The Bag to store values. This is of type KVpair
	// note: the types of KVpair (key and E) will be specified in the driver program
	ABag<KVpair<Key, E>> *myDict;

public:
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	BDictionary() {}									// Default constructor
	BDictionary(int dict_size)
	{
		myDict = new ABag<KVpair<Key, E>>(dict_size);	// Constructer to set the size of the Bag
	}
	~BDictionary() { delete[] myDict; }					// Base destructor, deletes myDict pointer
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Reinitialize dictionary
	void clear()
	{
		// Empty the Bag effectively emptying out the dictionary elements
		myDict->emptyBag();
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Insert a record
	// k: The key for the record being inserted.
	// e: The record being inserted.
	// Return true if insert is successful and false otherwise
	bool insert(const Key& k, const E& e)
	{
		KVpair<Key, E> thiskvpair(k,e);					// Create KVpair object using the constructer to setup the key and data
		bool result{ myDict->operator+=(thiskvpair) };	// Add the item to the myDict bag using += operator overload
		return result;									// Indicate result
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Looks for a record using the key and if found does the following:
	// - updates the E& rtnVal
	// - removes the record from the dictionary
	// - returns true
	// If the record is not found the function returns false.
	bool remove(const Key& k, E& rtnVal)
	{
		KVpair<Key, E> thiskvpair(k, rtnVal);		// Create KVpair object
		bool result{ myDict->remove(thiskvpair) };	// Remove item and ABag.h make sure rtnVal is updated
		rtnVal = thiskvpair.value();				// Update the return value using the appropriate get funciton for the value
		return result;								// Indicate result
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Takes an arbitrary record from the dictionary and does the following:
	// - updates the E& returnValue
	// - removes the record from the dictionary
	// - returns true
	// If the dictionary is empty the function returns false.
	bool removeAny(E& returnValue)
	{
		bool result;
		KVpair<Key, E> thiskvpair;					// Create KVpair object
		result = myDict->removeTop(thiskvpair);		// Remove the top object
		returnValue = thiskvpair.value();			// Update returnValue

		// "Against the rules" method of removing a random bag item
		//myDict->getrandomobject(thiskvpair);
		//result = myDict->remove(thiskvpair);

		return result;								// Indicate result
	}
	// ---------------------------------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Looks for a record using the key and if found does the following:
	// - updates the E& returnValue
	// - returns true
	// If the record is not found the function returns false.
	bool find(const Key& k, E& returnValue) const
	{
		KVpair<Key, E> thiskvpair(k, returnValue);	// Create KVpair object
		bool result = myDict->find(thiskvpair) ;	// Remove item and ABag.h makes sure rtnVal is updated
		returnValue = thiskvpair.value();			// Update the return value using the appropriate get funciton for the value
		return result;								// Indicate result
	}
	// ---------------------------------------------------------------------------------------------------------------------------
	
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Return the number of records in the dictionary.
	int size()
	{
		return myDict->size(); // Makes a call to Abag to get the number of things in the bag
	}
	// ---------------------------------------------------------------------------------------------------------------------------
};
