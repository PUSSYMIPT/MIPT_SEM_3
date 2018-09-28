//Run-report here: https://contest.yandex.ru/contest/9093/run-report/12054988/

#include <iostream>
#include <regex>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string& input, const std::string& splitExp) {
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(splitExp);
    std::sregex_token_iterator
    first{input.begin(), input.end(), re, -1},
    last;
    return {first, last};
}


std::string prefixToString (const std::vector<short>& prefixValues) {
    std::vector<bool> usedChars(30, false);
    std::string recycledString = "";
    std::vector<int> numbersOfChar(prefixValues.size(), 0);  // здесь будем хранить номер символа в алфавите
    short maxChar = 1;
    short prev = prefixValues[0];
    for(size_t i = 1; i < prefixValues.size(); ++i) {
        if (prefixValues[i] == 0){
            usedChars.assign(30, false);
            while (prev > 0) {
                usedChars[numbersOfChar[prev]] = true;
                prev = prefixValues[prev - 1];
            }
            numbersOfChar[i]= -1;
            for (short j = 1; j < maxChar; ++j) {
                if (!usedChars[j]) {
                    numbersOfChar[i] = j;
                    break;
                }
            }
            if (numbersOfChar[i] == -1) {
                numbersOfChar[i] = maxChar++;
            }
        }
        else {
            numbersOfChar[i] = numbersOfChar[prefixValues[i] - 1];
        }
        prev = prefixValues[i];
    }
    for (const auto & numChar: numbersOfChar) {
        recycledString += static_cast<char>(static_cast<short>('a') + numChar);
    }
    return recycledString;
}


std::vector<short> zToPrefix(const std::vector<short>& zFuncValues) {
    std::vector<short> prefixValues (zFuncValues.size(), 0);
    for(int i = 1; i < zFuncValues.size(); ++i) {
        if (zFuncValues[i] != 0) {
            for(short j = zFuncValues[i] - 1; j >= 0 && prefixValues[j + i] == 0; --j) {
                prefixValues[j + i] = j + 1;
            }
        }
    }
    return prefixValues;
}


int main(int argc, const char * argv[]) {
    std::vector<short> zValues;
    std::string values;
    std::getline(std::cin, values);
    for(const auto& sValue : split(values, " ")) {
        zValues.push_back(std::stoi(sValue));
    }
    std::vector<short> prefixValues = zToPrefix(zValues);
    std::cout << prefixToString(prefixValues);
    return 0;
}