#ifndef BASE_RECOVERED_DATA_H_
#define BASE_RECOVERED_DATA_H_
#include <iostream>
#include "Recoverable.h"
using namespace std;

class BaseRecoveredData
{
public:
	BaseRecoveredData(Recoverable& obj);
	virtual ~BaseRecoveredData() {}
	void* GetAddressInSharedMemory() {return addrInSharedMemory_;}
private:
	Recoverable& obj_;
	bool isFirst_;
	void* addrInSharedMemory_;

	friend ostream& operator<<(ostream&, BaseRecoveredData const&);
};

inline ostream& operator<<(ostream&os, BaseRecoveredData const&data)
{
	os << "name=" << data.obj_.name() << " "
	   << "memory size=" << data.obj_.GetRequiredSharedMemorySize() << " "
	   << "isFirst=" << data.isFirst_ << " "
	   << "address=" << data.addrInSharedMemory_
	   << endl;
	return os;
}
#endif
