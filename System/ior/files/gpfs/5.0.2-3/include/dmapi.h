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
/* @(#)05       1.16  src/avs/fs/mmfs/ts/dm/dmapi.h, mmfs, avs_rtac502, rtac5021836a 11/23/09 18:22:10                                          */
/*
 *
 * Define library calls for GPFS DMAPI 
 *
 */
#ifndef _DMAPI_H
#define _DMAPI_H

#include "dmapi_types.h"

/*
 * Function declarations for GPFS DMAPI
 */

#ifdef __cplusplus
extern "C"
{
#endif

  extern int dm_clear_inherit(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_attrname_t           *attrnamep      /* IN */
         );

  extern int dm_create_by_handle(
          dm_sessid_t             sid,            /* IN */
          void                    *dirhanp,       /* IN */
          size_t                  dirhlen,        /* IN */
          dm_token_t              token,          /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          char                    *cname          /* IN */
         );

  extern int dm_create_session(
          dm_sessid_t             oldsid,         /* IN */
          char                    *sessinfop,     /* IN */
          dm_sessid_t             *newsidp        /* OUT */
         );

  extern int dm_create_userevent(
          dm_sessid_t             sid,            /* IN */
          size_t                  msglen,         /* IN */
          void                    *msgdatap,      /* IN */
          dm_token_t              *tokenp         /* OUT */
         );

  extern int dm_destroy_session(
          dm_sessid_t             sid             /* IN */
         );

  extern int dm_downgrade_right(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token           /* IN */
         );

  extern int dm_fd_to_handle(
          int                     fd,             /* IN */
          void                    **hanpp,        /* OUT */
          size_t                  *hlenp          /* OUT */
         );

  extern int dm_find_eventmsg(
          dm_sessid_t             sid,            /* IN */
          dm_token_t              token,          /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_get_allocinfo(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_off_t                *offp,          /* IN/OUT */
          u_int                   nelem,          /* IN */
          dm_extent_t             *extentp,       /* OUT */
          u_int                   *nelemp         /* OUT */
         );

  extern int dm_get_bulkall(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   mask,           /* IN */
          dm_attrname_t           *attrnamep,     /* IN */
          dm_attrloc_t            *locp,          /* IN/OUT */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_get_bulkattr(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   mask,           /* IN */
          dm_attrloc_t            *locp,          /* IN/OUT */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_get_config(
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_config_t             flagname,       /* IN */
          dm_size_t               *retvalp        /* OUT */
         );

  extern int dm_get_config_events(
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          u_int                   nelem,          /* IN */
          dm_eventset_t           *eventsetp,     /* OUT */
          u_int                   *nelemp         /* OUT */
         );

  extern int dm_get_dirattrs(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   mask,           /* IN */
          dm_attrloc_t            *locp,          /* IN/OUT */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_get_dmattr(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_attrname_t           *attrnamep,     /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_get_eventlist(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   nelem,          /* IN */
          dm_eventset_t           *eventsetp,     /* OUT */
          u_int                   *nelemp         /* OUT */
         );

  extern int dm_get_events(
          dm_sessid_t             sid,            /* IN */
          u_int                   maxmsgs,        /* IN */
          u_int                   flags,          /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_get_fileattr(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   mask,           /* IN */
          dm_stat_t               *statp          /* OUT */
         );

  extern int dm_get_mountinfo(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_get_region(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   nelem,          /* IN */
          dm_region_t             *regbufp,       /* OUT */
          u_int                   *nelemp         /* OUT */
         );

  extern int dm_getall_disp(
          dm_sessid_t             sid,            /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_getall_dmattr(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_getall_inherit(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   nelem,          /* IN */
          dm_inherit_t            *inheritbufp,   /* OUT */
          u_int                   *nelemp         /* OUT */
         );

  extern int dm_getall_sessions(
          u_int                   nelem,          /* IN */
          dm_sessid_t             *sidbufp,       /* OUT */
          u_int                   *nelemp         /* OUT */
         );

  extern int dm_getall_tokens(
          dm_sessid_t             sid,            /* IN */
          u_int                   nelem,          /* IN */
          dm_token_t              *tokenbufp,     /* OUT */
          u_int                   *nelemp         /* OUT */
         );

  extern int dm_handle_cmp(
          void                    *hanp1,         /* IN */
          size_t                  hlen1,          /* IN */
          void                    *hanp2,         /* IN */
          size_t                  hlen2           /* IN */
         );

  extern void dm_handle_free(
          void                    *hanp,          /* IN */
          size_t                  hlen            /* IN */
         );

  extern u_int dm_handle_hash(
          void                    *hanp,          /* IN */
          size_t                  hlen            /* IN */
         );

  extern dm_boolean_t dm_handle_is_valid(
          void                    *hanp,          /* IN */
          size_t                  hlen            /* IN */
         );

  extern int dm_handle_to_fshandle(
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          void                    **fshanpp,      /* OUT */
          size_t                  *fslenp         /* OUT */
         );

  extern int dm_handle_to_fsid(
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_fsid_t               *fsidp          /* OUT */
         );

  extern int dm_handle_to_igen(
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_igen_t               *igenp          /* OUT */
         );

  extern int dm_handle_to_ino(
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_ino_t                *inop           /* OUT */
         );
  
  extern int dm_handle_to_snap(
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_snap_t               *isnapp          /* OUT */
         );

  extern int dm_handle_to_path(
          void                    *dirhanp,       /* IN */
          size_t                  dirhlen1,       /* IN */
          void                    *targhanp,      /* IN */
          size_t                  targhlen,       /* IN */
          size_t                  buflen,         /* IN */
          char                    *pathbufp,      /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern int dm_init_attrloc(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_attrloc_t            *locp           /* OUT */
         );

  extern int dm_init_service(
          char                    **versionstrpp  /* OUT */
         );

  extern int dm_make_fshandle(
          dm_fsid_t               *fsidp,         /* IN */
          void                    **hanpp,        /* OUT */
          size_t                  *hlenp          /* OUT */
         );

  extern int dm_make_handle(
          dm_fsid_t               *fsidp,         /* IN */
          dm_ino_t                *inop,          /* IN */
          dm_igen_t               *igenp,         /* IN */
          void                    **hanpp,        /* OUT */
          size_t                  *hlenp          /* OUT */
         );

  extern int dm_make_xhandle(
          dm_fsid_t               *fsidp,         /* IN */
          dm_ino_t                *inop,          /* IN */
          dm_igen_t               *igenp,         /* IN */
          dm_snap_t               *isnapp,        /* IN */
          void                    **hanpp,        /* OUT */
          size_t                  *hlenp          /* OUT */
         );

  extern int dm_mkdir_by_handle(
          dm_sessid_t             sid,            /* IN */
          void                    *dirhanp,       /* IN */
          size_t                  dirhlen,        /* IN */
          dm_token_t              token,          /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          char                    *cname          /* IN */
         );

  extern int dm_move_event(
          dm_sessid_t             srcsid,         /* IN */
          dm_token_t              token,          /* IN */
          dm_sessid_t             targetsid,      /* IN */
          dm_token_t              *rtokenp        /* OUT */
         );

  extern int dm_obj_ref_hold(
          dm_sessid_t             sid,            /* IN */
          dm_token_t              token,          /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen            /* IN */
         );

  extern int dm_obj_ref_query(
          dm_sessid_t             sid,            /* IN */
          dm_token_t              token,          /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen            /* IN */
         );

  extern int dm_obj_ref_rele(
          dm_sessid_t             sid,            /* IN */
          dm_token_t              token,          /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen            /* IN */
         );

  extern int dm_path_to_fshandle(
          char                    *path,          /* IN */
          void                    **hanpp,        /* OUT */
          size_t                  *hlenp          /* OUT */
         );

  extern int dm_path_to_handle(
          char                    *path,          /* IN */
          void                    **hanpp,        /* OUT */
          size_t                  *hlenp          /* OUT */
         );

  extern int dm_pending(
          dm_sessid_t             sid,            /* IN */
          dm_token_t              token,          /* IN */
          dm_timestruct_t         *delay          /* IN */
         );

  extern int dm_probe_hole(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_off_t                off,            /* IN */
          dm_size_t               len,            /* IN */
          dm_off_t                *roffp,         /* OUT */
          dm_size_t               *rlenp          /* OUT */
         );

  extern int dm_punch_hole(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_off_t                off,            /* IN */
          dm_size_t               len             /* IN */
         );

  extern int dm_query_right(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_right_t              *rightp         /* OUT */
         );

  extern int dm_query_session(
          dm_sessid_t             sid,            /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp,          /* OUT */
          size_t                  *rlenp          /* OUT */
         );

  extern dm_ssize_t dm_read_invis(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_off_t                off,            /* IN */
          dm_size_t               len,            /* IN */
          void                    *bufp           /* OUT */
         );

  extern int dm_release_right(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token           /* IN */
         );

  extern int dm_remove_dmattr(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          int                     setdtime,       /* IN */
          dm_attrname_t           *attrnamep      /* IN */
         );

  extern int dm_remove_dmattr_nosync(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          int                     setdtime,       /* IN */
          dm_attrname_t           *attrnamep      /* IN */
         );

  extern int dm_request_right(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   flags,          /* IN */
          dm_right_t              right           /* IN */
         );

  extern int dm_respond_event(
          dm_sessid_t             sid,            /* IN */
          dm_token_t              token,          /* IN */
          dm_response_t           response,       /* IN */
          int                     reterror,       /* IN */
          size_t                  buflen,         /* IN */
          void                    *respbufp       /* IN */
         );

  extern int dm_send_msg(
          dm_sessid_t             targetsid,      /* IN */
          dm_msgtype_t            msgtype,        /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp           /* IN */
         );

  extern int dm_set_disp(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_eventset_t           *eventsetp,     /* IN */
          u_int                   maxevent        /* IN */
         );

  extern int dm_set_dmattr(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_attrname_t           *attrnamep,     /* IN */
          int                     setdtime,       /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp           /* IN */
         );

  extern int dm_set_dmattr_nosync(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_attrname_t           *attrnamep,     /* IN */
          int                     setdtime,       /* IN */
          size_t                  buflen,         /* IN */
          void                    *bufp           /* IN */
         );

  extern int dm_set_eventlist(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_eventset_t           *eventsetp,     /* IN */
          u_int                   maxevent        /* IN */
         );

  extern int dm_set_eventlist_nosync(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_eventset_t           *eventsetp,     /* IN */
          u_int                   maxevent        /* IN */
         );

  extern int dm_set_fileattr(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   mask,           /* IN */
          dm_fileattr_t           *attrp          /* IN */
         );

  extern int dm_set_inherit(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_attrname_t           *attrnamep,     /* IN */
          mode_t                  mode            /* IN */
         );

  extern int dm_set_region(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   nelem,          /* IN */
          dm_region_t             *regbufp,       /* IN */
          dm_boolean_t            *exactflagp     /* OUT */
         );

  extern int dm_set_region_nosync(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          u_int                   nelem,          /* IN */
          dm_region_t             *regbufp,       /* IN */
          dm_boolean_t            *exactflagp     /* OUT */
         );

  extern int dm_set_return_on_destroy(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          dm_attrname_t           *attrnamep,     /* IN */
          dm_boolean_t            enable          /* IN */
         );

  extern int dm_symlink_by_handle(
          dm_sessid_t             sid,            /* IN */
          void                    *dirhanp,       /* IN */
          size_t                  dirhlen,        /* IN */
          dm_token_t              token,          /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          char                    *cname,         /* IN */
          char                    *path           /* IN */
         );

  extern int dm_sync_by_handle(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token           /* IN */
         );

  extern int dm_sync_dmattr_by_handle(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token           /* IN */
         );

  extern int dm_upgrade_right(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token           /* IN */
         );

  extern dm_ssize_t dm_write_invis(
          dm_sessid_t             sid,            /* IN */
          void                    *hanp,          /* IN */
          size_t                  hlen,           /* IN */
          dm_token_t              token,          /* IN */
          int                     flags,          /* IN */
          dm_off_t                off,            /* IN */
          dm_size_t               len,            /* IN */
          void                    *bufp           /* IN */
         );

#ifdef __cplusplus
}
#endif

#endif /* _DMAPI_H */
