#include "Words.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
/* TO DO
 * TEST TAR FILE
 * LOOK OVER REQUIREMENTS TO MAKE SURE ALL IS GOOD
 */
Words::Words(string input) {
    analyze(input);
}

Words::Words(const Words &rhs) : lexical(rhs.lexical), escaped(rhs.escaped) {}

Words &Words::operator=(const Words &rhs) {
    lexical = rhs.lexical;
    escaped = rhs.escaped;
    return *this;
}
//START OF hw5 METHODS
Words Words::operator+(const Words &rhs) const {
    vector<string> newLexical = lexical;
    vector<bool> newEscaped = escaped;
    Words test = Words(*this);                                  //copy left into new object
    for(unsigned long i = 0; i < rhs.lexical.size(); i++) {     //for size of right side vectors
        test.lexical.push_back(rhs.lexical[i]);                 //push all of the right into new object
        test.escaped.push_back(rhs.escaped[i]);
    }
    return test;                                                //return new object
}

Words Words::operator+=(const Words &rhs) {
    for(unsigned long i = 0; i < rhs.lexical.size(); i++) {     //for size of right side vectors
        lexical.push_back(rhs.lexical[i]);                      //push all of right onto left
        escaped.push_back(rhs.escaped[i]);
    }
    return *this;                                               //return left
}

bool Words::operator==(const Words &rhs) {
    if(lexical == rhs.lexical) {                                //compare left and right hand analyzed vectors
        return true;
    }
    else {
        return false;
    }
}

bool Words::operator!=(const Words &rhs) {
    if(lexical == rhs.lexical) {                                //compare left and right hand analyzed vectors
        return false;
    }
    else {
        return true;
    }
}

Words &Words::operator--() {
    //change object
    vector<int> vec;
    for(unsigned long i = 0; i < lexical.size(); i++){          //for size of analyzed vector
        if(lexical[i] == "") {                                  //if word is empty
             vec.push_back(i);                                  //push onto removal vector i
        }
        else {
            lexical[i] = lexical[i].substr(0, lexical[i].size()-1);            //else remove the last character in string;
        }
        
    }
    for(unsigned long i = 0; i < vec.size(); i++) {
        lexical.erase(lexical.begin() + vec[i]);                //remove all values dictated by every value in vec
    }
    return *this;
}

Words Words::operator--(int) {
    const auto save = *this;
    --*this;                                                    //call predecrement operator
    return save;
}

Words::Brackets Words::operator[](int num) {
    if(num >= (int)lexical.size()) {
        throw std::out_of_range("ERROR: ");
        cout << "./hw5: Index " << num << "is not within the limits of the size of the Object, value of " << lexical.size();
    }
    structTest.first = lexical[num];                            //set structs first variable to the string at analyzed(num) vector position
    structTest.second = escaped[num];                           //same but escaped information
    return structTest;
}
//BACK OF hw5 METHODS

Words::~Words() {
    //destructor
}

void Words::analyze(string input) {                             //worked for hw3 but I had to change it for some reason
    string lineContent;                                         //stuff started breaking with this homework
    vector<string> line;
    vector<bool> isWordEscaped;
    bool placeholder = false;
    for(unsigned long i = 0; i < input.size(); i++) {
        //cout<< "looked at char " << i << ": ";
        if(i==0 && !isspace(input[i])) {                        //had to add this if, elseif block
            //cout<< "passed firstchar if \n";                  //
            lineContent += input[i];                            //
            continue;                                           //
        }                                                       //
        else if(i==0 && isspace(input[i])) {                    //
            continue;                                           //
        }                                                       //until here
        
        if(input[i-1] == '\\') {
            //cout<< "passed previous escape char if \n";
            lineContent += input[i];
            placeholder = true;
        }
        else if(isspace(input[i])) {
            //cout << "passed isspace[i] if \n";
            if(lineContent == "") {
                continue;
            }
            else {
                line.push_back(lineContent);
                if(placeholder) {
                    isWordEscaped.push_back(true);
                }
                else {
                    isWordEscaped.push_back(false);
                }
                lineContent = "";
                placeholder = false;
            }
         }
         else if(input[i] == '\\') {
            //cout<< "passed current parent if \n";
             continue;
         }
         else if(input[i] == '(' ) {
            if(lineContent == "") {
                line.push_back("(");
                if(placeholder) {
                    isWordEscaped.push_back(true);
                }
                else {
                    isWordEscaped.push_back(false);
                }
                lineContent = "";
                placeholder = false;
            }
            else {
                line.push_back(lineContent);
                line.push_back("(");
                if(placeholder) {
                    isWordEscaped.push_back(true);
                }
                else {
                    isWordEscaped.push_back(false);
                }
                lineContent = "";
                placeholder = false;
            }
         }
         else if(input[i] == ')' ) {
            if(lineContent == "") {
                line.push_back(")");
                if(placeholder) {
                    isWordEscaped.push_back(true);
                }
                else {
                    isWordEscaped.push_back(false);
                }
                lineContent = "";
                placeholder = false;
            }
            else {
                line.push_back(lineContent);
                line.push_back(")");
                if(placeholder) {
                    isWordEscaped.push_back(true);
                }
                else {
                    isWordEscaped.push_back(false);
                }
                lineContent = "";
                placeholder = false;
            }
         }
         else {
             lineContent += input[i];
             //cout << "passed normally: current:\n" << lineContent <<"\n" ;
         }
         if(i+1 == input.size() && lineContent != "") {                             //this entire if block had to be added
            line.push_back(lineContent);
            if(placeholder) {
                    isWordEscaped.push_back(true);
                }
            else {
                    isWordEscaped.push_back(false);
            }
        }
    }
    escaped = isWordEscaped;
    lexical = line;
}

[[nodiscard]] size_t Words::size() const {
    int count = 0;
    for(unsigned long i = 0; i < lexical.size(); i++) {
        count++;
    }
    return count;
}

[[nodiscard]] bool Words::empty() const {
    if(lexical.empty()) {
        return true;
    }
    return false;
}

bool Words::get(size_t n, string &str, bool &q) const {
    if(lexical.size() < n ) {
        return false;
    }
    else {
        str = lexical[n];
        q = escaped[n];
    }
    return true;
}

ostream &operator<<(ostream &os, const Words &val) {
    for(unsigned long i = 0; i < val.lexical.size(); i++) {
        if(i == val.lexical.size()-1) {
            os << val.lexical[i];
            return os;
        }
        os << val.lexical[i] << ",";
    }
    return os;
}
