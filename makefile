all: ./src/main.cpp
	g++ -o main $^

clean:
	rm -f main *.o *.exe