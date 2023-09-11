#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include<fstream>

class Assembler {
public:
    Assembler();

    void encodeInstruction(const std::string& instruction);
    std::unordered_map<std::string, std::string> opcodes;
    std::unordered_map<std::string, int> registers;


    std::ofstream fout;

    std::vector<std::string> tokenizeInstruction(const std::string& instruction);
    std::string encode(const std::vector<std::string>& tokens);
    std::string check_bin(int num, int size);
    std::vector<std::string> opgen(const std::string& input);
    // Other private functions and member variables if needed
};

#endif // ASSEMBLER_HPP
