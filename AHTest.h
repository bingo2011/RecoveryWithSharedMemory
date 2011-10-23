#ifndef AH_TEST_H_
#define AH_TEST_H_

class Recoverable;
class AHTestRecoveredData;

class AHTest : public Recoverable
{
public:
	AHTest();
	~AHTest();

	void InitLocalObjects();
	void RecoverLocalObjects();
private:
	AHTestRecoveredData* ahTestData;
};

#endif
