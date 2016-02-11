#include "TownPeopleFinder.h"


TownPeopleFinder::TownPeopleFinder()
{
}

TownPeopleFinder::~TownPeopleFinder()
{
	DataClear();
}

void TownPeopleFinder::ReadData(char* inputFileName /*= nullptr*/)
{
	DataClear();

	char filename[256] = "\0";
	if ( inputFileName != nullptr )
	{
		strcpy_s(filename, inputFileName);
	}
	else
	{
		strcpy_s(filename, "마을1.txt");
	}

	FILE* fp = nullptr;
	fopen_s(&fp, filename, "r");
	if ( fp != nullptr )
	{
		int lineCount = 0;
		char line[256];
		if(fgets(line, 256, fp) != nullptr)
		{
			lineCount = atoi(line);
			printf_s("lineCount -> %d\n", lineCount);
		}
		
		peopleData.resize(lineCount);
		for ( int i = 0; i < lineCount; ++i )
		{
			if ( fgets(line, 256, fp) != nullptr )
			{
				char* token = nullptr;
				char* context = nullptr;
				char seperator[] = " \n\0";

				//주민번호
				int index = -1;
				token = strtok_s(line, seperator, &context);	
				if ( token )
				{
					index = atoi(token);
					printf_s("index -> %d\n", index);
				}

				//알고 있는 사람 수
				int humanCount = -1;
				token = strtok_s(nullptr, seperator, &context);	
				if ( token )
				{
					humanCount = atoi(token);
					printf_s("humanCount -> %d\n", humanCount);
				}

				//알고 있는 사람들의 번호
				if ( index != -1 )
				{
					TownPeople personData;
					personData.index = index;
					personData.knownHumans.resize(humanCount);
					for ( int i = 0; i < humanCount; ++i )
					{
						token = strtok_s(nullptr, seperator, &context);
						if ( token )
						{
							personData.knownHumans[i] = atoi(token);
						}
					}					
					peopleData[index-1] = std::move(personData);
				}				
			}
		}
		
		fclose(fp);
	}
}

void TownPeopleFinder::DataClear()
{
	for ( auto iterMap = peopleData.begin(); iterMap != peopleData.end(); ++iterMap )
	{
		iterMap->knownHumans.clear();
	}
	peopleData.clear();
	humans.clear();
}

void TownPeopleFinder::MakeHumanList()
{
	std::vector<int> target;
	target.push_back(1);	//1은 무조건 사람
	
	while ( target.empty() == false )
	{
		int index = target.back();
		target.pop_back();
		printf_s("index -> %d\n", index);
		printf_s("target size -> %d\n", target.size());
		printf_s("is target empty? -> %s\n", target.empty() ? "yes" : "no");

		TownPeople* person = &( peopleData[index-1] );
		printf_s("is human? -> %s\n", person->isHuman ? "yes" : "no");
		if ( person->isHuman == true )
		{
			continue;	//이게 없으면 무한 반복
		}

		person->isHuman = true;
		for ( int i = 0; i < (int)person->knownHumans.size(); ++i)
		{
			target.push_back(person->knownHumans[i]);
		}
	}

	//마지막으로 정리
	for ( auto iter = peopleData.cbegin(); iter != peopleData.cend(); ++iter )
	{
		if ( iter->isHuman == true )
		{
			humans.push_back(iter->index);
		}
	}	
}

void TownPeopleFinder::Print()
{
	printf_s("Print human list-------------------\n");
	//int count = 0;
	//for ( auto iter = humans.cbegin(); iter != humans.cend(); ++iter )
	//{
	//	printf_s("%-7d", *iter);
	//	count++;
	//	if ( count % 5 == 0 )
	//	{
	//		printf_s("\n");
	//	}		
	//}
	printf_s("\nHuman count : %d\n", humans.size());
	printf_s("-----------------------------------\n\n");
}