#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
	cerr << "usage: " << argv[0] << " file\n";
	return 1;
    }
    fstream F(argv[1], ios::in | ios::out);
    
    //ifstream in(argv[1]);
    
    if (!F) {
	cerr << argv[0] << ": can't open " << argv[1] << '\n';
	return 2;
    }
    
    /*ofstream out(argv[1]);
    if (!out) {
	cerr << argv[0] << ": can't open " << argv[1] << '\n';
	return 3;
    }*/
    int Fpos;
    int totalchar = 0;
    for (string line; getline(F, line); ) {
        for (size_t pos=0; (pos=line.find("Trump", pos)) != line.npos; ) {
            line.replace(pos, 5, "Biden");
            Fpos = F.tellg();
            F.seekp(totalchar + pos);
            F.write("Biden", 5);
            F.seekp(Fpos);
        }
        totalchar = F.tellg();
    }

}

// Note that line.npos ≡ string::npos.
// It’s a static constant, part of the string class.
// It’s a number that means “Sorry, I couldn’t find that.”
