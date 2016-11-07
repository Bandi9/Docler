#include <stdio.h>
#include <string.h>

#include "codetable.h"
#include "vigenere.h"

CArrayCodeTable::CArrayCodeTable(const char* cFilename)
{
// Load vtabla.dat into memory //
	FILE *pCodetableFile=fopen(cFilename,"rt");
	if(pCodetableFile==NULL)
	{
		printf("Nem sikerült megnyitni olvasásra a file-t: %s\n", cFilename);
		throw ArrayCodeTableInit_error {};
	}
	for(int i=0; i<abc_size && fscanf(pCodetableFile, "%s", vtable[i])!=0; i++)
	{
	}
	fclose(pCodetableFile);
}


char CArrayCodeTable::Get(const char cText, const char cKey)
{
	char cEncode = 0;
	int indexX = cKey-'A';
	int indexY = cText-'A';
	if (indexX<abc_size && indexY<abc_size)
	{
		cEncode=vtable[indexX][indexY];
	}

	return cEncode;
}
