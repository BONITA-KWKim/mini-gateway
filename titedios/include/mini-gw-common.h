#ifndef __MINI_GW_COMMON_H__
#define __MINI_GW_COMMON_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <string.h>

///
#define COUT_PREFIX "[" << __func__ << ":" <<  __LINE__ <<  "] "

/*
class MSG_RECORD {
public:
    MSG_RECORD(){
        memset(key, 0x00, sizeof(key));
        memset(subject, 0x00, sizeof(subject));
        memset(receiver, 0x00, sizeof(receiver));
        memset(sender_key, 0x00, sizeof(sender_key));
        memset(tmpl_code, 0x00, sizeof(tmpl_code));
        memset(nation_code, 0x00, sizeof(nation_code));
        memset(msg_body, 0x00, sizeof(msg_body));
    };
    ~MSG_RECORD();

    char *get_key() { return key; };
    char *get_subject() { return subject; };
    char *get_receiver() { return receiver; };
    char *get_sender_key() { return sender_key; };
    char *get_tmpl_code() { return tmpl_code; };
    char *get_nation_code() { return nation_code; };
    char *get_msg_body() { return msg_body; };

    char key[20];
    char subject[50];
    char receiver[16];
    char sender_key[30];
    char tmpl_code[20];
    char nation_code[4];
    char msg_body[4000];
private:
};
*/

#define IDLE             10
#define TRANSMIT_REQUEST 11
#define TRANSMITTED      12
#define RECORED          13
typedef struct _MSG_RECORD {
    int status;
    char key[20];
    char subject[50];
    char receiver[16];
    char sender_key[30];
    char tmpl_code[20];
    char nation_code[4];
    char msg_body[4000];
} MSG_RECORD;

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__MINI_GW_COMMON_H__z