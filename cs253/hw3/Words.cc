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

Words::~Words() {
    //destructor
}

void Words::analyze(string input) {
    string lineContent;
    vector<string> line;
    vector<bool> isWordEscaped;
    bool placeholder = false;
    for(unsigned long i = 0; i < input.size(); i++) {
        if(input[i-1] == '\\') {
            lineContent += input[i];
            placeholder = true;
        }
        else if(isspace(input[i])) {
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
