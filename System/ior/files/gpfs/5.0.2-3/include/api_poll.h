/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2007,2018          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)49       1.65  src/avs/fs/mmfs/ts/mmantras/api_poll.h, mmfs, avs_rtac502, rtac5021836a 7/9/18 11:44:51 */

#ifndef _h_api_poll
#define _h_api_poll



#include <stdio.h>
#include <vector>
#include <list>
#include <pthread.h>
#include <sys/time.h>
#include <assert.h>

/* MODS_START */
#include <string>
/* MODS_END */

#include <api_types.h>

/* String length */
#define NAME_STRING_LEN    256

#define PATH_STRING_LEN    1024

/* Comma separated string length */
#define LIST_STRING_LEN    1024

/* DJ_MODS_START */
/* Buf length for Return messages from GPFS */
#define MMCMD_RET_MSG_BUF_LEN  1024
/* Number of tokens in a GPFS cmd with small number of parameters */
#define MAX_NUM_TOKENS_SHORT_CMD 8

#define TIME_STAMP_CHARS   25

/* DJ_MODS_END */

/* Timer thread interval */
#define TIMER_INTERVAL     300

#define ADDRLIST_NODES	64

/* rpc objects */
#define RPC_OBJECTS 7
#define MAX_NUMBER_BUCKETS 26
#define MAX_SERVICES 26
#define MAX_MSG_TYPES 51
#define MAX_RPC_MAPPED_MSG_TYPES 2
#define MAX_MSG_RPC MAX_SERVICES * MAX_MSG_TYPES + MAX_RPC_MAPPED_MSG_TYPES

/* Management application protocol. It is for protocol-specific
   functionalities. */
typedef enum
{
  MGMT_SNMP = 0,
  MGMT_CIM = 1
} MgmtProtocol;

/* Enable logging */
#define ENABLE_MMANTRAS_LOG

/* Maximum log level */
#define MMANTRAS_LOG_MAX_LEVEL  3

/* Supported log levels */
enum MmantrasLogLevel
{
  INFO = 0,
  WARNING = 1,
  ERROR = 2,
  SEVERE = 3
};

#define LIBMMANTRAS_VERSION 3504  /* version of currently defined MMANTRAS
                                     interface - must update the corresponding
                                     version number at daemon side */

extern int libmmantrasVersion();

/* Define maximum number of objects */
#define  MAX_NODE         1024
#define  MAX_FS           32
#define  MAX_FILESETV3    10000
#define  MAX_DISK         1024
#define  MAX_POOL         256
#define  MAX_POLICY       32
#define  MAX_RULE         65536
#define  MAX_NSD_SERVER   32
#define  MAX_TASK         1024
#define  MAX_PCACHE_CMD_INFO 39  /* must be >= MAX_PCACHE_CMD */

#define CLUSTER_MANAGER   0x1
#define CLUSTER_STATUS    0x2
#define CLUSTER_STATE_ALL CLUSTER_MANAGER | CLUSTER_STATUS

#define AG_STAT_CHANNEL_WAIT      0
#define AG_STAT_SEND_TIME_TCP     1
#define AG_STAT_SEND_TIME_VERBS   2
#define AG_STAT_RECEIVE_TIME_TCP  3
#define AG_STAT_RPC_LATENCY_TCP   4
#define AG_STAT_RPC_LATENCY_VERBS 5
#define AG_STAT_RPC_LATENCY_MIXED 6

/* Info structs
   The latest data from GPFS is stored in an internal copy of these structs.
   The caller has his own copy, which is updated to be consistent with the
   internal copy by calling the PollingHandler::update routines. */


/* Asynchronous command execution information */
class ExecutionTask
{
  friend class PollingHandler;

  char cmd[NAME_STRING_LEN];
  std::vector<char *>argItems;
  int (*callbackFn)(void *callbackData);
  void *callbackData;

public:

  ExecutionTask(MErrno *errP);

  ~ExecutionTask();

  ExecutionTask& operator=(ExecutionTask &t);

  void setCmd(const char *cmdP);
  void addArg(char *argP);

  void copyArgs(ExecutionTask *taskP);

  inline char* getCmd() { return cmd; }
  inline UInt32 getNumArgItems() { return argItems.size(); }
  inline char *getArg(int d) { return argItems.at(d); }
};

/* Asynchronous command execution result */
class ExecutionResult
{
  UInt16 percentComplete;

public:
  ExecutionResult(MErrno *errP);

  ~ExecutionResult();

  inline UInt16 getPercentComplete() { return percentComplete; }
};

/* Disk server information */
class DiskServerInfo
{
  friend class PollingHandler;

  char name[NAME_STRING_LEN];

public:
  DiskServerInfo(MErrno *errP);

  ~DiskServerInfo();

  DiskServerInfo& operator=(DiskServerInfo &d);

  inline char* getName() { return name; }
};

/* Disk information */
class DiskInfo
{
  friend class PollingHandler;

  Boolean_t found;

  /* Indicate whether it is free NSD or not. */
  Boolean_t free;

  char name[NAME_STRING_LEN];
  char nodeName[NAME_STRING_LEN];       // for easy association

  /* Use only when this NSD is free. */
  char poolName[NAME_STRING_LEN];

  char status[NAME_STRING_LEN];
  char availability[NAME_STRING_LEN];
  char failureGroup[LIST_STRING_LEN];

  char volumeId[NAME_STRING_LEN];

  char metadata[NAME_STRING_LEN];
  char data[NAME_STRING_LEN];
  char diskWait[NAME_STRING_LEN];
  UInt64 totalSpace;
  UInt64 fullBlockFreeSpace;
  UInt64 subBlockFreeSpace;

  double readTime;
  double writeTime;
  double longestReadTime;
  double longestWriteTime;
  double shortestReadTime;
  double shortestWriteTime;
  UInt64 readBytes;
  UInt64 writeBytes;
  UInt32 readOps;
  UInt32 writeOps;

  UInt32 nodePerfCount;    // number of nodes that had valid contribution to perf aggregate

  std::vector<DiskServerInfo *>serverItems;
  std::vector<DiskServerInfo *>backupServerItems;

  void copyServers(DiskInfo *diskP);
  int getServerIndex(char *nameP);
  void copyBackupServers(DiskInfo *diskP);
  int getBackupServerIndex(char *nameP);

public:
  DiskInfo(MErrno *errP);

  ~DiskInfo();

  DiskInfo& operator=(DiskInfo &d);
  void clearStats();

  inline Boolean_t isFree() { return free; }

  inline char* getName() { return name; }
  inline char *getNodeName() { return nodeName; }

  /* Disk stats from EE get fs command */
  inline char *getStatus() { return status; }
  inline char *getAvailability() { return availability; }
  inline char *getFailureGroupId() { return failureGroup; }
  inline char *getVolumeId() { return volumeId; }
  inline char *getMetadata() { return metadata; }
  inline char *getData() { return data; }
  inline char *getDiskWait() { return diskWait; }
  inline UInt64 getTotalSpace() { return totalSpace; }
  inline UInt64 getFullBlockFreeSpace() { return fullBlockFreeSpace; }
  inline UInt64 getSubBlockFreeSpace() { return subBlockFreeSpace; }

  /* Disk performance statistics: see mmpmon ds for details */
  /* Note: getReadTime() and getWriteTime() return the total time of all
     operations; divide by the total ops to get average */
  inline double getReadTime() { return readTime; }    /* microseconds */
  inline double getWriteTime() { return writeTime; }
  inline double getLongestReadTime() { return longestReadTime; }
  inline double getLongestWriteTime() { return longestWriteTime; }
  inline double getShortestReadTime() { return shortestReadTime; }
  inline double getShortestWriteTime() { return shortestWriteTime; }
  inline UInt64 getReadBytes() { return readBytes; }
  inline UInt64 getWriteBytes() { return writeBytes; }
  inline UInt32 getReadOps() { return readOps; }
  inline UInt32 getWriteOps() { return writeOps; }
  inline UInt32 getNodePerfCount() { return nodePerfCount; }
  inline UInt32 getNumServerItems() { return serverItems.size(); }
  inline DiskServerInfo *getServer(int d) { return serverItems.at(d); }
  inline UInt32 getNumBackupServerItems() { return backupServerItems.size(); }
  inline DiskServerInfo *getBackupServer(int d) { return backupServerItems.at(d); }
  inline char *getPoolName() { return poolName; }
  void updateTotalSpace(UInt64 dSizeInKB) { totalSpace = dSizeInKB; }
  void updateDiskInfoStatus(char *dsStatus);
};

/* forward decl */
class FilesystemInfo;

/* Storage pool information */
class StoragePoolInfo
{
  friend class PollingHandler;

  char name[NAME_STRING_LEN];
  char status[NAME_STRING_LEN];
  UInt32 numDisks;
  UInt64 totalSpace;
  UInt64 freeSpace;

  UInt32 parentFS;    /* index of parent filesystem */
  Boolean_t found;

  /* Store the list of disk name - primary key */
  std::vector<DiskInfo *>diskItems;
  struct timeval diskRefreshTime;
  struct timeval diskPerfRefreshTime;

  void copyDisks(StoragePoolInfo *poolP);
  int getDiskInfoIndex(char *nameP);

  UInt64 totalBytesRead;
  UInt64 totalBytesWrite;
  double totalReadTime;
  double totalWriteTime;
  void clearStats();

public:
  StoragePoolInfo(MErrno *errP);
  ~StoragePoolInfo();
  StoragePoolInfo& operator=(StoragePoolInfo &sp);
  inline char *getName() { return name; }
  inline char *getStatus() { return status; }
  inline UInt64 getTotalSpace() { return totalSpace; }
  inline UInt64 getFreeSpace() { return freeSpace; }
  inline UInt32 getParent() { return parentFS; }
  inline UInt32 getNumDisks() { return numDisks; } // Use only when file system is mounted
  inline UInt32 getNumDiskItems() { return diskItems.size(); }
  inline DiskInfo *getDisk(int d) { return diskItems.at(d); }
  inline struct timeval getDiskRefreshTime() { return diskRefreshTime; }
  inline struct timeval getDiskPerfRefreshTime() { return diskPerfRefreshTime; }

  inline UInt64 getTotalBytesRead() { return totalBytesRead; }
  inline UInt64 getTotalBytesWrite() { return totalBytesWrite; }
  inline double getTotalReadTime() { return totalReadTime; }
  inline double getTotalWriteTime() { return totalWriteTime; }

};

/* Mounted node information */
class MountedNodeInfo
{
  friend class PollingHandler;

  char name[NAME_STRING_LEN];
  char ipAddr[NAME_STRING_LEN];

  Boolean_t found;

public:
  MountedNodeInfo(MErrno *errP);

  ~MountedNodeInfo();

  MountedNodeInfo& operator=(MountedNodeInfo &d);

  inline char* getName() { return name; }
  inline char* getIpAddr() { return ipAddr; }
};

/* File system policy rule information */
class RuleInfo
{
  friend class PollingHandler;

  char name[NAME_STRING_LEN];
  char desc[LIST_STRING_LEN];

public:
  RuleInfo(MErrno *errP);

  ~RuleInfo();

  RuleInfo& operator=(RuleInfo &d);

  inline char *getName() { return name; }
  inline char *getDesc() { return desc; }
};

/* File system policy information */
class PolicyInfo
{
  friend class PollingHandler;

  char name[NAME_STRING_LEN];
  char installUser[NAME_STRING_LEN];
  char installTime[NAME_STRING_LEN];

  std::vector<RuleInfo *>ruleItems;

  void copyRules(PolicyInfo *piP);
  int getRuleInfoIndex(char *nameP);

public:
  PolicyInfo(MErrno *errP);

  ~PolicyInfo();

  PolicyInfo& operator=(PolicyInfo &d);

  inline char *getName() { return name; }
  inline char *getInstallUser() { return installUser; }
  inline char *getInstallTime() { return installTime; }
  inline UInt32 getNumRules() { return ruleItems.size(); }
  inline RuleInfo *getRule(int r) { return ruleItems.at(r); }
};

/* File system performance */
class FilesystemPerf
{
  friend class PollingHandler;

  char fsName[NAME_STRING_LEN];
  char nodeName[NAME_STRING_LEN];
  char nodeIpAddr[NAME_STRING_LEN];

  UInt64 bytesRead;
  UInt64 bytesCache;
  UInt64 bytesWritten;
  UInt32 reads;
  UInt32 caches;
  UInt32 writes;
  UInt32 openCalls;
  UInt32 closeCalls;
  UInt32 readCalls;
  UInt32 writeCalls;
  UInt32 readdirCalls;
  UInt64 inodesWritten;
  UInt64 inodesRead;
  UInt64 inodesDeleted;
  UInt64 inodesCreated;
  UInt32 statCacheHit;
  UInt32 statCacheMiss;

  Boolean_t found;

public:
  FilesystemPerf(MErrno *errP);

  ~FilesystemPerf();

  FilesystemPerf& operator=(FilesystemPerf &fs);
  void clearStats();

  inline char *getFsName() { return fsName; }
  inline char *getNodeName() { return nodeName; }
  inline char *getNodeIpAddr() { return nodeIpAddr; }
  inline UInt64 getBytesRead() { return bytesRead; }
  inline UInt64 getBytesCache() { return bytesCache; }
  inline UInt64 getBytesWritten() { return bytesWritten; }
  inline UInt32 getReads() { return reads; }
  inline UInt32 getCaches() { return caches; }
  inline UInt32 getWrites() { return writes; }
  inline UInt32 getOpenCalls() { return openCalls; }
  inline UInt32 getCloseCalls() { return closeCalls; }
  inline UInt32 getReadCalls() { return readCalls; }
  inline UInt32 getWriteCalls() { return writeCalls; }
  inline UInt32 getReaddirCalls() { return readdirCalls; }
  inline UInt64 getInodesWritten() { return inodesWritten; }
  inline UInt64 getInodesRead() { return inodesRead; }
  inline UInt64 getInodesDeleted() { return inodesDeleted; }
  inline UInt64 getInodesCreated() { return inodesCreated; }
  inline UInt32 getStatCacheHit() { return statCacheHit; }
  inline UInt32 getStatCacheMiss() { return statCacheMiss; }
};

/* File system information */
class FilesystemInfo
{
  friend class PollingHandler;

  char name[NAME_STRING_LEN];

  /* Manager node name. */
  char manager[NAME_STRING_LEN];

  char status[NAME_STRING_LEN];
  char xstatus[NAME_STRING_LEN];

  UInt32 readDuration;
  UInt32 writeDuration;
  UInt32 numMgmt;
  UInt32 numMgrChange;
  UInt64 totalSpace;
  UInt64 numTotalInodes;
  UInt64 freeSpace;
  UInt64 numFreeInodes;
  UInt64 fullBlockFreeSpace;
  UInt64 subBlockFreeSpace;
  char threadWait[NAME_STRING_LEN];
  char diskWait[NAME_STRING_LEN];

  /* Configuration information. */
  UInt64 minFragmentSize;
  UInt64 inodeSize;
  UInt64 indirectBlockSize;
  UInt32 defaultMetadataReplicas;
  UInt32 maxMetadataReplicas;
  UInt32 defaultDataReplicas;
  UInt32 maxDataReplicas;
  char blockAllocationType[NAME_STRING_LEN];
  char fileLockingSemantics[NAME_STRING_LEN];
  char aclSemantics[NAME_STRING_LEN];
  UInt64 estimatedAverageFileSize;
  UInt64 numNodes;
  UInt64 blockSize;
  char quotaEnforced[NAME_STRING_LEN];
  char defaultQuotasEnabled[NAME_STRING_LEN];
  UInt64 maxNumInodes;
  char filesystemVersion[NAME_STRING_LEN];
  char supportForLargeLuns[NAME_STRING_LEN];
  char dmapiEnabled[NAME_STRING_LEN];
  char exactMtime[NAME_STRING_LEN];
  char suppressAtime[NAME_STRING_LEN];
  char automaticMountOption[NAME_STRING_LEN];
  char additionalMountOptions[NAME_STRING_LEN];
  char defaultMountPoint[NAME_STRING_LEN];

  UInt64 bytesRead;
  UInt64 bytesCache;
  UInt64 bytesWritten;

  UInt32 reads;
  UInt32 caches;
  UInt32 writes;

  UInt32 openCalls;
  UInt32 closeCalls;
  UInt32 readCalls;
  UInt32 writeCalls;
  UInt32 readdirCalls;

  UInt64 inodesWritten;
  UInt64 inodesRead;
  UInt64 inodesDeleted;
  UInt64 inodesCreated;

  UInt32 statCacheHit;
  UInt32 statCacheMiss;

  UInt32 nodePerfCount;

  /* Store the list of storage pools - primary key */
  std::vector<StoragePoolInfo *>poolItems;
  struct timeval          poolRefreshTime;    /* Last data refresh time */

  /* Store the list of mounted nodes */
  std::vector<MountedNodeInfo *>mountedNodeItems;

  /* Store the list of policies */
  std::vector<PolicyInfo *>policyItems;

  /* Store the list of per-node performance */
  std::vector<FilesystemPerf *>perfItems;

  /* Workspace indicating this item was found in the SDR file */
  Boolean_t found;

  /* MODS_START */
  bool updated;
  /* MODS_END */

  void copyPools(FilesystemInfo *fsP);
  int getStoragePoolInfoIndex(char *nameP);

  void copyMountedNodes(FilesystemInfo *fsP);
  int getMountedNodeIndex(char *ipAddrP);

  void copyPolicies(FilesystemInfo *fsP);
  int getPolicyInfoIndex(char *nameP);

  void copyPerNodePerfs(FilesystemInfo *fsP);
  int getPerNodePerfIndex(char *ipAddrP);

public:
  FilesystemInfo(MErrno *errP);

  ~FilesystemInfo();

  FilesystemInfo& operator=(FilesystemInfo &fs);
  void clearStats();

  /* Filesystem info from SDR and EE get fs */
  inline char *getName() { return name; }
  inline char *getManager() { return manager; }
  inline char *getStatus() { return status; }
  inline char *getXstatus() { return xstatus; }

  inline UInt32 getReadDuration() { return readDuration; }
  inline UInt32 getWriteDuration() { return writeDuration; }
  inline UInt32 getNumMgmt() { return numMgmt; }
  inline UInt32 getNumMgrChange() { return numMgrChange; }
  inline UInt64 getTotalSpace() { return totalSpace; }
  inline UInt64 getNumTotalInodes() { return numTotalInodes; }
  inline UInt64 getFreeSpace() { return freeSpace; }
  inline UInt64 getNumFreeInodes() { return numFreeInodes; }
  inline UInt64 getFullBlockFreeSpace() { return fullBlockFreeSpace; }
  inline UInt64 getSubBlockFreeSpace() { return subBlockFreeSpace; }

  /* Filesystem performance statistics from mmpmon gfis */
  inline char *getThreadWait() { return threadWait; }
  inline char *getDiskWait() { return diskWait; }

  inline UInt64 getMinFragmentSize() { return minFragmentSize; }
  inline UInt64 getInodeSize() { return inodeSize; }
  inline UInt64 getIndirectBlockSize() { return indirectBlockSize; }
  inline UInt64 getEstimatedAverageFileSize() { return estimatedAverageFileSize; }
  inline UInt64 getNumNodes() { return numNodes; }
  inline UInt64 getBlockSize() { return blockSize; }
  inline UInt64 getFSInodeLimit() { return maxNumInodes; }
  inline UInt32 getDefaultMetadataReplicas() { return defaultMetadataReplicas; }
  inline UInt32 getMaxMetadataReplicas() { return maxMetadataReplicas; }
  inline UInt32 getDefaultDataReplicas() { return defaultDataReplicas; }
  inline UInt32 getMaxDataReplicas() { return maxDataReplicas; }
  inline char *getBlockAllocationType() { return blockAllocationType; }
  inline char *getFileLockingSemantics() { return fileLockingSemantics; }
  inline char *getAclSemantics() { return aclSemantics; }
  inline char *getQuotaEnforced() { return quotaEnforced; }
  inline char *getDefaultQuotasEnabled() { return defaultQuotasEnabled; }
  inline char *getFilesystemVersion() { return filesystemVersion; }
  inline char *getSupportForLargeLuns() { return supportForLargeLuns; }
  inline char *getDmapiEnabled() { return dmapiEnabled; }
  inline char *getExactMtime() { return exactMtime; }
  inline char *getSuppressAtime() { return suppressAtime; }
  inline char *getAutomaticMountOption() { return automaticMountOption; }
  inline char *getAdditionalMountOptions() { return additionalMountOptions; }
  inline char *getDefaultMountPoint() { return defaultMountPoint; }

  inline UInt64 getBytesRead() { return bytesRead; }
  inline UInt64 getBytesCache() { return bytesCache; }
  inline UInt64 getBytesWritten() { return bytesWritten; }
  inline UInt32 getReads() { return reads; }
  inline UInt32 getCaches() { return caches; }
  inline UInt32 getWrites() { return writes; }
  inline UInt32 getOpenCalls() { return openCalls; }
  inline UInt32 getCloseCalls() { return closeCalls; }
  inline UInt32 getReadCalls() { return readCalls; }
  inline UInt32 getWriteCalls() { return writeCalls; }
  inline UInt32 getReaddirCalls() { return readdirCalls; }
  inline UInt64 getInodesWritten() { return inodesWritten; }
  inline UInt64 getInodesRead() { return inodesRead; }
  inline UInt64 getInodesDeleted() { return inodesDeleted; }
  inline UInt64 getInodesCreated() { return inodesCreated; }
  inline UInt32 getStatCacheHit() { return statCacheHit; }
  inline UInt32 getStatCacheMiss() { return statCacheMiss; }

  /* Storage pool information from EE get stgpools */
  inline UInt32 getNumStoragePools() { return poolItems.size(); }
  inline StoragePoolInfo *getStoragePool(int p) { return poolItems.at(p); }
  inline struct timeval getPoolRefreshTime() { return poolRefreshTime; }

  inline UInt32 getNodePerfCount() { return nodePerfCount; }

  inline UInt32 getNumMountedNodes() { return mountedNodeItems.size(); }
  inline MountedNodeInfo *getMountedNode(int n) { return mountedNodeItems.at(n); }

  inline UInt32 getNumPolicies() { return policyItems.size(); }
  inline PolicyInfo *getPolicy(int n) { return policyItems.at(n); }

  inline UInt32 getNumPerNodePerfs() { return perfItems.size(); }
  inline FilesystemPerf *getPerNodePerf(int n) { return perfItems.at(n); }

  /* MODS_START */
  inline bool wasUpdated() { return updated; }
  /* MODS_END */

};

/* Disk access information */
class DiskAccessInfo
{
  friend class PollingHandler;

  char diskName[NAME_STRING_LEN];
  Boolean_t local;
  char deviceName[NAME_STRING_LEN];
  char serverName[NAME_STRING_LEN];

public:
  DiskAccessInfo(MErrno *errP);

  ~DiskAccessInfo();

  DiskAccessInfo& operator=(DiskAccessInfo &d);

  inline char *getDiskName() { return diskName; }
  inline Boolean_t isLocal() { return local; }
  inline char *getDeviceName() { return deviceName; }
  inline char *getServerName() { return serverName; }
};

/* I/O statistics counted by context

   _response_ begin mmpmon iocs
   _mmpmon::iocs_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1262967025
     _tu_ 739667 _other_ 672560 18244 _mb_ 3427 580 _steal_ 5 8
     _cleaner_ 0 910 _sync_ 22 487 _logwrap_ 0 16703 _revoke_ 0 0
     _prefetch_ 9250 0  _logdata_ 9250 0 _nsdworker_ 9250 0
   _response_ end
*/

/* Define a version number for ioStatsInfo to allow
   future changes in this structure.
 */
#define GPFS_IOCS_VERSION 1

class IocStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  UInt32 iocUnknown_r;
  UInt32 iocUnknown_w;
  UInt32 iocMBHandler_r;
  UInt32 iocMBHandler_w;
  UInt32 iocSteal_r;
  UInt32 iocSteal_w;
  UInt32 iocCleaner_r;
  UInt32 iocCleaner_w;
  UInt32 iocSync_r;
  UInt32 iocSync_w;
  UInt32 iocLogwrap_r;
  UInt32 iocLogwrap_w;
  UInt32 iocRevoke_r;
  UInt32 iocRevoke_w;
  UInt32 iocPrefetch_r;
  UInt32 iocPrefetch_w;

public:
  IocStatsInfo(MErrno *errP);
  IocStatsInfo();
  ~IocStatsInfo();

  IocStatsInfo& operator=(IocStatsInfo &ioc);

  void clearStats();

  inline UInt32 getIocUnknown_r() { return iocUnknown_r; }
  inline UInt32 getIocUnknown_w() { return iocUnknown_w; }
  inline UInt32 getIocMBHandler_r() { return iocMBHandler_r; }
  inline UInt32 getIocMBHandler_w() { return iocMBHandler_w; }
  inline UInt32 getIocSteal_r() { return iocSteal_r; }
  inline UInt32 getIocSteal_w() { return iocSteal_w; }
  inline UInt32 getIocCleaner_r() { return iocCleaner_r; }
  inline UInt32 getIocCleaner_w() { return iocCleaner_w; }
  inline UInt32 getIocSync_r() { return iocSync_r; }
  inline UInt32 getIocSync_w() { return iocSync_w; }
  inline UInt32 getIocLogwrap_r() { return iocLogwrap_r; }
  inline UInt32 getIocLogwrap_w() { return iocLogwrap_w; }
  inline UInt32 getIocRevoke_r() { return iocRevoke_r; }
  inline UInt32 getIocRevoke_w() { return iocRevoke_w; }
  inline UInt32 getIocPrefetch_r() { return iocPrefetch_r; }
  inline UInt32 getIocPrefetch_w() { return iocPrefetch_w; }
  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
};

/* vfs statistics

_response_ begin mmpmon vfss
_mmpmon::vfss_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1262970919
  _tu_ 253243 _access_ 3106 0.037376 _close_ 218 0.033548 _create_ 0 0.000000
  _fclear_ 0 0.000000 _fsync_ 0 0.000000 _fsync_range_ 0 0.000000
  _ftrunc_ 0 0.000000 _getattr_ 13590 7.612393 _link_ 0 0.000000
  _lockctl_ 0 0.000000 _lookup_ 30154 1.026978 _map_lloff_ 0 0.000000
  _mkdir_ 0 0.000000 _mknod_ 0 0.000000 _open_ 218 0.127916
  _read_ 380 0.081198 _write_ 0 0.000000 _mmapRead_ 0 0.000000
  _mmapWrite_ 0 0.000000 _readdir_ 1131 0.459991 _readlink_ 0 0.000000
  _readpage_ 0 0.000000 _remove_ 3104 45.060595 _rename_ 0 0.000000
  _rmdir_ 0 0.000000 _setacl_ 0 0.000000 _setattr_ 0 0.000000
  _symlink_ 0 0.000000 _unmap_ 0 0.000000 _writepage_ 0 0.000000
  _tsfattr_ 0 0.000000 _tsfsattr_ 0 0.000000 _flock_ 0 0.000000
  _setxattr_ 0 0.000000 _getxattr_ 0 0.000000 _listxattr_ 0 0.000000
  _removexattr_ 0 0.000000 _encode_fh_ 0 0.000000 _decode_fh_ 0 0.000000
  _get_dentry_ 0 0.000000 _get_parent_ 0 0.000000 _mount_ 1 13.515959
  _statfs_ 0 0.000000 _sync_ 2796 5.254986 _vget_ 0 0.000000
_response_ end

*/

/* Define a version number for VfsStatsInfo to allow
   future changes in this structure.
 */
#define GPFS_VFSS_VERSION 1

class VfsStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  /* vfs calls */
  UInt32 accessCalls;
  UInt32 closeCalls;
  UInt32 createCalls;
  UInt32 fclearCalls;
  UInt32 fsyncCalls;
  UInt32 fsync_rangeCalls;
  UInt32 ftruncCalls;
  UInt32 getattrCalls;
  UInt32 linkCalls;
  UInt32 lockctlCalls;
  UInt32 lookupCalls;
  UInt32 map_lloffCalls;
  UInt32 mkdirCalls;
  UInt32 mknodCalls;
  UInt32 openCalls;
  UInt32 readCalls;
  UInt32 writeCalls;
  UInt32 mmapReadCalls;
  UInt32 mmapWriteCalls;
  UInt32 readdirCalls;
  UInt32 readlinkCalls;
  UInt32 readpageCalls;
  UInt32 removeCalls;
  UInt32 renameCalls;
  UInt32 rmdirCalls;
  UInt32 setaclCalls;
  UInt32 setattrCalls;
  UInt32 symlinkCalls;
  UInt32 unmapCalls;
  UInt32 writepageCalls;
  UInt32 tsfattrCalls;
  UInt32 tsfsattrCalls;
  UInt32 flockCalls;
  UInt32 setxattrCalls;
  UInt32 getxattrCalls;
  UInt32 listxattrCalls;
  UInt32 removexattrCalls;
  UInt32 encode_fhCalls;
  UInt32 decode_fhCalls;
  UInt32 get_dentryCalls;
  UInt32 get_parentCalls;
  UInt32 mountCalls;
  UInt32 statfsCalls;
  UInt32 syncCalls;
  UInt32 vgetCalls;

  /* total time spent on each call */
  float accessT;
  float closeT;
  float createT;
  float fclearT;
  float fsyncT;
  float fsync_rangeT;
  float ftruncT;
  float getattrT;
  float linkT;
  float lockctlT;
  float lookupT;
  float map_lloffT;
  float mkdirT;
  float mknodT;
  float openT;
  float readT;
  float writeT;
  float mmapReadT;
  float mmapWriteT;
  float readdirT;
  float readlinkT;
  float readpageT;
  float removeT;
  float renameT;
  float rmdirT;
  float setaclT;
  float setattrT;
  float symlinkT;
  float unmapT;
  float writepageT;
  float tsfattrT;
  float tsfsattrT;
  float flockT;
  float setxattrT;
  float getxattrT;
  float listxattrT;
  float removexattrT;
  float encode_fhT;
  float decode_fhT;
  float get_dentryT;
  float get_parentT;
  float mountT;
  float statfsT;
  float syncT;
  float vgetT;

public:
  VfsStatsInfo(MErrno *errP);
  VfsStatsInfo();
  ~VfsStatsInfo();

  VfsStatsInfo& operator=(VfsStatsInfo &v);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
  inline UInt32 getAccessCalls() { return  accessCalls; }
  inline UInt32 getCloseCalls() { return  closeCalls; }
  inline UInt32 getCreateCalls() { return  createCalls; }
  inline UInt32 getFclearCalls() { return  fclearCalls; }
  inline UInt32 getFsyncCalls() { return  fsyncCalls; }
  inline UInt32 getFsync_rangeCalls() { return  fsync_rangeCalls; }
  inline UInt32 getFtruncCalls() { return  ftruncCalls; }
  inline UInt32 getGetattrCalls() { return getattrCalls; }
  inline UInt32 getLinkCalls() { return  linkCalls; }
  inline UInt32 getLockctlCalls() { return  lockctlCalls; }
  inline UInt32 getLookupCalls() { return  lookupCalls; }
  inline UInt32 getMap_lloffCalls() { return  map_lloffCalls; }
  inline UInt32 getMkdirCalls() { return  mkdirCalls; }
  inline UInt32 getMknodCalls() { return mknodCalls; }
  inline UInt32 getOpenCalls() { return  openCalls; }
  inline UInt32 getReadCalls() { return  readCalls; }
  inline UInt32 getWriteCalls() { return  writeCalls; }
  inline UInt32 getMmapReadCalls() { return  mmapReadCalls; }
  inline UInt32 getMmapWriteCalls() { return  mmapWriteCalls; }
  inline UInt32 getReaddirCalls() { return  readdirCalls; }
  inline UInt32 getReadlinkCalls() { return readlinkCalls; }
  inline UInt32 getReadpageCalls() { return  readpageCalls; }
  inline UInt32 getRemoveCalls() { return removeCalls; }
  inline UInt32 getRenameCalls() { return renameCalls ; }
  inline UInt32 getRmdirCalls() { return rmdirCalls; }
  inline UInt32 getSetaclCalls() { return setaclCalls; }
  inline UInt32 getSetattrCalls() { return  setattrCalls; }
  inline UInt32 getSymlinkCalls() { return  symlinkCalls; }
  inline UInt32 getUnmapCalls() { return  unmapCalls; }
  inline UInt32 getWritepageCalls() { return  writepageCalls; }
  inline UInt32 getTsfattrCalls() { return  tsfattrCalls; }
  inline UInt32 getTsfsattrCalls() { return  tsfsattrCalls; }
  inline UInt32 getFlockCalls() { return  flockCalls; }
  inline UInt32 getSetxattrCalls() { return  setxattrCalls; }
  inline UInt32 getGetxattrCalls() { return  getxattrCalls; }
  inline UInt32 getListxattrCalls() { return listxattrCalls ; }
  inline UInt32 getRemovexattrCalls() { return  removexattrCalls; }
  inline UInt32 getEncode_fhCalls() { return  encode_fhCalls; }
  inline UInt32 getDecode_fhCalls() { return  decode_fhCalls; }
  inline UInt32 getGet_dentryCalls() { return  get_dentryCalls; }
  inline UInt32 getGet_parentCalls() { return  get_parentCalls; }
  inline UInt32 getMountCalls() { return  mountCalls; }
  inline UInt32 getStatfsCalls() { return  statfsCalls; }
  inline UInt32 getSyncCalls() { return  syncCalls; }
  inline UInt32 getVgetCalls() { return  vgetCalls; }

  inline float getAccessTime() { return  accessT; }
  inline float getCloseTime() { return  closeT; }
  inline float getCreateTime() { return  createT; }
  inline float getFclearTime() { return  fclearT; }
  inline float getFsyncTime() { return  fsyncT; }
  inline float getFsync_rangeTime() { return  fsync_rangeT; }
  inline float getFtruncTime() { return  ftruncT; }
  inline float getGetattrTime() { return  getattrT; }
  inline float getLinkTime() { return  linkT; }
  inline float getLockctlTime() { return  lockctlT; }
  inline float getLookupTime() { return  lookupT; }
  inline float getMap_lloffTime() { return  map_lloffT; }
  inline float getMkdirTime() { return  mkdirT; }
  inline float getMknodTime() { return mknodT; }
  inline float getOpenTime() { return  openT; }
  inline float getReadTime() { return  readT; }
  inline float getWriteTime() { return  writeT; }
  inline float getMmapReadTime() { return  mmapReadT; }
  inline float getMmapWriteTime() { return  mmapWriteT; }
  inline float getReaddirTime() { return  readdirT; }
  inline float getReadlinkTime() { return readlinkT; }
  inline float getReadpageTime() { return  readpageT; }
  inline float getRemoveTime() { return removeT; }
  inline float getRenameTime() { return renameT ; }
  inline float getRmdirTime() { return rmdirT; }
  inline float getSetaclTime() { return setaclT; }
  inline float getSetattrTime() { return  setattrT; }
  inline float getSymlinkTime() { return  symlinkT; }
  inline float getUnmapTime() { return  unmapT; }
  inline float getWritepageTime() { return  writepageT; }
  inline float getTimesfattrT() { return  tsfattrT; }
  inline float getTimesfsattrT() { return  tsfsattrT; }
  inline float getFlockTime() { return  flockT; }
  inline float getSetxattrTime() { return  setxattrT; }
  inline float getGetxattrTime() { return  getxattrT; }
  inline float getListxattrTime() { return listxattrT ; }
  inline float getRemovexattrTime() { return  removexattrT; }
  inline float getEncode_fhTime() { return  encode_fhT; }
  inline float getDecode_fhTime() { return  decode_fhT; }
  inline float getGet_dentryTime() { return  get_dentryT; }
  inline float getGet_parentTime() { return  get_parentT; }
  inline float getMountTime() { return  mountT; }
  inline float getStatfsTime() { return  statfsT; }
  inline float getSyncTime() { return  syncT; }
  inline float getVgetTime() { return  vgetT; }
};

/* Per node thread utilization stats

  _response_ begin mmpmon threads
  _mmpmon::threads_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1263415922
     _tu_ 317953 _nthreads_ 127 _seq_ 60149 _noncritical_ 13 28 1473
     _daemonstartup_ 14 16 33 _mbhandler_ 29 29 65 _rcvworker_ 10 11 266
     _revokeworker_ 0 0 35 _rangerevoke_ 0 0 20 _reclockrevoke_ 0 0 10
     _prefetch_ 1 1 72 _sgexception_ 0 3 16 _receiver_ 12 12 16
     _pcache_ 0 0 0 _multithreadworker_ 0 0 974
  _response_ end

*/

/* Define a version number for ThreadUtilInfo to allow
   future changes in this structure.
 */
#define GPFS_THRDS_VERSION 1

class ThreadUtilInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  UInt32 nThreads;
  UInt32 seq;

  /* Thread pool utilization (current/highest/maximum) */
  threadUtil_t noncritical;
  threadUtil_t daemonstartup;
  threadUtil_t mbhandler;
  threadUtil_t rcvworker;
  threadUtil_t revokeworker;
  threadUtil_t rangerevoke;
  threadUtil_t reclockrevoke;
  threadUtil_t prefetch;
  threadUtil_t sgexception;
  threadUtil_t receiver;
  threadUtil_t pcache;
  threadUtil_t multithreadworker;

public:
  ThreadUtilInfo(MErrno *errP);
  ThreadUtilInfo();
  ~ThreadUtilInfo();

  ThreadUtilInfo& operator=(ThreadUtilInfo &th_u);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
  inline UInt32 getNthreads() { return nThreads; }
  inline UInt32 getSeq() { return seq; }

  inline threadUtil_t *getNoncritical() { return &noncritical; }
  inline threadUtil_t *getDaemonstartup() { return &daemonstartup; }
  inline threadUtil_t *getMbhandler() { return &mbhandler; }
  inline threadUtil_t *getRcvworker() { return &rcvworker; }
  inline threadUtil_t *getRevokeworker() { return &revokeworker; }
  inline threadUtil_t *getRrangerevoke() { return &rangerevoke; }
  inline threadUtil_t *getReclockrevoke() { return &reclockrevoke; }
  inline threadUtil_t *getPrefetch() { return &prefetch; }
  inline threadUtil_t *getSgexception() { return &sgexception; }
  inline threadUtil_t *getReceiver() { return &receiver; }
  inline threadUtil_t *getPcache() { return &pcache; }
  inline Int32 getMultithreadWanted() { return multithreadworker.current; }
  inline Int32 getMultithreadRunning() { return multithreadworker.highest; }
  inline Int32 getMultithreadLimit() { return multithreadworker.maximum; }

};

/* rpcs stats
 *   _response_ begin mmpmon rpcs
 *   _mmpmon::rpcs_  _req_ node _n_ 192.168.56.168 _nn_ node3 _rn_ 192.168.56.167 _rnn_ node2 _rc_ 0 _t_ 1388052336  _tu_ 611492
 *   _rpcObj_ _obj_ AG_STAT_CHANNEL_WAIT _nsecs_ 1 _nmins_ 10 _nhours_ 0 _ndays_ 0
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   .........
 *   .........
 *   _rpcObj_ _obj_ AG_STAT_SEND_TIME_TCP _nsecs_ 1 _nmins_ 10 _nhours_ 0 _ndays_ 0
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   .........
 *   .........
 *   _response_ end
 *
 * rpcs ns
 *   _response_ begin mmpmon rpcs ns
 *   _mmpmon::rpcs_  _req_ node _n_ 192.168.56.168 _nn_ node3 _rc_ 0 _t_ 1388052336  _tu_ 611492
 *   _rpcObj_ _obj_ AG_STAT_CHANNEL_WAIT _nsecs_ 1 _nmins_ 0 _nhours_ 0 _ndays_ 0
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   _rpcObj_ _obj_ AG_STAT_SEND_TIME_TCP _nsecs_ 1 _nmins_ 0 _nhours_ 0 _ndays_ 0
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   _response_ end
 *
 * rpcs size
 *   _response_ begin mmpmon rpcs size
 *   _mmpmon::rpcs_ _req_ size _n_ 192.168.56.167 _nn_ node2 _rc_ 0 _t_ 1388417852  _tu_ 572950
 *   _rpcSize_ _size_ 64 _nsecs_ 60 _nmins_ 60 _nhours_ 24 _ndays_ 30
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   ........
 *   ........
 *   _response_ end
 *
 * rpcs message
 *   _response_ begin mmpmon rpcs message
 *   _mmpmon::rpcs_ _req_ message _n_ 192.168.56.167 _nn_ node2 _rc_ 0 _t_ 13907i61504  _tu_ 332981
 *   _rpcObj_ _obj_ xxxx _nsecs_ 60 _nmins_ 60 _nhours_ 24 _ndays_ 30
 *   _stats_ _tmu_ xxxx _av_ x.000, _min_ x.000, _max_ x.000, _cnt_ xxxx
 *   .......
 *   .......
 *   _response_ end
 *
 * rpcs raw
 *   _response_ begin mmpmon rpcs raw
 *   _mmpmon::rpcs_ _req_ raw _n_ 192.168.56.167 _nn_ node2 _rc_ 0 _t_ xxxx  _tu_ xxxx
 *   _rpcstat_ _rpcstator_ xxxx _rpcstatcnt_ xxxx
 *   _stat_ _cw_ xxxx _st_ xxxx _rt_ xxxx _rpclt_ xxxx _ds_ xxxx _dr_ xxxx _rdmas_ xxxx _rdmar_ xxxx _ni_ xxxx
 *   _stat_ _cw_ xxxx _st_ xxxx _rt_ xxxx _rpclt_ xxxx _ds_ xxxx _dr_ xxxx _rdmas_ xxxx _rdmar_ xxxx _ni_ xxxx
 *   .....
 *   _rpcexec_ _rpcexecor_ xxxx _rpcexeccnt_ xxxx
 *   _stat_ _rpcet_ xxxx _rpcsn_ xxxx _rpcmt_ xxxx
 *   _stat_ _rpcet_ xxxx _rpcsn_ xxxx _rpcmt_ xxxx
 *   .....
 *   .....
 *   _response_ end
 *
/* Define a version number for RPCUtilInfo to allow
 * future changes in this structure.
 */
#define GPFS_RPC_VERSION 1

/* class to mainatain stats for single time unit */
class PerfSample
{
public:
  double minValue; //min over a single time unit
  double maxValue; // max over a single time unit
  double sumValue; // average over a single time unit
  UInt64 valueCount; // count of stats over a single time unit

  inline PerfSample()
  {
    clearstats();
  }
  inline ~PerfSample(){};
  inline void clearstats()
  {
    minValue = maxValue = sumValue = valueCount = 0;
  }
};

/* class to maintain stats for all available secs/mins/hours/days
 * for an object */
class AggregatedRPCPerfStat
{
public:
  UInt32   numSecs; //num of secs maintained for an rpc object
  UInt32   numMins; // num of mins maintained for an rpc object
  UInt32   numHours; // num of hours maintained for an rpc object
  UInt32   numDays; // num of days maintained for an rpc object
  PerfSample *secondP; // array of PerfSample for nsecs
  PerfSample *minuteP; // array of PerfSample for  nmins
  PerfSample *hourP; // array of PerfSample for nhours
  PerfSample *dayP; //array of PerfSample for ndays
  char objName[NAME_STRING_LEN]; //Name of rpc object
  AggregatedRPCPerfStat(UInt32 nSeconds, UInt32 nMinutes, UInt32 nHours, UInt32 nDays, char *objectName);
  AggregatedRPCPerfStat();
  AggregatedRPCPerfStat(const AggregatedRPCPerfStat& agPerfStat);
  ~AggregatedRPCPerfStat();
  AggregatedRPCPerfStat& operator=(AggregatedRPCPerfStat &agPerfStat);

  inline UInt32 getNumSecs() { return numSecs;}
  inline UInt32 getNumMins() { return numMins;}
  inline UInt32 getNumHours() { return numHours;}
  inline UInt32 getNumDays() { return numDays;}
  /* return nth sec from secondP array */
  inline PerfSample *getSecs(int n)
  {
    assert(n < numSecs);
    return &(secondP[n]);
  }
  /* return nth min from minuteP array */
  inline PerfSample *getMins(int n)
  {
    assert(n < numMins);
    return &(minuteP[n]);
  }
  /* return nth hour from hourP array */
  inline PerfSample *getHours(int n)
  {
    assert(n < numHours);
    return &(hourP[n]);
  }
  /* return nth day from dayP array */
  inline PerfSample *getDays(int n)
  {
    assert(n < numDays);
    return &(dayP[n]);
  }
  inline char* getObjectName()
  {
    return objName;
  }
};

/* class to maintain rpc stats for every remote node */
class NodeUtilInfo
{
public:
  char nodeName[NAME_STRING_LEN]; /*Node name*/
  char nodeIpAddr[NAME_STRING_LEN]; /*Node ip address x.x.x.x */
  int numObjects; /*number of rpc objects for which stats is to be maintained */
  AggregatedRPCPerfStat *agRpcPerfStatP[RPC_OBJECTS]; /*array to maintain rpc stats for each rpc object*/
  NodeUtilInfo(MErrno *errP, char *nodeName, char *nodeIpAddr); /*contructor*/
  NodeUtilInfo(); /*constructor*/
  NodeUtilInfo(const NodeUtilInfo& nodeUtilInfo); /*copy constructor*/
  ~NodeUtilInfo(); /*destructor*/
  NodeUtilInfo& operator=(NodeUtilInfo &nodeUtilP); /* = operator overloading */
  inline int getNumObjects() /* returns number of rpc objects for which stats is maintained */
  {
    return numObjects;
  }
  inline AggregatedRPCPerfStat getRPCPerfStatObj(int n) /*returns nth rpc object*/
  {
    assert(n < numObjects);
    return *(agRpcPerfStatP[n]);
  }
};

/* class to maintain rpc stats info for all objects */
class RPCUtilInfo
{
  friend class PollingHandler;
  /* array to maintain rpc stats info per node
   * node1 to node2, node1 to node3, node1 to node4 */
  NodeUtilInfo *nodeUtilInfo[MAX_NODE];
  UInt32 numNodes; /*number of nodes for which rpc stats is maintained */
public:
  RPCUtilInfo(MErrno *errP); /*constructor*/
  RPCUtilInfo(); /*constructor*/
  RPCUtilInfo(const RPCUtilInfo& rpc_u); /*copy constructor*/
  ~RPCUtilInfo(); /*destructor */
  RPCUtilInfo& operator=(RPCUtilInfo &rpc_u); /* = operator overloading */
  void clearStats(); /* clears the information holded in RPCUtilInfo object */

  inline NodeUtilInfo getNodeUtilInfo(int n) /* returns rpc state for nth node */
  {
    assert(n < numNodes);
    return *(nodeUtilInfo[n]);
  }
  inline UInt32 getNumNodes() /*returns number of nodes */
  {
    return numNodes;
  }
};

class RawRPCStat
{
public :
  UInt64    channelWait;     // time waiting to get comm channel (nanoseconds)
  UInt64    sendTime;        // time to send message (nanoseconds)
  UInt64    receiveTime;     // time to receive message (nanoseconds)
  UInt64    RPCLatency;      // round trip time - RPC execution time (nanoseconds)
  UInt32    dataSent;        // length of payload sent, if any
  UInt32    dataReceived;    // length of payload received, if any
  Boolean_t rdmaSend;        // RPC sent via RMDA
  Boolean_t rdmaReceive;     // RPC received via RMDA
  int nodeAddr;              // node address
  RawRPCStat()
  {
    channelWait = 0;
    sendTime = 0;
    receiveTime = 0;
    RPCLatency = 0;
    dataSent = 0;
    dataReceived = 0;
    rdmaSend = false;
    rdmaReceive = false;
    nodeAddr = 0;
  }
  ~RawRPCStat(){}
};

class RawRPCExec
{
public :
  UInt64   RPCExecTime; /* time to execute RPC on target node (nanoseconds)*/
  UInt16   RPCservice_no; /* RPC service number */
  UInt32 RPCmsg_type; /* RPC message type */
  RawRPCExec()
  {
    RPCExecTime = 0;
    RPCservice_no = 0;
    RPCmsg_type = 0;
  }
  ~RawRPCExec(){}
};

/* class to maintain network performance stats for raw type */
class RPCRawUtilInfo
{
  friend class PollingHandler;
  RawRPCExec *rpcExecP; /* array to maintain info for rpc exec objects*/
  RawRPCStat *rpcStatP; /*array to maintain info for rpc stat objects*/
  int rpcStatOverRunCount; /*count of buffer overruns for rpc stat*/
  int rpcExecOverRunCount; /*count of buffer overruns for rpc exec*/
  int rpcStatCount; /* rpc stat count*/
  int rpcExecCount; /* rpc exec count*/
public:
  RPCRawUtilInfo(MErrno *errP);
  RPCRawUtilInfo();
  ~RPCRawUtilInfo();
  RPCRawUtilInfo& operator=(RPCRawUtilInfo &rpcRaw_u);
  void clearStats();
  /* return nth rpc stat object */
  inline RawRPCStat *getRPCStatObj(int n)
  {
    assert(n < rpcStatCount);
    return &rpcStatP[n];
  }
  /* return nth rpc exec object */
  inline RawRPCExec *getRPCExecObj(int n)
  {
    assert(n < rpcExecCount);
    return &rpcExecP[n];
  }
  inline int getRpcStatOverRunCount() { return rpcStatOverRunCount; }
  inline int getRpcExecOverRunCount() { return rpcExecOverRunCount; }
  inline int getRpcStatCount() { return rpcStatCount; }
  inline int getRpcExecCount() { return rpcExecCount; }
};

/* class to maintain network performance stats as per message sizes */
class RPCSizeUtilInfo
{
  friend class PollingHandler;
  /* array to maintain aggregated stat */
  AggregatedRPCPerfStat *agRpcPerfStatP[MAX_NUMBER_BUCKETS];
  int sizePerBucket[MAX_NUMBER_BUCKETS]; /* bucket sizes */
  int numBucketOutput; /* output available for num of buckets */

  /* Set aggregated rpc performance stat for nth bucket*/
  inline void setRPCPerfStatObj(AggregatedRPCPerfStat *agPerfStat, int n)
  {
     assert(n < MAX_NUMBER_BUCKETS);
     agRpcPerfStatP[n] = agPerfStat;
  }
public:
  RPCSizeUtilInfo(MErrno *errP);
  RPCSizeUtilInfo();
  ~RPCSizeUtilInfo();
  RPCSizeUtilInfo& operator=(RPCSizeUtilInfo &rpc_u);
  void clearStats();
  /* get aggregated performance stat for nth bucket */
  inline AggregatedRPCPerfStat getRPCPerfStatObj(int n)
  {
    assert(n < MAX_NUMBER_BUCKETS && n < numBucketOutput);
    return *(agRpcPerfStatP[n]);
  }
  /* get bucket size for nth bucket */
  inline int getSizePerBucket(int n)
  {
    assert(n < MAX_NUMBER_BUCKETS && n < numBucketOutput);
    return sizePerBucket[n];
  }
  /* get total num of buckets available */
  inline int getNumBuckets()
  {
    return numBucketOutput;
  }
};

/* class to maintain network performance stats as per message types */
class RPCMsgUtilInfo
{
  friend class PollingHandler;
  /*Aggregated performance stat per message type */
  AggregatedRPCPerfStat *agRpcPerfStatP[MAX_MSG_RPC];
  int numMsgOutput; /*num of message types available */

  /* set aggaregated stats for nth agRpcPerfStatP */
  inline void setRPCPerfStatObj(AggregatedRPCPerfStat *agPerfStat, int n)
  {
    assert(n < MAX_MSG_RPC);
    agRpcPerfStatP[n] = agPerfStat;
  }
public:
  RPCMsgUtilInfo(MErrno *errP);
  RPCMsgUtilInfo();
  ~RPCMsgUtilInfo();
  RPCMsgUtilInfo& operator=(RPCMsgUtilInfo &rpc_u);
  void clearStats();

  /* get aggaregated stats for nth agRpcPerfStatP */
  inline AggregatedRPCPerfStat *getRPCMsgStatObj(int n)
  {
    assert(n < MAX_MSG_RPC && n < numMsgOutput);
    return agRpcPerfStatP[n];
  }
  inline int getNumMsg()
  {
    return numMsgOutput;
  }
};

/* class to maintain stats for one secs for an object */
class AggregatedRPCPerfStatPerSec
{
public:
  PerfSample secondP; /* array of PerfSample for nsecs */
  char objName[NAME_STRING_LEN]; /* Name of rpc object */
  AggregatedRPCPerfStatPerSec();
  ~AggregatedRPCPerfStatPerSec();
  AggregatedRPCPerfStatPerSec(const AggregatedRPCPerfStatPerSec& agPerfStat); /* copy constructor */
};

/* class to maintain aggregated rpc stats info for one sec for all objects */
class AggregatedRPCUtilInfoPerSec
{
  friend class PollingHandler;
  AggregatedRPCPerfStatPerSec * agRpcPerfStatP[RPC_OBJECTS];
  UInt32 numObjects;
  /* set the value of AggregatedRPCPerfStat for nth object */
  inline void setRPCPerfStatObj(AggregatedRPCPerfStatPerSec *agPerfStat, int n)
  {
    assert(n < RPC_OBJECTS);
    agRpcPerfStatP[n] = agPerfStat;
  }
public:
  AggregatedRPCUtilInfoPerSec();
  ~AggregatedRPCUtilInfoPerSec();
  AggregatedRPCUtilInfoPerSec& operator=(AggregatedRPCUtilInfoPerSec &rpc_u);
  void clearStats();
  /* return AggregatedRPCPerfStat for nth object */
  inline AggregatedRPCPerfStatPerSec getRPCPerfStatObj(int n)
  {
    assert(n < numObjects);
    return *(agRpcPerfStatP[n]);
  }
  inline UInt32 getNumObjects()
  {
    return numObjects;
  }
};

/* Cache hit miss statistics

   _response_ begin mmpmon chms
   _mmpmon::chms_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1263846820
                 _tu_ 373341 _dch_ 0 _dcm_ 0 _sch_ 43027 _scm_ 34
   _response_ end

*/

/* Define a version number for CacheStatsInfo to allow
   future changes in this structure.
 */
#define GPFS_CHMS_VERSION 1

class CacheStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  UInt32 dataCacheHit;   /* _dch_ */
  UInt32 dataCacheMiss;  /* _dcm_ */
  UInt32 statCacheHit;   /* _sch_ */
  UInt32 statCacheMiss;  /* _scm_ */

public:
  CacheStatsInfo(MErrno *errP);
  CacheStatsInfo();
  ~CacheStatsInfo();

  CacheStatsInfo& operator=(CacheStatsInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
  inline UInt32 getDataCacheHit() { return dataCacheHit; }
  inline UInt32 getDataCacheMiss() { return dataCacheMiss; }
  inline UInt32 getStatCacheHit() { return statCacheHit; }
  inline UInt32 getStatCacheMiss() { return statCacheMiss; }
};

/*
 * PANACHE statistics
   _response_ begin mmpmon pncs
   _mmpmon::pncs_ _n_ 192.168.115.156 _nn_ hs21n20 _rc_ 0 _t_ 1263954355
     _tu_ 209718 _fs_ fs1 _fset_ ro
     _br_ 0 _bw_ 0 _ws_ 0 _wl_ 0 _wa_ 0 _ne_ 0 _nf_ 0 _ns_ 0 _nr_ 0
     _ncmd_ 20 _q_ 0 _i_ 0 _c_ 0 _e_ 0 _f_ 0 _n_ 0
               _q_ 0 _i_ 0 _c_ 0 _e_ 0 _f_ 0 _n_ 0
               _q_ 0 _i_ 0 _c_ 0 _e_ 0 _f_ 0 _n_ 0
              ...
               _q_ 0 _i_ 0 _c_ 0 _e_ 0 _f_ 0 _n_ 0
               _q_ 0 _i_ 0 _c_ 0 _e_ 0 _f_ 0 _n_ 0
   _response_ end
 *
 */
/********************************/
/* Define a version number for verbsServerStatsInfo to allow
   future changes in this structure.
 */
#define GPFS_VERBSSERVERSTATS_VERSION 1

class VerbsServerStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */

  char   destination[NAME_STRING_LEN];
  char   state[NAME_STRING_LEN];
  UInt64 curRdma;
  UInt64 waitRdma;
  UInt64 rdmaRead;
  UInt64 rdmaWrite;
  UInt64 rdmaReadKb;
  UInt64 rdmaWriteKb;
  UInt32 device;
  UInt32 port;

public:
  VerbsServerStatsInfo(MErrno *errP);
  ~VerbsServerStatsInfo();

  VerbsServerStatsInfo& operator=(VerbsServerStatsInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }

  inline char  *getDestination() { return destination; }
  inline char  *getState() { return state; }

  inline UInt64 getCurRdma() { return curRdma; }
  inline UInt64 getWaitRdma() { return waitRdma; }
  inline UInt64 getRdmaRead() { return rdmaRead; }
  inline UInt64 getRdmaWrite() { return rdmaWrite; }
  inline UInt64 getRdmaReadKb() { return rdmaReadKb; }
  inline UInt64 getRdmaWriteKb() { return rdmaWriteKb; }
  inline UInt32 getDevice() { return device; }
  inline UInt32 getportNum() { return port; }

};
/******************************/

/******************************/

/* Define a version number for verbsClientStatsInfo to allow
   future changes in this structure.
 */
#define GPFS_VERBSCLIENTSTATS_VERSION 1

class VerbsClientStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */

  char   destination[NAME_STRING_LEN];
  char   state[NAME_STRING_LEN];
  UInt64 curReadWrite;
  UInt64 peakReadWrite;
  UInt64 fileRead;
  UInt64 fileWrite;
  UInt64 fileReadKb;
  UInt64 fileWriteKb;
  UInt32 device;
  UInt32 port;

public:
  VerbsClientStatsInfo(MErrno *errP);
  ~VerbsClientStatsInfo();

  VerbsClientStatsInfo& operator=(VerbsClientStatsInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }

  inline char  *getDestination() { return destination; }
  inline char  *getState() { return state; }

  inline UInt64 getCurReadWrite() { return curReadWrite; }
  inline UInt64 getPeakReadWrite() { return peakReadWrite; }
  inline UInt64 getFileRead() { return fileRead; }
  inline UInt64 getFileWrite() { return fileWrite; }
  inline UInt64 getFileReadKb() { return fileReadKb; }
  inline UInt64 getFileWriteKb() { return fileWriteKb; }
  inline UInt32 getDevice() { return device; }
  inline UInt32 getportNum() { return port; }

};

/****************************/

/* Define a version number for tscommCfgInfo to allow
   future changes in this structure.
 */
#define GPFS_TSCOMMCFG_VERSION 1

class TscommCfgInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */

  UInt32 portNum;
  UInt32 nodeNum;
  char   nodeAddr[NAME_STRING_LEN];
  char   addrList[ADDRLIST_NODES * NAME_STRING_LEN];
  UInt32 curDaemonVer;
  UInt32 comptDmnVer;
  UInt32 maxComptVer;
  UInt32 maxFeatureLevel;

public:
  TscommCfgInfo(MErrno *errP);
  ~TscommCfgInfo();

  TscommCfgInfo& operator=(TscommCfgInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }

  inline char  *getNodeAddr() { return nodeAddr; }
  inline char  *getAddrList() { return addrList; }

  inline UInt32 getportNum() { return portNum; }
  inline UInt32 getnodeNum() { return nodeNum; }
  inline UInt32 getcurDaemonVer() { return curDaemonVer; }
  inline UInt32 getcomptDmnVer() { return comptDmnVer; }
  inline UInt32 getmaxComptVer() { return maxComptVer; }
  inline UInt32 getmaxFeatureLevel() { return maxFeatureLevel; }

};

/* Define a version number for ClusterCfgInfo to allow
   future changes in this structure.
 */
#define GPFS_CLUSTERCFG_VERSION 1

class ClusterCfgInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */

  char	 clusterId[NAME_STRING_LEN];
  UInt32 nodeNumber;
  char   nodeAddr[NAME_STRING_LEN];
  char   hostName[NAME_STRING_LEN];
  char   ipAddr[NAME_STRING_LEN];
  char   admin[NAME_STRING_LEN];
  char   gpnTrans[NAME_STRING_LEN];
  char   gpnStatus[NAME_STRING_LEN];
  char   nodeStatus[NAME_STRING_LEN];
  UInt32 joinSeq;
  UInt32 failCnt;
  UInt32 fsManaged;
  UInt32 cnfsGrp;
  UInt32 readChkSum;
  UInt32 writeChkSum;
  char   lastFail[NAME_STRING_LEN];

public:
  ClusterCfgInfo(MErrno *errP);
  ~ClusterCfgInfo();

  ClusterCfgInfo& operator=(ClusterCfgInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }

  inline char  *getclusterId() { return clusterId; }
  inline UInt32 getnodeNumber() { return nodeNumber; }
  inline char  *getNodeAddr() { return nodeAddr; }
  inline char  *getHostName() { return hostName; }
  inline char  *getIpAddr() { return ipAddr; }
  inline char  *getAdmin() { return admin; }
  inline char  *getGpnTrans() { return gpnTrans; }
  inline char  *getGpnStatus() { return gpnStatus; }
  inline char  *getNodeStatus() { return nodeStatus; }

  inline UInt32 getjoinSeq() { return joinSeq; }
  inline UInt32 getfailCnt() { return failCnt; }
  inline UInt32 getfsManaged() { return fsManaged; }
  inline UInt32 getcnfsGrp() { return cnfsGrp; }
  inline UInt32 getreadChkSum() { return readChkSum; }
  inline UInt32 getwriteChkSum() { return writeChkSum; }
  inline char  *getLastFail() { return lastFail; }

};

/* Define a version number for PCacheStatsInfo to allow
   future changes in this structure.
 */
#define GPFS_PNCS_VERSION 1

class PCacheStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  char   fsName[NAME_STRING_LEN];
  char   fsetName[NAME_STRING_LEN];

  UInt64 bytesRead;
  UInt64 bytesWritten;
  UInt32 numExpire;   /* msgs exec due to timer */
  UInt32 numForce;    /* msgs exec due to Q limit, etc */
  UInt32 numSync;     /* msgs exec due to sync cmd */
  UInt32 numRevoke;   /* msgs exec due to revoke */
  UInt32 shortest_waitTime;  /* in seconds */
  UInt32 longest_waitTime;   /* in seconds */
  UInt32 average_waitTime;   /* in seconds */
  UInt32 numPcacheCmds;
  pCacheCmdInfo_t pCacheCmds[MAX_PCACHE_CMD_INFO];
  UInt64 numMsgExecuted;
  UInt32 numHomeConn;
  UInt32 numHomeDisc;
  UInt32 numFsetExp;

public:
  PCacheStatsInfo(MErrno *errP);
  ~PCacheStatsInfo();

  PCacheStatsInfo& operator=(PCacheStatsInfo &c);

  void clearStats();

  pCacheCmdInfo_t *getPCacheCmdInfoP(int cmd);

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
  inline char  *getFsName() { return fsName; }
  inline char  *getFsetName() { return fsetName; }

  inline UInt64 getBytesRead() { return bytesRead; }
  inline UInt64 getBytesWritten() { return bytesWritten; }
  inline UInt32 getNumExpire() { return numExpire; }
  inline UInt32 getNumForce() { return numForce; }
  inline UInt32 getNumSync() { return numSync; }
  inline UInt32 getNumRevoke() { return numRevoke; }
  inline UInt32 getShortest_waitTime() { return shortest_waitTime; }
  inline UInt32 getLongest_waitTime() { return longest_waitTime; }
  inline UInt32 getAverage_waitTime() { return average_waitTime; }
  inline UInt32 getNumPacheCmds() { return numPcacheCmds; }
  inline UInt64 getNumMsgExecuted() { return numMsgExecuted; }
  inline UInt32 getNumHomeConn() { return numHomeConn; }
  inline UInt32 getNumHomeDisc() { return numHomeDisc; }
  inline UInt32 getNumFsetExp() { return numFsetExp; }

};

/*
  NSD server statistics

  mmpmon nsd_dst
  _response_ begin mmpmon nsd_dst
  _mmpmon::nsd_dst_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1336694189 _tu_ 901270 _dev_ /dev/rhdisk6 _d_ gpfs6nsd
  _r_ _ops_ 127 _b_ 6645760 _tw_ 0.091637
  _w_ _ops_ 29 _b_ 98304 _tw_ 0.170669
  _mmpmon::nsd_dst_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1336694189 _tu_ 901291 _dev_ /dev/rhdisk7 _d_ gpfs7nsd
  _r_ _ops_ 51 _b_ 116224 _tw_ 0.014138
  _w_ _ops_ 22 _b_ 33792 _tw_ 0.008239
  _response_ end

   non-server:

  _response_ begin mmpmon nsd_dst
  _mmpmon::nsd_dst_ _n_ 192.168.1.10 _nn_ enterprise _rc_ 1 _t_ 1336693954 _tu_ 173891 _dev_ -
  _response_ end

 */
#define GPFS_NSD_DST_VERSION 1

class NsdServerStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  char   devName[NAME_STRING_LEN]; /* device name of the disk */
  char   nsdName[NAME_STRING_LEN]; /* NSD name */

  UInt32 readOps;      /* number of disk read operations */
  UInt32 writeOps;     /* number of disk write operations */

  UInt64 bytesRead;    /* number of bytes read from disk */
  UInt64 bytesWritten; /* number of bytes written to disk */

  double readTime;  /* total time waiting for disk operations, in seconds */
  double writeTime; /* total time waiting for disk operations, in seconds */

public:
  NsdServerStatsInfo(MErrno *errP);
  ~NsdServerStatsInfo();

  NsdServerStatsInfo& operator=(NsdServerStatsInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
  inline char  *getDevName() { return devName; }
  inline char  *getNsdName() { return nsdName; }

  inline double getReadTime() { return readTime; }
  inline double getWriteTime() { return writeTime; }
  inline UInt64 getBytesRead() { return bytesRead; }
  inline UInt64 getBytesWritten() { return bytesWritten; }
  inline UInt32 getReadOps() { return readOps; }
  inline UInt32 getWriteOps() { return writeOps; }
};

/*
  File system IO stats: list one set of application view stats
  for each file system on the node.

  mmpmon fis
  _response_ begin mmpmon fis
  _mmpmon::fis_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1337051301 _tu_ 718946 _cl_ voyager.gpfs.net _fs_ fs1 _d_ 6 _br_ 33622 _bw_ 0 _oc_ 6 _cc_ 6 _rdc_ 17 _wc_ 0 _dir_ 2 _iu_ 17
  _mmpmon::fis_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1337051301 _tu_ 718946 _cl_ voyager.gpfs.net _fs_ fs3 _d_ 2 _br_ 130881 _bw_ 0 _oc_ 11 _cc_ 11 _rdc_ 47 _wc_ 0 _dir_ 2 _iu_ 7
  _response_ end

  When no file systems are mounted:

  mmpmon fis
  _response_ begin mmpmon fis
  _mmpmon::fis_ _n_ 192.168.1.8 _nn_ voyager _rc_ 1 _t_ 1337052131 _tu_ 269656 _cl_ - _fs_ -
  _response_ end

 */
#define GPFS_FIOS_VERSION 1

class FsIoStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  UInt32 diskCount; /* number of disks in the file system */
  char   ipAddr[NAME_STRING_LEN];

  char   fsName[NAME_STRING_LEN]; /* file system */

  UInt64 bytesRead;   /* number of bytes read from disk (disk and cache) */
  UInt64 bytesWritten;/* number of bytes written, to both disk and cache */

  UInt32 openCalls;   /* number of open() call requests serviced by GPFS */
  UInt32 closeCalls;  /* number of close() call requests serviced by GPFS */
  UInt32 readCalls;   /* number of application read requests serviced by GPFS */
  UInt32 writeCalls;  /* number of write requests serviced by GPFS */
  UInt32 readdirCalls;/* number of readdir() call requests serviced by GPFS */

  UInt64 inodeUpdateCalls; /* number of inode updates to disk */

public:
  FsIoStatsInfo(MErrno *errP);
  ~FsIoStatsInfo();

  FsIoStatsInfo& operator=(FsIoStatsInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
  inline char  *getFsName() { return fsName; }

  inline UInt32 getDiskCount() { return diskCount; }
  inline UInt64 getBytesRead() { return bytesRead; }
  inline UInt64 getBytesWritten() { return bytesWritten; }

  inline UInt32 getOpenCalls() { return openCalls; }
  inline UInt32 getCloseCalls() { return closeCalls; }
  inline UInt32 getReadCalls() { return readCalls; }
  inline UInt32 getWriteCalls() { return writeCalls; }
  inline UInt32 getReaddirCalls() { return readdirCalls; }
  inline UInt64 getInodeUpdateCalls() { return inodeUpdateCalls; }
};

/*
   Storage pool IO stats: lists one set of application-view stats for
   each storage pool on the node.

   mmpmon plios
   _response_ begin mmpmon plios
   _mmpmon::plios_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1337053867 _tu_ 242440 _cl_ voyager.gpfs.net _fs_ fs1 _pl_ system _d_ 2 _br_ 595314176 _bw_ 1624064
   _mmpmon::plios_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1337053867 _tu_ 242440 _cl_ voyager.gpfs.net _fs_ fs1 _pl_ poolA _d_ 3 _br_ 35840 _bw_ 0
   _mmpmon::plios_ _n_ 192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1337053867 _tu_ 242440 _cl_ voyager.gpfs.net _fs_ fs3 _pl_ system _d_ 2 _br_ 56961024 _bw_ 18432
   _response_ end


   When no file systems are mounted:

   mmpmon plios
   _response_ begin mmpmon plios
   _mmpmon::plios_ _n_ 192.168.1.8 _nn_ voyager _rc_ 1 _t_ 1337053946 _tu_ 596610 _cl_ - _fs_ -
   _response_ end

 */
#define GPFS_PLIOS_VERSION 1

class PoolIoStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  char   fsName[NAME_STRING_LEN]; /* file system */
  char   poolName[NAME_STRING_LEN]; /* pool name */

  UInt32 diskCount; /* number of disks in the file system */

  UInt64 bytesRead;    /* number of bytes read */
  UInt64 bytesWritten; /* number of bytes written */

public:
  PoolIoStatsInfo(MErrno *errP);
  ~PoolIoStatsInfo();

  PoolIoStatsInfo& operator=(PoolIoStatsInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getIpAddr() { return ipAddr; }
  inline char  *getFsName() { return fsName; }
  inline char  *getPoolName() { return poolName; }

  inline UInt32 getDiskCount() { return diskCount; }

  inline UInt64 getBytesRead() { return bytesRead; }
  inline UInt64 getBytesWritten() { return bytesWritten; }
};


/*
   Disk Stats
   I/O statistics taken over all mounted file systems as seen by the
   node and presented as total values for ecah disk in each file system.

   mmpmon ds
   _response_ begin mmpmon ds
   _mmpmon::ds_ _n_ 192.168.1.8  _nn_ voyager _rc_ 0 _t_ 1339704723 _tu_ 718796 _cl_ voyager.gpfs.net _fs_ fs3 _d_ gpfs8nsd
   _r_ _ops_ 13 _b_ 46080 _tw_ 0.002274 _qt_ 0.002274 _stw_ 0.000133 _sqt_ 0.000133 _ltw_ 0.000279 _lqt_ 0.000279
   _w_ _ops_ 2 _b_ 1024 _tw_ 0.000715 _qt_ 0.000715 _stw_ 0.000349 _sqt_ 0.000349 _ltw_ 0.000366 _lqt_ 0.000366
   _mmpmon::ds_ _n_  192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1339704723 _tu_ 718824 _cl_ voyager.gpfs.net _fs_ fs3 _d_ gpfs10nsd
   _r_ _ops_ 5 _b_ 2560 _tw_ 0.000809 _qt_ 0.000809 _stw_ 0.000151 _sqt_ 0.000151 _ltw_ 0.000174 _lqt_ 0.000174
   _w_ _ops_ 2 _b_ 1024 _tw_ 0.000736 _qt_ 0.000736 _stw_ 0.000361 _sqt_ 0.000361 _ltw_ 0.000375 _lqt_ 0.000375
   _mmpmon::ds_ _n_  192.168.1.8 _nn_ voyager _rc_ 0 _t_ 1339704723 _tu_ 718855 _cl_ voyager.gpfs.net _fs_ fs6 _d_ gpfs18nsd
   _r_ _ops_ 3 _b_ 17408 _tw_ 0.000645 _qt_ 0.000645 _stw_ 0.000145 _sqt_ 0.000145 _ltw_ 0.000260 _lqt_ 0.000260
   _w_ _ops_ 0 _b_ 0 _tw_ 0.000000 _qt_ 0.000000 _stw_ 0.000000 _sqt_ 0.000000 _ltw_ 0.000000 _lqt_ 0.000000
   _response_ end

   When no file systems are mounted:

   mmpmon ds
   _response_ begin mmpmon ds
   _mmpmon::ds_ _n_  192.168.1.8 _nn_ voyager _rc_ 1 _t_ 1339704802 _tu_ 927135 _cl_ - _fs_ -
   _response_ end

 */
#define GPFS_DS_VERSION 1

class DiskStatsInfo
{
  friend class PollingHandler;

  Int32  version;   /* version of this stat structure */
  Int32  length;    /* size of this structure */
  Int32  rc;        /* return code from mmpmon */
  char   ipAddr[NAME_STRING_LEN];

  char   fsName[NAME_STRING_LEN];   /* file system */
  char   diskName[NAME_STRING_LEN]; /* disk name */
  char   clusterName[NAME_STRING_LEN]; /* clusterName */

  UInt32 readOps;      /* number of disk read operations */
  UInt32 writeOps;     /* number of disk write operations */

  UInt64 bytesRead;    /* number of bytes read from disk */
  UInt64 bytesWritten; /* number of bytes written to disk */

  /* Times are in seconds. */
  double readTime;  /* total time waiting for disk operations, in seconds */
  double writeTime; /* total time waiting for disk operations, in seconds */

  double queueReadTime; /* total time spent between being queued for a disk
                           operation and the completion of that operation */
  double queueWriteTime; /* total time spent between being queued for a disk
                           operation and the completion of that operation */

  double shortestReadTime; /* shortest time spent waiting for a disk oper */
  double shortestWriteTime;

  double shortestQueueReadTime; /* shortest time between being queued for a disk
                                  operation and the completion of that oper. */
  double shortestQueueWriteTime;

  double longestReadTime;  /* longest spent waiting for a disk oper */
  double longestWriteTime;

  double longestQueueReadTime; /* longest time between being queued for a disk
                                  operation and the completion of that oper. */
  double longestQueueWriteTime;

public:
  DiskStatsInfo(MErrno *errP);
  ~DiskStatsInfo();

  DiskStatsInfo& operator=(DiskStatsInfo &c);

  void clearStats();

  inline Int32  getVersion() { return version; }
  inline Int32  getLength() { return length; }
  inline Int32  getRc() { return rc; }
  inline char  *getFsName() { return fsName; }
  inline char  *getDiskName() { return diskName; }
  inline char  *getIpAddr() { return ipAddr; }
  inline char  *getClusterName() { return clusterName; }

  inline UInt32 getReadOps() { return readOps; }
  inline UInt32 getWriteOps() { return writeOps; }
  inline UInt64 getBytesRead() { return bytesRead; }
  inline UInt64 getBytesWritten() { return bytesWritten; }

  inline double getReadTime() { return readTime; }
  inline double getWriteTime() { return writeTime; }
  inline double getQueueReadTime() { return  queueReadTime; }
  inline double getQueueWriteTime() { return  queueWriteTime; }
  inline double getShortestReadTime() { return  shortestReadTime; }
  inline double getShortestWriteTime() { return  shortestWriteTime; }
  inline double getShortestQueueReadTime() { return  shortestQueueReadTime; }
  inline double getShortestQueueWriteTime() { return  shortestQueueWriteTime; }
  inline double getLongestReadTime() { return  longestReadTime; }
  inline double getLongestWriteTime() { return  longestWriteTime; }
  inline double getLongestQueueReadTime() { return  longestQueueReadTime; }
  inline double getLongestQueueWriteTime() { return  longestQueueWriteTime; }
};


/* Node information */
class NodeInfo
{
  friend class PollingHandler;

  char name[NAME_STRING_LEN];
  char ipAddr[NAME_STRING_LEN];
  char platform[NAME_STRING_LEN];
  char endian[NAME_STRING_LEN];
  char type[NAME_STRING_LEN];
  char osname[NAME_STRING_LEN];
  char admin[NAME_STRING_LEN];
  char status[NAME_STRING_LEN];
  char version[NAME_STRING_LEN];
  UInt32 failureCount;
  UInt32 threadWait;
  char healthy[NAME_STRING_LEN];
  char diagnosis[NAME_STRING_LEN];
  UInt64 pagePoolSize;
  UInt32 prefetchThreads;
  UInt32 maxMBPS;
  UInt32 maxFilesToCache;
  UInt32 maxStatCache;
  UInt32 worker1Threads;
  UInt32 dmapiEventTimeout;
  UInt32 dmapiMountTimeout;
  UInt32 dmapiSessFailureTimeout;
  UInt32 nsdServerWaitTimeWindowOnMount;
  UInt32 nsdServerWaitTimeForMount;
  char unmountOnDiskFail[32];

  double readTime;
  double writeTime;

  Boolean_t found;

  std::vector<DiskAccessInfo *>diskAccessItems;

  void copyDiskAccesses(NodeInfo *nodeP);
  int getDiskAccessIndex(char *nameP);

  /* I/O statistics counted by context */
  IocStatsInfo *iocStatsP;

  /* vfs statistics */
  VfsStatsInfo *vfsStatsP;

  /* thread pool utilization */
  ThreadUtilInfo *threadUtilP;

  /* rpc performance stat */
  RPCUtilInfo *rpcUtilP;

  /* rpc raw stats */
  RPCRawUtilInfo *rpcRawUtilP;

  /* rpc performance stats according to size */
  RPCSizeUtilInfo *rpcSizeUtilP;

  /* rpc performance stats according to size */
  RPCMsgUtilInfo *rpcMsgUtilP;

  /* aggregation of rpc performance stats per sec on local node */
  AggregatedRPCUtilInfoPerSec *rpcUtilPerSecP;

  /* cache hit/miss stats */
  CacheStatsInfo *cacheStatsP;

  std::vector<PCacheStatsInfo *>PCacheStatsItems;

  TscommCfgInfo *tscommCfgP;

  VerbsClientStatsInfo *verbsClientP;
  VerbsServerStatsInfo *verbsServerP;

public:
  NodeInfo(MErrno *errP);

  ~NodeInfo();

  NodeInfo& operator=(NodeInfo &n);
  void clearStats();

  /* Node info from SDR */
  inline char *getName() { return name; }
  inline char *getIpAddr() { return ipAddr; }
  inline char *getType() { return type; }
  inline char *getEndian() { return endian; }
  inline char *getOsName() { return osname; };
  inline char *getVersion() { return version; }
  inline char *getPlatform() { return platform; }

  /* Node info from EE get nodes */
  inline char *getAdmin() { return admin; }
  inline char *getStatus() { return status; }
  inline UInt32 getFailureCount() { return failureCount; }
  inline UInt32 getThreadWait() { return threadWait; }
  inline char *getHealthy() { return healthy; }
  inline char *getDiagnosis() { return diagnosis; }

  inline UInt64 getPagePoolSize() { return pagePoolSize; }
  inline UInt32 getPrefetchThreads() { return prefetchThreads; }
  inline UInt32 getMaxMBPS() { return maxMBPS; }
  inline UInt32 getMaxFilesToCache() { return maxFilesToCache; }
  inline UInt32 getMaxStatCache() { return maxStatCache; }
  inline UInt32 getWorker1Threads() { return worker1Threads; }
  inline UInt32 getDmapiEventTimeout() { return dmapiEventTimeout; }
  inline UInt32 getDmapiMountTimeout() { return dmapiMountTimeout; }
  inline UInt32 getDmapiSessFailureTimeout() { return dmapiSessFailureTimeout; }
  inline UInt32 getNsdServerWaitTimeWindowOnMount() { return nsdServerWaitTimeWindowOnMount; }
  inline UInt32 getNsdServerWaitTimeForMount() { return nsdServerWaitTimeForMount; }
  inline char *getUnmountOnDiskFail() { return unmountOnDiskFail; }

  inline UInt32 getNumDiskAccesses() { return diskAccessItems.size(); }
  inline DiskAccessInfo *getDiskAccess(int d) { return diskAccessItems.at(d); }

  inline VfsStatsInfo *getVfsStatsInfo() { return vfsStatsP; }
  inline IocStatsInfo *getIocStatsInfo() { return iocStatsP; }
  inline ThreadUtilInfo *getThreadUtilInfo() { return threadUtilP; }
  inline RPCUtilInfo *getRPCUtilInfo() { return rpcUtilP; }
  inline RPCRawUtilInfo *getRPCRawUtilInfo() { return rpcRawUtilP; }
  inline RPCSizeUtilInfo *getRPCSizeUtilInfo() { return rpcSizeUtilP; }
  inline RPCMsgUtilInfo *getRPCMsgUtilInfo() { return rpcMsgUtilP; }
  inline AggregatedRPCUtilInfoPerSec *getAggregatedRPCUtilInfoPerSec() { return rpcUtilPerSecP; }
  inline CacheStatsInfo *getCacheStatsInfo() { return cacheStatsP; }

  inline UInt32 getNumPcacheFsets() { return PCacheStatsItems.size(); }
  inline PCacheStatsInfo *getPcacheFset(int d) { return PCacheStatsItems.at(d); }

  inline TscommCfgInfo  *getTscommCfgInfoP() { return tscommCfgP;}
  inline VerbsClientStatsInfo *getVerbsClientStatsInfoP() { return verbsClientP;}
  inline VerbsServerStatsInfo *getVerbsServerStatsInfoP() { return verbsServerP;}

  /* Currently unused */
  inline double getReadTime() { return readTime; }
  inline double getWriteTime() { return writeTime; }
};

/* Cluster information */
class ClusterInfo
{
  friend class PollingHandler;

  /* parsable from mmsdrfs */
  char name[NAME_STRING_LEN];
  char id[NAME_STRING_LEN];
  char type[NAME_STRING_LEN];
  char minReleaseLevel[NAME_STRING_LEN];
  char uidDomain[NAME_STRING_LEN];
  char remoteShellCommand[NAME_STRING_LEN];
  char remoteFileCopyCommand[NAME_STRING_LEN];
  char primaryServer[NAME_STRING_LEN];
  char secondaryServer[NAME_STRING_LEN];

  UInt32 maxBlockSize;
  UInt32 distributedTokenServer;
  /*UInt32 useDiskLease;*/
  UInt32 failureDetectionTime;
  UInt32 tcpPort;
  UInt32 minMissedPingTimeout;
  UInt32 maxMissedPingTimeout;

  UInt32 sdrfsGenNumber;

  struct timeval clusterRefreshTime;

  /* Store the list of node name - primary key */
  std::vector<NodeInfo *>nodeItems;
  struct timeval nodeRefreshTime;

  /* Store the list of file system name - primary key */
  std::vector<FilesystemInfo *>fsItems;
  struct timeval FSRefreshTime;
  struct timeval FSPerfRefreshTime;

  std::vector<DiskInfo *>freeDiskItems;

  /* Store the list of ClusterCfgItems */
  std::list<ClusterCfgInfo *>ClusterCfgItems;

  void copyNodes(ClusterInfo *clP);
  void copyFS(ClusterInfo *clP);
  void copyFreeDisks(ClusterInfo *clP);
  int getNodeInfoIndex(char *ipAddrP);
  int getNodeInfoIndexByName(char *nameP);
  int getFilesystemInfoIndex(char *nameP);
  int getFreeDiskInfoIndex(char *nameP);

  struct timeval diskSDRRefreshTime;

public:
  ClusterInfo(MErrno *errP);

  ~ClusterInfo();

  ClusterInfo& operator=(ClusterInfo &cl);

  /* member accessors */
  inline char *getName() { return name; }
  inline char *getId() { return id; }
  inline char *getType() { return type; }
  inline char *getMinReleaseLevel() { return minReleaseLevel; }
  inline char *getUidDomain() { return uidDomain; }
  inline char *getRemoteShellCommand() { return remoteShellCommand; }
  inline char *getRemoteFileCopyCommand() { return remoteFileCopyCommand; }
  inline char *getPrimaryServer() { return primaryServer; }
  inline char *getSecondaryServer() { return secondaryServer; }
  inline UInt32 getMaxBlockSize() { return maxBlockSize; }
  inline struct timeval getClusterRefreshTime() { return clusterRefreshTime; }
  inline UInt32 getSdrfsGenNumber() { return sdrfsGenNumber; }

  inline UInt32 getNumNodes() { return nodeItems.size(); }
  inline NodeInfo *getNode(int n) { return nodeItems.at(n); }
  inline struct timeval getNodeRefreshTime() { return nodeRefreshTime; }
  inline UInt32 getNumFilesystems() { return fsItems.size(); }
  inline FilesystemInfo *getFilesystem(int f) { return fsItems.at(f); }
  inline struct timeval getFSRefreshTime() { return FSRefreshTime; }
  inline struct timeval getFSPerfRefreshTime() { return FSPerfRefreshTime; }
  inline UInt32 getDistributedTokenServer() { return distributedTokenServer; }
  inline UInt32 getFailureDetectionTime() { return failureDetectionTime; }
  inline UInt32 getTCPPort() { return tcpPort; }
  inline UInt32 getMinMissedPingTimeout() { return minMissedPingTimeout; }
  inline UInt32 getMaxMissedPingTimeout() { return maxMissedPingTimeout; }
  inline UInt32 getNumFreeDisks() { return freeDiskItems.size(); }
  inline DiskInfo *getFreeDisk(int d) { return freeDiskItems.at(d); }

  inline UInt32 getNumClusterCfgNodes() { return ClusterCfgItems.size(); }
  inline ClusterCfgInfo *getClusterCfgInfoP(int d)
  {
    int cnt = 0;
    std::list<ClusterCfgInfo*>::const_iterator iterator;
    for (iterator = ClusterCfgItems.begin(); iterator != ClusterCfgItems.end();
         ++iterator, cnt++) {
      if (cnt == d)
        return *iterator;
    }
    return (ClusterCfgInfo *) NULL;
  }
};

/* Cluster status information */
class ClusterStatus
{
  friend class PollingHandler;

public:
  char managerNode[NAME_STRING_LEN];
  char managerIpAddr[NAME_STRING_LEN];
  UInt32 nLocalNodes;      /* number of nodes defined in the cluster */
  UInt32 nLocalJoined;     /* number of local nodes active in the cluster */
  UInt32 nRmtJoined;       /* number of remote nodes joined in this cluster */
  UInt32 nQNodesInCluster; /* number of quorum nodes defined in the cluster */
  UInt32 nQNodesJoined;    /* number of quorum nodes active in the cluster */
  UInt32 cfgMinQuorumNodes;/*  minimum no of nodes to reach quorum */
  UInt32 quorumAchieved ;  /* Quorum achieved (=1), not achieved (=0)*/

public:
  ClusterStatus();
  ~ClusterStatus();

  void init();

  /* member accessors */
  inline char *getManagerNode() { return managerNode; }
  inline char *getManagerIpAddr() { return managerIpAddr; }
  inline UInt32 getNLocalNodes() { return nLocalNodes; }
  inline UInt32 getNLocalJoined() { return nLocalJoined; }
  inline UInt32 getNRmtJoined() { return nRmtJoined; }
  inline UInt32 getNQNodesInCluster() { return nQNodesInCluster; }
  inline UInt32 getNQNodesJoined() { return nQNodesJoined; }
  inline UInt32 getCfgMinQuorumNodes() { return cfgMinQuorumNodes; }
  inline UInt32 getQuorumAchieved() { return quorumAchieved; }
};

/* MODS_START */
class FileSet
{

  friend class PollingHandler;

public:

  UInt32 gpfsFilesetVersion;
  char gpfsFilesetName[NAME_STRING_LEN];
  char gpfsFileSystemName[NAME_STRING_LEN];
  char gpfsFilesetID[NAME_STRING_LEN];
  char gpfsFilesetRootINode[NAME_STRING_LEN];
  char gpfsFilesetStatus[NAME_STRING_LEN];
  char gpfsFilesetPath[PATH_STRING_LEN];
  char gpfsFilesetParentID[NAME_STRING_LEN];
  UInt64 gpfsFilesetINodes;
  char gpfsFilesetCreated[TIME_STAMP_CHARS];
  UInt64 gpfsFilesetDataInKB;
  char gpfsFilesetComment[NAME_STRING_LEN];
  bool gpfsFilesetIsLinked;
  bool gpfsFilesetHasComment;

  // methods
  inline char* getName() { return gpfsFilesetName; }
  inline char* getId() { return gpfsFilesetID; }
  inline char* getRootINode() { return gpfsFilesetRootINode; }
  inline char* getParentId() { return gpfsFilesetParentID; }
  inline UInt64 getINodes() { return gpfsFilesetINodes; }
  inline UInt64 getData() { return gpfsFilesetDataInKB; }
  inline char* getComment() { return gpfsFilesetComment; }
  inline char* getFSName() { return gpfsFileSystemName; }
  inline char* getStatus() { return gpfsFilesetStatus; }
  inline char* getPath() { return gpfsFilesetPath; }
  inline char* getCreated() { return gpfsFilesetCreated; }
  inline UInt32 getVersion() { return gpfsFilesetVersion; }

private:
};

class User
{
  friend class PollingHandler;
public:

  User()
  {
    hasName = false;
  }

  char gpfsUserName[NAME_STRING_LEN];
  char gpfsUserFileSystemName[NAME_STRING_LEN];
  char gpfsUserClusterName[NAME_STRING_LEN];
  char gpfsUserHomePath[NAME_STRING_LEN];
  UInt32 gpfsUserId;
  UInt32 gpfsMainGroupId;

  // temporary flag to show that this user has a name
  bool hasName;

  inline char* getName() { return gpfsUserName; }
  inline char* getFSName() { return gpfsUserFileSystemName; }
  inline char* getCSName() { return gpfsUserClusterName; }
  inline char* getHomePath() { return gpfsUserHomePath; }
  inline UInt32 getUserId() { return  gpfsUserId; }
  inline UInt32 getMainGroupId() { return  gpfsMainGroupId; }

private:
};

class Group
{
  friend class PollingHandler;
public:

  Group() { hasName = false; }

  char gpfsGroupName[NAME_STRING_LEN];
  char gpfsGroupFileSystemName[NAME_STRING_LEN];
  char gpfsGroupClusterName[NAME_STRING_LEN];
  UInt32 gpfsGroupId;

  // temporary flag to show that this group has a name
  bool hasName;

  inline char* getName() { return gpfsGroupName; }
  inline char* getFSName() { return gpfsGroupFileSystemName; }
  inline char* getCSName() { return gpfsGroupClusterName; }
  inline UInt32 getGroupId() { return  gpfsGroupId; }

private:
};

/* DJ_MODS_START */
class FileOrDirOwner
{

    friend class PollingHandler;

public:

  char osOwnerName[NAME_STRING_LEN];
  char osGroupName[NAME_STRING_LEN];
  char osFileOrDirList[NAME_STRING_LEN]; // ',' separated list..same as chown
  Boolean_t dir;
  Boolean_t jnxn;

  inline char* getOwnerName() { return osOwnerName; }
  inline char* getGroupName() { return osGroupName; }
  inline char* getFileOrDirList() { return osFileOrDirList; }
  inline Boolean_t isDirectory() { return dir; }
  inline Boolean_t isJnxn() { return jnxn; }

private:
};
/* DJ_MODS_END*/

class Quota
{

public:

  Quota()
  {
    gpfsQuotaHeader = 0;
    gpfsQuotaVersion = 0;
    gpfsQuotaType = 0;
    gpfsQuotaID = 0;
    gpfsQuotaBlockUsage = 0;
    gpfsQuotaBlockQuota = 0;
    gpfsQuotaBlockLimit = 0;
    gpfsQuotaBlockInDoubt = 0;
    gpfsQuotaFilesUsage = 0;
    gpfsQuotaFilesQuota = 0;
    gpfsQuotaFilesLimit = 0;
    gpfsQuotaFilesInDoubt = 0;
    gpfsQuotaFilesInDoubt = 0;

    gpfsQuotaClusterName.clear();
    gpfsQuotaFileSystemName.clear();
    gpfsQuotaEntityName.clear();
    gpfsQuotaBlockGrace.clear();
    gpfsQuotaFilesGrace.clear();
    gpfsQuotaRemarks.clear();
  }

  std::string gpfsQuotaClusterName;
  UInt32 gpfsQuotaHeader;
  UInt32 gpfsQuotaVersion;
  std::string gpfsQuotaFileSystemName;
  UInt16 gpfsQuotaType;
  UInt32 gpfsQuotaID;
  std::string gpfsQuotaEntityName;
  UInt64 gpfsQuotaBlockUsage;
  UInt64 gpfsQuotaBlockQuota;
  UInt64 gpfsQuotaBlockLimit;
  UInt32 gpfsQuotaBlockInDoubt;
  std::string gpfsQuotaBlockGrace;
  UInt64 gpfsQuotaFilesUsage;
  UInt64 gpfsQuotaFilesQuota;
  UInt64 gpfsQuotaFilesLimit;
  UInt32 gpfsQuotaFilesInDoubt;
  std::string gpfsQuotaFilesGrace;
  std::string gpfsQuotaRemarks;

  inline std::string getClusterName() { return gpfsQuotaClusterName; }
  inline UInt32 getHeader() { return  gpfsQuotaHeader; }
  inline UInt32 getVersion() { return gpfsQuotaVersion; }
  inline std::string getFileSystemName() { return gpfsQuotaFileSystemName; }
  inline UInt16 getType() { return gpfsQuotaType; }
  inline UInt32 getId() { return gpfsQuotaID; }
  inline std::string getEntityName() { return gpfsQuotaEntityName; }
  inline UInt64 getBlockUsage() { return gpfsQuotaBlockUsage; }
  inline UInt64 getBlockQuota() { return gpfsQuotaBlockQuota; }
  inline UInt64 getBlockLimit() { return gpfsQuotaBlockLimit; }
  inline UInt32 getBlockInDoubt() { return gpfsQuotaBlockInDoubt; }
  inline std::string getBlockGrace() { return gpfsQuotaBlockGrace; }
  inline UInt64 getFilesUsage() { return gpfsQuotaFilesUsage; }
  inline UInt64 getFilesQuota() { return gpfsQuotaFilesQuota; }
  inline UInt64 getFilesLimit() { return gpfsQuotaFilesLimit; }
  inline UInt32 getFilesInDoubt() { return gpfsQuotaFilesInDoubt; }
  inline std::string getFilesGrace() { return gpfsQuotaFilesGrace; }
  inline std::string getRemarks() { return gpfsQuotaRemarks; }

private:

};
/* MODS_END */

#define dfprintf if (debug) fprintf

/* forward declaration */
class MmpmonWrapperUtils;
class CommandWrapperUtils;

/* flag: polling scope */
#define POLL_CLUSTER        0x01   /* poll local cluster - default */
#define POLL_ALL_CLUSTERS   0x02   /* poll local and remote clusters (if any) */
#define POLL_NODE           0x04   /* poll local node only */

/* Provide pull API to external tasks */
class PollingHandler
{
  friend class ClusterInfo;
  friend class NodeInfo;
  friend class FilesystemInfo;
  friend class DiskInfo;

  MmpmonWrapperUtils *wrapper;

  /* Thread for executing predefined command scripts to cache the results.
     Potentially long-time taking command scripts should be added here. */
  pthread_t cmdThread;

  /* Thread for doing things regularly. Currently, it wakes up a command
     thread periodically. */
  pthread_t timerThread;

  /* Thread for doing configurations. */
  pthread_t dispatchThread;

  CommandWrapperUtils *cmdWrapper;

  /* Flag that decides whether a command thread should terminate. */
  int terminate;

  /* Flag that decides whether thimer thread should terminate. */
  int timer_terminate;

  /* Flag that decides whether dispatch thread should terminate. */
  int execTerminate;

  ClusterInfo *recipe;

  /* Main routine for command thread. */
  static void *cmdHandlerBody(void *argP);

  /* Main routine for timer thread. */
  static void *timerHandlerBody(void *argP);

  /* Main routine for dispatch thread. */
  static void *dispatchHandlerBody(void *argP);

  MErrno initNodeList();

  void   initClusterRecipe(ClusterInfo *infoP);
  MErrno checkFailedNode();
  char *grabValue(char *buf, int index, char *answer);

  pthread_mutex_t mutex;

  /* Execution task list. It is added by external tasks. */
  pthread_mutex_t listMutex;
  std::vector<ExecutionTask *>execTaskItems;

  int debug;
  MgmtProtocol protocol;
  Int32 pid; /* external process id, to identify this connection */

  /* Update rule info in PolicyInfo */
  MErrno fillRuleInfo(FilesystemInfo *fsP, PolicyInfo *policyP);

  int pollingScope;
  int nNodesInList;

public:

  Int32 getPid() { return pid; }

  MErrno cleanupNodeList();
  PollingHandler(MErrno *errP, MgmtProtocol proto, int debg = 0,
                 int scope = POLL_CLUSTER);
  ~PollingHandler();

  static MErrno init(MgmtProtocol proto, int debg = 0,
                     int scope = POLL_CLUSTER);
  static void term();

  MmpmonWrapperUtils *getMmpmonWrapper() { return wrapper; }

  /* Cluster recipe is ClusterInfo object which contains primary keys of
     nodes, file systems and disks. It is parsed from mmsdrfs file. */
  MErrno refreshClusterRecipe(int scope = POLL_CLUSTER);

  MErrno parseClusterFile(ClusterInfo *cl);

  /* Get a copy of the cluster info */
  MErrno getClusterInfo(ClusterInfo *clP);

  /* current status of cluster */
  MErrno getClusterStatus(ClusterStatus *clStatusP,
                          int flag = CLUSTER_STATE_ALL);

  MErrno updateDiskSDRInfo(int norefresh=0);

  /* The following update calls will update both the internal copy of the
     data and the caller's copy, which is pointed to by clP. */

  MErrno updateClusterInfo(ClusterInfo *clP, int norefresh=0);

  /* Update node list which belongs to the specified cluster */
  MErrno updateNodeInfo(ClusterInfo *clP, int norefresh=0);

  /* MODS_START */
  /* Method used to quickly populate mount point for nodes->file systems */
  MErrno updateFilesystemMountPointInfo(ClusterInfo *clP);
  /* MODS_END */

  /* Update filesystem list which belongs to the specified cluster */
  MErrno updateFilesystemInfo(ClusterInfo *clP, int getPerf=0);

  /* Update storage pool list which belongs to the specified filesystem
     (NULL=all filesystems) */
  MErrno updateStoragePoolInfo(ClusterInfo *clP, char *fsName=NULL);

  /* Update disk list which belongs to the specified filesystem/pool
     (NULL=all pools in the filesystem) */
  MErrno updateDiskInfo(ClusterInfo *clP, char *fsName, char *poolName=NULL,
                        int getPerf=0);

  MErrno updateFreeDiskInfo(ClusterInfo *clP);

  /* Update per node ioc statistics */
  MErrno updateIocStatsInfo(ClusterInfo *clP);

  /* Update per node VFS statistics */
  MErrno updateVfsStatsInfo(ClusterInfo *clP);

  /* Update per node thread pool utilization  statistics */
  MErrno updateThreadUtilInfo(ClusterInfo *clP);

  /* Update per node cache hit miss statistics */
  MErrno updateCacheStatsInfo(ClusterInfo *clP);

  /* Update per node pcache gateway statistics */
  MErrno updatePCacheStatsInfo(ClusterInfo *clP);

  MErrno updateClusterCfgInfo(ClusterInfo *clP);

  MErrno updateTscommCfgInfo(ClusterInfo *clP);

  MErrno updateVerbsClientInfo(ClusterInfo *clP);

  MErrno updateVerbsServerInfo(ClusterInfo *clP);

  MErrno updateRPCUtilInfo(ClusterInfo *clP, Int16 tmu=0, Int16 time=0);

  MErrno updateRPCRawUtilInfo(ClusterInfo *clP);

  MErrno updateRPCSizeUtilInfo(ClusterInfo *clP, Int16 tmu=0, Int16 time=0);

  MErrno updateRPCMsgUtilInfo(ClusterInfo *clP, Int16 tmu=0, Int16 time=0);

  MErrno updateRPCUtilInfoPerSec(ClusterInfo *clP);

  MErrno processCommand(const char *cmd);

  MErrno copyRecipe(ClusterInfo *clP);

  /* Update mounted node info in FilesystemInfo */
  MErrno updateMountedNodeInfo(ClusterInfo *clP);

  /* Update policy info in FilesystemInfo */
  MErrno updatePolicyInfo(ClusterInfo *clP);

  /* Update file system manager node info in FilesystemInfo */
  MErrno updateFilesystemManagerInfo(ClusterInfo *clP);

  /* Update file system configuration info in FilesystemInfo */
  MErrno updateFilesystemConfigInfo(ClusterInfo *clP);

  /* Update disk access info in NodeInfo */
  MErrno updateDiskAccessInfo(ClusterInfo *clP);

  /* Update NSD server info in DiskInfo */
  MErrno updateDiskServerInfo(DiskInfo *diskP, char *serverListP,
                              char *backupServerListP);

  /* Update indirect disk access info (through NSD servers) in NodeInfo */
  MErrno updateIndirectDiskAccessInfo(ClusterInfo *clP, DiskInfo *diskP);

  /* MODS_START */
  /* Update the file set list */
  MErrno getFileSet(char *fileSystemName, char *fileSetName, FileSet *fileSet);
  MErrno getFileSets(char *fileSystemName, std::vector<FileSet *>*fileSetList);

  MErrno getFileSets1(char *fileSystemNameP,
                     FileSet *fileSetListP,  /* caller allocated/freed */
                     int *nElemP  /* in: size of fileSetListP
                                     out: number of filesets needed */
                     );
  /* type: users=1, group=2, fileset=3 */
  MErrno getQuota(int type, const char *fsName,
                  const char *entityName, Quota *quota );
#ifdef MMANTRAS_QUOTAS
  MErrno getQuotas(int type, const char *fsName,
                   std::vector <Quota *>*quotas );
#endif

  MErrno createFileSet(FileSet fileSet,
                       std::string *gpfsMsg, bool isNull);

  MErrno deleteFileSet(FileSet fileSet,
                       bool force, std::string *gpfsMs);

  MErrno editQuota(char *cFsName, char *cType,
                   char *cEntityId, UInt64 *cNewFileSoftLim,
                   UInt64 *cNewFileHardLim, UInt64 *cNewBlockSoftLim,
                   UInt64 *cNewBlockHardLim,  char *cNaramGracePeriod,
                   std::string *gpfsMsg);

  MErrno editFileset(char *cFsName, char *cType,
                     char *cEntityId, char *cNewName, char *cNewComment,
                     std::string *gpfsMsg);

  /* DJ_MODS_START */
  // Link a fileset
  MErrno linkFileSet(FileSet jnxnFileset, std::string *gpfsMsg);

  // Unlink a fileset
  MErrno unlinkFileSet(const char *fsetNameOrJnxnPath,
                       const char *tgt, bool isFsetName, bool force,
                       std::string *gpfsMsg);

  // Change owner or group of a file
  // NOTE: This is not GPFS fucntionality per se .. it is a convenience for VSC
  MErrno changeOwnerAndOrGroup(FileOrDirOwner newOwnerGrp);

  // Change owner and group of a file/dir to match that of a template
  // source file/dir
  MErrno changeFileOrDirOwnership(FileOrDirOwner src,
                                  FileOrDirOwner tgt, std::string *gpfsMsg);

  // Change ACLs of a file/dir to match that of a template source file/dir
  MErrno changeFileOrDirACL(FileOrDirOwner src,
                            FileOrDirOwner tgt, int aclType,
                            std::string *gpfsMsg);
  /* DJ_MODS_END */

#ifdef MMANTRAS_QUOTAS
  MErrno getUsers(char *fsName, char *fsNameMntPt,
                  char *csName, std::vector<User *> *userList);

  MErrno getGroups(char *fsName, char *fsNameMntPt,
                   char *csName, std::vector<Group *> *groupList);
#endif

  MErrno getHomePath(char *user, char *path);
  MErrno getPrimaryId(char *user, UInt32 *pid);

  /* MODS_END */


  /* Get the SDRFS gen number from the local node */
  UInt32 getSdrfsGenNumber();
  UInt32 getSdrfsGenNumberFromRecipe();
  MErrno updateSdrfsGenNumber(UInt32 sdrGen);

  /* Called by a main thread. Wake up timer thread. */
  void wakeupTimerThread();

  /* Called by a timer thread. Wait a main thread to wake it up. */
  void waitMainThread();

  /* Called by a timer thread. Wake up command thread which
      executes several command scripts. */
  void wakeupCmdThread();

  /* Called by a command thread. When command thread starts,
      it waits timer thread to wake it up. */
  void waitTimerThread();

  /* Called by a command thread. When command thread finishes,
      wake up any waiter thread. */
  void notifyCmdThreadDone();

  /* Called by external tasks. Wait until the command thread finishes
      its work. */
  void waitCmdThreadDone();

  /* Called by a main thread. When an execution task is being added,
      it is called to wake up dispatch thread. */
  void wakeupDispatchThread();

  /* Called by a dispatch thread. Wait any execution task to be
     arrived. */
  void waitExecutionTask();

  /* Add asynchronous execution task. */
  MErrno addExecutionTask(const char *cmd, char *argP, int (*callbackFn)(void *),
                          void *callbackData);

  /* Extract an execution task from list. */
  MErrno getExecTaskFromList(ExecutionTask *taskP);

  /* Initialize buffer. */
  MErrno initBuf(char *buf);

  /* Get GPFS daemon state. */
  MErrno getDaemonState();

  /* MODS_START */
  char *getTimeStampInMilliseconds(char *timeStamp, char *cdateP);

  std::string buffer2string(char * buffer, int itemsToCopy);
  std::vector<std::string> tokenHelper(char *buf, int expectedTokens );

  void getPollingLock();
  void releasePollingLock();
  /* MODS_END */

  int getPollingScope() { return pollingScope; };
  int getNNodesInList() { return nNodesInList; };
  Boolean_t isLocalNodeStats() { return (pollingScope & POLL_NODE) ?
                                                          true:false; };
  /* Per node statistics */
  MErrno iocStatsInfo(int flags, void *bufferP, int bufferSize,
                      int *nElemP, int *errP);
  MErrno vfsStatsInfo(int flags, void *bufferP, int bufferSize,
                      int *nElemP, int *errP);
  MErrno threadUtilInfo(int flags, void *bufferP, int bufferSize,
                        int *nElemP, int *errP);
  MErrno cacheStatsInfo(int flags, void *bufferP, int bufferSize,
                        int *nElemP, int *errP);
  MErrno pCacheStatsInfo(int flags, void *bufferP, int bufferSize,
                         int *nElemP, int *errP);
  MErrno clusterCfgInfo(int flags, void *bufferP, int bufferSize,
                         int *nElemP, int *errP);
  MErrno nsdServerStatsInfo(int flags, void *bufferP, int bufferSize,
                            int *nElemP, int *errP);
  MErrno fsIoStatsInfo(int flags, void *bufferP, int bufferSize,
                       int *nElemP, int *errP);
  MErrno poolIoStatsInfo(int flags, void *bufferP, int bufferSize,
                         int *nElemP, int *errP);
  MErrno diskStatsInfo(int flags, void *bufferP, int bufferSize,
                       int *nElemP, int *errP);
};

extern PollingHandler *thePollingHandler;

void ts_log(int level, const char *component, const char* fmtString, ...);
long file_size(char * fname);
void log_update();

#endif /* _h_api_poll */
