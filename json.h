#pragma once

#include <string>
#include <map>
#include <variant>
#include <vector>
#include <cstdint>
#include <string>

namespace cpp_json{

class JsonKeyErrorException : public std::exception{
public:
    JsonKeyErrorException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override  {
        return _msg.c_str();
    }
private:
    std::string _msg;
};

class JsonParsingErrorException : public std::exception{
public:
    JsonParsingErrorException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override  {
        return _msg.c_str();
    }
private:
    std::string _msg;
};

class JsonValueTypeErrorException : public std::exception{
public:
    JsonValueTypeErrorException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override  {
        return _msg.c_str();
    }
private:
    std::string _msg;
};

class JsonIndexOfBoundException : public std::exception{
public:
    JsonIndexOfBoundException(const std::string& msg) : _msg(msg){}
    virtual const char* what() const noexcept override  {
        return _msg.c_str();
    }
private:
    std::string _msg;
};

class JsonObject;
using JsonList = std::vector<JsonObject>;
using JsonDict = std::map<std::string, JsonObject>;

enum class JsonValueType{
    INT,
    DOUBLE,
    STRING,
    LIST,
    DICT,
    BOOL,
    NULL_VALUE
};

std::string to_string(JsonValueType value_type);

class JsonObject{
    friend JsonObject parse_json(const std::string& json_str);
    friend bool operator==(const JsonObject& lhs, const JsonObject& rhs);
public:
    JsonObject();
    JsonObject(int64_t value);
    JsonObject(int value);
    JsonObject(double value);
    JsonObject(bool value);
    JsonObject(const std::string& value);
    JsonObject(const char* value);
    JsonObject(const JsonList& value);
    JsonObject(const JsonDict& value);
    JsonObject(nullptr_t value);
    JsonObject& operator=(int64_t value);
    JsonObject& operator=(int value);
    JsonObject& operator=(double value);
    JsonObject& operator=(bool value);
    JsonObject& operator=(const std::string& value);
    JsonObject& operator=(const char* value);
    JsonObject& operator=(const JsonList& value);
    JsonObject& operator=(const JsonDict& value);
    JsonObject& operator=(nullptr_t value);
    void set_int(int64_t value);
    void set_int(int value);
    void set_double(double value);
    void set_bool(bool value);
    void set_string(const std::string& value);
    void set_string(const char* value);
    void set_list(const JsonList& value);
    void set_dict(const JsonDict& value);
    void set_null();
    int64_t get_int();
    double get_double();
    bool get_bool();
    std::string get_string();
    JsonList& get_list_by_ref();
    JsonDict& get_dict_by_ref();
    const JsonList& get_list();
    const JsonDict& get_dict();
    JsonObject& operator[](const std::string& key);
    JsonObject& operator[](int64_t index);
    JsonValueType get_value_type() const;
private:
    JsonValueType _value_type;
    int64_t _int_value;
    double _double_value;
    std::string _string_value;
    JsonList _list_value;
    JsonDict _dict_value;
    bool _bool_value;
};

bool operator==(const JsonObject& lhs, const JsonObject& rhs);

JsonObject parse_json(const std::string& json_str);
std::string to_string(JsonObject json_object);
std::string to_string(bool value);

} 