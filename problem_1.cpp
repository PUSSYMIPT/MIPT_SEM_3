//Run report here: https://contest.yandex.ru/contest/9093/run-report/12027609/

#include <array>
#include <iostream>
#include <string>
#include <vector>

class TemplateMatch{
public:
    TemplateMatch(std::string_view pattern): pattern(pattern) {
        prefixValue = prefixFunction(pattern);
    }
    
    
    void indexMatch(std::istream & inpStream, std::ostream & outStream) {
        char symbol = inpStream.get();
        auto pattern_size = pattern.length();
        size_t cur = 0, i = 1;
        inpStream.get(symbol);  // пропускаем '\n'
        short it = 0;
        while (symbol != '\n') {
            cur = onlinePrefix(cur, symbol, pattern);
            if (cur == pattern_size){
                ans[it] = i - pattern_size;
                ++it;
            }
            ++i;
            inpStream.get(symbol);
            if (it > 50){
                this->printAns(outStream, 51);
                it = 0;
            }
        }
        this->printAns(std::cout, it);
    }
private:
    std::string_view pattern;
    std::vector<size_t> prefixValue;
    std::array<size_t, 51> ans;
    
    
    std::vector<size_t> prefixFunction(std::string_view input) {
        prefixValue.assign (input.size(), 0);
        size_t cur;
        for (size_t i = 1; i < input.size(); ++i) {
            cur = prefixValue[i-1];
            while (input[i] != input[cur] && cur != 0) {
                cur = prefixValue[cur - 1];
            }
            if (input[i] == input[cur]) {
                ++cur;
            }
            prefixValue[i] = cur;
        }
        return prefixValue;
    }
    
    
    size_t onlinePrefix(size_t prev, char curCh, std::string_view pattern) {
        size_t cur = prev;
        while (curCh != pattern[cur] && cur > 0) {
            cur = prefixValue[cur - 1];
        }
        if (curCh == pattern[cur]) {
            return ++cur;
        }
        return cur;
    }
    
    
    void printAns(std::ostream & stream, short iter) {
        for(short i = 0; i < iter; ++i)
            stream << ans[i] << ' ';
    }
};


int main() {
    std::string pattern;
    std::cin >> pattern;
    TemplateMatch  patternMatch(pattern);
    patternMatch.indexMatch(std::cin, std::cout);
}