#ifndef BASE_RECOVERED_DATA_H_
#define BASE_RECOVERED_DATA_H_
#include <iostream>
using namespace std;

class Recoverable;

class BaseDataSection
{
public:
	BaseDataSection(Recoverable& obj);
	virtual ~BaseDataSection();
	void* GetAddressInSharedMemory() {return addrInSharedMemory_;}
private:
	Recoverable& obj_;
	bool isFirst_;
	void* addrInSharedMemory_;

	friend ostream& operator<<(ostream&, BaseDataSection const&);
};

inline ostream& operator<<(ostream&os, BaseDataSection const&data)
{
	os << "name=" << data.obj_.name() << " "
	   << "memory size=" << data.obj_.GetRequiredSharedMemorySize() << " "
	   << "isFirst=" << data.isFirst_ << " "
	   << "address=" << data.addrInSharedMemory_
	   << endl;
	return os;
}
#endif
