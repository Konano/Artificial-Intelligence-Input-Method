make: main.exe training.exe

main.exe: main.cpp function.h
	g++ main.cpp -o main -O2
	
training.exe: training.cpp function.h
	g++ training.cpp -o training -O2

.PHONY: clean
clean:
	del *.exe