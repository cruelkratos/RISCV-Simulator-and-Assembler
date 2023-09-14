#include<vector>
#include<bitset>
class RF{
    private:
    std::vector<std::bitset<32>> Register;
    public:
    RF(){
        Register.resize(32);
    }
    ~RF(){
        Register.clear();
    }

};