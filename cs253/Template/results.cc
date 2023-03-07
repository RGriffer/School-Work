#include <iomanip>	// for right, setw
#include <iostream>
#include <map>
#include <string>
#include <array>
#include <cstring>
#include <string.h>

using namespace std;

template <typename T>
class BarGraph {
  public:
    void operator+=(const T &datum) {
        data[datum]++;
    }
    void dump() const {
	for (const auto &val : data)
	    cout << right << setw(10) << val.first << ' '
		 << string(val.second, '*') << '\n';
        cout << '\n';
    }
    template<typename T1>
    friend ostream &operator<<(ostream &out, const BarGraph<T1> &datum);
  private:
    map<T, unsigned> data;
};

template <>
class BarGraph<bool> {
    unsigned false_count = 0, true_count = 0;
  public:
    void operator+=(bool datum) {
	datum ? true_count++ : false_count++;
    }
    friend ostream &operator<<(ostream &out, const BarGraph<bool> &datum);
    void dump() const {
        cout << "     false " << string(false_count, '*') << "\n"
                "      true " << string(true_count,  '*') << "\n\n";
    }
};
// I cannot figure this out right now if I have time later this week i will come back to it.
/*template <> 
class BarGraph<char> {
    char arrChar[50];
    int arrInt[50] = {10000};
    int loc = 0;
public:
    void setZero(int arr[]) {
        for(unsigned long i = 0; i < 50; i++) {
            arr[i] = 0;
        }
    }
    
    void operator +=(char c) {
        if(arrInt[0] == 10000) {
            setZero(arrInt);
        }
        for(unsigned long i = 0; i < sizeof(arrChar); i++) {
            if(c == arrChar[i]) {
                arrInt[i]++;
            }
            else {
                arrChar[strlen(arrChar)] = c;
                arrInt[i]++;
            }
        }
    }
    
    void operator +=(string str) {
        if(arrInt[0] == 10000) {
            setZero(arrInt);
        }
        for(unsigned long i = 0; i < sizeof(arrChar); i++) {
            if(str.at(loc) == arrChar[i]) {
                arrInt[i]++;
            }
            else {
                arrChar[strlen(arrChar)] = str.at(loc);
                arrInt[i]++;
            }
            loc++;
        }
        loc = 0;
    }
    friend ostream &operator<<(ostream &out, const BarGraph<char> &datum);
}; */

template <typename T>
ostream &operator<<(ostream &os, const BarGraph<T> &datum) {
    for (const auto &val : datum.data) 
	    os << right << setw(10) << val.first << ' '
		 << string(val.second, '*') << '\n';
        os << '\n';
        return os;
}

ostream &operator<<(ostream &os, const BarGraph<bool> &var) {
    os << "     false " << string(var.false_count, '*') << "\n"
            "      true " << string(var.true_count,  '*') << "\n\n";
    return os;
}
/*
ostream &operator<<(ostream &os, const BarGraph <char> &var) {
    for (auto val : var.arrChar)
        os << right << setw(10) << var.arrChar[val] << ' ' << string(var.arrInt[val], '*') << '\n';
    return os;
}
*/
int main() {
    BarGraph<int> alpha;
    alpha += 12;
    alpha += 6;
    alpha += 4;
    alpha += 6;
    //alpha.dump();
    cout << alpha;

    BarGraph<double> beta;
    beta += 3.14;
    beta += 2.71828;
    beta += 6.023e23;
    beta += 2.71828;
    //beta.dump();
    cout << beta;

    BarGraph<bool> gamma;
    gamma += false;
    gamma += true;
    gamma += false;
    gamma += true;
    gamma += true;
    //gamma.dump();
    cout << gamma;

    BarGraph<char> delta;
    delta += 'G';
    delta += 'e';
    delta += 'o';
    delta += 'f';
    delta += 'f';
    //delta += "Colorado";
    delta.dump();
    //cout << delta;

    return 0;
}
