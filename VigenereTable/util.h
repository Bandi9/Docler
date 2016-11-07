#ifndef UTIL_H_
#define UTIL_H_

class IUtil
{
public:
	virtual ~IUtil() {}
	virtual void ConvertText(char* SText) = 0;
	void GetString(const char* SUserInfo, int textSize, char* SOutputText);
	void WriteTextToFile(const char* sFilename, char* sText);
};

class CHungarianTextUtil: public IUtil
{
public:
	virtual void ConvertText(char* SText);

private:
	char ConvertChar(char cInput) const;
};



#endif /* UTIL_H_ */
