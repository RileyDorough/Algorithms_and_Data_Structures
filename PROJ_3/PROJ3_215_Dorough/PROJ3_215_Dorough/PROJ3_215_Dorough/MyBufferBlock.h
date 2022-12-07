// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Programming Assignment 3
// MyBufferBlock.h - implementation of BufferBlockADT.h
// This class exists to hold an array of characters and a block ID
// Created by Chandler Whitley and Riley Dorough
// -------------------------------------------------------------------------------------------------

#pragma once
#include "BufferBlockADT.h"

// Implementation of BufferBlockADT.h
class MyBufferBlock : public BufferblockADT
{
private:
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//Instance variables:
	int myblockID;		// ID for the blocks position in "hard drive" space
	char* myblock;		// Pointer to the array of characters in the block
	int size;			// Added private variable to hold the size of the block in bits?
	// -------------------------------------------------------------------------------------------------

public:
	// sz is the size of the character array data
	// points to.
	MyBufferBlock() { size = 4096; }
	MyBufferBlock(char* data, int sz = 4096) { myblock = data; size = sz; }
	~MyBufferBlock() { delete myblock; }

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// read the block from pos to pos + sz-1 (or to the end of the block)
	void getData(int pos, int sz, char* data)
	{
		// pos is the start of the access call inside the specific block
		// This is handeled by the process that calls the getData function using % operator

		// loop from i = 0 to the size or if the pointer exceedes the range in the block 
		for (int i = 0; (i < (sz)) || ((i+pos) > getBlocksize()); i++) 
		{
			data[i] = myblock[i+pos]; // copy the character over
		}
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//setID
	void setID(int id)
	{
		myblockID = id;
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//getID
	int getID() const
	{
		return myblockID;
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//getBlocksize
	int getBlocksize() const
	{
		return size;
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//return the block
	char* getBlock() const
	{
		return myblock;
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//set the block
	void setBlock(char* blk)
	{
		// Reinitialize the array to the correct size and copy elements over

		myblock = new char[size];
		for (int i = 0; i < (size); i++)
		{
			myblock[i] = blk[i];
		}
	}
	// --------------------------------------------------------------------------------------------------
};