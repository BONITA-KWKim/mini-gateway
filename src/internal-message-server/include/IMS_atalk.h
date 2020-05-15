#pragma once

#include "IMS_base.h"
#include "parser.h"
#include "util-mmf.h"

#define DEBUG

#define	MMF_IDX_PTN 0
#define	MMF_IDX_MSG 1
#define	MMF_IDX_RPT 2

#define BACKLOG            50    /* how many pending connections queue will hold */
#define	MAX_PTN_RECORDS	   2500  /* IMPORTANT!!!: If 5000, memory allocation error occurred */
#define	MAX_MMF_RECORDS	   1000
#define MAX_SOCKET_THREAD  50

// [ MMF ] //
#define MMF_PTN_FILENAME "mts_PTN"
#define MMF_MSG_FILENAME "mts_MSG"
#define MMF_RPT_FILENAME "mts_RPT"

#define SEMAPHORE_PERMS    0600
#define SEMAPHORE_POOLNAME "mts_semPOOL"
#define SEMAPHORE_MSGNAME  "mts_semMSG"
#define SEMAPHORE_RPTNAME  "mts_semRPT"

#define MAX_ATALK_ENQUEUE 100

class IMS_ATALK : IMS_BASE
{
public:
	IMS_ATALK () {}
	IMS_ATALK (utility::string_t url);

	pplx::task<void> open () { return m_listener.open(); }
	pplx::task<void> close () { return m_listener.close(); }

private:
	// void handle_get (http_request msg);
	// void handle_put (http_request msg);
	void handle_post (http_request msg);
	// void handle_delete (http_request msg);
	std::vector<utility::string_t> requestPath(const http_request & message) ;
	int request_to_send_message(std::string message);

	http_listener m_listener;
	UTILMMF *util_mmf;
	MSG_RECORD *msg_record;
};
