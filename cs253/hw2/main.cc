#include <sys/types.h>	// fork() & wait()
#include <unistd.h>	// fork(), execvp()
#include <cstdlib>	// exit()
#include <wait.h>	// wait()
#include <vector>	// vector<>
#include <string>	// string
#include <iostream>
#include <fstream>

using namespace std;

bool execute(vector<string> command) {
    // Convert vector of C++ strings to an array of C strings for exectp():
    vector<char *> argv;		// vector of C string pointers
    for (auto &v : command)		// for each C++ string:
	argv.push_back(v.data());	//    add address of C-string inside it
    argv.push_back(nullptr);		// argv ends with a null pointer

    // Duplicate ourself: -1:error, 0:child, >0:parent
    const auto pid = fork();		// step #1: copy ourself
    if (pid < 0)
	return false;			// fork failure?
    if (pid == 0) {			// child?
	execvp(argv[0], argv.data());	// step #2: replace child with new prog
	exit(0xff);			// only got here if execvp() failed.
    }
    int status;
    wait(&status);			// step #3: wait for child to finish
    return status != 0xff00;		// true iff we succeeded
}

bool meatWork(string str, vector<string> line) {
    string lineContent;
    int leftParen = 0;
    int rightParen = 0;
    for(unsigned long i = 0; i < str.size(); i++) {
        if(str[i-1] == '\\') {
            lineContent += str[i];
        }
        else if(isspace(str[i])) {
            if(lineContent == "") {
                continue;
            }
            else {
                line.push_back(lineContent);
                lineContent = "";
            }
         }
         else if(str[i] == '\\') {
            continue;
         }
         else if(str[i] == '(' ) {
            if(lineContent == "") {
                line.push_back("(");
                lineContent = "";
            }
            else {
                line.push_back(lineContent);
                line.push_back("(");
                lineContent = "";
            }
            leftParen++;
         }
         else if(str[i] == ')' ) {
            if(lineContent == "") {
                line.push_back(")");
                lineContent = "";
            }
            else {
                line.push_back(lineContent);
                line.push_back(")");
                lineContent = "";
            }
            rightParen++;
         }
         else {
             lineContent += str[i];
         }
    }
            if(line.empty()) {
                return true;  //temporary solution, need to go get food.
            }
            if(line[1] != "(") {
                cerr << "ERROR: ./hw2: Second word is not an open parenthesis.\n";
                return false;
            }
                    
            else if(line[line.size()-1] != ")") {
                cerr << "ERROR: ./hw2: Last word is not a closing parenthesis.\n";
                return false;
            }
            else if(leftParen != 1 && rightParen != 1) {
                cerr << "ERROR: ./hw2: There are unescaped parenthesis other than the second work and last word.\n";
                return false;
            }
            else {
                line.erase(line.begin() + 1);
                line.erase(line.begin() + line.size() - 1);
            }
            /*cout << "VECOTR CONTENTS TEST: \n";
            for (auto val: line) {
                cout << val << "\n";
            }*/
            if(!execute(line)) {
                cerr << "ERROR: ./hw2: Can't run: " << str << "\n";
                return false;
            }
                
            line.clear();
            str = "";
            lineContent = "";
            return true;
}
            


int main(int argc, char *argv[]) {
    
    string str;
    vector<string> line;
    ifstream infile1;
    
    if(argc > 1) {
        for (int i = 1; i < argc; i++) {
            infile1.open(argv[i]);
            if(!infile1.is_open()) {
                cerr << "./hw2: File " << argv[i] << " cannot be opened.\n";
                return 1;
            }
            else {
                while(getline(infile1, str)) {
                    if(!meatWork(str, line)) {
                        return 1;
                    }
                }
                infile1.close();
            }
        }
    }
    else if(argc == 1) {
        while(getline(cin,str)) {
            if(!meatWork(str, line)) {
                return 1;
            }
        }
    }
    else {
        cerr << "./hw2: error, cannot handle these areguments \n";
    }
    return 0;
}
