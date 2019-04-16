/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2010,2018          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)18       1.5  src/avs/fs/mmfs/ts/mmantras/api_types.h, mmfs, avs_rtac502, rtac5021836a 12/22/10 14:55:05 */
#ifndef _h_api_types
#define _h_api_types

/*
 * api_types.h
 *   type definition used in MMANTRAS library
 */

typedef enum 
{
  M_OK = 0,
  M_ERR = 1,
  M_RECOVERED = 2
} MErrno;

typedef short                  Int16;
typedef int                    Int32;
typedef long long              Int64;
typedef unsigned short         UInt16;
typedef unsigned int           UInt32;
typedef unsigned long long     UInt64;

typedef unsigned int           Boolean_t;

struct threadUtil
{
  UInt32 current;
  UInt32 highest;
  UInt32 maximum;
};
typedef struct threadUtil threadUtil_t;

struct pCacheCmdInfo
{
  UInt32 queuedPcacheCmds;
  UInt32 inflightPcacheCmds;
  UInt32 completedPcacheCmds;
  UInt32 errorPcacheCmds;
  UInt32 filteredPcacheCmds;
  UInt32 enoentPcacheCmds;
};
typedef struct  pCacheCmdInfo pCacheCmdInfo_t;


/* mmantras library debug routine */
extern void ts_print(const char *str);

#endif /* _h_api_types */

