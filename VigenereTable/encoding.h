#ifndef ENCODING_H_
#define ENCODING_H_

#include "codetable.h"
#include "util.h"

class IEncoding
{
public:
	virtual void Encode(char* sCodeText, char* sEncodeText) = 0;
	virtual ~IEncoding() {};
};

class CVigenereEncoding: public IEncoding
{
public:
	CVigenereEncoding();
	CVigenereEncoding(ICodeTable* _cCodeTable, IUtil* _cUtil, const char* _sKeyText);
	virtual void Encode(char* sCodeText, char* sEncodeText);
	~CVigenereEncoding();
protected:
	void GenerateLongKeyText(const char* sCodeText);

private:
	ICodeTable* cCodeTable;
	IUtil* cUtil;
	char* sKeyText;
};

#endif /* ENCODING_H_ */
