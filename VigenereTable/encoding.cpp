#include <stdio.h>
#include <string.h>

#include "encoding.h"
#include "vigenere.h"

CVigenereEncoding::CVigenereEncoding()
	: cCodeTable(NULL)
	, cUtil(NULL)
{
	sKeyText = new char[1];
	sKeyText[0] = '\0';
}

CVigenereEncoding::CVigenereEncoding(ICodeTable* _cCodeTable, IUtil* _cUtil, const char* _sKeyText)
	: cCodeTable(_cCodeTable)
	, cUtil(_cUtil)
{
	sKeyText=new char[strlen(_sKeyText)+1];
	strcpy(sKeyText, _sKeyText);
	cUtil->ConvertText(sKeyText);
}

CVigenereEncoding::~CVigenereEncoding()
{
	cCodeTable = NULL;
	cUtil = NULL;
	delete [] sKeyText;
}

// Encode text with key //
void CVigenereEncoding::Encode(char* sCodeText, char* sEncodeText)
{
	if (cCodeTable == NULL || cUtil == NULL) {
		throw Encode_error {};
	}

	cUtil->ConvertText(sCodeText);
	size_t codeTextSize=strlen(sCodeText);
	if (codeTextSize==0)
	{
		printf("A nyílt szöveg nem tartalmaz értelmezhetõ betût!\n");
		throw Encode_error {};
	}

	printf("\nAz átalakított nyílt szöveg: %s\n",sCodeText);

	if (strlen(sKeyText)==0)
	{
		printf("A kulcs szöveg nem tartalmaz értelmezhetõ betût!\n");
		throw Encode_error {};
	}

	GenerateLongKeyText(sCodeText);
	printf("\nAz új kulcs szöveg: %s\n", sKeyText);

	for(size_t i=0; i<codeTextSize; i++)
	{
		sEncodeText[i]=cCodeTable->Get(sCodeText[i], sKeyText[i]);
	}
	sEncodeText[codeTextSize]=0;
}

// Generate a long key text //
void CVigenereEncoding::GenerateLongKeyText(const char* sCodeText)
{
	size_t codeTextSize = strlen(sCodeText);
	size_t keyTextSize = strlen(sKeyText);

	if (keyTextSize==0)
	{
		return;
	}

	char* sShortKeyText=new char[keyTextSize+1];
	strcpy(sShortKeyText, sKeyText);

	delete [] sKeyText;
	sKeyText=new char[codeTextSize+keyTextSize];
	strcpy(sKeyText, "");

	while(strlen(sKeyText)<codeTextSize)
	{
		strcat(sKeyText, sShortKeyText);
	}

	sKeyText[codeTextSize]=0;

	delete [] sShortKeyText;
}
