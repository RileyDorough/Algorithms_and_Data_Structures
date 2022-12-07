// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Programming Assignment 3
// LRUBufferPool.h - implementation of BufferPoolADT.h
// This class manages a buffer pool made of MyBufferBlock.h objects
// Created by Chandler Whitley and Riley Dorough
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
#include "BufferPoolADT.h"
#include "MyBufferBlock.h"
#include <fstream>

// ADT for buffer pools using the message-passing style
class LRUBufferPool : public BufferPoolADT {
private:
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//The buffer pool consists of X number of buffer blocks

	MyBufferBlock * poolblocks; // The Buffer P00l
	fstream input;				// Input file
	int BlockSize;				// Size of each block
	int PoolSize;				// Size of the Pool starting at 1 to avoid confusion
	// -------------------------------------------------------------------------------------------------
	 
public:
	//Constructor gets the filename of the file to be buffered,
	//opens the file, and instantiates poolSize buffer blocks by
	//reading the file and filling the blocks in order.  When the constructor
	//is done the buffer pool blocks should be full with the beginning
	//contents of the input file.
	LRUBufferPool() {}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096) 
	{
		// Set parameters
		BlockSize = blockSize;
		PoolSize = poolSize;

		// Create the pool with the specified number of blocks
		poolblocks = new MyBufferBlock[poolSize](); 
		
		// Open the input file
		input.open(filename.c_str(), fstream::in | fstream::binary);

		// Check to see if the file is avialable
		if (!input)
			cout << "error opening file\n";


		else
		{
			// Now populate each block
			// Use byte mode and fill it up
			// Pushing back the blocks so most recently used is at the top

			for (int i = (poolSize - 1); i >= 0; --i)
			{
				char * temparray = new char[BlockSize];		// create temporary array to read into
				input.seekg(i*BlockSize);					// Go to the correct position
				input.read(temparray, BlockSize);			// Read the correct number of bytes into the temporary array

				// Read the array into the correct location and set ID . . . also delete temp pointer to avoid memory leak
				poolblocks[i].setBlock(temparray);
				poolblocks[i].setID(i);
				temparray = nullptr;
			}
		}
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	~LRUBufferPool() 
	{
		input.close();			// Close the input file
		delete[] poolblocks;	// Delete the pointers to blocks
		poolblocks = nullptr;	// Set pointer to NULL
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos)
	{
		int thisblocknum = (pos / BlockSize);	// Figure out which block the request is in
		int blockindex;							// Variable to signify the blocks ID
		int start = (pos % BlockSize);			// Find where to start
		bool inpool = false;					

		// Check to see if this block is already in the pool
		for (int i = 0; i < PoolSize; i++)
		{
			if (poolblocks[i].getID() == thisblocknum)
			{
				blockindex = i;
				inpool = true;
			}
		}

		if (inpool)
		{
			// Create temporary block using the information already in the pool
			MyBufferBlock temporaryblock(poolblocks[blockindex].getBlock(), BlockSize);
			temporaryblock.setID(poolblocks[blockindex].getID());

			// Shift items down that had been above this block
			for (int j = (blockindex); j > 0; --j)
			{
				poolblocks[j].setBlock(poolblocks[j-1].getBlock());
				poolblocks[j].setID(poolblocks[j - 1].getID());
			}
			
			// Put the correct block at the top
			poolblocks[0].setBlock(temporaryblock.getBlock());
			poolblocks[0].setID(temporaryblock.getID());
		}


		if (!inpool)
		{
			char * tempchararray = new char[BlockSize];			// create temporary array to read into
			input.seekg(thisblocknum * BlockSize);				// Go to the correct position
			input.read(tempchararray, BlockSize);				// Read the correct number of bytes into the temporary array
			
			// Replace LRU with new block
			poolblocks[PoolSize - 1].setBlock(tempchararray);
			poolblocks[PoolSize - 1].setID(thisblocknum);

			// Make temporary block so its value is not lost
			MyBufferBlock newtemporaryblock(poolblocks[PoolSize - 1].getBlock(), BlockSize);
			newtemporaryblock.setID(poolblocks[PoolSize - 1].getID());
			tempchararray = nullptr;

			// Shift everything down
			for (int k = (PoolSize - 1); k > 0; --k)
			{
				poolblocks[k].setBlock(poolblocks[k - 1].getBlock());
				poolblocks[k].setID(poolblocks[k - 1].getID());
			}

			// Put new block at the top
			poolblocks[0].setBlock(newtemporaryblock.getBlock());
			poolblocks[0].setID(newtemporaryblock.getID());

		}
		
		// Get the data
		poolblocks[0].getData(start, sz, space);
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder()
	{
		std::cout << "\nbuffer block order from most recently used to LRU is :\n";

		// Loop through the blocks and output their ID
		for (int i = 0; i < PoolSize; ++i)
		{
			std::cout << poolblocks[i].getID() << "  ";
		}

		cout << "\n";
	}
	// -------------------------------------------------------------------------------------------------

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID()
	{
		// The least recently used block will be at the end of the array.
		return poolblocks[PoolSize - 1].getID();
	}
	// -------------------------------------------------------------------------------------------------
};