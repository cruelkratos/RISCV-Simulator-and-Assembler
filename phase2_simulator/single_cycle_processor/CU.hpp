#include<vector>
#include<bitset>
#include<string>
#include<GPR.hpp>
class CU{
    private:
    std::string controlword;
    public:
    CU(){
        this->controlword = "";
    }
    std::string get_controlWord(std::bitset<7> opcode , RF& RegSet){
        // we make changes to the actual GeneralPurpose Registers :)
        std::string lol = opcode.to_string();
        if(lol == "0110011"){
            //r type
            controlword.push_back('1');//access GPR
            controlword.push_back('0');//no immi
            controlword.push_back("10");
            controlword.push_back('0');//no writing
            controlword.push_back('0');//mem_read_no
            controlword.push_back('1');//write to GPR
            controlword.push_back('0');
        }

        else if(lol == "0010011"){
            // i type!
            controlword.push_back('0');//access GPR
            controlword.push_back('1');//yo immi
            controlword.push_back("10");
            controlword.push_back('0');//no writing
            controlword.push_back('0');//mem_read_no
            controlword.push_back('1');//write to GPR
            controlword.push_back('0');
        }
        else if(lol == "0000011"){
            //loading from mem
            controlword.push_back('0');//access GPR
            controlword.push_back('1');//yo immi
            controlword.push_back("00");
            controlword.push_back('0');//no writing
            controlword.push_back('1');//mem_read_yes
            controlword.push_back('1');//write to GPR
            controlword.push_back('0');
        }
        else if(lol == "0100011"){
            //store in mem
            controlword.push_back('1');//access GPR
            controlword.push_back('1');//yo immi
            controlword.push_back("00");
            controlword.push_back('1');//no writing
            controlword.push_back('1');//mem_read_yes
            controlword.push_back('0');//write to GPR
            controlword.push_back('0');
        }
        else if(lol =="1100011"){
            //later
        }
        else if(lol == "1100111"){
            //later
        }
        else{
            std::cerr<<"INVALID INSTRUCTION!"<<std::endl;
        }
        std::string news = controlword;
        controlword = "";
        return news;
    }


};