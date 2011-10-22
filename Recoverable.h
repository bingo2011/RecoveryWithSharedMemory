#ifndef RECOVERABLE_H_
#define RECOVERABLE_H_

class Recoverable
{
public:
	Recoverable();
	virtual ~Recoverable();
	void std:string name() = 0;
	void int GetRequiredSharedMemorySize() = 0;
	virtual void InitLocalObjects() = 0;
	virtual void RecoverLocalObjects() = 0;
};
#endif
