#include "BaseRecoveredData.h"
#include "Recoverable.h"
#include "SharedMemory.h"

BaseRecoveredData::BaseRecoveredData(Recoverable& obj)
:obj_(obj)
{
	int ret = SystemAllocateSharedMemory(&addrInSharedMemory_, obj.GetRequiredSharedMemorySize(),
			obj.name().c_str(), isFirst_);

	if (isFirst_)
	{
		obj.InitLocalObjects();
	}
	else
	{
		// recovery mode
		obj.RecoverLocalObjects();
	}

}

BaseRecoveredData::~BaseRecoveredData()
{
	SystemFreeSharedMemory(addrInSharedMemory_);
}
