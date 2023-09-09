#pragma GCC optimize("O3")
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<bitset>
#include <sstream>
#include<vector>
#include<string>
// using namespace std;
std::ofstream fout("encoded.txt");
std::ifstream fin("instruction.txt");
std::string reg_bin(int num) {
    // Ensure that the number is within the valid 5-bit range (0 to 31)
    if (num < 0 || num > 31) {
        return "XXXXX";
    }
    std::bitset<5> binary(num);
    return binary.to_string();
}


class Assembler{
    public:
    std::unordered_map<std::string,std::string> opcodes;
    std::unordered_map<std::string,int> registers;
    
    std::vector<std::string> opgen(const std::string& input) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string t;

    while (std::getline(ss, t, ',')) {
        result.push_back(t);
    }

    return result;}

    void enCode(std::vector<std::string> &v){
        if(v.size()<3){
            std::cerr<<"Invalid"<<std::endl;
            return;
        }
        std::string out;
        out += this->opcodes[v[0]]; //encodes opcode
        if(this->registers.find(v[1])== this->registers.end()){
            std::cerr<<"Invalid Instruction lol"<<std::endl;
            for(int i =0;i<32;i++){fout<<"X";}fout<<std::endl;
            return;
        }
        out+= reg_bin(this->registers[v[1]]); //encodes rd(destination register location)
        if(v.size()==3){
            
            if(v[0][0] == 'l'){

        switch (v[0][1]) {
        case 'w':
            out += "000";
            break;

        case 'd':
            out += "011";
            break;

        case 'h':
            out += "001";
            break;

        case 'b':
            out += "010";
            break;

        default:
            std::cerr << "Invalid input." << std::endl;
            out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            break;
    }
            }
            else{
                //store word

            }

            
        }

        else{

        }
        
    }
};
    

int main(void){
    std::ios::sync_with_stdio(false);
    Assembler a;
    a.opcodes["add"] = "0110011";a.opcodes["sub"] = "0110011";
    a.opcodes["lw"] = "0000011";a.registers["t1"] = 6;a.registers["a0"] =10;
    a.registers["a1"] =11;a.opcodes["ld"] = "0000011";a.opcodes["lh"] = "0000011";a.opcodes["lb"] = "0000011";a.opcodes["sw"] ="0100011";a.opcodes["sd"] ="0100011";a.opcodes["sh"] ="0100011";
    a.opcodes["sb"] ="0100011";
    a.registers["ra"] = 1;a.registers["t0"] = 5;a.registers["t2"] = 7;
    
    std::string s;


    while(getline(fin,s)){
        std::vector<std::string> inst =  a.opgen(s);
        if(a.opcodes.find(inst[0])==a.opcodes.end()){
            std::cerr<<"Invalid Instruction lol"<<std::endl;
            for(int i =0;i<32;i++){fout<<"X";}fout<<std::endl;
        }
        else{
            
        }
    }
    
    return 0;
}