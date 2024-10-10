test: json_object.o json_parser.o
	g++ test.cpp -o test_app json_object.o json_parser.o
manual_test: json_object.o json_parser.o
	g++ manual_test.cpp -o manual_test_app json_object.o json_parser.o
json_object.o: json.h json_object.cpp
	g++ json_object.cpp -o json_object.o -c
json_parser.o: json.h json_parser.cpp
	g++ json_parser.cpp -o json_parser.o -c
	

clean:
	-rm test_app manual_test_app
	-rm *.o