#pragma once
#include <vector>

class TownPeople
{
public:
	TownPeople(){};
	~TownPeople(){};

	int index = -1;
	bool isHuman = false;
	std::vector<int> knownHumans;
};

