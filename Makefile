.PHONY: all program clean

all: program

program:
	g++ *.cpp -o program.exe

clean:
	rm -f program.exe
