#pragma once

#include <string>
#include <map>
#include <variant>
#include <vector>
#include <cstdint>

namespace cpp_json{

class JsonKeyErrorException : public std::exception{

};

class JsonParsingErrorException : public std::exception{

};

using _JsonDict = std::map<std::string, JsonValue>;

using _JsonVariant = std::variant<
    std::string, 
    int64_t, 
    std::vector<JsonValue>, 
    double, 
    _JsonDict
>;

class JsonValue{
public:
    JsonValue& operator[](const std::string& key);
    void operator=(JsonValue& value);
    int64_t get_int();
    double get_double();
    std::string get_string();
    std::vector<JsonValue> get_list();
    std::map<std::string, JsonValue> get_dict();
private:
    _JsonVariant _values;
};

class JsonObject{
public:
    JsonObject();
    JsonObject(const std::string& json_str);
    JsonValue operator[](const std::string key);
private:
    std::map<std::string, JsonValue> _values;
};



}