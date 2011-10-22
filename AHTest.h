#ifndef AH_TEST_H_
#define AH_TEST_H_

#include "Recoverable.h"

class AHTest : public Recoverable
{
public:
	AHTest();
	~AHTest();

	void InitLocalObjects();
	void RecoverLocalObjects();
private:
	int n_;
	float f_;
};

#endif
