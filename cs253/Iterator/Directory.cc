#include "Directory.h"
#include <iostream>

using namespace std;

// The directory iterator pre-fetches the name.  That is, readdir()
// is called when you first create the iterator, and upon ++.
//
// An end() iterator is designated by a null pointer for its DIR *.
// When readdir() fails, we set our pointer to null.

DirectoryIterator::DirectoryIterator(DIR *dp_arg, string str) : dp(dp_arg), pattern(str) {
    ++*this;				// get that first entry
    
}


// Get the next entry in the directory (that we like) and
// put it in the member variable name.

DirectoryIterator &DirectoryIterator::operator++() {	// pre-increment
    while (auto p = readdir(dp)) {	// Read a directory entry.
	name = p->d_name;		// C-string ⇒ C++ string
	if(wanted(name)) {
        return *this;
    }// Everything else, I like!
    }
    dp = nullptr;			// readdir failed; don’t try again.
    return *this;
}

string DirectoryIterator::operator*() const {
    return name;			// Fetched in a previous ++.
}

bool DirectoryIterator::operator!=(const DirectoryIterator &rhs) const {
    return dp != rhs.dp;
}

bool DirectoryIterator::wanted(string name) const {
    //Fix #3
    if(pattern != "NULL") {
        if (name.find(pattern) != std::string::npos) {
            return true;
        }
        else {
            return false;
        }
    }
    //Fix #2
    if(name == "." || name == "..") {
        return false;
    }
    return true;
}



//////////////// Directory methods

Directory::Directory(const char dirname[]) : dp(opendir(dirname)){ 
    //Fix #1
    if (!dp) {
        throw runtime_error("opendir() has failed.");
    }
    
}
Directory::Directory(const char dirname[], string namePattern) : dp(opendir(dirname)), pattern(namePattern){ 
    if (!dp) {
        throw runtime_error("opendir() has failed.");
    }
}


Directory::~Directory() {
    if (dp)				// Only if opendir() succeeded:
	closedir(dp);			//   should we close it.
}

Directory::iterator Directory::begin() const {
    
        return iterator(dp, pattern);
    
}

Directory::iterator Directory::end() const {
    return iterator();
}
