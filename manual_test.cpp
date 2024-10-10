#include "json.h"

#include <iostream>
#include <string>

using namespace cpp_json;

int main(){
    JsonDict dict;
    dict["name"] = JsonObject("Max");
    dict["age"] = JsonObject(34);
    dict["a"] = JsonDict{
        {"b", 1},
        {"c", 2},
        {"d", JsonDict{
                {"e", 251},
                {"m", JsonList{1,21,3}}
            }
        }
        
    };
    std::cout << to_string(dict["a"]["d"]["m"][1].get_value_type()) << "\n";
    std::cout << dict["a"]["d"]["m"][1].get_int() << "\n";
    for (auto& i : dict["a"]["d"]["m"].get_list()){
        std::cout << "foreach: " << i.get_int() << "\n";
    }
}