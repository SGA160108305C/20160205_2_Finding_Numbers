#pragma once
#include <vector>
#include <list>

#include "TownPeople.h"

class TownPeopleFinder
{
public:
	TownPeopleFinder();
	~TownPeopleFinder();

	void ReadData(char* inputFileName = nullptr);
	void MakeHumanList();
	void Print();

protected:
	std::vector<TownPeople> peopleData;
	std::list<int> humans;

	void DataClear();
};

