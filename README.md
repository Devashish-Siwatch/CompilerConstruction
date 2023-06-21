# CompilerConstruction

The repository contains the compiler implementation for a custom language as a part of course work for CS F363 - Compiler Construction at BITS Pilani under instructor Vandana Agarwal.

The language supports features such as

* Static scoping of variables
* Assignment, I/O, Declarative, Iterative, Conditional, Function call statements
* Returning multiple values from a function
* Arithmetic and boolean expressions
* Strongly typed language

The compiler has the following components:-

* Lexer - The lexer is responsible for separating and identifying the 
different tokens present in the user-provided source code. It classifies
each word/symbol present into the appropriate token and passes the generated
stream of tokens to the parser. The classification is done using a Definitive 
Finite Automaton specifies the type of token based on the characters present 
in the lexeme. 

* Parser - The parser receives the stream of tokens from the lexer and generates a parse 
tree for the source code based on the language's grammar. We have represented the 
grammar using a context-free grammar of more than 100 rules, and have used top-down parsing
to parse the stream of tokens. 

* Semantic Analyzer - The semantic analyzer uses the parse tree generated by the parser to first 
create an Abstract Syntax Tree and then utilizes the AST to create appropriate symbol tables for
different methods and scopes, while populating the variables with their types, offsets, values etc.

