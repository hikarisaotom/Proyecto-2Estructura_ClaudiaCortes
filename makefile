huffman:TreeNode.o main.o TreeElement.o
	g++ TreeNode.o main.o TreeElement.o -o huffman

TreeNode.o:	TreeNode.h TreeNode.cpp TreeElement.h
	g++ -c TreeNode.cpp

TreeElement.o:	TreeElement.h TreeElement.cpp
	g++ -c TreeElement.cpp

main.o:	main.cpp TreeNode.h TreeElement.h
	g++ -c main.cpp

