#include <vector>
#include <iostream>
#include <string>

class Words {
    
public:
    std::vector<std::string> lexical;
    std::vector<bool> escaped;
    Words(std::string input);
    //Words(std::vector<std::string> vec, std::vector<bool> var);
    Words() = delete;
    Words(const Words &);
    Words &operator=(const Words &);
    
    ~Words();
    void analyze(std::string input);
    size_t size() const;
    bool empty() const;
    bool get(size_t n, std::string &, bool &) const;
    //hw5 operators
    Words operator+(const Words &) const ;
    Words operator+=(const Words &);
    bool operator==(const Words &);
    bool operator!=(const Words &);
    Words &operator--();
    Words operator--(int);
    explicit operator bool() const { return (lexical.size() > 0); }
    
    struct Brackets {
        std::string first;
        bool second;
    };
    Brackets structTest;
    Brackets operator[](int);
    //end hw5 operators
    //begin hw7 operators
    /*class iterator {
    private:
        pointer my_ptr;
    public:
        iterator(pointer ptr) : my_ptr(ptr) {}
        iterator begin() { return this[0]; }
        iterator end() { return this[this->lexical.size()-1] }
        iterator& operator++() { my_ptr++; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const iterator& a, const iterator& b) { return a.my_ptr == b.my_ptr; };
        friend bool operator!= (const iterator& a, const iterator& b) { return a.my_ptr != b.my_ptr; }; 
    
    };
    
    bool reject(std::string str);
    bool isrejected = false;
    std::string rejectstr = "PLACEHOLDER";*/
    //end hw7 operators
};

std::ostream &operator<<(std::ostream &, const Words &);
