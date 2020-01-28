#ifndef __MINI_GW_COMMON_H__
#define __MINI_GW_COMMON_H__

#ifdef _cplusplus
extern "C"{
#endif

///
#define COUT_PREFIX "[" << __func__ << ":" <<  __LINE__ <<  "] "

typedef struct _MSG_RECORD {
    int test;
} MSG_RECORD;

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__MINI_GW_COMMON_H__