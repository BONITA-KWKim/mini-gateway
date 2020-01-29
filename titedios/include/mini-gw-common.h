#ifndef __MINI_GW_COMMON_H__
#define __MINI_GW_COMMON_H__

#ifdef _cplusplus
extern "C"{
#endif

///
#define COUT_PREFIX "[" << __func__ << ":" <<  __LINE__ <<  "] "

typedef struct _MSG_RECORD {
    int test;
    char key[20];
    char subject[50];
    char receiver[16];
    char sender_key[30];
    char tmpl_code[20];
    char nation_code[4];
} MSG_RECORD;

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__MINI_GW_COMMON_H__z