#pragma GCC optimize("O3")
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<bits/stdc++.h>
using namespace std;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

class Assembler{
    public:
    unordered_map<string,string> opcodes;
    unordered_map<string,string> registers;
};
    

int main(void){
    ios::sync_with_stdio(false);
    Assembler a;
    a.opcodes["add"] = "0110011";a.opcodes["sub"] = "0110011";
    a.opcodes["lw"] = "0000011";
    
    return 0;
}