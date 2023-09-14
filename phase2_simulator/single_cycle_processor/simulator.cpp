#include<fstream>
#include<vector>
#include<ALU.hpp>
#include<../../phase1_assemble/assemble.hpp>
#include<bitset>
#include<memory.hpp>
#include<GPR.hpp>

int main(void){
    std::vector<std::string> encodings;
    std:: ifstream fin("encoding.txt");
    ALU myALU; //Alu obj
    RF RegSet;// Register obj
    std::string s;
    while (getline(fin,s))
        encodings.push_back(s);
    for(auto it: encodings){
        std::string q = it.substr(0,7);
         int nig = std::stoi(q, nullptr, 2);
        std::bitset<7> opcode(nig);
        myALU.ALUOP(opcode,RegSet);
    }
    return 0;
}