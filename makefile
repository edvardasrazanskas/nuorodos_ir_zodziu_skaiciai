main: headers.o
	g++ -o3 -o main main.cpp headers.o
funkcijos:
	g++ -c headewrs.cpp
clean:
	del *.o main.exe