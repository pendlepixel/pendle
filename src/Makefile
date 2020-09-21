objects = main.o sql_parser.o sql_analyse.o b_plus_tree.o b_plus_tree_index_node.o b_plus_tree_leaf_node.o
CPP = g++
CPPFLAGS = -std=c++11

main : $(objects)
	$(CPP) $(CPPFLAGS) $(objects) -o main

main.o : data_def.h sql_parser.h b_plus_tree.h b_plus_tree_index_node.h b_plus_tree_leaf_node.h

sql_parser.o : data_def.h sql_parser.h

sql_analyse.o : data_def.h sql_analyse.h

b_plus_tree.o : data_def.h b_plus_tree.h b_plus_tree_index_node.h b_plus_tree_leaf_node.h

b_plus_tree_index_node.o : data_def.h b_plus_tree_index_node.h

b_plus_tree_leaf_node.o : data_def.h b_plus_tree_leaf_node.h

.PHONY : clean

clean:
	-rm $(objects)
