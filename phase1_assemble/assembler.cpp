#pragma GCC optimize("O3")
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<bitset>
#include <sstream>
#include<vector>
#include<string>
#include "assemble.hpp"

Assembler::Assembler() {
    // Constructor initialized in hpp file
  
}

std::string Assembler::check_bin(int num, int size) {
    // Create a std::bitset of the desired size
    std::bitset<11> binary(num);
    // Convert the bitset to a string
    std::string binaryStr = binary.to_string();
    // Truncate or pad with leading zeros to match the specified size
    if (binaryStr.length() > size) 
    binaryStr = binaryStr.substr(binaryStr.length() - size);
    else if (binaryStr.length() < size) 
    binaryStr = std::string(size - binaryStr.length(), '0') + binaryStr;

    return binaryStr;
}

std::string Assembler::encode(const std::vector<std::string>& v) {
    // Implementation of encode
    if (v.size() < 3) {
  std::cerr << "Invalid" << std::endl;
  return;
}
std::string out;
out += this -> opcodes[v[0]]; //encodes opcode
if (this -> registers.find(v[1]) == this -> registers.end()) {
  std::cerr << "Invalid Instruction lol" << std::endl;
  for (int i = 0; i < 32; i++) {
    fout << "X";
  }
  fout << std::endl;
  return;
}
out += check_bin(this -> registers[v[1]], 5); //encodes rd(destination register location)
if (v.size() == 3) {

  if (v[0][0] == 'l') {
    switch (v[0][1]) {
    case 'w':
      out += "010";
      break;
    case 'h':
      out += "001";
      break;
    case 'b':
      out += "000";
      break;
    default:
      std::cerr << "Invalid input." << std::endl;
      out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
      break;
    }
    // rs1:
    std::string s3;
    bool lol = false;
    std::string imm;
    for (int i = 0; i < v[2].size(); i++) {
      if (v[2][i] != ')' && lol) s3.push_back(v[2][i]);
      if (v[2][i] == '(') {
        lol = true;
      }
      if (!lol) {
        imm.push_back(v[2][i]);
      }
    }
    if (this -> registers.find(s3) == this -> registers.end()) {
      std::cerr << "Invalid input." << std::endl;
      out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
      return;
    }
    out += check_bin(this -> registers[s3], 5);
    int c = std::stoi(imm);
    std::string x = check_bin(c, 11);
    out += x;
  } else {
    //store word
    switch (v[0][1]) {
    case 'w':
      out += "010";
      break;
    case 'h':
      out += "001";
      break;
    case 'b':
      out += "000";
      break;
    default:
      std::cerr << "Invalid input." << std::endl;
      out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
      break;
    }
  }
} else {
  //R type // I Type // Btype

}
return out;
}



std::vector<std::string> Assembler::opgen(const std::string& input) {
    // Implementation of opgen
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string t;
    while (std::getline(ss, t, ',')) 
        result.push_back(t);
    
    return result;

}

int main() {
    Assembler a;
    std::string s;
    std:: ifstream fin("instruction.txt");
    std:: ofstream fout("encodings.txt");
    while (getline(fin, s)) {
        std::vector<std::string> inst =  a.opgen(s);
        if(a.opcodes.find(inst[0])==a.opcodes.end()){
            std::cerr<<"Invalid Instruction lol"<<std::endl;
            for(int i =0;i<32;i++){fout<<"X";}fout<<std::endl;
        }
        else{
            fout<<a.encode(inst)<<std::endl;
        }
    }
    fin.close();    
    fout.close();
    return 0;
}