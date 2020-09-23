objects = main.o sql_parser.o sql_analyse.o 
storagePath = Storage/
CPP = g++
CPPFLAGS = -std=c++11

main : $(objects)
	$(CPP) $(CPPFLAGS) $(objects) -o main

main.o : data_def.h sql_parser.h $(storagePath)storage.o

sql_parser.o : data_def.h sql_parser.h

sql_analyse.o : data_def.h sql_analyse.h

.PHONY : clean

clean:
	-rm $(objects)
