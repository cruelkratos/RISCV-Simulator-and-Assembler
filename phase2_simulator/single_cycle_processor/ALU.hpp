#include<iostream>
#include<vector>
#include<bitset>
#include<string>
#include<GPR.hpp>
class ALU{
    public:
    std::bitset<32> ALUOP(std::bitset<7> opcode , RF& RegSet){
        // we make changes to the actual GeneralPurpose Registers :)
        std::string lol = opcode.to_string();
        if(lol == "0110011"){

        }

        else if(lol == "0010011"){

        }
        else if(lol == "0000011"){

        }
        else if(lol == "0100011"){

        }
        else if(lol =="1100011"){

        }
        else if(lol == "1100111"){

        }
        else{
            std::cerr<<"INVALID INSTRUCTION!"<<std::endl;
        }
    }

};