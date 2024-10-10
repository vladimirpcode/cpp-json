# cpp-json

Пример использования. Словарям и спискам лучше указывать тип вручную (как в примере) и не полагаться на вывод типов. Т.е. не {...}, а JsonDict{...}

Работа осуществляется через объекты типа JsonObject и функции 
```cpp
JsonObject parse_json(const std::string& json_str);
std::string to_string(JsonObject json_object);
```

```cpp
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

    std::cout << "\n\n\n";
    std::cout << to_string(JsonObject(dict)) << "\n";
```

Вывод:

```
целое число
21
foreach: 1
foreach: 21
foreach: 3



{
   "a": {
      "b": 1,
      "c": 2,
      "d": {
         "e": 251,
         "m": [
            1,
            21,
            3
         ]
      }
   },
   "age": 34,
   "name": "Max"
}
```