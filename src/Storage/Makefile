objects = storage.o
originPath = ../
CPP = g++
CPPFLAGS = -std=c++11

storage.o : $(originPath)data_def.h storage.h

b_plus_tree.o : storage_data_def.h b_plus_tree.h b_plus_tree_index_node.h b_plus_tree_leaf_node.h

b_plus_tree_index_node.o : storage_data_def.h b_plus_tree_index_node.h

b_plus_tree_leaf_node.o : storage_data_def.h b_plus_tree_leaf_node.h

.PHONY : clean

clean:
	-rm $(objects)
