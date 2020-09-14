objects = main.o sql_parser.o sql_analyse.o
CPP = g++
CPPFLAGS = -std=c++11

main : $(objects)
	$(CPP) $(CPPFLAGS) $(objects) -o main

main.o : data_def.h sql_parser.h b_plus_tree.h

sql_parser.o : data_def.h sql_parser.h

sql_analyse.o : data_def.h sql_analyse.h

b_plus_tree.o : data_def.h b_plus_tree.h

.PHONY : clean

clean:
	-rm $(objects)
