stage1exe   :   driver.o parser.o lexer.o stack.o stack_linked_list.o linkedlist.o hashmap.o treeADT.o
	cc -o stage1exe driver.o parser.o lexer.o stack.o stack_linked_list.o linkedlist.o hashmap.o treeADT.o

clean:
	rm *.o