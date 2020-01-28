#ifndef __UTIL_MMF_H__
#define __UTIL_MMF_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SEMAPHORE_PERMS 0600

typedef struct {
	int mmf_fd;
	int mmf_flag;
	int mmf_perm;
	int	mmf_recsize;
	int mmf_reccount;
	int mmf_bytes;
	int add_bytes;
	int sem_flag;
	char *mmf_filename;
	char *sem_filename;
	void *sem_ptr;
	void *mmf_ptr;
} MMF_INFO;

class UTILMMF {
public:
	UTILMMF(){}
	~UTILMMF(){}

	/// name: attach_MMF
	/// parameter
	/// return
	///  - void *: memory address
	/// desc
	///  - Something to configure MMF and semaphore is input this function.
	///  Input parametes are saved into gMMFInfo(global variable) and 
	///  actual some processes are done in private function(attach_MMF_func).
	void *attach_MMF(int idx, int mmf_flag, char *mmf_filename, 
                     int mmf_recsize, int mmf_reccount, int add_bytes, 
                     int sem_flag, char *sem_filename);

	int gUseSemaphore;
private:
	/// name: attach_MMF_func
	/// parameter: MMF_INFO *pinfo: configuration information
	/// return
	///  - void *: memory address
	/// desc
	///  - Create file to use memory mappaed by filename and mapping to memory.
	///  Semaphore is created.
	void *attach_MMF_func(MMF_INFO *pinfo);

	// 0: PTN  1: MSG  2:RPT
	MMF_INFO gMMFInfo[3];
};

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__UTIL_MMF_H__