#include<bits/stdc++.h>
#include<fstream>
std::vector<std::bitset<32>> Register(32);
std::vector<int> M(1e5, 0);
class Fetch{
    public:
    int PC;
    bool NOP;
    Fetch(){
        NOP=false;
        PC = 0;
    }

};

class Decode{
    public:
    std::bitset<32> Inst;
    bool NOP;
    void work(Execute & ex){
        std::bitset<7> opcode(this->Inst.to_string().substr(0, 7));
        std::bitset<5> rd(this->Inst.to_string().substr(7,12));
        std::bitset<3> func3(this->Inst.to_string().substr(12,15));
        std::bitset<12> IMM(this->Inst.to_string().substr(20, 32));
        std::bitset<5> RS1(this->Inst.to_string().substr(15, 20));
        std::bitset<5> RS2(this->Inst.to_string().substr(20, 25));
        std::bitset<7> func7(this->Inst.to_string().substr(25, 32));
        ex.func3 =  func3;
        ex.opcode = opcode;
        ex.Rd =  rd;
        ex.IMM = IMM;
        ex.rs1 = RS1;
        ex.rs2 = RS2;
        ex.func7 = func7;
    }
};

class Execute{
    public:
    std::bitset<7> opcode;
    std::bitset<3> func3;
    std::bitset<5> Rd;
    std::bitset<5> rs1;
    std::bitset<12> IMM;
    std::bitset<5> rs2;
    std::bitset<7> func7;
    bool read;
    bool write;
    bool NOP;
    int ALUOp;
    bool enable;
    void exe(WB & wb1 , Memory & m1){
        if(opcode == std::bitset<7>("0110011")){
            //R-type
            int res=0;
            if(func3==std::bitset<3>("000")){
                if(func7 ==std::bitset<7>("0000000")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) + static_cast<int>(Register[static_cast<int>(rs2.to_ulong())].to_ulong());
                wb1.reg_write(Rd,res);
            }
            else{
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) - static_cast<int>(Register[static_cast<int>(rs2.to_ulong())].to_ulong());
                wb1.reg_write(Rd,res);
            }
            }
            else if(func3==std::bitset<3>("100")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) ^ static_cast<int>(Register[static_cast<int>(rs2.to_ulong())].to_ulong());
                wb1.reg_write(Rd,res);
            }
            else if(func3==std::bitset<3>("110")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) | static_cast<int>(Register[static_cast<int>(rs2.to_ulong())].to_ulong());
                wb1.reg_write(Rd,res);
            }
            else if(func3==std::bitset<3>("111")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) & static_cast<int>(Register[static_cast<int>(rs2.to_ulong())].to_ulong());
                wb1.reg_write(Rd,res);
            }
            else{
                std::cerr<<"The Simulator only supports addition/subtraction/xor/and/or"<<std::endl;
            }
        }
        else if(opcode == std::bitset<7>("0010011")){
            //I-type
            int res=0;
            if(func3==std::bitset<3>("000")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) + static_cast<int>(IMM.to_ulong());
                wb1.reg_write(Rd,res);
            }
            else if(func3==std::bitset<3>("100")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) ^ static_cast<int>(IMM.to_ulong());
                wb1.reg_write(Rd,res);
            }
            else if(func3==std::bitset<3>("110")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) | static_cast<int>(IMM.to_ulong());
                wb1.reg_write(Rd,res);
            }
            else if(func3==std::bitset<3>("111")){
                res = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) & static_cast<int>(IMM.to_ulong());
                wb1.reg_write(Rd,res);
            }
            else{
                std::cerr<<"The Simulator only supports addition/xor/and/or"<<std::endl;
            }

        }
        else if(opcode == std::bitset<7>("0000011")){
            //I-type but memory load
            int loc = static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong()) + static_cast<int>(IMM.to_ulong());
            wb1.reg_write(Rd,M[loc]);

        }
        else if (opcode == std::bitset<7>("0100011")){
            //S-type
            m1.work_is_going_on(rs1,rs2,static_cast<int>(IMM.to_ulong()));
        }
        else{
            //BT
            std::cerr<<"wrong instruction provided"<<std::endl;
        }
    }

};

class Memory{
    public:
    std::bitset<32> ALURes;
    std::bitset<32> Data;
    std::bitset<5>   rs;
    std::bitset<5>   rt;
    std::bitset<5> reg_wrt_add;
    bool read;
    bool write;
    bool NOP;
    bool enable;
    void work_is_going_on(std::bitset<5> rs1, std::bitset<5> rs2 , int imm){
        M[imm + static_cast<int>(Register[static_cast<int>(rs1.to_ulong())].to_ulong())] = static_cast<int>(Register[static_cast<int>(rs2.to_ulong())].to_ulong());
    }
};

class WB{
    public:
    std::bitset<5>   rs;
    std::bitset<5>   rt;
    std::bitset<5> reg_wrt_add;
    bool enable;
    bool NOP;
    void reg_write(std::bitset<5> Rd, int res){
        Register[static_cast<int>(Rd.to_ulong())] = std::bitset<32>(res);//write back stage
    }
};


signed main(void){
    std::ifstream fin;
    Fetch fetch;
    Decode decode;
    Execute execute;
    Memory mem;
    WB write_back;
    fin.open("instructions.txt");
    std::bitset<32> inst;
    while(fin>>inst){
        fetch.PC +=4;
        decode.Inst = inst;
        decode.work(execute);
        execute.exe(write_back,mem);
    }
    return 0;
}