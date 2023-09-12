#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include<fstream>

class Assembler {
public:
    Assembler(){
  this->opcodes["add"] = "0110011";
  this->opcodes["sub"] = "0110011";
  this->opcodes["lw"] = "0000011";
  this->registers["t1"] = 6;
  this->registers["a0"] = 10;
  this->registers["a1"] = 11;
  this->opcodes["lh"] = "0000011";
  this->opcodes["lb"] = "0000011";
  this->opcodes["sw"] = "0100011";
  this->opcodes["sh"] = "0100011";
  this->opcodes["sb"] = "0100011";
  this->registers["ra"] = 1;
  this->registers["t0"] = 5;
  this->registers["t2"] = 7;
    }

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
