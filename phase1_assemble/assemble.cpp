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
std::string check_bin(int num, int size) {
    // Create a std::bitset of the desired size
    std::bitset<11> binary(num);

    // Convert the bitset to a string
    std::string binaryStr = binary.to_string();

    // Truncate or pad with leading zeros to match the specified size
    if (binaryStr.length() > size) {
        binaryStr = binaryStr.substr(binaryStr.length() - size);
    } else if (binaryStr.length() < size) {
        binaryStr = std::string(size - binaryStr.length(), '0') + binaryStr;
    }

    return binaryStr;
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
        out+= check_bin(this->registers[v[1]],5); //encodes rd(destination register location)
        if(v.size()==3){
            
        if(v[0][0] == 'l'){
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
            break;}    
        // rs1:
        std::string s3;
        bool lol = false;
        std:: string imm;
        for(int i =0;i<v[2].size();i++){
            if(v[2][i]!=')' && lol) s3.push_back(v[2][i]);
            if(v[2][i]=='('){
                lol = true;
            }
            if(!lol){
                imm.push_back(v[2][i]);
            }
        }
        if(this->registers.find(s3) == this->registers.end()){std::cerr << "Invalid input." << std::endl;
        out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";return;}
        out+= check_bin(this->registers[s3],5);
        int c = std::stoi(imm);
        std::string x = check_bin(c,11);
        out +=x;}
            else{
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
            break;}}}
        else{
            //R type // I Type // Btype


        }}
};
    

int main(void){
    std::ios::sync_with_stdio(false);
    Assembler a;
    a.opcodes["add"] = "0110011";a.opcodes["sub"] = "0110011";
    a.opcodes["lw"] = "0000011";a.registers["t1"] = 6;a.registers["a0"] =10;
    a.registers["a1"] =11;a.opcodes["lh"] = "0000011";a.opcodes["lb"] = "0000011";a.opcodes["sw"] ="0100011";a.opcodes["sh"] ="0100011";a.opcodes["sb"] ="0100011";
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