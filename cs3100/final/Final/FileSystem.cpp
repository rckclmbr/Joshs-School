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
		if(strcmp(current[i].name,"") == 0) continue;

		char df;
		if(! (current[i].modes & FS_DIR)) // It's a directory
			df = 'f';
		else
			df = 'd';

		cout << df << "\t" << current[i].name << "\t\t" << current[i].size << endl;

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


	if (index == NIL) {
		cerr << "No file by that name" << endl;
		return;
	}

	int block = current[index].link;

	if (!(current[index].modes & FS_DIR))		// it's a file
	{
		current[index].link = NIL;
		while(block != -1) {
			int temp = FAT[block];
			FAT[block] = 0;
			block = temp;
		}

	}
	else						// it's a directory
	{
		if ( strcmp(name, "/") == 0)			// can't remove root directory
			return;

		dir_ent temp_dir[DIRSIZE];

		readBlock(block, (char *)temp_dir);

		if (temp_dir[0].size != 1) {		// can't delete a non-empty directory
			cerr << "Cannot delete:  directory is not empty" << endl;
			return;
		}

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
	if(strlen(old_name) == 0 || strlen(new_name) == 0) {
		cerr << "USAGE: rename <old_name> <new_name>\n";
		return;
	}

	int index = getByName(current, old_name);
	strcpy(current[index].name, new_name);

	writeBlock(dir_block, (char*)current);
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
	FAT[block] = -1;
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
	if( strcmp(dir, "/") == 0 || dir[0] == '\0' ) {
		dir_block = ROOTBLK;
	}
	else {
		int index = getByName(current, dir);
		if(index == NIL) return;
		if(current[index].modes & FS_FILE) return;
		dir_block = current[index].link;
	}
	readBlock(dir_block, (char*)current);

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
	int dir = getByName(current, name);

	if (dir == NIL)		// it's a directory
		return NIL;

	// Check to see if any slots are open
	for(int i = 0; i < MAXOPEN; i++)
	{
		dir_ent* dp = open_files[i].dir;
		if(dp && dp->name == name)
			return NIL;	// File already open
	}

	for(int index = 0; index < MAXOPEN; index++) {
		if(!open_files[index].dir) {	// If it's available for us to grab
			open_files[index].dir = &current[dir];
			open_files[index].buffer = (char*)malloc(sizeof(char) * BLOCK);
			memset(open_files[index].buffer, 0, BLOCK);
			open_files[index].block = current[dir].link;
			open_files[index].pointer = 0;

			if(mode == READ)
				open_files[index].bufp = BLOCK;
			else
				open_files[index].bufp = 0;
			
			return index;
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
	if(fd == NIL) return; // Shouldn't happen anyways, but just in case

	writeBlock(dir_block, (char*)current);

	delete open_files[fd].buffer;
	open_files[fd].dir = NULL;
}




// reads an "count" bytes from the file represented by the integer file descriptor
// in two the application provided buffer (abuffer).

int FileSystem::read(int fd, char* abuffer, int count)
{
	int abufp = 0;
	int block;

	for(;;) {
		if(abufp < count && open_files[fd].pointer < open_files[fd].dir->size) {
			block = open_files[fd].block;
			open_files[fd].block = FAT[block];
			if(open_files[fd].bufp == BLOCK) {	// Buffer is empty
				if(block == NIL)
					return abufp;	// No more blocks in file
				readBlock(block, open_files[fd].buffer);
			}
			int avail = BLOCK - abufp;
			int trans = min(avail, count);
			trans = min(trans, open_files[fd].dir->size - open_files[fd].pointer);
			memcpy(abuffer + abufp, open_files[fd].buffer, trans);
			open_files[fd].bufp = 0;
			abufp += trans;
			open_files[fd].pointer += trans;
			open_files[fd].bufp += trans;
		} else {
			return abufp;
		}
	}
}



// Writes "count" bytes from the application provided buffer (abuffer) to the file represented by
// the integer file descriptor.

void FileSystem::write(int fd, char* abuffer, int count)
{
	if(fd == NIL) {
		cout << "Error writing file" << endl;
		return;
	}
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
	if(fd == NIL) return;

	int	block = allocate();					// Get a free block

	writeBlock(block, open_files[fd].buffer);	// Copies the data from the buffer to the free store

	if (open_files[fd].block == NIL)		// the first write
		open_files[fd].dir->link = block;	// 1st block in directory
	else
		FAT[open_files[fd].block] = block;	// block in FAT

	FAT[block] = NIL;								// EOF
	open_files[fd].bufp = 0;						// Reset our buffer pointer to 0
	open_files[fd].block = block;					// Set our block to the block we just wrote
	memset(open_files[fd].buffer, 0, BLOCK);		// Reset the buffer to all nulls
	open_files[fd].dir->size += open_files[fd].bufp;	// Update the size

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
	if(name[0] == '\0') return NIL;

	for(int index = 0; index < DIRSIZE; index++) {
		if( strcmp(current[index].name, name) == 0 )
			return index;
	}
	return NIL;
}


// reads a block located at LBA "block" from the simulated file system
// into the application provided buffer.
void FileSystem::readBlock(int block, char* buffer)
{
	file.seekg(block * BLOCK);
	file.read(buffer, BLOCK);
	//buffer[BLOCK] = '\0';
}



// writes data from the application provided buffer to the block
// located at LBA "block".

void FileSystem::writeBlock(int block, char* buffer)
{
	file.seekp(block * BLOCK);
	file.write(buffer, BLOCK);
}



// loads the file access table.

void FileSystem::loadFAT()
{
	// move to the start of the file for reading
	file.seekg(FATBLK * BLOCK);
	file.read((char*)FAT, 4 * BLOCK);
	
}



// saves the file access table.

void FileSystem::saveFAT()
{
	// move to the start of the file for writing
	file.seekp(FATBLK * BLOCK);
	file.write((char*)FAT, 4 * BLOCK);
}


// allocates a block of memory from the free store,
// marks the memory as in use, and returns the block address of the memory.

int FileSystem::allocate()
{
	for(int i = DATABLK; i < NBLOCKS; i++) {
		if(FAT[i] == 0)
			return i;
	}

	cerr << "Error in allocate!" << endl;
	return NIL; // Memory was full?
}

