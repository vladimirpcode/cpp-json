#include "../json.h"
#include <string>
#include <iostream>

using namespace std::string_literals;

int main(int argc, char** argv){
    try{
        cpp_json::JsonObject json_object = cpp_json::parse_json(std::string(argv[1]));
        std::cout << cpp_json::to_string(json_object);
    } catch (std::exception e){
        std::cout << "<error>\n"; 
    }
    return 0;
}