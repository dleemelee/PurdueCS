##################################################################################
#######      For a detailed task description, go to MyVector.h      ##############		
##################################################################################
###### 										DO NOT MODIFY THIS FILE 									#############

OUTPUT=	task2

all: main.cpp constructors.o MyVector_fxns.cpp
	g++ -std=c++11 -Wall -Werror -g -o $(OUTPUT) main.cpp  MyVector_fxns.cpp constructors.o

clean:
	rm -f $(OUTPUT) total.txt *.out .local.total.out
