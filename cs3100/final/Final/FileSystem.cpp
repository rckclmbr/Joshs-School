#include "FileSystem.h"
#include <memory.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;


//---------------- constructor and destructor ------------------------------------------


// opens the simulated file system in read, write, and binary modes

FileSystem::FileSystem() : file("filesystem", ios::in | ios::out | ios::binary)
{
	memset(open_files, 0, sizeof(open_files));		// init open file table
	readBlock(ROOTBLK, (char*)root);			// read root directory
	memcpy(current, root, DIRSIZE * sizeof(dir_ent));	// copy route to current directory
	dir_block = ROOTBLK;					// init block containing current directory
	loadFAT();						// load the file access table
}


FileSystem::~FileSystem()
{
	saveFAT();						// save the file access table
	file.close();						// close the simulated filesystem
}



//---------------- High-level operations -----------------------------------------------


// lists and formats the contents of the current directory

void FileSystem::list()
{
	// must complete
	for(int i = 0; i < DIRSIZE; i++) {
		if(! strcmp(current[i].name,"")) continue;

		char df;
		if(current[i].modes == FS_FILE)
			df = 'f';
		else
			df = 'd';

		cout << df << "\t" << (char*)current[i].name << "\t\t" << current[i].size << endl;

	}
}



// removes an entry from the file system.
// Files are removed without question; directories are removed only if empty.
// removes the entry from the current directory and returns blocks to the free store
// by linking them in the FAT.

void FileSystem::remove(char* name)
{
	if (strlen(name) == 0)
	{
		cerr << "USAGE: remove <file | dir>\n";
		return;
	}


	int	index = getByName(current, name);

	if (index == NIL)
		return;

	int block = current[index].link;

	if (!(current[index].modes & FS_DIR))		// it's a file
	{
		// unlink FAT and return all blocks to free list
		// ********************************* must complete *************************************
	}
	else						// it's a directory
	{
		if (!strcmp(name, "/"))			// can't remove current directory
			return;

		dir_ent temp_dir[DIRSIZE];

		readBlock(block, (char *)temp_dir);
		if (temp_dir[0].size != 1)		// can't delete a non-empty directory
			return;

		// remove ".." name from deleted directory and return block to free list (FAT)
		FAT[block] = 0;
		temp_dir[index].name[0] = '\0';
	}

	// remove entry from current directory
	current[index].name[0] = '\0';
	writeBlock(dir_block, (char*)current);
}




// Renames a file or directory in the current directory.
// the new name may not already exist in the current directory.
// the current directory is saved to disk.

void FileSystem::rename(char* old_name, char* new_name)
{
	if(strlen(old_name) == 0 || strlen(new_name) == 0)
		cerr << "USAGE: rename <old_name> <new_name>\n";
	// must complete
}



// makes a new directory of the current directory.
// The new name may not already exist in the current directory.

void FileSystem::mkdir(char* dir)
{
	if (strlen(dir) == 0)
	{
		cerr << "USAGE: mkdir <dir>\n";
		return;
	}

	int	index = getByName(current, dir);

	if (index != NIL)				// dir name already in current directory
		return;

	for (index = 0; index < DIRSIZE; index++)
		if (current[index].name[0] == '\0')
			break;

	if (index == DIRSIZE)				// out of room
		return;

	int	block = allocate();



	// set up new directory

	dir_ent	new_dir[DIRSIZE];

	memset((char *)new_dir, 0, BLOCK);
	strcpy(new_dir[0].name, "..");
	new_dir[0].size = 1;
	new_dir[0].modes = FS_DIR;
	new_dir[0].link = dir_block;



	// add entry to current directory

	strcpy(current[index].name, dir);
	current[0].size += 1;
	current[index].modes = FS_DIR;
	current[index].size = 1;
	current[index].link = block;



	// save both directories to the "disk drive"

	writeBlock(dir_block, (char*)current);
	writeBlock(block, (char*)new_dir);
}



// change directory.
// The argument to this command may have one of four values:
// "/" changes to the root directory;
// ".." changes to the current directory's immediate parent;
// if the argument names a directory in the current directory, it becomes the new directory;
// if the argument is empty (i.e., there is no argument) changes to the root directory.

void FileSystem::cd(char* dir)
{
	// must complete
	if(strcmp(dir, "/")) {
		memcpy((char*)current, (char*)root, sizeof(dir_ent) * DIRSIZE);
	}
}




// prints the full pathname of the current working directory.

void FileSystem::pwd()
{
	pwd(current[0].link, dir_block);
	cout << endl;
}



//---------------- Low-level operations  -----------------------------------------------


// creates a new file in the current directory and opens it in write mode.
// the operation fails if the current directory already contains an entry with the given name.
// the function returns an integer file descriptor, which is an index into the open files table.

int FileSystem::create(char* name)
{
	int	index = getByName(current, name);

	if (index != NIL)				// directory already contains a
		return NIL;				// file with this name

	for (index = 0; index < DIRSIZE; index++)
		if (current[index].name[0] == '\0')
			break;

	if (index == DIRSIZE)				// out of room
		return NIL;

	strcpy(current[index].name, name);
	current[index].size = 0;
	current[index].modes = FS_FILE;
	current[index].link = NIL;
	current[0].size += 1;

	writeBlock(dir_block, (char*)current);

	return open(name, WRITE);
}



// opens the named file if it exists in the current directory;
// adds a new entry to the open files table and allocates a the file buffer
// ( i.e., a large character array) and saves the address in the open file table pointer field.
// initializes the buffer pointer (bufp): BLOCK for READ and 0 for WRITE.
// returns an integer file descriptor, which is an index into the open files table, if the
// open is successful or NIL on error.

int FileSystem::open(char* name, int mode)
{
	int block = getByName(current, name);
	if(block == NIL) return NIL;
	// Check to see if any slots are open
	for(int i = 0; i < MAXOPEN; i++)
	{
		if(open_files[i].block == NIL) {
			char buffer[BLOCK];
			open_files[i].block = block;
			open_files[i].bufp = mode;
			open_files[i].buffer = buffer;
			open_files[i].pointer = 0;
			open_files[i].dir = current;
			return i;
		}
	}
	return NIL;// number of open files exceeded
		// must complete
}


// Closes the file represented by the integer file descriptor.
// Removes the file from the open files table and deletes a file buffer.
// Saves the current directory to the simulated disk.

void FileSystem::close(int fd)
{
	flush(fd);
	open_files[fd].bufp = NIL;
	open_files[fd].pointer = NIL;
	open_files[fd].block = NIL;
	delete open_files[fd].buffer;
	delete open_files[fd].dir;
	// must complete
}




// reads an "count" bytes from the file represented by the integer file descriptor
// in two the application provided buffer (abuffer).

int FileSystem::read(int fd, char* abuffer, int count)
{
	if(open_files[fd].block == NIL) return NIL;			// File descriptor doesn't exist
	if(open_files[fd].bufp == 0) return NIL;	 // File was opening for reading, not writing
	
	int block = open_files[fd].block;

	readBlock(block, abuffer);

	// must complete
	return 0;
}



// Writes "count" bytes from the application provided buffer (abuffer) to the file represented by
// the integer file descriptor.

void FileSystem::write(int fd, char* abuffer, int count)
{
	int	abufp = 0;  // Start at the beginning of the buffer

	while (count)
	{
		int	avail = BLOCK - open_files[fd].bufp;	// spaces in file buffer
		int	trans = min(avail, count);		// # of bytes to transfer (until we fill up the buffer,
											// or until we've transferred everything we need to)

		// (memcpy(void* to, void* from, int how_many);
		memcpy(open_files[fd].buffer + open_files[fd].bufp, abuffer + abufp, trans);

		abufp += trans;
		open_files[fd].bufp += trans;			// Update the pointer 
		count -= trans;							// Update amount of bytes we have to transfer

		if (open_files[fd].bufp == BLOCK)		// file buffer is full
			flush(fd);
	}

	open_files[fd].dir->size += abufp;			// Update the dir size
}




// Writes any remaining bytes in the file buffer to the file represented by the integer file descriptor.

void FileSystem::flush(int fd)
{
	if (open_files[fd].bufp == 0)	// If there's nothing in the buffer, there's nothing to do
		return;

	int	block = allocate();					// Get a free block
	writeBlock(block, open_files[fd].buffer);	// Copies the data from the buffer to the free store

	if (open_files[fd].block == NIL)		// the first write
		open_files[fd].dir->link = block;	// 1st block in directory
	else
		FAT[open_files[fd].block] = block;	// block in FAT

	FAT[block] = NIL;								// Reset our 
	open_files[fd].bufp = 0;						// Reset our buffer pointer to pos 0
	open_files[fd].block = block;					// Set our block to the block we just wrote
	memset(open_files[fd].buffer, 0, BLOCK);		// Reset the buffer to all nulls
	open_files[fd].dir->size += open_files[fd].bufp;	// Update the dir size
}





//---------------- Internal (i.e., private) Operations --------------------------------



// Finds the directory stored at block a "child" in the directory stored at block "parent"
// and prints out the child directory's name.  Uses recursion to climb from the child to
// the parent until the root directory is located.

void FileSystem::pwd(int parent, int child)
{
	dir_ent	temp[DIRSIZE];
	readBlock(parent, (char*)temp);

	if (parent != ROOTBLK)
		pwd(temp[0].link, parent);

	cout << "/";

	for (int i = 1; i < DIRSIZE; i++)
		if (temp[i].link == child)
		{
			cout << temp[i].name;
			break;
		}
}



// searches a directory and locates an entry by name.

int FileSystem::getByName(dir_ent dir[DIRSIZE], char* name)
{
	// must complete
	return NIL;
}


// reads a block located at LBA "block" from the simulated file system
// into the application provided buffer.
void FileSystem::readBlock(int block, char* buffer)
{
	file.seekp(block * BLOCK);
	file.read(buffer, BLOCK);
}



// writes data from the application provided buffer to the block
// located at LBA "block".

void FileSystem::writeBlock(int block, char* buffer)
{
	file.seekg(block * BLOCK);
	file.write(buffer, BLOCK);
}



// loads the file access table.

void FileSystem::loadFAT()
{
	// move to the start of the file for reading
	file.seekp(FATBLK * BLOCK);
	file.read((char*)FAT, 4 * BLOCK);
	file.read((char*)root, BLOCK);
	
}



// saves the file access table.

void FileSystem::saveFAT()
{
	// move to the start of the file for writing
	file.seekp(FATBLK * BLOCK);
	file.write((char*)FAT, 4 * BLOCK);
	file.write((char*)root, BLOCK);
}


// allocates a block of memory from the free store,
// marks the memory as in use, and returns the block address of the memory.

int FileSystem::allocate()
{
	// 0 is free space, -1 is in use but not linked to anything yet.
	// must complete
	return -1;
}

