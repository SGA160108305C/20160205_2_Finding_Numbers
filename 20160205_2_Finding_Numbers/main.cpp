#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "TownPeopleFinder.h"

#pragma comment(lib, "winmm.lib")

void main()
{	
	DWORD start = timeGetTime();

	TownPeopleFinder townPeople;
	//townPeople.ReadData();
	townPeople.ReadData("¸¶À»1.txt");	
	townPeople.MakeHumanList();
	townPeople.Print();
	
	DWORD end = timeGetTime();
	printf_s("find Time : %d\n", end - start);
	
	getchar();
}