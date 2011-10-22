#ifndef RECOVERABLE_H_
#define RECOVERABLE_H_
#include <string>
using namespace std;

class Recoverable
{
public:
	Recoverable() {}
	virtual ~Recoverable() {}
	virtual string name() = 0;
	virtual int GetRequiredSharedMemorySize() = 0;
	virtual void InitLocalObjects() = 0;
	virtual void RecoverLocalObjects() = 0;
};
#endif
