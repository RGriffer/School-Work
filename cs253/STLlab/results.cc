#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
    
    //read in integers until user puts in 0
    vector<int> vect;
    int add;
    cin >> add;
    while(add != 0) {
        vect.push_back(add);
        cin >> add;
    }
    //unnecessary, get rid of before turn in
    /*cout << "vector test: \n";
    
    for (auto val : vect) {
        cout << val << "\n";
    }*/
    //read file to string
    ifstream file;
    file.open("/etc/resolv.conf");
    string str;
    char c;
    while(file.get(c)) {
        str += c;
    }
    
    
    //put string into multiset
    multiset<char> setOfMulti;
    for (auto val : str) {
        setOfMulti.insert(val);
    }
    
    set<char> characterSet;
    for (auto val : setOfMulti) {
        characterSet.insert(val);
    }
    
    //print string
    cout << "string: size=" << str.size() << " " << str << " ";
    
    //print set
    cout << "set: size=" << characterSet.size() << " ";
    for(auto val: characterSet) {
        cout << val;
    }
    cout << "\n";
    
    //print multiset
    cout << "multiset: size=" << setOfMulti.size() << " ";
    for(auto val : setOfMulti) {
        cout << val;
    }
    cout << "\n";
    
    //QUESTION 7: Based on on the output I got, string returns a the whole string with all of the characters in order.
    //The set is 26 because it takes the string but only takes a SINGLE of each character that shows up in the entire file/string
    //The multiset is 113 because it takes all of the characters in the file. However it sorts them to be in order so the output
    //of the string and the multiset are different even though they have the exact same characters in them. multiset is ordered and 
    //string is not.
    
}
