#include "json.h"

#include <algorithm>

namespace cpp_json{

JsonValue& JsonValue::operator[](const std::string& key){
    _JsonDict* dict_ptr = std::get_if<_JsonDict>(&_values);
    if (!dict_ptr){
        throw JsonKeyErrorException();
    }
    if (std::find(dict_ptr->begin(), dict_ptr->end(), key) == dict_ptr->end()){
        throw JsonKeyErrorException();
    }
}

}