all: a.out

a.out: main.cpp test.o
	g++ main.cpp test.o -o a.out

test.o: test.cpp
	g++ -c test.cpp -o test.o 

clean:
	rm *.ii *.s *.o a.out