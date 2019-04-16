/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2018          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)06       1.57  src/avs/fs/mmfs/ts/dm/dmapi_types.h, mmfs, avs_rtac502, rtac5021836a 2/17/17 10:31:56 */
/*
 *
 * Define external types for GPFS DMAPI 
 *
 */
#ifndef _DMAPI_TYPES_H
#define _DMAPI_TYPES_H

#include <sys/types.h>

/*
 * Type definitions for GPFS DMAPI external interfaces
 */

/* Basic scalar types */

typedef int                     dm_signed32;
typedef unsigned int            dm_unsigned32;
typedef long long               dm_signed64;
typedef unsigned long long      dm_unsigned64;

struct dm_scalar128
{
  dm_unsigned64  high;
  dm_unsigned64  low;
#ifdef __cplusplus
  bool operator == (const dm_scalar128& rhs) const
    { return high == rhs.high && low == rhs.low; };
  bool operator != (const dm_scalar128& rhs) const
    { return high != rhs.high || low != rhs.low; };
  bool operator < (const dm_scalar128& rhs) const
    { return high < rhs.high || (high == rhs.high && low < rhs.low); };
  bool operator > (const dm_scalar128& rhs) const
    { return high > rhs.high || (high == rhs.high && low > rhs.low); };
  bool operator <= (const dm_scalar128& rhs) const
    { return high < rhs.high || (high == rhs.high && low <= rhs.low); };
  bool operator >= (const dm_scalar128& rhs) const
    { return high > rhs.high || (high == rhs.high && low >= rhs.low); };
#endif  /* __cplusplus */
};
typedef struct dm_scalar128 dm_scalar128;

#define DM_SCALAR128_EQ(x, y) (((x).high==(y).high) && ((x).low==(y).low))
#define DM_SCALAR128_NE(x, y) (((x).high!=(y).high) || ((x).low!=(y).low))
#define DM_SCALAR128_LT(x, y) (((x).high<(y).high) || (((x).high==(y).high) && ((x).low<(y).low)))
#define DM_SCALAR128_GT(x, y) (((x).high>(y).high) || (((x).high==(y).high) && ((x).low>(y).low)))
#define DM_SCALAR128_LE(x, y) (((x).high<(y).high) || (((x).high==(y).high) && ((x).low<=(y).low)))
#define DM_SCALAR128_GE(x, y) (((x).high>(y).high) || (((x).high==(y).high) && ((x).low>=(y).low)))

typedef dm_signed64     dm_off_t;
typedef dm_unsigned64   dm_size_t;
typedef dm_signed64     dm_ssize_t;

#ifdef _AIX
typedef ino_t dm_ino_t;
#else
typedef dm_unsigned64 dm_ino_t; 
#endif

typedef dm_unsigned64 dm_fsid_t;
typedef dm_unsigned32 dm_igen_t;

typedef dm_unsigned64 dm_snap_t;
#define DM_SNAP_ROOT ((dm_snap_t) 0)
#define DM_SNAP_INVALID ((dm_snap_t) -1)

typedef enum
{
  DM_FALSE = 0,
  DM_TRUE = 1
} dm_boolean_t;

/* Iterator for a filesystem scan */
typedef dm_signed64  dm_attrloc_t;

/* Variable-length data */
struct dm_vardata
{
  int              vd_offset;
  unsigned int     vd_length;
};
typedef struct dm_vardata dm_vardata_t;

/* Interpreters for variable length data */

#define DM_GET_LEN(basePtr, vardataFieldName)                   \
         (((basePtr)->vardataFieldName.vd_offset == 0) ?        \
          (size_t)DM_INVALID_HLEN :                             \
          (((basePtr)->vardataFieldName.vd_offset == 1) ?       \
           (size_t)DM_GLOBAL_HLEN :                             \
           ((basePtr)->vardataFieldName.vd_length)              \
        ))

/* The prtType parameter in the DM_GET_VALUE() macro is pointer type
   (for example "int *"). The value of the macro is a pointer of the give type,
   or NULL if the data length (as given by the DM_GET_LEN() macro) is zero. */
#define DM_GET_VALUE(basePtr, vardataFieldName, ptrType)        \
         (((basePtr)->vardataFieldName.vd_offset == 0) ?        \
          (ptrType)DM_INVALID_HANP :                            \
          (((basePtr)->vardataFieldName.vd_offset == 1) ?       \
           (ptrType)DM_GLOBAL_HANP :                            \
            (((basePtr)->vardataFieldName.vd_length == 0) ?     \
             NULL :                                             \
             (ptrType)((char *)(basePtr)+(basePtr)->vardataFieldName.vd_offset)\
        )))

/* Iterator for lists of variable length structures */

/* The ptrType parameter in the DM_STEP_TO_NEXT() macro is a pointer type
   (for example "dm_attrlist_t *"). The value of the macro is a pointer
   of the given type, or NULL if the current element is the last in the list.*/
#define DM_STEP_TO_NEXT(basePtr, ptrType)            \
             (((basePtr)->_link == 0) ? NULL :       \
              (ptrType)((char *)(basePtr) + (basePtr)->_link))

#define DM_ATTR_NAME_SIZE       8

/* Name of an extended attribute */
struct dm_attrname
{
  u_char              an_chars[DM_ATTR_NAME_SIZE];
};
typedef struct dm_attrname dm_attrname_t;

/* Session identifier */
typedef dm_unsigned64  dm_sessid_t;

/* Node identifier */
typedef dm_unsigned32  dm_nodeid_t;  /* GPFS Specific - not in XDSM standard */

/* List of extended attributes */
struct dm_attrlist
{
  dm_ssize_t          _link;
  dm_attrname_t       al_name;
  dm_vardata_t        al_data;
};
typedef struct dm_attrlist      dm_attrlist_t;

/* Attributes of the GPFS DMAPI implementation */
typedef enum
{
  DM_CONFIG_INVALID,                /* Lower than any attribute */
  DM_CONFIG_BULKALL,
  DM_CONFIG_CREATE_BY_HANDLE,
  DM_CONFIG_DTIME_OVERLOAD,
  DM_CONFIG_LEGACY,
  DM_CONFIG_LOCK_UPGRADE,
  DM_CONFIG_MAX_ATTR_ON_DESTROY,
  DM_CONFIG_MAX_ATTRIBUTE_SIZE,
  DM_CONFIG_MAX_HANDLE_SIZE,
  DM_CONFIG_MAX_MANAGED_REGIONS,
  DM_CONFIG_MAX_MESSAGE_DATA,
  DM_CONFIG_OBJ_REF,
  DM_CONFIG_PENDING,
  DM_CONFIG_PERS_ATTRIBUTES,
  DM_CONFIG_PERS_EVENTS,
  DM_CONFIG_PERS_INHERIT_ATTRIBS,
  DM_CONFIG_PERS_MANAGED_REGIONS,
  DM_CONFIG_PUNCH_HOLE,
  DM_CONFIG_TOTAL_ATTRIBUTE_SPACE,
  DM_CONFIG_WILL_RETRY,
  DM_CONFIG_MAX                   /* GPFS specific - higher than any attribute */
} dm_config_t;

#define DM_CONFIG_LOWEST  (DM_CONFIG_INVALID + 1)  /* GPFS specific - lowest attribute  */
#define DM_CONFIG_HIGHEST (DM_CONFIG_MAX -1)       /* GPFS specific - highest attribute */

/* Names of events */
typedef enum
{
  DM_EVENT_INVALID,           /* Lower than any event */
  DM_EVENT_CLOSE,
  DM_EVENT_MOUNT,
  DM_EVENT_PREUNMOUNT,        DM_EVENT_UNMOUNT,
  DM_EVENT_NOSPACE,
  DM_EVENT_DEBUT,
  DM_EVENT_CREATE,            DM_EVENT_POSTCREATE,
  DM_EVENT_REMOVE,            DM_EVENT_POSTREMOVE,
  DM_EVENT_RENAME,            DM_EVENT_POSTRENAME,
  DM_EVENT_SYMLINK,           DM_EVENT_POSTSYMLINK,
  DM_EVENT_LINK,              DM_EVENT_POSTLINK,
  DM_EVENT_READ,
  DM_EVENT_WRITE,
  DM_EVENT_TRUNCATE,
  DM_EVENT_ATTRIBUTE,
  DM_EVENT_CANCEL,
  DM_EVENT_DESTROY,
  DM_EVENT_USER,
  DM_EVENT_PREPERMCHANGE,
  DM_EVENT_POSTPERMCHANGE,
  DM_EVENT_DIRECT_READ,      /* GPFS specific */
  DM_EVENT_MAX               /* Higher than any event */
} dm_eventtype_t;

#define DM_EVENT_BASE_MAX DM_EVENT_PREPERMCHANGE
#define DM_EVENT_MAX_POSSIBLE 32
#define DM_EVENT_EXP_COUNT (DM_EVENT_MAX-DM_EVNT_BASE_MAX)

/* Set of events */
typedef dm_unsigned32   dm_eventset_t;

#define DM_EVENT_LOWEST  (DM_EVENT_INVALID + 1) /* GPFS specific - lowest event */
#define DM_EVENT_HIGHEST (DM_EVENT_MAX - 1)     /* GPFS specific - highest event */

/* Operations on sets of events */

#define DMEV_SET(ev, eset)     (((((int) (ev)) >= DM_EVENT_LOWEST)                      \
                                    && (((int) (ev)) <= DM_EVENT_HIGHEST))               \
                                 ? (eset) |= (((dm_eventset_t) 1) << (((int) (ev)) - 1))  \
                                 : (eset))

#define DMEV_CLR(ev, eset)     (((((int) (ev)) >= DM_EVENT_LOWEST)                      \
                                    && (((int) (ev)) <= DM_EVENT_HIGHEST))               \
                                 ? (eset) &= ~(((dm_eventset_t) 1) << (((int) (ev)) - 1)) \
                                 : (eset))

#define DMEV_ZERO(eset)        ((eset) = (dm_eventset_t) DM_EVENT_INVALID)


#define DMEV_ISSET(ev, eset)   ((((int) (ev)) >= DM_EVENT_LOWEST)                        \
                                && (((int) (ev)) <= DM_EVENT_HIGHEST)                    \
                                && (((dm_eventset_t) (eset)) & (((dm_eventset_t) 1) << (((int) (ev)) - 1))))

/* GPFS Specific event set operations -  not in XDSM standard */

/* Add all events to eset */
#define DMEV_ALL(eset)         ((eset) = ~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))

/* check if eset is empty (contains no events) */
#define DMEV_ISZERO(eset) ((((dm_eventset_t) (eset)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))) == (dm_eventset_t) DM_EVENT_INVALID)

/* check if eset contains all events */
#define DMEV_ISALL(eset) ((((dm_eventset_t) (eset)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))) == ~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))

/* Add to eset2 all events of eset1 */
#define DMEV_ADD(eset1, eset2) ((eset2) = ((((dm_eventset_t) (eset1)) | ((dm_eventset_t) (eset2))) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))))

/* Remove from eset2 all events of eset1 */
#define DMEV_REM(eset1, eset2) ((eset2) = (((dm_eventset_t) (eset2)) & (~((dm_eventset_t) (eset1)))))

/* Restrict eset2 by eset1 (remove from eset2 any event that is not in eset1) */
#define DMEV_RES(eset1, eset2) ((eset2) = ((((dm_eventset_t) (eset1)) & ((dm_eventset_t) (eset2))) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))))

/* Check if eset1 and eset2 are equal (have the same events) */
#define DMEV_ISEQ(eset1, eset2)  ((((dm_eventset_t) (eset1)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))) == (((dm_eventset_t) (eset2)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))))

/* Check if eset1 and eset2 are disjoint (have no events in common) */
#define DMEV_ISDISJ(eset1, eset2)  ((((dm_eventset_t) (eset1)) & ((dm_eventset_t) (eset2)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))) == (dm_eventset_t) DM_EVENT_INVALID)

/* Check if eset1 is a subset of eset2 (all events of eset1 are in eset2) */
#define DMEV_ISSUB(eset1, eset2)  ((((dm_eventset_t) (eset1)) & ((dm_eventset_t) (eset2)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))) == (((dm_eventset_t) (eset1)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))))

/* Normalize the contents of eset (unused bits in the mask are cleared).
   Useful if eset was not obtained entirely by means of DMEV_XXX() macros*/
#define DMEV_NORM(eset)  ((eset) = (((dm_eventset_t)(eset)) & (~((~((dm_eventset_t) DM_EVENT_INVALID)) << DM_EVENT_HIGHEST))))

/* Extent types */
typedef enum
{
  DM_EXTENT_INVALID,
  DM_EXTENT_RES,
  DM_EXTENT_HOLE
} dm_extenttype_t;

struct dm_extent
{
  dm_extenttype_t     ex_type;
  dm_signed32         ex_pad_to_dword;  /* dm_off_t is 64b, need to pad */
  dm_off_t            ex_offset;
  dm_size_t           ex_length;
};
typedef struct dm_extent dm_extent_t;

/* Disposition information */
struct dm_dispinfo
{
  dm_ssize_t          _link;
  dm_vardata_t        di_fshandle;
  dm_eventset_t       di_eventset;
};
typedef struct dm_dispinfo dm_dispinfo_t;

typedef dm_scalar128 dm_token_t;

/* Comparison macros for tokens - GPFS specific - not in XDSM standard */
#define DM_TOKEN_EQ(x, y)  DM_SCALAR128_EQ(x, y)
#define DM_TOKEN_NE(x, y)  DM_SCALAR128_NE(x, y)
#define DM_TOKEN_LT(x, y)  DM_SCALAR128_LT(x, y)
#define DM_TOKEN_GT(x, y)  DM_SCALAR128_GT(x, y)
#define DM_TOKEN_LE(x, y)  DM_SCALAR128_LE(x, y)
#define DM_TOKEN_GE(x, y)  DM_SCALAR128_GE(x, y)

/* Sequence number for event cancellation */
typedef dm_scalar128 dm_sequence_t;

/* Comparison macros for sequence numbers - GPFS specific - not in XDSM standard */
#define DM_SEQUENCE_EQ(x, y)  DM_SCALAR128_EQ(x, y)
#define DM_SEQUENCE_NE(x, y)  DM_SCALAR128_NE(x, y)
#define DM_SEQUENCE_LT(x, y)  DM_SCALAR128_LT(x, y)
#define DM_SEQUENCE_GT(x, y)  DM_SCALAR128_GT(x, y)
#define DM_SEQUENCE_LE(x, y)  DM_SCALAR128_LE(x, y)
#define DM_SEQUENCE_GE(x, y)  DM_SCALAR128_GE(x, y)

/* Event message header */
struct dm_eventmsg
{
  dm_ssize_t          _link;
  dm_eventtype_t      ev_type;
  dm_token_t          ev_token;
  dm_sequence_t       ev_sequence;
  dm_nodeid_t         ev_nodeid;   /* GPFS specific - not in XDSM standard */
  dm_vardata_t        ev_data;
};
typedef struct dm_eventmsg dm_eventmsg_t;


/* Cancel event message */
struct dm_cancel_event
{
  dm_sequence_t       ce_sequence;
  dm_token_t          ce_token;
};
typedef struct dm_cancel_event dm_cancel_event_t;

/* Data event message */
struct dm_data_event
{
  dm_vardata_t        de_handle;
  dm_off_t            de_offset;
  dm_size_t           de_length;
};
typedef struct dm_data_event dm_data_event_t;

/* Destroy event message */
struct dm_destroy_event
{
  dm_vardata_t        ds_handle;
  dm_attrname_t       ds_attrname;
  dm_vardata_t        ds_attrcopy;
};
typedef struct dm_destroy_event dm_destroy_event_t;

/* Mount event message */
struct dm_mount_event
{
  mode_t              me_mode;
  dm_vardata_t        me_handle1;
  dm_vardata_t        me_handle2;
  dm_vardata_t        me_name1;
  dm_vardata_t        me_name2;
  dm_vardata_t        me_roothandle;
};
typedef struct dm_mount_event dm_mount_event_t;

/* Namespace event message */
struct dm_namesp_event
{
  mode_t              ne_mode;
  dm_vardata_t        ne_handle1;
  dm_vardata_t        ne_handle2;
  dm_vardata_t        ne_name1;
  dm_vardata_t        ne_name2;
  int                 ne_retcode;
};
typedef struct dm_namesp_event  dm_namesp_event_t;

/* Flags for the mode field of mount, preunmount and unmount event messages */
#define DM_MOUNT_RDONLY       (0x1)
#define DM_UNMOUNT_FORCE      (0x2)
#define DM_LOCAL_MOUNT        (0x4) /* GPFS specific - not in XDSM standard */
#define DM_REMOTE_MOUNT       (0x8) /* GPFS specific - not in XDSM standard */

struct dm_timestruct
{
  time_t              dm_tv_sec;
  dm_signed32         dm_tv_nsec;
};
typedef struct dm_timestruct  dm_timestruct_t;

/* DMAPI file attributes */
struct dm_fileattr
{
  mode_t              fa_mode;
  uid_t               fa_uid;
  gid_t               fa_gid;
  time_t              fa_atime;
  time_t              fa_mtime;
  time_t              fa_ctime;
  time_t              fa_dtime;
  dm_off_t            fa_size;
};
typedef struct dm_fileattr  dm_fileattr_t;

struct dm_fileattr32
{
  mode_t              fa_mode;
  uid_t               fa_uid;
  gid_t               fa_gid;
  dm_signed32         fa_atime;
  dm_signed32         fa_mtime;
  dm_signed32         fa_ctime;
  dm_signed32         fa_dtime;
  dm_off_t            fa_size;
};
typedef struct dm_fileattr32  dm_fileattr32_t;

struct dm_fileattr64
{
  mode_t              fa_mode;
#if defined(__sun)
  u_int               fa_uid;
  u_int               fa_gid;
#else
  uid_t               fa_uid;
  gid_t               fa_gid;
#endif
  dm_signed32         fa_pad_to_dword;
  dm_signed64         fa_atime;
  dm_signed64         fa_mtime;
  dm_signed64         fa_ctime;
  dm_signed64         fa_dtime;
  dm_off_t            fa_size;
};
typedef struct dm_fileattr64  dm_fileattr64_t;

/* Message types for user events */
typedef enum
{
  DM_MSGTYPE_INVALID,
  DM_MSGTYPE_SYNC,
  DM_MSGTYPE_ASYNC
} dm_msgtype_t;

/* Region descriptor */
struct dm_region
{
  dm_off_t            rg_offset;
  dm_size_t           rg_size;
  u_int               rg_flags;
  dm_signed32         rg_opaque; /* GPFS specific - not in XDSM standard */
};
typedef struct dm_region dm_region_t;

#define DM_REGION_NOEVENT       (0x0)
#define DM_REGION_READ          (0x1)
#define DM_REGION_WRITE         (0x2)
#define DM_REGION_TRUNCATE      (0x4)
#define DM_REGION_DIRECT_READ   (0x8) /* GPFS specific - read without recall */


/* Responses for dm_respond_event() */
typedef enum
{
  DM_RESP_INVALID,
  DM_RESP_CONTINUE,
  DM_RESP_ABORT,
  DM_RESP_DONTCARE
} dm_response_t;

/* Access rights */
typedef enum
{
  DM_RIGHT_NULL,
  DM_RIGHT_SHARED,
  DM_RIGHT_EXCL
} dm_right_t;

/* Status information */
struct dm_stat
{
  dm_ssize_t          _link;
  dm_vardata_t        dt_handle;
  dm_vardata_t        dt_compname;
  dm_eventset_t       dt_emask;
  int                 dt_nevents;
  int                 dt_pers;
  int                 dt_pmanreg;
  time_t              dt_dtime;
  u_int               dt_change;
  dev_t               dt_dev;
  dm_ino_t            dt_ino; 
  mode_t              dt_mode;
  nlink_t             dt_nlink;
  uid_t               dt_uid;
  gid_t               dt_gid;
  dev_t               dt_rdev;
  dm_off_t            dt_size;
  time_t              dt_atime;
  time_t              dt_mtime;
  time_t              dt_ctime;
  u_int               dt_blksize;
  dm_size_t           dt_blocks;
  int                 dt_gpfsqa1; /* GPFS specific - not in XDSM standard */
  int                 dt_gpfsqa2; /* GPFS specific - not in XDSM standard */
  u_int               dt_poolid;  /* GPFS specific - not in XDSM standard */
  int                 dt_fopen;   /* GPFS specific - not in XDSM standard */
};
typedef struct dm_stat  dm_stat_t;


/* File attribute masks */
#define DM_AT_ATIME             (0x0001)
#define DM_AT_CFLAG             (0x0002)
#define DM_AT_CTIME             (0x0004)
#define DM_AT_DTIME             (0x0008)
#define DM_AT_EMASK             (0x0010)
#define DM_AT_GID               (0x0020)
#define DM_AT_HANDLE            (0x0040)
#define DM_AT_MODE              (0x0080)
#define DM_AT_MTIME             (0x0100)
#define DM_AT_PATTR             (0x0200)
#define DM_AT_PMANR             (0x0400)
#define DM_AT_SIZE              (0x0800)
#define DM_AT_STAT              (0x1000)
#define DM_AT_UID               (0x2000)
#define DM_AT_FOPEN             (0x4000)   /* Is the file open elsewhere? 
                                              Only valid on dm_get_fileattr */

struct dm_xstat
{
  dm_ssize_t          _link;
  dm_stat_t           dx_statinfo;
  dm_vardata_t        dx_attrdata;
};
typedef struct dm_xstat dm_xstat_t;


/* Max size of a session label */
#define DM_SESSION_INFO_LEN     256

/* Special session identifier */
#define DM_NO_SESSION           ((dm_sessid_t) 0)

/* Flag indicating whether to wait in dm_get_events */
#define DM_EV_WAIT              (0x1)

/* Flag indicating whether to wait in dm_request_right */
#define DM_RR_WAIT              (0x1)

/* Flag indicating whether the request right call is from panache eviction */
#define DM_PCACHE_EVICT         (0x10)

/* Special file handles */
#define DM_GLOBAL_HANP          ((void *)(size_t)0xFFFFFFFD)
#define DM_GLOBAL_HLEN          ((size_t)0)

#define DM_INVALID_HANP         ((void *)(size_t)0xFFFFFFFF)
#define DM_INVALID_HLEN         ((size_t)0)

/* Special tokens */
static const dm_token_t                _dmNoToken = { 0, 0 };
#define DM_NO_TOKEN             _dmNoToken

static const dm_token_t                _dmInvalidToken = { 0, 1 };
#define DM_INVALID_TOKEN        _dmInvalidToken

/* Flag for the dm_write_invis() call */
#define DM_WRITE_SYNC           (0x1)

/* Version identifier
   Warning: Do not change this version number unless coordinated with 
            external callers, for example TSM, of GPFS dmapi library.
 */
#define DM_VER_STR_CONTENTS     "GPFS DMAPI 4.10"

struct dm_inherit
{
  dm_attrname_t       ih_name;
  mode_t              ih_filetype;
};
typedef struct dm_inherit dm_inherit_t;

#endif /* _DMAPI_TYPES_H */
