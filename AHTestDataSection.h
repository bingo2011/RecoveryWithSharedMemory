#ifndef AHTEST_RECOVEREDDATA_H_
#define AHTEST_RECOVEREDDATA_H_
#include "BaseDataSection.h"

class AHTestDataSection : public BaseDataSection
{
public:
	AHTestDataSection(Recoverable& obj): BaseDataSection(obj) {}
	~AHTestDataSection(){}
private:
	int n_;
	float f_;
};
#endif
