/*                                                                              */
/* Copyright (C) 2001 International Business Machines                           */
/* All rights reserved.                                                         */
/*                                                                              */
/* This file is part of the GPFS user library.                                  */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following conditions           */
/* are met:                                                                     */
/*                                                                              */
/*  1. Redistributions of source code must retain the above copyright notice,   */
/*     this list of conditions and the following disclaimer.                    */
/*  2. Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*  3. The name of the author may not be used to endorse or promote products    */
/*     derived from this software without specific prior written                */
/*     permission.                                                              */
/*                                                                              */
/* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR         */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES    */
/* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.      */
/* IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, */
/* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;  */
/* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,     */
/* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR      */
/* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF       */
/* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                   */
/*                                                                              */
/* @(#)69       1.9  src/avs/fs/mmfs/ts/util/gpfs_lwe.h, mmfs, avs_rtac502, rtac5021836a 1/18/17 17:22:53 */
/*
 *  Library calls for GPFS interfaces
 */
#ifndef H_GPFS_LWE
#define H_GPFS_LWE

#ifdef __cplusplus
extern "C" {
#endif

static const char LWE_JSON[] =
"{\"type\":\"record\",\
  \"name\":\"LWE\",\
    \"fields\":[\
      {\"name\": \"fsName\", \"type\": \"string\"},\
      {\"name\": \"event\", \"type\": \"string\"},\
      {\"name\": \"pathName\", \"type\": \"string\"},\
      {\"name\": \"pathNewName\", \"type\": \"string\"},\
      {\"name\": \"URL\", \"type\": \"string\"},\
      {\"name\": \"inode\", \"type\": \"long\"},\
      {\"name\": \"openFlags\", \"type\": \"string\"},\
      {\"name\": \"poolName\", \"type\": \"string\"},\
      {\"name\": \"fileSize\", \"type\": \"long\"},\
      {\"name\": \"ownerUserId\", \"type\": \"int\"},\
      {\"name\": \"ownerGroupId\", \"type\": \"int\"},\
      {\"name\": \"atime\", \"type\": \"string\"},\
      {\"name\": \"mtime\", \"type\": \"string\"},\
      {\"name\": \"nowTime\", \"type\": \"string\"},\
      {\"name\": \"elapsedTime\", \"type\": \"string\"},\
      {\"name\": \"clientUserId\", \"type\": \"string\"},\
      {\"name\": \"clientGroupId\", \"type\": \"string\"},\
      {\"name\": \"clientIp\", \"type\": \"string\"},\
      {\"name\": \"processId\", \"type\": \"int\"}\
      {\"name\": \"targetPoolName\", \"type\": \"string\"},\
      {\"name\": \"bytesRead\", \"type\": \"long\"},\
      {\"name\": \"bytesWritten\", \"type\": \"long\"},\
      {\"name\": \"clusterName\", \"type\": \"string\"},\
      {\"name\": \"nodeName\", \"type\": \"string\"},\
  ]}";

#define GPFS_DEVNAMEX "/dev/ss0"  /* Must be the same as GPFS_DEVNAME */
#define kLWEvent 169             /* Must be the same as LWEvent in enum kxOps */
#define LWE_MAX_FIELD 256
#define LWE_UPDATE 201
typedef long long Int64_t;

struct lweHeader
{
  int      lwe_version;     /* in/out                       */
  int      lwe_fd;          /* in                           */
  int      lwe_sync;        /* in:  sync request            */
  int      lwe_event;       /* in:  events requeste         */
                            /* out: event returned          */
  int      lwe_data;        /* in:  data requested          */
                            /* out: data returned           */
  int      lwe_rc;          /* out for all the rest         */
  int      lwe_seq;         /* Event sequence number        */
};

struct lweAttr
{
  struct lweHeader lweHdr;
  Int64_t  lwe_inode;
  int      lwe_oiOpenFlags; /* Original value of open flags */

  /* Original credentials when the file was opened */
  int      lwe_userId;
  int      lwe_groupId;
  int      lwe_processId;
  int      lwe_ownerUserId;
  int      lwe_ownerGroupId;

  Int64_t  lwe_fileSize;
  Int64_t  lwe_bytesRead;
  Int64_t  lwe_bytesWritten;
  Int64_t  lwe_elapsedTime;
  struct timespec lwe_atime;
  struct timespec lwe_mtime;
  struct timespec lwe_nowTime;
  int      lwe_plen;
  int      lwe_plen2;
  char     lwe_fsName[LWE_MAX_FIELD+1];
  char     lwe_NFS_IP[NFS_IP_SIZE+1];
  char     lwe_poolName[LWE_MAX_FIELD+1];
  char     lwe_targetPoolName[LWE_MAX_FIELD+1];
  char     lwe_clusterName[LWE_MAX_FIELD+1];
  char     lwe_nodeName[LWE_MAX_FIELD+1];
  /* keep path at the end */
  char     lwe_path[PATH_MAX+1];
  char     lwe_path2[PATH_MAX+1];
};

#define LWE_ONE_PATH (sizeof(struct lweAttr)-PATH_MAX)
#define LWE_NO_PATH (sizeof(struct lweAttr)-(PATH_MAX*2))

#ifdef __cplusplus
}
#endif

#endif /* H_GPFS_LWE */
