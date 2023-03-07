#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED

#include <dirent.h>
#include <string>
#include <optional>

// Normally, I’d have DirectoryIterator be a nested class, Directory::iterator,
// to avoid namespace pollution.  However, this is easier to read.

class DirectoryIterator {
  public:
    DirectoryIterator() = default;
    DirectoryIterator(DIR *dp_arg, std::string str);
    DirectoryIterator &operator++();
    std::string operator*() const;
    bool operator!=(const DirectoryIterator &) const;
    
  private:
    DIR *dp = nullptr;
    std::string pattern = "NULL";
    std::string name;
    bool wanted(std::string name) const;
};

class Directory {
  public:
    typedef DirectoryIterator iterator;
    Directory() = delete;		// not really necessary
    Directory(const char dirname[]);
    Directory(const char dirname[], std::string namePattern);
    ~Directory();
    iterator begin() const;
    iterator end() const;
    
  private:
    DIR *dp;				// null if open failed
    std::string pattern = "NULL";
    
    
};

#endif /* DIRECTORY_H_INCLUDED */
