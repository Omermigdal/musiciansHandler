#ifndef PROJ_H

#define PROJ_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Macros.h"

#define INSTRUMENTS_SIZE 20
#define PLAYERS_SIZE 11
#define MAX_LINE_LEN 150
#define NOT_FOUND -1
#define COUNT 10
#define READING_INSTRUMENT 1
#define READING_INS_NUM 2
#define READING_IMPORTANCE 3

typedef struct treeNode {
	char* instrument; // Instrument's name
	unsigned short insId; // Instrument's Id
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;

typedef struct musicianpriceinstrument {
	unsigned short insId;
	float price;
} MusicianPriceInstrument;

typedef struct listNode {
	MusicianPriceInstrument* data;
	struct listNode* next;
} ListNode;

typedef struct mpiList {
	ListNode* head;
	ListNode* tail;
} MPIList;

typedef struct musician {
	char** name;
	int nameSize;
	MPIList instruments;
} Musician;

typedef struct concertInstrument {
	int num;
	int instID;
	char importance;
} ConcertInstrument;

typedef struct ciNode {
	ConcertInstrument* instData;
	struct ciNode* next;
} CINode;

typedef struct ciList {
	CINode* head;
	CINode* tail;
} CIList;

typedef struct date
{
	int day, month, year;
	float hour;
} Date;

typedef struct concert {
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;

void checkMemoryAllocation(void*);
TreeNode* createNewTNode(char*, int, TreeNode*, TreeNode*);
void printTreeInorder(InstrumentTree);
void printTreeInorderHelper(TreeNode*);
void freeTree(InstrumentTree);
void freeTreeHelper(TreeNode*);
void print2DUtil(TreeNode*, int);
void print2D(TreeNode*);
int findInsId(InstrumentTree, char*);
int findInsIdHelper(TreeNode*, char*);
void makeEmptyList(MPIList*);
bool isEmptyList(MPIList* lst);
void insertDataToEndList(MPIList* lst, unsigned short insID, float InPrice);
ListNode* createNewListNode(unsigned short insID, float price, ListNode* next);
void insertNodeToEndList(MPIList* lst, ListNode* tail);
ListNode* getNodeByIndex(MPIList* lst, int index);
int countMusicians(FILE* fp);
int* createNumOfPlayersPerInst(Musician**, int, int);
Musician*** createMusiciansCollection(Musician** musiciansGroup, int numOfMusicians, int numOfInstruments);
void createMusiciansCollectionArrays(Musician*** MusiciansCollection, int* numOfPlayersPerInsArr, int numOfInstruments);
void printPlayersByInst(Musician*** MusicianCollection, Musician** musicianArr, int numOfInstruments, int numOfMusicians);
InstrumentTree createInstTreeFromTxt(FILE* fp, int* numOfInst);
TreeNode* insertInstrumentToTree(TreeNode* root, char* InstrumentName, int instID);
Musician** createMusicianGroup(FILE* fp, InstrumentTree* tr, int* numOfMusician);
void fixMusicianFullName(char* line, char*** stringArray, int* logSize, int* physSize);
int musicianNameSize(char** musicianLine, InstrumentTree* tr);
Musician* createMusician(char** currLineStrArray, int linesStrArraySize, InstrumentTree tr);
void addNameToMusician(char** name, int namePhysSize, int* nameLogSize, char* currStr);
Concert createConcertInfoFromLine(char* line, InstrumentTree tr);
float createFormattedHour(char* strHour);
bool isEmptyCIList(CIList* lst);
void insertNodeToEndCIList(CIList* lst, CINode* tail);
void insertDataToEndCIList(CIList* lst, int insID, int numOfInst, char instImportance);
CINode* createNewCIListNode(int instID, int numOfInst, char instImportance, CINode* next);
int countNumOfCINodes(CIList* lst);
float getInstPriceByID(MPIList lst, int instID);
void copyArr(Musician** dest, Musician** src, int size);
Musician** mergeByFlag(Musician** arr1, int size1, Musician** arr2, int size2, char ascend_flag, int instID);
void mergeSort(Musician** pArr, int size, char ascend_flag, int instID);

#endif