#include "../json.h"

#include <string>
#include <iostream>
#include <functional>
#include <vector>

using namespace std::string_literals;
using namespace cpp_json;

static int assert_counter = 0;
static int success_assert_counter = 0;

void assert(bool expr, const std::string& msg_if_fail){
    assert_counter++;
    if (!expr){
        std::cout << "assertion error: "s + msg_if_fail + "\n";
    } else {
        success_assert_counter++;
    }
}

void assert(bool expr){
    assert(expr, ""s);
}

using test_function = std::function<void()>;

void test_json_object_constructors();
void test_json_object_assignment_operators();
void test_json_object_setters_and_getters();
void test_json_object_getters_by_reference();
void test_json_object_get_operators();

int main(){
    std::vector<test_function> test_functions{
        test_json_object_constructors,
        test_json_object_assignment_operators,
        test_json_object_setters_and_getters,
        test_json_object_getters_by_reference,
        test_json_object_get_operators,
    };
    for (auto func : test_functions){
        func();
    }
    std::cout << success_assert_counter << " / " << assert_counter << " ассертов \n";
    if (success_assert_counter == assert_counter){
        std::cout << "успешно\n";
    } else {
        std::cout << "есть ошибки\n";
    }
}

void test_json_object_constructors(){
    JsonObject json_obj;
    assert(json_obj.get_value_type() == JsonValueType::DICT, "JsonObject(): ожидался дефолтный тип DICT");

    json_obj = JsonObject(JsonDict{{"a", 1}});
    assert(json_obj.get_value_type() == JsonValueType::DICT, "JsonObject(const JsonDict& value): ожидался тип DICT");
    assert(json_obj.get_dict() == JsonDict{{"a", 1}}, "JsonObject(const JsonDict& value): значения не равны");

    json_obj = JsonObject(static_cast<int64_t>(10));
    assert(json_obj.get_value_type() == JsonValueType::INT, "JsonObject(int64_t): ожидался тип INT");
    assert(json_obj.get_int() == static_cast<int64_t>(10), "JsonObject(int64_t value): значения не равны");

    json_obj = JsonObject(static_cast<int>(12));
    assert(json_obj.get_value_type() == JsonValueType::INT, "JsonObject(int): ожидался тип INT");
    assert(json_obj.get_int() == static_cast<int>(12), "JsonObject(int value): значения не равны");

    json_obj = JsonObject(static_cast<double>(10.1));
    assert(json_obj.get_value_type() == JsonValueType::DOUBLE, "JsonObject(double): ожидался тип DOUBLE");
    assert(json_obj.get_double() == static_cast<double>(10.1), "JsonObject(double value): значения не равны");

    json_obj = JsonObject(true);
    assert(json_obj.get_value_type() == JsonValueType::BOOL, "JsonObject(bool): ожидался тип BOOL");
    assert(json_obj.get_bool() == true, "JsonObject(bool value): значения не равны");

    json_obj = JsonObject("str"s);
    assert(json_obj.get_value_type() == JsonValueType::STRING, "JsonObject(const std::string&): ожидался тип STRING");
    assert(json_obj.get_string() == "str"s, "JsonObject(const std::string& value): значения не равны");

    json_obj = JsonObject("abc");
    assert(json_obj.get_value_type() == JsonValueType::STRING, "JsonObject(const char*): ожидался тип STRING");
    assert(json_obj.get_string() == "abc", "JsonObject(const char* value): значения не равны");

    json_obj = JsonObject(JsonList({1,2,3}));
    assert(json_obj.get_value_type() == JsonValueType::LIST, "JsonObject(const JsonList&): ожидался тип LIST"); 
    assert(json_obj.get_list() == JsonList({1,2,3}), "JsonObject(const JsonList& value): значения не равны");

    json_obj = JsonObject(JsonDict({{"name", "vlad"},{"age", 38}}));
    assert(json_obj.get_value_type() == JsonValueType::DICT, "JsonObject(const JsonDict&): ожидался тип DICT"); 
    assert(json_obj.get_dict() == JsonDict({{"name", "vlad"},{"age", 38}}), "JsonObject(const JsonDict& value): значения не равны");

    json_obj = JsonObject(nullptr);
    assert(json_obj.get_value_type() == JsonValueType::NULL_VALUE, "JsonObject(nullptr_t): ожидался тип NULL_VALUE");
    
}

void test_json_object_assignment_operators(){
    JsonObject json_obj;
    json_obj = static_cast<int64_t>(32);
    assert(json_obj.get_value_type() == JsonValueType::INT, "JsonObject& operator=(int64_t value): ожидался тип INT");
    assert(json_obj.get_int() == static_cast<int64_t>(32), "JsonObject& operator=(int64_t value): после присваивания значения не равны");

    json_obj = static_cast<int>(45);
    assert(json_obj.get_value_type() == JsonValueType::INT, "JsonObject& operator=(int value): ожидался тип INT");
    assert(json_obj.get_int() == static_cast<int>(45), "JsonObject& operator=(int value): после присваивания значения не равны");

    json_obj = static_cast<double>(71.0);
    assert(json_obj.get_value_type() == JsonValueType::DOUBLE, "JsonObject& operator=(double value): ожидался тип DOUBLE");
    assert(json_obj.get_double() == static_cast<double>(71.0), "JsonObject& operator=(double value): после присваивания значения не равны");

    json_obj = false;
    assert(json_obj.get_value_type() == JsonValueType::BOOL, "JsonObject& operator=(bool value): ожидался тип BOOL");
    assert(json_obj.get_bool() == false, "JsonObject& operator=(bool value): после присваивания значения не равны");

    json_obj = "Max"s;
    assert(json_obj.get_value_type() == JsonValueType::STRING, "JsonObject& operator=(const std::string& value): ожидался тип STRING");
    assert(json_obj.get_string() == "Max"s, "JsonObject& operator=(const std::string& value): после присваивания значения не равны");

    json_obj = "Bob";
    assert(json_obj.get_value_type() == JsonValueType::STRING, "JsonObject& operator=(const char* value): ожидался тип STRING");
    assert(json_obj.get_string() == "Bob", "JsonObject& operator=(const char* value): после присваивания значения не равны");

    json_obj = JsonList{1,2,3};
    assert(json_obj.get_value_type() == JsonValueType::LIST, "JsonObject& operator=(const JsonList& value): ожидался тип LIST");
    assert(json_obj.get_list() == JsonList{1,2,3}, "JsonObject& operator=(const JsonList& value): после присваивания значения не равны");

    json_obj = JsonDict{{"name", "bob"},{"age", 56},{"level", 21}};
    assert(json_obj.get_value_type() == JsonValueType::DICT, "JsonObject& operator=(const JsonDict& value): ожидался тип DICT");
    assert(json_obj.get_dict() == JsonDict{{"name", "bob"},{"age", 56},{"level", 21}}, "JsonObject& operator=(const JsonDict& value): после присваивания значения не равны");

    json_obj = nullptr;
    assert(json_obj.get_value_type() == JsonValueType::NULL_VALUE, "JsonObject& operator=(nullptr_t value): ожидался тип NULL_VALUE");
}

void test_json_object_setters_and_getters(){
    JsonObject json_obj;

    json_obj.set_int(static_cast<int64_t>(99));
    assert(json_obj.get_value_type() == JsonValueType::INT, "JsonObject::set_int(int64_t) несоответствие типа после выполнения метода");
    assert(json_obj.get_int() == static_cast<int64_t>(99), "JsonObject::set_int(int64_t): значения после выполнения метода не равны");

    json_obj.set_int(static_cast<int>(11));
    assert(json_obj.get_value_type() == JsonValueType::INT, "JsonObject::set_int(int) несоответствие типа после выполнения метода");
    assert(json_obj.get_int() == static_cast<int>(11), "JsonObject::set_int(int): значения после выполнения метода не равны");

    json_obj.set_double(static_cast<double>(22.2));
    assert(json_obj.get_value_type() == JsonValueType::DOUBLE, "JsonObject::set_int(double) несоответствие типа после выполнения метода");
    assert(json_obj.get_double() == static_cast<double>(22.2), "JsonObject::set_double(double): значения после выполнения метода не равны");

    json_obj.set_bool(true);
    assert(json_obj.get_value_type() == JsonValueType::BOOL, "JsonObject::set_int(bool) несоответствие типа после выполнения метода");
    assert(json_obj.get_bool() == true, "JsonObject::set_bool(bool): значения после выполнения метода не равны");

    json_obj.set_string("rob"s);
    assert(json_obj.get_value_type() == JsonValueType::STRING, "JsonObject::set_int(const std::string&) несоответствие типа после выполнения метода");
    assert(json_obj.get_string() == "rob"s, "JsonObject::set_string(const std::string&): значения после выполнения метода не равны");

    json_obj.set_string("tom");
    assert(json_obj.get_value_type() == JsonValueType::STRING, "JsonObject::set_int(const char*) несоответствие типа после выполнения метода");
    assert(json_obj.get_string() == "tom", "JsonObject::set_string(const char*): значения после выполнения метода не равны");

    json_obj.set_list(JsonList{1,2,88,"12"});
    assert(json_obj.get_value_type() == JsonValueType::LIST, "JsonObject::set_int(const JsonList&) несоответствие типа после выполнения метода");
    assert(json_obj.get_list() == JsonList{1,2,88,"12"}, "JsonObject::set_list(const JsonList&): значения после выполнения метода не равны");

    json_obj.set_dict(JsonDict{{"a", 2},{"b", "f"},{"c", JsonDict()}});
    assert(json_obj.get_value_type() == JsonValueType::DICT, "JsonObject::set_int(const JsonDict&) несоответствие типа после выполнения метода");
    assert(json_obj.get_dict() == JsonDict{{"a", 2},{"b", "f"},{"c", JsonDict()}}, "JsonObject::set_dict(const JsonDict&): значения после выполнения метода не равны");

    json_obj.set_null();
    assert(json_obj.get_value_type() == JsonValueType::NULL_VALUE, "JsonObject::set_null() несоответствие типа после выполнения метода");
}

void test_json_object_getters_by_reference(){
    JsonObject json_obj = JsonDict{{"name", "bob"}, {"age", 23}};
    json_obj.get_dict_by_ref()["name"] = "max";
    json_obj.get_dict_by_ref()["age"] = 36;
    assert(json_obj.get_dict() == JsonDict{{"name", "max"}, {"age", 36}}, "JsonObject::get_dict_by_ref: ошибка");

    json_obj = JsonList{1, "a", true, 10.2};
    json_obj.get_list_by_ref()[0] = 2;
    json_obj.get_list_by_ref()[1] = 30.2;
    json_obj.get_list_by_ref()[2] = "abc";
    json_obj.get_list_by_ref()[3] = false;
    assert(json_obj.get_list() == JsonList{2, 30.2, "abc", false}, "JsonObject::get_list_by_ref: ошибка");

}

void test_json_object_get_operators(){
    JsonObject json_obj = JsonDict{{"a", JsonDict{{"b", JsonDict{{"c", 1}}}}}};
    assert(json_obj["a"]["b"]["c"] == 1, "Object& operator[](const std::string& key): ошибка");
    json_obj = JsonList{1, JsonList{2, 3, JsonList{1,2,3,4, JsonList{1,2}}}};
    assert(json_obj[1][2][4][1] == 2, "JsonObject& operator[](int64_t index): ошибка");
    json_obj = JsonDict{
        {"first", JsonList{
            1,
            JsonDict{
                {"c", JsonList{
                    1, 2, 3
                }}
            }
        }}
    };
    assert(json_obj["first"][1]["c"][1] == 2, "JsonObject& operator[](): ошибка");
}
