#include <stdio.h>

#include "vigenere.h"

#include "codetable.h"
#include "encoding.h"

static const char* const tableFilename = "vtabla.dat";
static const char* const resultFilename = "kodolt.dat";

static const int codeTextSize = 255;
static const int keyTextSize = 5;

int main()
{
	char sCodeText[codeTextSize+2] = "";
	char sKeyText[keyTextSize+2] = "";
	char sEncodeText[codeTextSize+1] = "";

	IUtil* cTextUtil = NULL;
	ICodeTable* cCodeTable = NULL;
	IEncoding* cEncoding = NULL;

	int ret = 0;

	try
	{
		cTextUtil = new CHungarianTextUtil;
		// Input text //
		cTextUtil->GetString("Kérem adja meg a szöveget", codeTextSize, sCodeText);

		// Input key //
		cTextUtil->GetString("Kérem adja meg a kulcsot", keyTextSize, sKeyText);

		cCodeTable = new CArrayCodeTable(tableFilename);
		cEncoding = new CVigenereEncoding(cCodeTable, cTextUtil, sKeyText);

		cEncoding->Encode(sCodeText, sEncodeText);
		printf("Kódolt szöveg: %s\n", sEncodeText);

		cTextUtil->WriteTextToFile(resultFilename, sEncodeText);

		delete cEncoding;
		delete cCodeTable;
		delete cTextUtil;
	}
	catch (...)
	{
		if (cTextUtil)
		{
			delete cTextUtil;
		}
		if (cCodeTable)
		{
			delete cCodeTable;
		}
		if (cEncoding)
		{
			delete cEncoding;
		}
		ret = -1;
	}

	return ret;
}

