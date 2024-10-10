#include "json.h"

#include <utility>
#include <string>

using namespace std::string_literals;

namespace cpp_json{

constexpr char EOT = 4;

bool is_whitespace(char c){
    return c == 32 || c == 9 || c == 13 || c == 10;
}

bool is_number(char c){
    return c >= '0' && c <= '9';
}

class ParsingWrapper{
public:
    char ch;
    ParsingWrapper(const std::string& source) : _source(source), _index(0){
        get_next();
    }
    void get_next(){
        if (_index >= _source.size()){
            ch = EOT;
            return;
        }
        ch = _source[_index];
        _index++;
        while (is_whitespace(ch)){
            if (_index >= _source.size()){
                ch = EOT;
                return;
            }
            ch = _source[_index];
            _index++;
        }
    }
    void check(char c){
        if (ch != c){
            throw JsonParsingErrorException("ожидалось '"s  + c + "' но '"s + ch + "'"s);
        }
        get_next();
    }
private:
    std::string _source;
    int64_t _index;
};

JsonObject parse_value(ParsingWrapper& wrap);
std::pair<std::string, JsonObject> parse_dict_item(ParsingWrapper& wrap);
JsonObject parse_dict(ParsingWrapper& wrap);
JsonObject parse_list(ParsingWrapper& wrap);
std::string parse_string(ParsingWrapper& wrap);
JsonObject parse_number(ParsingWrapper& wrap);
JsonObject parse_bool(ParsingWrapper& wrap);
JsonObject parse_null(ParsingWrapper& wrap);

JsonObject parse_json(const std::string& json_str){
    ParsingWrapper wrap(json_str);
    return parse_dict(wrap);
}

JsonObject parse_value(ParsingWrapper& wrap){
    if (wrap.ch == '"'){
        std::string str_value = parse_string(wrap);
        JsonObject obj;
        obj.set_string(str_value);
        return obj;
    }
    if (is_number(wrap.ch)){
        return parse_number(wrap);
    }
    if (wrap.ch == '['){
        return parse_list(wrap);
    }
    if (wrap.ch == '{'){
        return parse_dict(wrap);
    }
    if (wrap.ch == 'f' || wrap.ch == 't'){
        return parse_bool(wrap);
    }
    if (wrap.ch == 'n'){
        return parse_null(wrap);
    }
    throw JsonParsingErrorException("Ожидалось число, строка, словарь или массив. Но встречен символ '"s + wrap.ch + "'"s);
}

std::pair<std::string, JsonObject> parse_dict_item(ParsingWrapper& wrap){
    std::string key = parse_string(wrap);
    wrap.check(':');
    JsonObject value = parse_value(wrap);
    return std::make_pair(key, value);
}

JsonObject parse_dict(ParsingWrapper& wrap){
    wrap.check('{');
    JsonDict json_dict;
    if (wrap.ch == '"'){
        auto key_and_value = parse_dict_item(wrap);
        json_dict[key_and_value.first] = key_and_value.second;
        while (wrap.ch == ','){
            wrap.get_next();
            auto key_and_value = parse_dict_item(wrap);
            json_dict[key_and_value.first] = key_and_value.second;
        }
    }
    wrap.check('}');
    JsonObject json_obj;
    json_obj.set_dict(json_dict);
    return json_obj;
}

JsonObject parse_list(ParsingWrapper& wrap){
    wrap.check('[');
    JsonList list;
    if (wrap.ch != ']'){
        JsonObject array_item = parse_value(wrap);
        list.push_back(array_item);
        while (wrap.ch == ','){
            wrap.get_next();
            JsonObject array_item = parse_value(wrap);
            list.push_back(array_item);
        }
    }
    wrap.check(']');
    JsonObject obj;
    obj.set_list(list);
    return obj;
}

std::string parse_string(ParsingWrapper& wrap){
    wrap.check('"');
    std::string str = "";
    while (wrap.ch != EOT && wrap.ch != '"'){
        str += wrap.ch;
        wrap.get_next();
    }
    wrap.check('"');
    return str;
}

JsonObject parse_number(ParsingWrapper& wrap){
    int int_part = 0;
    int float_part = 0;
    int divider = 1;
    bool is_float_value = false;
    while (is_number(wrap.ch)){
        int_part = int_part * 10 + (wrap.ch - '0');
        wrap.get_next();
    }
    if (wrap.ch == '.'){
        is_float_value = true;
        wrap.get_next();
        if (!is_number(wrap.ch)){
            throw JsonParsingErrorException("Ожидалось дробная часть числа "s + std::to_string(int_part));
        }
        while (is_number(wrap.ch)){
            float_part = float_part * 10 + (wrap.ch - '0');
            wrap.get_next();
            divider *= 10;
        }
    }
    JsonObject obj;
    if (is_float_value){
        obj.set_double(int_part + (float_part / divider));
    } else {
        obj.set_int(int_part);
    }
    return obj;
}

void check_keyword(ParsingWrapper& wrap, const std::string& keyword){
    std::string current_str = ""s;
    for (char c : keyword){
        current_str += wrap.ch;
        if ((wrap.ch) != c){
            throw JsonParsingErrorException("ожидалось "s + keyword + " но "s + current_str);
        }
        wrap.get_next();
    }
}

JsonObject parse_bool(ParsingWrapper& wrap){
    if (wrap.ch == 'f'){
        check_keyword(wrap, "false"s);
        return JsonObject("false"s);
    }
    if (wrap.ch == 't'){
        check_keyword(wrap, "true"s);
        return JsonObject("true"s);
    }
    throw JsonParsingErrorException("Ожидалось булево значение");
}

JsonObject parse_null(ParsingWrapper& wrap){
    if (wrap.ch == 'n'){
        check_keyword(wrap, "null"s);
        return JsonObject("null"s);
    }
    throw JsonParsingErrorException("Ожидалось null-значение");
}

std::string make_tab(int tab_index){
    std::string result = ""s;
    for (int i = 0; i < tab_index; ++i){
        result += "   ";
    }
    return result;
}

std::string _to_string(JsonObject json_object, int tab_index){
    std::string result = ""s;
    switch (json_object.get_value_type())
    {
        case JsonValueType::DICT: {
            result += "{\n"s;
            bool first = true;
            for (auto [key, value] : json_object.get_dict()){
                if (first){
                    first = false;
                } else {
                    result += ",\n"s;
                }
                result += make_tab(tab_index + 1) + "\""s + key + "\": "s;
                result += _to_string(value, tab_index + 1);
            }
            result += "\n"s;
            result += make_tab(tab_index) + "}"s;
            return result;
        }
        case JsonValueType::DOUBLE:
            return std::to_string(json_object.get_double());
        case JsonValueType::INT:
            return std::to_string(json_object.get_int());
        case JsonValueType::LIST: {
            result += "[\n"s;
            bool first = true;
            for (auto i : json_object.get_list()){
                if (first){
                    first = false;
                } else {
                    result += ",\n"s;
                }
                result += make_tab(tab_index + 1) + _to_string(i, tab_index + 1);
            }
            result += "\n"s;
            result += make_tab(tab_index) + "]"s;
            return result;
        }
        case JsonValueType::STRING: {
            result += "\""s + json_object.get_string() + "\""s;
            return result;
        }
        case JsonValueType::BOOL:
            return to_string(json_object.get_bool());
        case JsonValueType::NULL_VALUE:
            return "null"s;
        default:
            return "<error>";

    }
    return result;
}

std::string to_string(JsonObject json_object){
    return _to_string(json_object, 0);
}

std::string to_string(bool value){
    if (value){
        return "true"s;
    }
    return "false"s;
}

}