test_with_python: json_object.o json_parser.o
	g++ test/test_with_python.cpp -o test/test_with_python json_object.o json_parser.o

cpp_test: json_object.o json_parser.o
	g++ test/cpp_test.cpp -o test/cpp_test json_object.o json_parser.o

json_object.o: json.h json_object.cpp
	g++ json_object.cpp -o json_object.o -c
json_parser.o: json.h json_parser.cpp
	g++ json_parser.cpp -o json_parser.o -c
	

clean:
	-rm test/test_with_python test/cpp_test
	-rm *.o