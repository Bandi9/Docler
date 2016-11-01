/*
 * feladat.cpp
 *
 *  Created on: 2016. okt. 31.
 *      Author: Bandi
 */

#include <stdio.h>
#include <string.h>

#define DEBUG 0

#define VIGENERE_INPUT_FILE "vtabla.dat"
#define VIGENERE_OUTPUT_FILE "kodolt.dat"
#define CODE_TEXT_LENGTH 256
#define KEY_TEXT_LENGTH 6
#define ABC_SIZE 26

// If someone need to generate vtable.dat. (I needed to compile it on my Android phone.)
void GenerateVtable()
{
	FILE *fp=fopen("vtable.dat","w");
	if(fp!=NULL)
	{
		int i, j;
		char character;
		for(i=0; i<ABC_SIZE; i++)
		{
			for(j=0, character=i+j; j<ABC_SIZE; j++, character++)
			{
				if(character==ABC_SIZE)
					character=0;

				fputc(character+'A', fp);
			}
			if(i<ABC_SIZE-1)
				fputc('\n', fp);
		}
		fclose(fp);
	}
	else
	{
		printf("Error opening file for writing : %s\n","vtable.dat");
	}
}


// Convert text to uppercase, remove non letters and convert special hungarian characters to english.
char ConvertChar(char cInput)
{
	char cOutput = '\0';

	if('A'<=cInput && cInput<='Z')
		cOutput=cInput;
	else if('a'<=cInput && cInput<='z')
		cOutput=cInput-32;
	else
	{
		switch(cInput)
		{
			case '�':
			case '�':
				cOutput='A';
				break;
			case '�':
			case '�':
				cOutput='E';
				break;
			case '�':
			case '�':
				cOutput='I';
				break;
			case '�':
			case '�':
			case '�':
			case '�':
			case '�':
			case '�':
				cOutput='O';
				break;
			case '�':
			case '�':
			case '�':
			case '�':
			case '�':
			case '�':
				cOutput='U';
				break;
		}
	}

#if DEBUG
	printf("DEBUG: input:%c output:%c\n",cInput,cOutput);
#endif
	return cOutput;
}

int main()
{
	char codeText[CODE_TEXT_LENGTH] = "";
	char keyTextLong[CODE_TEXT_LENGTH] = "";
	char keyText[KEY_TEXT_LENGTH] = "";
	char vtable[ABC_SIZE][ABC_SIZE];
	char encodeText[CODE_TEXT_LENGTH+KEY_TEXT_LENGTH-2] = "";

// Input text //
	printf("K�rem adja meg a sz�veget (max 255 karakter): ");
	gets(codeText);

// Convert text to uppercase, remove non letters and convert special hungarian characters to english //
	int read, write;
	int codeTextLen = strlen(codeText);
	for(read=write=0; read<codeTextLen; read++)
	{
		char newChar=ConvertChar(codeText[read]);
		if(newChar!='\0')
		{
			codeText[write++]=newChar;
		}
	}
	codeText[write]=0;
	printf("\nAz �talak�tott ny�lt sz�veg: %s\n",codeText);

// Input key //
	printf("K�rem adja meg a kulcsot (min 1, max %d karakter): ", KEY_TEXT_LENGTH-1);
	gets(keyText);

// Convert key to uppercase //
	int i;
	int keyTextLen = strlen(keyText);
	for(i=0;i<keyTextLen;i++)
	{
		if('a'<=keyText[i] && keyText[i]<='z')
			keyText[i]=keyText[i]-32;
	}
#if DEBUG
	printf("DEBUG: key text:%s\n",keyText);
#endif

// Interling key to long of text //
	codeTextLen = strlen(codeText);
	while(strlen(keyTextLong)<codeTextLen)
		strcat(keyTextLong, keyText);

	keyTextLong[codeTextLen]=0;
#if DEBUG
	printf("DEBUG: \ncode:%s\nkey :%s\n",codeText,keyTextLong);
#endif
	printf("\nAz �j kulcssz�veg: %s\n", keyTextLong);

// Load vtabla.dat into memory //
	FILE *codetablefile=fopen(VIGENERE_INPUT_FILE,"rt");
	if(codetablefile==NULL)
	{
		printf("Error opening input file %s\n", VIGENERE_INPUT_FILE);
		return 0;
	}
	for(i=0; i<ABC_SIZE && fscanf(codetablefile, "%s", vtable[i])!=0; i++)
	{
#if DEBUG
		printf("DEBUG: %s\n", vtable[i]);
#endif
	}
	fclose(codetablefile);

// Encode text with key //
	for(i=0;i<codeTextLen;i++)
	{
		encodeText[i]=vtable[keyTextLong[i]-'A'][codeText[i]-'A'];
	}
	encodeText[i]=0;
	printf("K�dolt sz�veg: %s\n", encodeText);

// Write to file the encoded text //
	FILE *fp=fopen(VIGENERE_OUTPUT_FILE,"w");
	if(fp!=NULL)
	{
		fputs(encodeText, fp);
		fclose(fp);
	}
	else
	{
		printf("Error opening output file %s\n", VIGENERE_OUTPUT_FILE);
		return 0;
	}

	return 0;
}
