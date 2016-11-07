#ifndef CODETABLE_H_
#define CODETABLE_H_

class ICodeTable
{
public:
	virtual ~ICodeTable() {}
	virtual char Get(const char cText, const char cKey) = 0;
};

class CArrayCodeTable: public ICodeTable
{
public:
	CArrayCodeTable(const char* cFilename);
	virtual char Get(const char cText, const char cKey);

private:
	static const int abc_size=26;
	char vtable[abc_size][abc_size];
};


#endif /* CODETABLE_H_ */
