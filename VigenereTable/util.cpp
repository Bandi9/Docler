#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "util.h"
#include "vigenere.h"

void IUtil::GetString(const char* SUserInfo, int textSize, char* SOutputText)
{
	printf("%s (min 1, max %d karakter): ", SUserInfo, textSize);
	if (fgets(SOutputText, textSize+1, stdin)) {
		size_t outputTextSize=strlen(SOutputText);

		if (SOutputText[outputTextSize-1]=='\n')
		{
			SOutputText[--outputTextSize]=0;		// remove \n character from the end of text
		}

		if (outputTextSize==0)
		{
			printf("Üres szöveg!\n");
			throw GetStringIsEmpty_error {};
		}
	}
}

// Write the encoded text into file //
void IUtil::WriteTextToFile(const char* sFilename, char* sText)
{
	FILE *fp=fopen(sFilename,"w");
	if(fp!=NULL)
	{
		fputs(sText, fp);
		fclose(fp);
	}
	else
	{
		printf("Nem sikerült megnyitni írásra a file-t: %s\n", sFilename);
		throw WriteTextToFile_error {};
	}
}


// Convert character to uppercase, remove non letters and convert special hungarian character to english.
char CHungarianTextUtil::ConvertChar(char cInput) const
{
	char cOutput = 0;

	if (isupper(cInput)) {
		cOutput=cInput;
	}
	else if (islower(cInput)) {
		cOutput=(char)toupper(cInput);
	}
	else {
		switch (cInput) {
			case 'á':
			case 'Á':
				cOutput='A';
				break;
			case 'é':
			case 'É':
				cOutput='E';
				break;
			case 'í':
			case 'Í':
				cOutput='I';
				break;
			case 'ó':
			case 'ö':
			case 'õ':
			case 'Ó':
			case 'Ö':
			case 'Õ':
				cOutput='O';
				break;
			case 'ú':
			case 'ü':
			case 'û':
			case 'Ú':
			case 'Ü':
			case 'Û':
				cOutput='U';
				break;
			default:
				;
		}
	}

	return cOutput;
}

// Convert text to upper case, remove non letters and convert special hungarian characters to english.
void CHungarianTextUtil::ConvertText(char* sText)
{
	if (sText == NULL) {
		return;
	}

	size_t textSize = strlen(sText);
	size_t read, write;
	for (read = write = 0; read < textSize; read++) {
		char newChar = ConvertChar(sText[read]);
		if (newChar != '\0') {
			sText[write++] = newChar;
		}
	}
	sText[write] = '\0';
}


