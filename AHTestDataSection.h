#ifndef AHTEST_RECOVEREDDATA_H_
#define AHTEST_RECOVEREDDATA_H_
#include "BaseDataSection.h"

class AHTestDataSectioin : public BaseDataSection
{
public:
	AHTestDataSectioin(Recoverable& obj): BaseDataSection(obj) {}
	~AHTestDataSectioin(){}
private:
	int n_;
	float f_;
};
#endif
