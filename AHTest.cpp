#include "AHTest.h"
#include "AHTestDataSection.h"

AHTest::AHTest()
{
	AHTestDataSection *a = new AHTestDataSection(*this);
}

AHTest::~AHTest()
{

}

void AHTest::InitLocalObjects()
{

}

void AHTest::RecoverLocalObjects()
{

}
