

#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

//void SystemInitSharedMemory();

bool SystemAllocateSharedMemory(void **  newMemory,
							   int size,
							   const char * name,
							   bool &isFirst);

bool SystemFreeSharedMemory(void * pShared_Memory);




#endif /* SHAREDMEMORY_H_ */
