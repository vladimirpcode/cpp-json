test: json_object.o json_parser.o
	g++ test.cpp -o test_app json_object.o json_parser.o
json_object.o: json.h json_object.cpp
	g++ json_object.cpp -o json_object.o -c
json_parser.o: json.h json_parser.cpp
	g++ json_parser.cpp -o json_parser.o -c

clean:
	-rm test_app
	-rm *.o