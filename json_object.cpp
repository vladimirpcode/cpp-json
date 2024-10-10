#include "json.h"

#include <algorithm>
#include <string>

using namespace std::string_literals;

namespace cpp_json{

std::string to_string(JsonValueType value_type){
    switch (value_type){
        case JsonValueType::DICT:
            return "словарь"s;
        case JsonValueType::DOUBLE:
            return "число с плавающей точкой"s;
        case JsonValueType::INT:
            return "целое число"s;
        case JsonValueType::LIST:
            return "массив"s;
        case JsonValueType::STRING:
            return "строка"s;
        case JsonValueType::BOOL:
            return "булев тип";
        case JsonValueType::NULL_VALUE:
            return "null-значение";
    }
    return "неизвестный тип"s;
}

JsonObject::JsonObject()
    : _value_type(JsonValueType::DICT)
{

}


JsonObject::JsonObject(int64_t value){
    set_int(value);
}

JsonObject::JsonObject(int value){
    set_int(value);
}

JsonObject::JsonObject(double value){
    set_double(value);
}

JsonObject::JsonObject(const std::string& value){
    set_string(value);
}


JsonObject::JsonObject(const char* value){
    set_string(value);
}

JsonObject::JsonObject(const JsonDict& value){
    set_dict(value);
}

JsonObject::JsonObject(const JsonList& value){
    set_list(value);
}


JsonObject::JsonObject(bool value){
    set_bool(value);
}


JsonObject& JsonObject::operator[](const std::string& key){
    if (_value_type != JsonValueType::DICT){
        throw JsonValueTypeErrorException("ожидался элемент типа 'словарь', но "s + to_string(_value_type));
    }
    auto iter = _dict_value.find(key);
    if (iter == _dict_value.end()){
        throw JsonKeyErrorException("Не найден ключ "s + key + " в словаре"s);
    }
    return iter->second;
}


JsonObject& JsonObject::operator[](int64_t index){
    if (_value_type != JsonValueType::LIST){
        throw JsonValueTypeErrorException("ожидался масив в операторе [], но "s + to_string(_value_type));
    }
    if (index >= _list_value.size()){
        throw JsonIndexOfBoundException("индекс "s + std::to_string(index) + " выходит за границы массива размером "s + std::to_string(_list_value.size()));
    }
    return _list_value[index];
}


JsonObject& JsonObject::operator=(int64_t value){
    set_int(value);
    return *this;
}

JsonObject& JsonObject::operator=(double value){
    set_double(value);
    return *this;
}

JsonObject& JsonObject::operator=(std::string value){
    set_string(value);
    return *this;
}

JsonObject& JsonObject::operator=(const JsonList& value){
    set_list(value);
    return *this;
}

JsonObject& JsonObject::operator=(const JsonDict& value){
    set_dict(value);
    return *this;
}


JsonObject& JsonObject::operator=(bool value){
    set_bool(value);
    return *this;
}


JsonObject& JsonObject::operator=(nullptr_t value){
    set_null();
    return *this;
}

int64_t JsonObject::get_int(){
    if (_value_type != JsonValueType::INT){
        throw JsonValueTypeErrorException("ожидался элемент типа 'целое число', но "s + to_string(_value_type));
    }
    return _int_value;
}

double JsonObject::get_double(){
    if (_value_type != JsonValueType::DOUBLE){
        throw JsonValueTypeErrorException("ожидался элемент типа 'число с плавающей точкой', но "s + to_string(_value_type));
    }
    return _double_value;
}

std::string JsonObject::get_string(){
    if (_value_type != JsonValueType::STRING){
        throw JsonValueTypeErrorException("ожидался элемент типа 'строка', но "s + to_string(_value_type));
    }
    return _string_value;
}

JsonList& JsonObject::get_list(){
    if (_value_type != JsonValueType::LIST){
        throw JsonValueTypeErrorException("ожидался элемент типа 'лист', но "s + to_string(_value_type));
    }
    return _list_value;
}

JsonDict& JsonObject::get_dict(){
    if (_value_type != JsonValueType::DICT){
        throw JsonValueTypeErrorException("ожидался элемент типа 'словарь', но "s + to_string(_value_type));
    }
    return _dict_value;
}

bool JsonObject::get_bool(){
    if (_value_type != JsonValueType::BOOL){
        throw JsonValueTypeErrorException("ожидался элемент типа 'булев тип', но "s + to_string(_value_type));
    }
    return _bool_value;
}

void JsonObject::set_int(int64_t value){
    _value_type = JsonValueType::INT;
    _int_value = value;
}

void JsonObject::set_double(double value){
    _value_type = JsonValueType::DOUBLE;
    _double_value = value;
}

void JsonObject::set_string(const std::string& value){
    _value_type = JsonValueType::STRING;
    _string_value = value;
}

void JsonObject::set_list(const JsonList& value){
    _value_type = JsonValueType::LIST;
    _list_value = value;
}

void JsonObject::set_dict(const JsonDict& value){
    _value_type = JsonValueType::DICT;
    _dict_value = value;
}


void JsonObject::set_bool(bool value){
    _value_type = JsonValueType::BOOL;
    _bool_value = value;
}

void JsonObject::set_null(){
    _value_type = JsonValueType::NULL_VALUE;
}

JsonValueType JsonObject::get_value_type() const{
    return _value_type;
}

}