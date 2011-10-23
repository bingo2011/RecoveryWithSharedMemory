#include "BaseDataSection.h"
#include "Recoverable.h"
#include "SharedMemory.h"

BaseDataSection::BaseDataSection(Recoverable& obj)
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

BaseDataSection::~BaseDataSection()
{
	SystemFreeSharedMemory(addrInSharedMemory_);
}
