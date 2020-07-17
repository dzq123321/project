#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class Util{
    public:
        static void MakeKV(std::unordered_map<std::string, std::string> &header_kv, std::string &sub){
            std::size_t pos = str.find(": ");
            if(std::string::npos == pos){
                return;
            }

            string key = str.substr(0, pos);
            string value = str.substr(pos+2);
            header_kv.insert({key, value});
        }//Content-Length: 30
};
