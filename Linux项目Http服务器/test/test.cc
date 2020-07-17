#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;


int main()
{
    string str = "Content-Length: 30";
    std::size_t pos = str.find(": ");
    if(std::string::npos == pos){
        return 1;
    }

    string key = str.substr(0, pos);
    string value = str.substr(pos+2);

    cout <<"key : " << key << endl;
    cout << "value : " << value << endl;
    unordered_map<string, string> m;
 //   m.insert(std::make_pair<std::string, std::string>(key, value));
    m.insert({key, value});

    return 0;

}
