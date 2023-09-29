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
        std::bitset<7> a("0110011");
        auto controlWord = myControlUnit.get_controlWord(opcode,RegSet);
        std::string func7 ="XXXXXXX";
        if(opcode==a){
            func7 = it.substr(25,32);
        }
        int rs1 = std::stoi(it.substr(15,20),nullptr,2);
        int rs2 = (controlWord[0]-'1') ? std::stoi(it.substr(20,25),nullptr,2) : std::stoi(it.substr(20,32),nullptr,2);
        std::string func3 = it.substr(12,15);
        myALU.ALUAction(func7,func3,controlWord,rs1,rs2);
    }
    fin.close();
    return 0;
}