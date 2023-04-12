compiler   :   driver.o parser.o lexer.o stack.o stack_linked_list.o linkedlist.o hashmap.o treeADT.o ast.o ast_traversal.o function_hash.o symbol_hash.o
	cc -o compiler driver.o parser.o lexer.o stack.o stack_linked_list.o linkedlist.o hashmap.o treeADT.o ast.o ast_traversal.o function_hash.o symbol_hash.o

clean:
	rm *.o