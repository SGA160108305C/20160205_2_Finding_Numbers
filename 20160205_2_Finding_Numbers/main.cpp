#include <stdio.h>
#include "Tree.h"

int main()
{	
	Tree tree;
	tree.Insert(1, true);
	tree.Insert(2, true);
	tree.Insert(14, true);
	tree.Insert(13, true);

	tree.ReadData("¸¶À»1.txt");

	getchar();
}