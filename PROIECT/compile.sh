#!/bin/bash
echo "Curatare..."
rm -f proiect lex.yy.c proiect.tab.c proiect.tab.h

echo "Generare parser (Bison)..."
bison -d proiect.y

echo "Generare lexer (Flex)..."
flex proiect.l

echo "Compilare (G++)..."
g++ lex.yy.c proiect.tab.c SymTable.cpp AST.cpp -o proiect -std=c++17

echo "Gata! Ruleaza: ./proiect input_test_corect.txt"