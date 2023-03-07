#include "Words.h"      // I meant to do that.
#include <iostream>
#include <cassert>
 
using namespace std;
 
int main() {
    string w;
    bool b;
    const auto prog = R"(
        1\) dogs\\n2\) cats
        )";
 
    Words words(prog);
    cout << "There are " << words.size() << " words.\n";
    for (size_t i=0; i<words.size(); i++) {
        words.get(i, w, b);
        cout << i << ": “" << w << "”";
        if (b)
            cout << " (escaped)";
        cout << '\n';
    }
    cout << words << '\n';
    words.analyze("Applejack Pinkie\\ Pie");
    words.analyze(")\tQ\n≠\rFNORD\f\v ");
    assert(words.size() == 4);
 
    const auto w2(words);
    cout << w2.size() << "\n";
    cout << w2.empty() << "\n";
    assert(w2.get(3, w, b) && w == "FNORD" && !b);
    assert(!w2.get(999, w, b));
 
    cout << w2 << "\nDone.\n";
 
    return 0;
}
