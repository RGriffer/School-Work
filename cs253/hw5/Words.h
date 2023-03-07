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
};

std::ostream &operator<<(std::ostream &, const Words &);
