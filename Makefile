#MakeFile
#Universidad Simon Bolivar
#Autor: David Lilue
#Carnet: 09-10444

CC = g++
MAIN = main.cpp
EXE = P2
#DEPS = 
OBJS = main.o

clean_compile: $(EXE)
	\rm -f *.o *.out

$(EXE): $(MAIN)
	$(CC) $(MAIN) -o $@ 

%.o: %.c
	$(CC) -c $<

clean:
	\rm -f *.o *.out P2