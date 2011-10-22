#ifndef BASE_RECOVERED_DATA_H_
#define BASE_RECOVERED_DATA_H_

class Recoverable;

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

inline ostream& operator<<(ostream&os, BaseRecoveredData const&arr)
{
	os << "name=" << obj.name() << " "
	   << "memory size=" << obj.GetRequiredSharedMemorySize() << " "
	   << "isFirst=" << isFirst_ << " "
	   << "address=" << addrInSharedMemory_
	   << endl;
	return os;
}
#endif
