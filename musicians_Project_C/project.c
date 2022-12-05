#include "Project.h"

// function allocates and returns a treee node with the data provided
TreeNode* createNewTNode(char* instrument, int insId, TreeNode* left, TreeNode* right)
{
	TreeNode* res;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(res);
	res->instrument = (char*)malloc(sizeof(char));
	checkMemoryAllocation(res->instrument);
	res->instrument = instrument;
	res->insId = insId;
	res->left = left;
	res->right = right;
	return res;
}

// this function is casing for recursive function
void printTreeInorder(InstrumentTree tr)
{
	printTreeInorderHelper(tr.root);
}

// this function recieves a treeNode ( root)  and prints  the tree in order
void printTreeInorderHelper(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		printTreeInorderHelper(root->left); // left
		printf("instrument: %s\n", root->instrument); // right
		printf("id : %d\n", root->insId);
		printTreeInorderHelper(root->right); // root
	}
}

// this function is casing to recursive function
void freeTree(InstrumentTree tr)
{
	freeTreeHelper(tr.root);
}

// function recieves a tree node ( root)
// function frees all the allocated memory of the tree.
void freeTreeHelper(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeHelper(root->left);
		freeTreeHelper(root->right);
		free(root->instrument);
		free(root);
	}
}

void print2DUtil(TreeNode* root, int space)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("(%s) %d\n", root->instrument, root->insId);

	// Process left child
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(TreeNode* root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}

int findInsId(InstrumentTree tree, char* instrument)
{
	return findInsIdHelper(tree.root, instrument);
}

int findInsIdHelper(TreeNode* root, char* instrument)
{
	int found;
	if (root == NULL)
		return NOT_FOUND;
	else
	{
		found = findInsIdHelper(root->left, instrument);
		if (found == NOT_FOUND)
		{
			found = findInsIdHelper(root->right, instrument);
		}
		if (found == NOT_FOUND)
		{
			if (strcmp(root->instrument, instrument) == 0)
			{
				return root->insId;
			}
			else
				return NOT_FOUND;
		}

	}
}

// function receieves a pointer
// function is checking if the pointer is null
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation error");
		exit(1);
	}
}

int countMusicians(FILE* fp) {

	long int fileLastPos;
	int counter = 0;
	char tmpStr[150];

	fileLastPos = ftell(fp);

	rewind(fp);

	while (fgets(tmpStr, MAX_LINE_LEN, fp) != NULL) {
		counter++;
	}

	fseek(fp, fileLastPos, SEEK_SET);

	return counter;

}

void makeEmptyList(MPIList* lst) {
	lst->head = NULL;
	lst->tail = NULL;
}

ListNode* createNewListNode(unsigned short insID, float InPrice, ListNode* next) {

	ListNode* res;
	MusicianPriceInstrument* resSt;

	res = (ListNode*)malloc(sizeof(ListNode));
	if (!res) {
		exit(1);
	}

	resSt = (MusicianPriceInstrument*)malloc(sizeof(MusicianPriceInstrument));
	if (!resSt) {
		exit(1);
	}

	resSt->insId = insID;
	resSt->price = InPrice;
	res->data = resSt;
	res->next = next;

	return res;

}

void insertDataToEndList(MPIList* lst, unsigned short insID, float InPrice)
{
	ListNode* newTail;
	newTail = createNewListNode(insID, InPrice, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(MPIList* lst, ListNode* tail)
{
	if (isEmptyList(lst) == true) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

void makeEmptyCIList(CIList* lst) {
	lst->head = NULL;
	lst->tail = NULL;
}

CINode* createNewCIListNode(int instID, int numOfInst, char instImportance, CINode* next) {

	CINode* res;
	ConcertInstrument* resCI;

	res = (CINode*)malloc(sizeof(CINode));
	checkNullPointer(res);

	resCI = (ConcertInstrument*)malloc(sizeof(ConcertInstrument));
	checkNullPointer(resCI);

	resCI->instID = instID;
	resCI->num = numOfInst;
	resCI->importance = instImportance;
	res->instData = resCI;
	res->next = next;

	return res;

}

void insertDataToEndCIList(CIList* lst, int insID, int numOfInst, char instImportance)
{
	CINode* newTail;
	newTail = createNewCIListNode(insID, numOfInst, instImportance, NULL);
	insertNodeToEndCIList(lst, newTail);
}

void insertNodeToEndCIList(CIList* lst, CINode* tail)
{
	if (isEmptyCIList(lst) == true) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

float getInstPriceByID(MPIList lst, int instID) {

	ListNode* curr = lst.head;
	float res = 0;

	while (curr != NULL) {

		if (curr->data->insId == instID) {
			return curr->data->price;
		}
		curr = curr->next;
	}

	return res;

}

ListNode* getNodeByIndex(MPIList* lst, int index) {

	ListNode* curr = lst->head;

	while (curr != NULL && index > 0) {
		curr = curr->next;
		index--;
	}

	return curr;

}

bool isEmptyList(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

bool isEmptyCIList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

// function creates a musician collection array
// musicianCollection[i] is and array of musicians playing the instrument with insId as i.
Musician*** createMusiciansCollection(Musician** musiciansGroup, int numOfMusicians, int numOfInstruments)
{
	ListNode* currIns;
	int currInsID, currIndOfCurrIns;
	Musician* currMusician;
	int i;

	Musician*** MusiciansCollection = (Musician***)malloc(numOfInstruments * sizeof(Musician**));// allocationg the array to array of pointers to the muscians
	checkMemoryAllocation(MusiciansCollection);

	int* numOfPlayersPerInsArr = createNumOfPlayersPerInst(musiciansGroup, numOfInstruments, numOfMusicians); // change name
	createMusiciansCollectionArrays(MusiciansCollection, numOfPlayersPerInsArr, numOfInstruments);

	int* numOfPlayersPerIns_LogSize = (int*)calloc(numOfInstruments, sizeof(int)); // creating an helping array to save the logsize of each instruments player
	checkMemoryAllocation(numOfPlayersPerIns_LogSize);

	for (i = 0; i < numOfMusicians; i++) // going over the musiciansGroup array (going over each musician)
	{
		currMusician = musiciansGroup[i];
		currIns = currMusician->instruments.head;
		while (currIns != NULL) // going over each instrument played by the current musician
		{
			currInsID = currIns->data->insId; // the id of the current instruments in the instruments list
			currIndOfCurrIns = numOfPlayersPerIns_LogSize[currInsID]; // the index of the array of pointers to musician
			MusiciansCollection[currInsID][currIndOfCurrIns] = currMusician; // update pointer to musician playing the certain insttrument.
			numOfPlayersPerIns_LogSize[currInsID]++;  // update logical size of the array of the pointers to the musicians playing the instrument.
			currIns = currIns->next;
		}
	}

	free(numOfPlayersPerIns_LogSize);
	free(numOfPlayersPerInsArr);

	return MusiciansCollection;
}

// function allocates musician** arrays to each cell in the musicianCollection array.
void createMusiciansCollectionArrays(Musician*** MusiciansCollection, int* numOfPlayersPerInsArr, int numOfInstruments)
{
	int i;
	for (i = 0; i < numOfInstruments; i++)
	{
		MusiciansCollection[i] = (Musician**)malloc(numOfPlayersPerInsArr[i] * sizeof(Musician*)); // creating musician array for each instrument
		checkMemoryAllocation(MusiciansCollection[i]);
	}
}

// function creates an int array
//  numOfPlayersPerIns[i] holds the number of players playing the instrument which his ID is i.
int* createNumOfPlayersPerInst(Musician** musicianGroup, int numOfInst, int numOfMusician)
{
	int i, j, tmpInsID;
	int* numOfPlayersPerIns;
	ListNode* curr;
	numOfPlayersPerIns = (int*)calloc(numOfInst, sizeof(int));
	checkMemoryAllocation(numOfPlayersPerIns);

	for (i = 0; i < numOfMusician; i++) // going over musicians
	{

		curr = musicianGroup[i]->instruments.head;

		while (curr != NULL) // going over each musician's instruments
		{

			tmpInsID = curr->data->insId;

			numOfPlayersPerIns[tmpInsID]++; // updating the array as explained in header of function

			curr = curr->next;

		}

	}

	return numOfPlayersPerIns;

}

// to be deleted
// print players playing each instrument.
void printPlayersByInst(Musician*** MusicianCollection, Musician** musicianArr, int numOfInstruments, int numOfMusicians)
{

	int* Size = createNumOfPlayersPerInst(musicianArr, numOfInstruments, numOfMusicians);
	int i;

	for (i = 0; i < numOfInstruments; i++)
	{
		printf("instrument number #%d: ", i);
		for (int j = 0; j < Size[i]; j++) {
			printf("%s ", MusicianCollection[i][j]->name[0]);
		}
		printf("\n");
	}

}

// function recieves a tree root and instrument information
// function inserts the instrument to correct place in the tree.
TreeNode* insertInstrumentToTree(TreeNode* root, char* InstrumentName, int instID) {

	TreeNode* newNode;

	if (root == NULL) {
		newNode = createNewTNode(InstrumentName, instID, NULL, NULL);
		return newNode;
	}

	if (strcmp(InstrumentName, root->instrument) < 0)
	{
		root->left = insertInstrumentToTree(root->left, InstrumentName, instID);
	}
	else
	{
		root->right = insertInstrumentToTree(root->right, InstrumentName, instID);
	}

	return root;

}

// function creates and returns the instrument tree created from the text file recieved
InstrumentTree createInstTreeFromTxt(FILE* fp, int* numOfInst)
{

	char tmpStr[MAX_LINE_LEN]; // creating static string for the input
	char* currStr = NULL;
	int tmpLogSize, instCounter = 0;
	long int fileLastPos;
	InstrumentTree res;
	TreeNode* root = NULL;

	fileLastPos = ftell(fp); // saving the file pointer

	while (fgets(tmpStr, MAX_LINE_LEN, fp) != NULL) // going over each line in the file and inserting to tmpStr.
	{
		if (!(feof(fp)))
		{
			tmpLogSize = strlen(tmpStr) - 1;
			tmpStr[tmpLogSize] = '\0'; // removing the \n from the string
		}

		currStr = (char*)malloc(tmpLogSize * sizeof(char));
		if (currStr == NULL) {
			exit(1);
		}
		strcpy(currStr, tmpStr);
		root = insertInstrumentToTree(root, currStr, instCounter);
		instCounter++;
	}

	fseek(fp, fileLastPos, SEEK_SET); // returning the file pointer to the spot before making the tree

	*numOfInst = instCounter;
	res.root = root;

	return res;

}

// creates the musician full name ( string array) from the line recieved
void fixMusicianFullName(char* line, char*** stringArray, int* logSize, int* physSize)
{
	char* currString;
	char** localStringArray;
	int lStringArrayPhys = 2, lStringArrayLog = 0;
	localStringArray = (char**)malloc(lStringArrayPhys * sizeof(char*));
	checkMemoryAllocation(localStringArray);
	char seps[] = " ,.;:?!-\t'()[]{}<>~_\n";
	currString = strtok(line, seps);

	while (currString != NULL) // tokenizing the line
	{
		localStringArray[lStringArrayLog] = currString; // inserting line to correct spot in the string array 
		lStringArrayLog++;

		if (lStringArrayPhys == lStringArrayLog) // chekking for enough space in the string array
		{
			lStringArrayPhys *= 2;
			localStringArray = (char**)realloc(localStringArray, lStringArrayPhys * sizeof(char*));
			checkMemoryAllocation(localStringArray);
		}
		currString = strtok(NULL, seps); // progressing tokenzier 
	}

	*stringArray = localStringArray; // returning output viariables
	*logSize = lStringArrayLog;
	*physSize = lStringArrayPhys;
}

// function returns the size of the name of the musician recieved
int musicianNameSize(char** musicianFullName, InstrumentTree* tr) {

	int i = 0, nameSize = 0;

	while (findInsId(*tr, musicianFullName[i]) == -1) // if the string describing the musican is not an instrument - it is a part of his name
	{
		nameSize++;
		i++;
	}

	return nameSize;

}

// function creates the musicianGroup array
Musician** createMusicianGroup(FILE* fp, InstrumentTree* tr, int* numOfMusician) {
	// create num of players per inst 
	char line[MAX_LINE_LEN];
	char** currMusicianFullName;
	int logSizeStrArr, physSizeStrArr, numOfMusicians, writeInd = 0;
	Musician* currMusician;
	Musician** musiciansGroup;
	numOfMusicians = countMusicians(fp);
	musiciansGroup = (Musician**)malloc(numOfMusicians * sizeof(Musician*));
	checkNullPointer(musiciansGroup);

	while (fgets(line, MAX_LINE_LEN, fp) != NULL) // going over the lines in the text file
	{
		fixMusicianFullName(line, &currMusicianFullName, &logSizeStrArr, &physSizeStrArr); // creating the musician name (string array), without the instruments in the line
		currMusician = createMusician(currMusicianFullName, logSizeStrArr, *tr); // creating a musician according to the line
		musiciansGroup[writeInd] = currMusician; // adding the muscian created to musicianGroup
		writeInd++;
		// need to free of the string array with the name mixed with instrumnets
	}
	// free memory allocation needed....................................................

	*numOfMusician = numOfMusicians;
	return musiciansGroup;
}

// function creates and returns a musician
Musician* createMusician(char** musicianFullName, int musicianFullNameSize, InstrumentTree tr)
{
	int i;
	Musician* musician = (Musician*)malloc(sizeof(Musician));
	checkNullPointer(musician);
	makeEmptyList(&(musician->instruments)); // creating instrument list for the new musician
	int namePhysSize = musicianNameSize(musicianFullName, &tr), nameLogSize = 0; // the name is still with instruments and price inside
	int currInsPrice, currInsId;

	musician->name = (char**)malloc(namePhysSize * sizeof(char*));// allocating memory for the full name(string array).

	for (i = 0; i < musicianFullNameSize; i++)
	{
		currInsId = findInsId(tr, musicianFullName[i]);
		if (currInsId == NOT_FOUND) // current string is a name
		{
			addNameToMusician(musician->name, namePhysSize, &nameLogSize, musicianFullName[i]);
		}
		else // current string is an instrument
		{
			currInsPrice = atoi(musicianFullName[i + 1]); // price is always first string after instrument // maybe sscanf
			insertDataToEndList(&(musician->instruments), currInsId, currInsPrice);
			i++;
		}
	}
	musician->nameSize = nameLogSize;
	return musician;

}

// function adds the string wich is not an instrument or price to the full name of the musican.
void addNameToMusician(char** musicianFullName, int namePhysSize, int* nameLogSize, char* not_InstrumentOrPrice)
{
	char* nameToAdd = _strdup(not_InstrumentOrPrice);
	musicianFullName[*nameLogSize] = nameToAdd;
	(*nameLogSize)++;
}

char* getConcertLine() {

	char* concertLine;
	char tmpChar;
	int logSize = 0, physSize = 2;

	concertLine = (char*)malloc(physSize * sizeof(char));
	checkNullPointer(concertLine);

	scanf("%c", &tmpChar);

	while (tmpChar != '\n') {
		if (logSize == physSize) {
			physSize *= 2;
			concertLine = (char*)realloc(concertLine, physSize * sizeof(char));
			checkNullPointer(concertLine);
			concertLine[logSize] = tmpChar;
		}
		else {
			concertLine[logSize] = tmpChar;
		}
		logSize++;
		scanf("%c", &tmpChar);
	}

	if (logSize == physSize) {
		physSize *= 2;
		concertLine = (char*)realloc(concertLine, physSize * sizeof(char));
		checkNullPointer(concertLine);
		concertLine[logSize] = '\0';
	}
	else {
		concertLine[logSize] = '\0';
	}

	concertLine = (char*)realloc(concertLine, logSize + 1 * sizeof(char));
	checkNullPointer(concertLine);

	return concertLine;

}

Concert createConcertInfoFromLine(char* line, InstrumentTree tr)
{
	Concert resConcert;
	makeEmptyCIList(&(resConcert.instruments));

	bool finishedReadingInst = false;
	const char seps[] = " ";
	char* hour, * token, * currInstrument, instReadingIndex = READING_INSTRUMENT; // reading instuments starts from reading the nstrument name
	int currInstId, currNumInst;
	char currInsImportance;

	resConcert.name = strtok(line, seps); // get concert name from line
	resConcert.date_of_concert.day = atoi(strtok(NULL, seps)); // get day from line
	resConcert.date_of_concert.month = atoi(strtok(NULL, seps)); // get month from line
	resConcert.date_of_concert.year = atoi(strtok(NULL, seps)); // get year from line

	hour = strtok(NULL, seps); // get hour from line "20:30"
	resConcert.date_of_concert.hour = createFormattedHour(hour); // push new format to hour

	token = strtok(NULL, seps);
	while (token != NULL)
	{

		if (instReadingIndex == READING_INSTRUMENT) // reading the instrument
		{
			currInstrument = token;
			currInstId = findInsId(tr, currInstrument);
			instReadingIndex++;
		}
		else if (instReadingIndex == READING_INS_NUM) // reading number of instruments
		{
			currNumInst = atoi(token);
			instReadingIndex++;
		}
		else if (instReadingIndex == READING_IMPORTANCE) // reading importance of the current instrument
		{
			currInsImportance = token[0];
			finishedReadingInst = true;
			instReadingIndex = 1;
		}

		if (finishedReadingInst == true)
		{
			insertDataToEndCIList(&(resConcert.instruments), currInstId, currNumInst, currInsImportance);
			finishedReadingInst = false;
		}

		token = strtok(NULL, seps);

	}

	return resConcert;

}

float createFormattedHour(char* strHour)
{
	int hour, minutes;
	float newHour, newMinutes, time;
	sscanf(strHour, "%f:%d", &newHour, &minutes);

	newMinutes = (float)minutes / 60.0;
	time = newMinutes + newHour;

	return time;
}

int countNumOfCINodes(CIList* lst) {

	CINode* curr = lst->head;
	int counter = 0;

	while (curr != NULL) {

		counter++;
		curr = curr->next;

	}

	return counter;

}

void mergeSort(Musician** pArr, int size, char ascend_flag, int instID)
{
	Musician** tmpArr = (Musician**)malloc(size * sizeof(Musician*));
	checkNullPointer(tmpArr);

	if (tmpArr == NULL)
	{
		printf("Memory allocation failed");
		exit(1);
	}
	if (size <= 1)
		return;
	else
	{
		mergeSort(pArr, size / 2, ascend_flag, instID); // recursive call with half of the array
		mergeSort(pArr + size / 2, size - size / 2, ascend_flag, instID); // recursive call with the second half of the array.
		tmpArr = mergeByFlag(pArr, size / 2, pArr + size / 2, size - size / 2, ascend_flag, instID);
	}
	copyArr(pArr, tmpArr, size); // copying temp to pArr
	free(tmpArr);
}

Musician** mergeByFlag(Musician** arr1, int size1, Musician** arr2, int size2, char ascend_flag, int instID)
{
	int ind1, ind2, resInd;
	float tmpPrice1, tmpPrice2;
	ind1 = ind2 = resInd = 0;
	Musician** res = (Musician**)malloc((size1 + size2) * sizeof(Musician*)); // initializing the result int* array
	checkNullPointer(res);

	while ((ind1 < size1) && (ind2 < size2)) // whule we are not finished going over the arrays.
	{
		tmpPrice1 = getInstPriceByID(arr1[ind1]->instruments, instID);
		tmpPrice2 = getInstPriceByID(arr2[ind2]->instruments, instID);

		if ((ascend_flag - '0') == 0) // if the users wats the arrays to be merged ascended.
		{
			if (tmpPrice1 <= tmpPrice2) // checking the value of the arrays (int).
			{
				res[resInd] = arr1[ind1];
				ind1++;
			}
			else
			{
				res[resInd] = arr2[ind2];
				ind2++;
			}
			resInd++;
		}
		else // the user wants the arrays to be merged descended.
		{
			if (tmpPrice1 >= tmpPrice2)
			{
				res[resInd] = arr1[ind1];
				ind1++;
			}
			else
			{
				res[resInd] = arr2[ind2];
				ind2++;
			}
			resInd++;
		}
	}
	while (ind1 < size1)
	{
		res[resInd] = arr1[ind1];
		resInd++;
		ind1++;
	}
	while (ind2 < size2)
	{
		res[resInd] = arr2[ind2];
		resInd++;
		ind2++;
	}
	return res;
}

void copyArr(Musician** dest, Musician** src, int size)
{
	for (int i = 0; i < size; i++)
		dest[i] = src[i];
}
