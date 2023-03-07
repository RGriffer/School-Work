#include <vector>
#include <iostream>
#include <string>

class Words {
    
public:
    std::vector<std::string> lexical;
    Words(std::string input);
    Words() = delete;
    Words(const Words &);
    Words &operator=(const Words &);
    ~Words();
    void analyze(std::string input);
    size_t size() const;
    bool empty() const;
    bool get(size_t n, std::string &, bool &) const;
    std::vector<bool> escaped;
};

std::ostream &operator<<(std::ostream &, const Words &);
