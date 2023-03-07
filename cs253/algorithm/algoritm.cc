#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;
bool less5(int i) { return i < 5; }

int main() {
    vector<short> pi = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4};
    string alpha="abcdefghijklmnopqrstuvwxyz", digits="0123456789";
    char cbuf[100] = { };	// contains 100 '\0' chars
    list<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    short powers[] = {1,2,4,8,16,32,64};
    int ibuf[100];		// contains unknown values

    cout << "Exercise 0\n";
    copy(alpha.begin(), alpha.end(), cbuf);
    cout << cbuf << '\n';
    
    cout << "Exercise 1\n";
    reverse(begin(cbuf), end(cbuf));
    for(auto e : cbuf) std::cout << e;
    cout << '\n';
    
    cout << "Exercise 2\n";
    transform(primes.begin(), primes.end(), begin(ibuf), [](int i) -> int {return i + 1;});
    for(int i; i < 10; i++) std::cout << ibuf[i] << " ";
    cout << '\n';
    
    cout << "Exercise 3\n";
    if(any_of(primes.begin(), primes.end(), [](int i) { return i%2 == 0;})) cout << "div 2\n";
    else if(any_of(primes.begin(), primes.end(), [](int i) { return i%42 == 0;})) cout << "div 42\n";
    
    cout << "Exercise 4\n";
    std::list<int>::iterator it;
    it = find(primes.begin(), primes.end(), 13);
    cout << *next(it) << '\n';
    
    cout << "Exercise 5\n";
    int counter = count(pi.begin(), pi.end(), 3);
    cout << counter << "\n";
    
    cout << "Exercise 6\n";
    counter = count_if(pi.begin(), pi.end(), less5);
    cout << counter << "\n";
    
    cout << "Exercise 7\n";
    vector<short>::iterator result = max_element(pi.begin(), pi.end());
    cout << *result << "\n";
    
    cout << "Exercise 8\n";
    sort(pi.begin(), pi.end());
    for(auto e : pi) std::cout << e << " ";
    cout << '\n';
    
    cout << "Exercise 9\n";
    vector<short>::iterator low = lower_bound(pi.begin(), pi.end(), 7);
    cout << (low - pi.begin()) << "\n";
    
    cout << "Exercise 10\n";
    //int f = *set_intersection(pi.begin(), pi.end(), powers, powers+7, begin(ibuf));
    int f = 0;
    for(auto myIterator = begin(ibuf);
        set_intersection(pi.begin(), pi.end(), powers, powers+7, begin(ibuf)) != myIterator; 
        myIterator++) 
    {
        cout << ibuf[f++] << " ";
    }
    cout << '\n';
}
