#----------------------------------------------------------------------------
# Build process for MNA 
#
# Coder - Nahit Pawar
#         MTech Indian Institute of Technology Bombay, India
# Starting Date  - 10/01/13
# Last Modified  - 04/08/13
#
#----------------------------------------------------------------------------

CPP    = g++ -std=c++11
CFLAGS = -g -Wall -o3
RM     = rm

EXEC   = mna
OBJECTS = \
	main.o \
	convertNetworkIntoGraph.o \
	dcAnalyzer.o \
	LUDecomposition.o\
        printSolution.o

.PHONEY: clean
.PHONEY: all
.PHONEY: compile
.PHONEY: acknowledge


all: $(OBJECTS) compile acknowledge

main.o : main.cpp
			$(CPP) -g -c $^

convertNetworkIntoGraph.o : convertNetworkIntoGraph.cpp
							$(CPP) -g -c $^
dcAnalyzer.o : dcAnalyzer.cpp
				$(CPP) -g -c $^
LUDecomposition.o : LUDecomposition.cpp
					$(CPP) -g -c $^

printSolution.o : printSolution.cpp
					$(CPP) -g -c $^


compile:
		$(CPP) $(CFLAGS) $(OBJECTS) -o $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

acknowledge:
		@echo " "
		@echo " "
		@echo "Perfecto! Compilation Done Successfully........"
		@echo " "
		@echo " "
