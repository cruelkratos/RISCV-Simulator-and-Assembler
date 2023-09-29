#include<fstream>
#include<vector>
#include<ALU.hpp>
#include<../../phase1_assemble/assemble.hpp>
#include<bitset>
#include<memory.hpp>
#include<GPR.hpp>
#include<CU.hpp>

int main(void){
    std::vector<std::string> encodings;
    std:: ifstream fin("encoding.txt");
    ALU myALU; //Alu obj
    RF RegSet;// Register obj
    CU myControlUnit;
    std::string s;
    while (getline(fin,s))
        encodings.push_back(s);
    for(auto it: encodings){
        std::string q = it.substr(0,7);
         int nig = std::stoi(q, nullptr, 2);
        std::bitset<7> opcode(nig);
        auto controlWord = myControlUnit.get_controlWord(opcode,RegSet);
    }
    fin.close();
    return 0;
}