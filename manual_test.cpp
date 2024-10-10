#include "json.h"

#include <iostream>
#include <string>

using namespace cpp_json;
using namespace std::string_literals;

int main(){
    JsonDict dict;
    dict["name"] = JsonObject("Max");
    dict["lastname"] = JsonObject("Jonson"s);
    dict["age"] = JsonObject(34);
    dict["a"] = JsonDict{
        {"b", 1},
        {"c", 2},
        {"d", JsonDict{
                {"e", 251},
                {"m", JsonList{1,21,3}}
              }
        },
        {"booleans", JsonList{false, true, false}}
    };
    
    std::cout << to_string(dict["name"].get_value_type()) << "\n";
    std::cout << to_string(JsonObject(dict)) << "\n";
}