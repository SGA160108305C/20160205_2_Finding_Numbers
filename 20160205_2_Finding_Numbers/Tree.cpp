#include <string>
#include "Tree.h"


Tree::Tree()
{
}

Tree::~Tree()
{
	Clear();
}

void Tree::Insert(int index, bool isHuman)
{
	TreeNode* node = new TreeNode();
	node->index = index;
	node->isHuman = isHuman;

	if (root != nullptr)
	{
		TreeNode* target = root;
		bool insertFinish = false;
		while (insertFinish != true)
		{
			if (target->index > index)
			{
				//왼쪽으로 이동
				if (target->childLeft != nullptr)
				{
					target = target->childLeft;
				}
				else
				{
					target->childLeft = node;
					insertFinish = true;
				}
			}
			else if (target->index < index)
			{
				//오른쪽으로 이동
				if (target->childRight != nullptr)
				{
					target = target->childRight;
				}
				else
				{
					target->childRight = node;
					insertFinish = true;
				}
			}
			else
			{
				//같은 경우
				delete node;
				node = nullptr;
				insertFinish = true; //종료
			}
		}
	}
	else
	{
		root = node;
	}
}

TreeNode* Tree::Find(int index)
{
	TreeNode* node = root;
	
	while (node != nullptr)
	{
		if (node->index < index)
		{
			node = node->childRight;
		}
		else if (node->index > index)
		{
			node = node->childLeft;
		}
		else
		{
			break;
		}
	}
	getParent(node);
	return node;
}

void Tree::Delete(int index)
{
	if (root == nullptr)
	{
		printf_s("\nTree is empty!\n");
		return;
	}

	TreeNode* target = Find(index);

	if (target == nullptr)
	{
		printf_s("\nNo such node to delete!\n");
		return;
	}

	if (root == target)
	{
		deleteRoot();
		return;
	}

	TreeNode* parent = getParent(target);
	TargetLocation location = getLocation(target);
	int smallestIndexInRightSubtree = 0;

	TargetType targetType;
	if (target->childLeft == nullptr && target->childRight == nullptr)
	{
		targetType = HAS_NO_CHILD;
	}

	else if (target->childLeft != nullptr && target->childRight == nullptr)
	{
		targetType = HAS_LEFT_CHILD;
	}

	else if (target->childLeft == nullptr && target->childRight != nullptr)
	{
		targetType = HAS_RIGHT_CHILD;
	}

	else
	{
		targetType = HAS_TWO_CHILDREN;
	}

	switch (targetType)
	{
	case Tree::HAS_NO_CHILD:
		switch (location)
		{
		case Tree::IS_LEFT:
			parent->childLeft = nullptr;
			break;

		case Tree::IS_RIGHT:
			parent->childRight = nullptr;
			break;

		default:
			break;
		}

		delete target;
		target = nullptr;

		break;

	case Tree::HAS_LEFT_CHILD:
		switch (location)
		{
		case Tree::IS_LEFT:
			parent->childLeft = target->childLeft;
			break;
		case Tree::IS_RIGHT:
			parent->childRight = target->childLeft;
			break;
		default:
			break;
		}

		delete target;
		target = nullptr;

		break;

	case Tree::HAS_RIGHT_CHILD:
		switch (location)
		{
		case Tree::IS_LEFT:
			parent->childLeft = target->childRight;
			break;
		case Tree::IS_RIGHT:
			parent->childRight = target->childRight;
			break;
		default:
			break;
		}

		delete target;
		target = nullptr;

		break;

	case Tree::HAS_TWO_CHILDREN:
		smallestIndexInRightSubtree = getSmallestIndexFromRightSubtree(target);
		Delete(smallestIndexInRightSubtree);
		target->index = smallestIndexInRightSubtree;

		break;

	default:
		break;
	}
}

void Tree::deleteRoot()
{
	int smallestIndexInRightSubtree = 0;

	TargetType targetType;
	if (root->childLeft == nullptr && root->childRight == nullptr)
	{
		targetType = HAS_NO_CHILD;
	}

	else if (root->childLeft != nullptr && root->childRight == nullptr)
	{
		targetType = HAS_LEFT_CHILD;
	}

	else if (root->childLeft == nullptr && root->childRight != nullptr)
	{
		targetType = HAS_RIGHT_CHILD;
	}

	else
	{
		targetType = HAS_TWO_CHILDREN;
	}

	switch (targetType)
	{
	case Tree::HAS_NO_CHILD:
		delete root;
		root = nullptr;

		break;

	case Tree::HAS_LEFT_CHILD:
		root = root->childLeft;

		break;

	case Tree::HAS_RIGHT_CHILD:
		root = root->childRight;

		break;

	case Tree::HAS_TWO_CHILDREN:
		smallestIndexInRightSubtree = getSmallestIndexFromRightSubtree(root);
		Delete(smallestIndexInRightSubtree);
		root->index = smallestIndexInRightSubtree;

		break;

	default:
		break;
	}
}

int Tree::getSmallestIndexFromRightSubtree(TreeNode* node)
{
	TreeNode* target = node->childRight;

	while (target->childLeft != nullptr)
	{
		target = target->childLeft;
	}

	return target->index;
}

TreeNode* Tree::getParent(TreeNode* node)
{
	TreeNode* target = root;
	TreeNode* parent = nullptr;

	while (target != nullptr)
	{
		if (target->index < node->index)
		{
			parent = target;
			target = target->childRight;
		}
		else if (target->index > node->index)
		{
			parent = target;
			target = target->childLeft;
		}
		else
		{
			break;
		}
	}

	return parent;
}

Tree::TargetLocation Tree::getLocation(TreeNode* node)
{
	TreeNode* target = root;
	TargetLocation targetLocation;

	while (target != nullptr)
	{
		if (target->index < node->index)
		{
			targetLocation = IS_RIGHT;
			target = target->childRight;
		}
		else if (target->index > node->index)
		{
			targetLocation = IS_LEFT;
			target = target->childLeft;
		}
		else
		{
			break;
		}
	}

	return targetLocation;
}

void Tree::Print()
{
	printf_s("Tree Print-----------------\n");
	Print(root);
	printf_s("\n---------------------------\n");
}

void Tree::Print(TreeNode* node)
{
	if (node)
	{
		Print(node->childLeft);
		printf_s("%d ", node->index);
		Print(node->childRight);
	}
}

void Tree::Clear()
{
	
}

void Tree::ReadData(char* inputFileName/* = nullptr*/)
{
	if (inputFileName == nullptr)
	{
		printf_s("No data file name provided!\n");
		return;
	}

	FILE* fp = nullptr;
	fopen_s(&fp, inputFileName, "r");
	char line[1024];
	if (fp != nullptr)
	{
		while (
			fgets(line, 256, fp) != nullptr)
		{
			ParseLine(line);
		}

		fclose(fp);
	}
}

void Tree::ParseLine(char* line)
{
	char delim[] = " :;,\t\n";
	char* token = NULL;
	char* next_token = NULL;

	token = strtok_s(line, delim, &next_token);
	int index = std::stoi(token);

	while (token != NULL)
	{
		token = strtok_s(NULL, delim, &next_token);

		int num = std::stoi(token);
		printf_s("Insert(%d)\n", num);

		Insert(num);
		Print();
	}
}