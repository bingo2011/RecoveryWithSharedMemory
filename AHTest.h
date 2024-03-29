#ifndef AH_TEST_H_
#define AH_TEST_H_

#include "Recoverable.h"
class AHTestDataSection;

class AHTest : public Recoverable
{
public:
	AHTest();
	~AHTest();

	void InitLocalObjects();
	void RecoverLocalObjects();
private:
	AHTestDataSection* ahTestData;
};

#endif
