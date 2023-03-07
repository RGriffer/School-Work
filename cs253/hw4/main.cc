#include <sys/types.h>	// fork() & wait()
#include <unistd.h>	// fork(), execvp()
#include <cstdlib>	// exit()
#include <wait.h>	// wait()
#include <vector>	// vector<>
#include <string>	// string
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

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

bool meatWork(string str, vector<string> line, bool verbose, unsigned long maxArg, string st, bool singleCheck) {
    string lineContent;
    int leftParen = 0;
    int rightParen = 0;
    string charToPush = "";
    for(unsigned long i = 0; i < str.size(); i++) {
        //This entire for loop checks whatever is given to st against the current char by looping through st. st=signleton characters passed by -s
        //find out how to make date() not work but date ( ) work
        //find out how to make \ escape the singleton character.
        if (singleCheck) {    
            for(unsigned long j = 0; j < st.size(); j++) {
                    if (str[i] == st[j]) {
                        charToPush = st[j];
                        if(str[i-1] == '\\') {
                            continue;
                        }
                        if(lineContent == "") {
                            if(charToPush == "(") {
                                leftParen++;
                            }
                            else if(charToPush == ")") {
                                rightParen++;
                            }
                        }
                        else {
                            line.push_back(lineContent);
                            lineContent = "";
                            if(charToPush == "(") {
                                leftParen++;
                            }
                            else if(charToPush == ")") {
                                rightParen++;
                            }
                        }
                        line.push_back(charToPush);
                        
                    }
            }
        }
        //All hw3 stuff that works for hw2
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
                continue;
            }
         }
         else if(str[i] == '\\') {
            continue;
         }
         
         else if(charToPush != "") {
            charToPush = "";
             continue;
        }
         else {
            if(!singleCheck) {
                if(str[i] == '(' ) { //going into this but doing nothing when in it and not pushing it and going to else statement
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
                    continue;
                }
                else if(str[i] == ')') {
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
                    continue;
                }
            }
             lineContent += str[i];
         }
         if(lineContent == "(" && isspace(str[i+1])) {
             leftParen++;
         }
         else if(lineContent == ")" && isspace(str[i+1])) {
             rightParen++;
         }
    }       
            
            if(line.empty()) {
                return true;  //no longer temporary, not fucking with this
            }
            if(line[1] != "(") {
                cerr << "ERROR: ./hw4: Second word is not an open parenthesis.\n";
                return false;
            }
                    
            else if(line[line.size()-1] != ")") {
                cerr << "ERROR: ./hw4: Last word is not a closing parenthesis.\n";
                return false;
            }
            else if(leftParen != 1 && rightParen != 1) {
                cerr << "ERROR: ./hw4: There are unescaped parenthesis other than the second work and last word.\n";
                return false;
            }
            else {
                line.erase(line.begin() + 1);
                line.erase(line.begin() + line.size() - 1);
            }
            if (verbose) {  //print verbose if given true by -v
                cout << "Executing:\n";
                int printSlot = 0;
                for(auto val: line) {
                    cout << printSlot << ": \"" << val << "\"\n";
                    printSlot++;
                }
                printSlot = 0;
            }
            if(line.size() - 1 > maxArg && maxArg != 0) { //Check for arguments that exceed given in -m
                cerr << "ERROR: ./hw4: amount of arguments for " << str << " exceeds maximum given in -m " << maxArg << ".\n";
                return false;
            }
            if(!execute(line)) {
                cerr << "ERROR: ./hw4: Can't run: " << str << "\n";
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
    bool verboseCheck = false;
    int opt;
    unsigned long maxArgValue = 0;
    int num;
    string singletons;
    bool sCheck = false;
    int mCounter = 0; 
    int sCounter = 0;
    //Check for options.
    while ((opt = getopt(argc,argv, "vm:s:")) != -1) {
        switch(opt) {
            case 'v':  //-v = verbose
                verboseCheck = true;
                break;
            case 'm': //-m = max_args
                //FIND OUT HOW TO THROW ERROR WHEN PASSED DOUBLE SUCH AS 10.4934
                mCounter++;
                if(mCounter > 1) {
                    cerr << "ERROR: ./hw4: Called -s more than once. \n";
                    return 1;
                }
                num = atoi(optarg);
                if(num < 1 || num > 100) {
                    cerr << "ERROR: ./hw4: -m must contain a integer value between 1-100.\n";
                    return 1;
                }
                maxArgValue = num;
                num = 0;
                break;
            case 's': //-s = singleton characters specified
                sCounter++;
                if(sCounter > 1) {
                    cerr << "ERROR: ./hw4: Called -s more than once. \n";
                    return 1;
                }
                singletons = string(optarg);
                sCheck = true;
                break;
            default:
                cout << "ERROR: ./hw4: given option is not supported. please use -v/-m int/ -s \"string\"\n";
                return 1;
        }
    }
    //check arguments and decide if should read from standard input or file.
    if(argc > optind) {
        for (int i = optind; i < argc; i++) {
            infile1.open(argv[i]);
            if(!infile1.is_open()) {
                cerr << "./hw4: File \"" << argv[i] << "\" cannot be opened.\n";
                return 1;
            }
            else {
                while(getline(infile1, str)) {
                    if(!meatWork(str, line, verboseCheck, maxArgValue, singletons, sCheck)) {
                        return 1;
                    }
                }
                infile1.close();
            }
        }
    }
    else if(argc == optind) { //take from CIN
        while(getline(cin,str)) {
            if(!meatWork(str, line, verboseCheck, maxArgValue, singletons, sCheck)) {
                return 1;
            }
        }
    }
    else {
        cerr << "./hw4: error, cannot handle these arguments \n"; //If you see this you fucked up
    }
    return 0;
}
