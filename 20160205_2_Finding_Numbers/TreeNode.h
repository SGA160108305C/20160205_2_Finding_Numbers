#pragma once

class TreeNode
{
public:
	TreeNode(void){};
	~TreeNode(void){};

	int index = 0;
	int nominator = 0;
	bool isHuman = false;
	//void* data = nullptr;
	TreeNode* childLeft = nullptr;
	TreeNode* childRight = nullptr;
};


