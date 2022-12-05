#include "Project.h"

void main()
{
	InstrumentTree tr;
	Musician** musicianGroup;
	Musician*** MusicianCollection;
	FILE* fp = fopen("instruments.txt", "r");
	FILE* f = fopen("players.txt", "r");
	int numOfInst, numOfMusician;
	int loopIndex, numOfInstInConcert;
	char* concertLine;

	checkNullPointer(fp);
	checkNullPointer(f);

	tr = createInstTreeFromTxt(fp, &numOfInst);
	//print2D(tr.root);
	//printf("\n\n");

	musicianGroup = createMusicianGroup(f, &tr, &numOfMusician);
	MusicianCollection = createMusiciansCollection(musicianGroup, numOfMusician, numOfInst);

	concertLine = getConcertLine();

	while (concertLine[0] != '\0')
	{

		Concert res = createConcertInfoFromLine(concertLine, tr);
		//numOfInstInConcert = countNumOfCINodes(&res);

		CINode* currInst = res.instruments.head;
		int* numOfPlayersPerInst = createNumOfPlayersPerInst(musicianGroup, numOfInst, numOfMusician);
		while (currInst != NULL)
		{
			mergeSort(MusicianCollection[currInst->instData->instID], numOfPlayersPerInst[currInst->instData->instID], currInst->instData->importance, currInst->instData->instID);
			currInst = currInst->next;
		}
		concertLine = getConcertLine();

	}

	system("pause");

}
