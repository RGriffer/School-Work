#include <iostream>
#include <string>

using namespace std;

int main() {
    
    string content = "";
    int wordCount = 0;
    char c;
    int wordLength;
    int low = -1;
    int high = -1;
    
    while (cin.get(c)) {
        //Check to see if the character is whitespace AND the content is empty
        // so that it does not count the whitespace into content
        if(isspace(c) && content == "") {
            continue;
        }
        //check for left parenthesis, this is such ugly code but it works so I am not touching it.
        if(c == '(') {
            //return the word (if any) before the parenthesis
            if(content != "") {
                cout << "Word is \"" << content << "\"\n";
                wordCount++;
                wordLength = content.length();
                if(low == -1) {
                    low = wordLength;
                }
                if(high == -1) {
                    high = wordLength;
                }
                if(low > wordLength) {
                    low = wordLength;
                }
                if(high < wordLength) {
                    high = wordLength;
                }
            }
            //now for the parenthesis
            content = "(";
            cout << "Word is \"" << content << "\"\n";
            wordCount++;
            //update word low or high if necessary.
            wordLength = content.length();
            if(low == -1) {
                low = wordLength;
            }
            if(high == -1) {
                high = wordLength;
            }
            if(low > wordLength) {
                low = wordLength;
            }
            if(high < wordLength) {
                high = wordLength;
            }
            content = "";
            continue;
        }
        //check for right parenthesis, ugly code bleh.
        else if(c == ')') {
            //return the word (if any) before the parenthesis
            if(content != "") {
                cout << "Word is \"" << content << "\"\n";
                wordCount++;
                //update low or high if necessary
                wordLength = content.length();
                if(low == -1) {
                    low = wordLength;
                }
                if(high == -1) {
                    high = wordLength;
                }
                if(low > wordLength) {
                    low = wordLength;
                }
                if(high < wordLength) {
                    high = wordLength;
                }
            }
            //now for the parenthesis
            content = ")";
            cout << "Word is \"" << content << "\"\n";
            wordCount++;
            wordLength = content.length();
            if(low == -1) {
                    low = wordLength;
            }
            if(high == -1) {
                    high = wordLength;
            }
            if(low > wordLength) {
                low = wordLength;
            }
            if(high < wordLength) {
                high = wordLength;
            }
            content = "";
            continue;
        }
        
        //check to see if it is not whitespace, add it to content if not.
        if(!isspace(c)) {
            content+=c;
        }
        //if we do hit whitespace and there is stuff in content, output content.
        else {
            cout << "Word is \"" << content << "\"\n";
            wordLength = content.length();
            if(low == -1) {
                low = wordLength;
            }
            if(high == -1) {
                high = wordLength;
            }
            if(low > wordLength) {
                low = wordLength;
            }
            if(high < wordLength) {
                high = wordLength;
            }
            wordCount++;
            content = "";
        }
        
    }
    //Check if there are words in the file, if none return standard error.
    if (wordCount == 0) {
            cerr << "There are no words. Please give me some words to find.\n";
            return 1;
        }
    cout << "Words: " << wordCount << "\n";
    cout << "Word range: " << low << "-" << high << "\n";
    //cout << content;
    return 0;
}
