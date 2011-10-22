#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "SharedMemory.h"


struct shared_memory_db_item
{
	int descriptor;
	std::string file_name;
};


std::map<void* , shared_memory_db_item> shared_memory_db;


//////////////////////////////////////////////////////////////////////
bool SystemAllocateSharedMemory(void **  newMemory,
							   int size,
							   const char * name,
							   bool &isFirst)
{
    isFirst=false;

	if ( getenv("MRM_SINGLE_PROCESS") &&
		 getenv("MRM_NO_SHARED_MEMORY"))
	{
		*newMemory = malloc(size);
		isFirst = true;
		return true;
	}

	int sharedMemoryDescriptor;
    key_t shared_memory_key;

    std::string shared_memory_name;
    shared_memory_name = name;
    shared_memory_name = "/tmp/" + shared_memory_name;

    int ret=open(shared_memory_name.c_str(),O_RDWR|O_CREAT,0666);
    if (-1==ret)
    {
        perror("SystemAllocateSharedMemory:: Error Opening file");
        perror(shared_memory_name.c_str());
        abort();
        return false;
    }
    close(ret);

    chmod(shared_memory_name.c_str(),S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

    if ((shared_memory_key = ftok (shared_memory_name.c_str(), 'm'))== -1)
    {
        perror("SystemAllocateSharedMemory - ftok failed");
        abort();
        return false;
    }

    isFirst=true;

    if ((sharedMemoryDescriptor=shmget(shared_memory_key,
                                         size ,
                                         IPC_CREAT|IPC_EXCL|0666)) ==-1)
    {
        if (errno!=EEXIST)
        {   //we have an error reaching the shared memory
            perror("shmget failed");
            abort();
            return false;
        }
        else
        {
            isFirst = false;
            if ((sharedMemoryDescriptor=shmget(shared_memory_key,size,0))==-1)
            {
               perror("shmget2 failed");
               abort();
               return false;
            }
        }
    }

    *newMemory = shmat(sharedMemoryDescriptor ,0 ,0);
    if (*newMemory == (void*)-1)
    {
    	 // todo : make the log work
    	//CRITICAL("SystemAllocateSharedMemory shmat cannot allocate memory");
        perror("SystemAllocateSharedMemory shmat cannot allocate memory");
        abort();
        return false;
    }
    shared_memory_db[*newMemory].descriptor = sharedMemoryDescriptor;
    shared_memory_db[*newMemory].file_name = shared_memory_name;
    return true;

}


//////////////////////////////////////////////////////////////////////
bool SystemFreeSharedMemory(void * pShared_Memory)
{
	if (getenv("MRM_SINGLE_PROCESS") &&
		getenv("MRM_NO_SHARED_MEMORY"))
	{
		free(pShared_Memory);
		return true;
	}

	int Shared_Memory_Descriptor = shared_memory_db[pShared_Memory].descriptor;
	std::string Shared_Memory_File_Name = shared_memory_db[pShared_Memory].file_name;

    int number_of_attached_procs;
    struct shmid_ds temp_shm_struct;

    if (-1==shmdt(pShared_Memory))
    {
        //perror("SystemFreeSharedMemory shmdt failed");
        //abort();
        return false;
    }

    if (-1==shmctl(Shared_Memory_Descriptor,IPC_STAT,&temp_shm_struct))
    {
        perror("SystemFreeSharedMemory shmctl get stat failed");
        abort();
        return false;
    }

    number_of_attached_procs=temp_shm_struct.shm_nattch;
    if (number_of_attached_procs==0)
    {
        if (-1==shmctl(Shared_Memory_Descriptor,IPC_RMID,0))
        {
            perror("SystemFreeSharedMemory shmctl IPC_RMID failed");
            abort();
            return false;
        }
    }

    remove(Shared_Memory_File_Name.c_str());
    shared_memory_db.erase(pShared_Memory);
    return true;

}

