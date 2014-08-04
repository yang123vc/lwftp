/*
 * lwftp.h : a lightweight FTP client using raw API of LWIP
 *
 * Copyright (c) 2014 GEZEDO
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Author: Laurent GONZALEZ <lwip@gezedo.com>
 *
 */

#include "lwip/opt.h"
#include "lwip/ip.h"

enum lwftp_results {
  LWFTP_RESULT_OK=0,
  LWFTP_RESULT_ERR_UNKNOWN,   /** Unknown error */
  LWFTP_RESULT_ERR_CONNECT,   /** Connection to server failed */
  LWFTP_RESULT_ERR_HOSTNAME,  /** Failed to resolve server hostname */
  LWFTP_RESULT_ERR_CLOSED,    /** Connection unexpectedly closed by remote server */
  LWFTP_RESULT_ERR_TIMEOUT,   /** Connection timed out (server didn't respond in time) */
  LWFTP_RESULT_ERR_SRVR_RESP  /** Server responded with an unknown response code */
};

/** LWFTP control connection state */
typedef enum  {
  LWFTP_CLOSED=0,
  LWFTP_CONNECTED,
  LWFTP_USER_SENT,
  LWFTP_PASS_SENT,
  LWFTP_TYPE_SENT,
  LWFTP_PASV_SENT,
  LWFTP_STOR_SENT,
  LWFTP_STORING,
  LWFTP_QUIT,
  LWFTP_QUIT_SENT,
} lwftp_state_t;

/** LWFTP session structure */
typedef struct {
  // User interface
  ip_addr_t     server_ip;
  u16_t         server_port;
  char          *remote_path;
  char          *user;
  char          *pass;
  uint          (*data_source)(const char**, uint);
  void          (*done_fn)(int);
  // Internal data
  lwftp_state_t   control_state;
  lwftp_state_t   data_state;
  struct tcp_pcb  *control_pcb;
  struct tcp_pcb  *data_pcb;
} lwftp_session_t;

// LWFTP API
err_t lwftp_store(lwftp_session_t *s);
