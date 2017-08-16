# Makefile

FC = g++
FFLAGS = -std=c++14 -Wall -g
OBJS = binary_io.o
EXEC = isotxs_cpp.exe

$(EXEC) : $(OBJS)
	$(FC) $(FLAGS) -o $(EXEC) $(OBJS)

%.o : %.cpp
	$(FC) $(FLAGS) -c $<

clean : 
	rm -f *.exe *.o
