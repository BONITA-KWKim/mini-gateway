#include "util-mmf.h"

void *UTILMMF::attach_MMF(int idx, int mmf_flag, char *mmf_filename, 
                          int mmf_recsize, int mmf_reccount, int add_bytes, 
                          int sem_flag, char *sem_filename)
{
	gMMFInfo[idx].mmf_flag     = mmf_flag;
	gMMFInfo[idx].mmf_perm     = SEMAPHORE_PERMS;
	gMMFInfo[idx].mmf_filename = mmf_filename;
	gMMFInfo[idx].mmf_recsize  = mmf_recsize;
	gMMFInfo[idx].mmf_reccount = mmf_reccount;
	gMMFInfo[idx].mmf_bytes    = mmf_recsize * mmf_reccount;
	gMMFInfo[idx].add_bytes    = add_bytes;

	gMMFInfo[idx].sem_flag     = sem_flag;
	gMMFInfo[idx].sem_filename = sem_filename;

	void *ptr = attach_MMF_func(&gMMFInfo[idx]);
	return (ptr);
}

void *UTILMMF::attach_MMF_func (MMF_INFO *pinfo)
{
	size_t mmfsize = pinfo->mmf_bytes + pinfo->add_bytes;
	// pinfo->mmf_fd = shm_open (pinfo->mmf_filename,  /* name from smem.h */
 	// 						  pinfo->mmf_flag,      /* read/write, create if needed */
	// 						  pinfo->mmf_perm);   	/* access permissions (0644) */
    
    /// create and open file descriptor
	if (-1 == (pinfo->mmf_fd = open(pinfo->mmf_filename, O_RDWR | O_CREAT | O_TRUNC, pinfo->mmf_perm))){
		perror("open");
		return NULL;
	}

	if (-1 == ftruncate(pinfo->mmf_fd, (off_t)mmfsize)) {
		perror("ftruncate");
		return NULL;
	}

	fprintf(stderr, "attach_MMF_func: size is %ld\n", mmfsize);
	if (pinfo->mmf_fd < 0) {
		perror("Can't open shared memory...");
	}

	if (0 < (pinfo->mmf_flag & O_CREAT))
		ftruncate(pinfo->mmf_fd, mmfsize); /* get the bytes */

	pinfo->mmf_ptr = mmap(NULL,       	          /* let system pick where to put segment */
  						  mmfsize,   	          /* how many bytes */
						  PROT_READ | PROT_WRITE, /* access protections */
						  MAP_SHARED, 	          /* mapping visible to other processes */
						  pinfo->mmf_fd,          /* file descriptor */
						  0);         	          /* offset: start at 1st byte */
	if ((void *) -1  == pinfo->mmf_ptr) {
		fprintf(stderr, "errno:%d, mmf_ptr = %x\n", errno, pinfo->mmf_ptr);
		perror("Can't get mmf...");
	}

	/* semahore code to lock the shared mem */
	if (pinfo->sem_flag) {
		if (gUseSemaphore) {
				pinfo->sem_ptr = sem_open (pinfo->sem_filename, /* name */
										   O_CREAT,        		/* create the semaphore */
										   pinfo->mmf_perm,  	/* protection perms */
										   0);            		/* initial value */
				if (pinfo->sem_ptr == (void*) -1)
					perror("sem_open");
		}
	}
	return pinfo->mmf_ptr;
}
