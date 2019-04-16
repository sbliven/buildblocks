/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2018               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*                                                                              */
/* Copyright (C) 2018 International Business Machines                           */
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
/* @(#)71       1.5.1.3  src/avs/fs/mmfs/ts/util/gpfs_watch.h, mmfs, avs_rtac502, rtac502s001a 10/1/18 14:10:41 */
/*
 *   Library calls for GPFS WATCH FOLDER interfaces
 */
#ifndef _h_gpfs_watch
#define _h_gpfs_watch
/* inotify emulation for GPFS - using LWE/policy, Kafka, and so forth */
#include <sys/inotify.h>
#include <sys/types.h>
#include <libio.h>

/* gpfs_diag_watch flags. Log messages written to /var/adm/ras/mmwf.log */
#define GPFS_WATCH_NODEBUG               (0x0) //default
#define GPFS_WATCH_DEBUG                 (0x1)

/* public API methods - mimicking the Linux inotify API */

/* :notyet: integration of our inotify fd with standard unix fd for poll()ing */
# ifdef __cplusplus
extern "C" {
# endif
/* NAME: gpfs_init_watch
 *
 * FUNCTION: The gpfs_init_watch subroutine initializes a watch and returns a
 *           parent watch descriptor (pwd). The gpfs_init_watch subroutine
 *           checks if you have enabled watch folder. It also checks if you
 *           will exceed the maximum number of watches per file system (25).
 *
 *           If you have not enabled watch folder functionality, gpfs_init_watch
 *           will fail. If you already have 100 watches on your cluster for all
 *           file systems combined, gpfs_init_watch will fail.
 *
 *           Note: The parent watch descriptor and the child watch descriptors
 *           are not Linux file descriptors. For example, one cannot poll the
 *           descriptors.
 *
 * PARAMETERS: void
 *
 * RETURNS: The gpfs_init_watch subroutine returns the pwd on success or -1 on
 *           failure.
 *
 * Errno: Errno is set if -1 is returned.
 *        ENOKEY
 *            Watch folder is not enabled. Check with IBM Spectrum Scale™
 *            support to enable it.
 *        EINTR
 *            Maximum number of watches were exceeded on this cluster. The
 *            maximum number of watches allowed per cluster is 100.
 *        Note: Further errnos might be reported depending on the inner
 *              instrumentation of the API. Use gpfs_watch_strerror to learn
 *              more about an error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 */
  int gpfs_init_watch(); /* returning an inotify fd */

/* NAME: gpfs_add_watch
 *
 * FUNCTION: The gpfs_add_watch subroutine watches files in the folder
 *           specified by pathname. The watch is non-recursive like
 *           Linux inotify. This means that the contents in subdirectories
 *           under the watched directory are not watched. The gpfs_add_watch
 *           subroutine registers your intention to watch said folder. In
 *           addition, it also verifies if the file system that you want to
 *           watch is owned by the local cluster. Currently, watches over
 *           file systems mounted on an accessing cluster are not supported.
 *
 * PARAMETERS:
 *             pwd
 *               The parent watch descriptor that is returned by gpfs_init_watch.
 *               You can set up multiple child watches (directory, fileset, or
 *               inode space) under the same parent watch as long as they are
 *               watching the same file system.
 *             pathname
 *               The path of the directory that is being watched.
 *             event_mask
 *               One or more of the events {IN_ACCESS,IN_ATTRIB,IN_CLOSE_NOWRITE,
 *                                        IN_CLOSE_WRITE,IN_CREATE,IN_DELETE,
 *                                        IN_DELETE_SELF,IN_MODIFY,IN_MOVED_FROM,
 *                                        IN_MOVE_SELF}
 *
 * RETURNS: The gpfs_add_watch subroutine returns the child watch descriptor (cwd)
 *          on success or -1 on failure.
 *
 * Errno: Errno is set if -1 is returned.
 *        EBADF
 *          Invalid pwd was passed.
 *         ENODEV
 *           The path is not a mounted IBM Spectrum Scale™ file system.
 *         EXDEV
 *           The path belongs to a different file system.
 *         ENOSYS
 *            This cluster is not the owning cluster for this file system.
 *         EINTR
 *            Exceeded the number of watches allowed for a file system (25).
 *         EDOM
 *            The file system level needs to be upgraded. Watch folder is
 *            not supported.
 *         EDESTADDRREQ
 *            The message queue for this cluster is not ready. Enable the
 *            message queue before starting a watch.
 *         ENODATA
 *             Message queue error.
 *         EHOSTUNREACH
 *             Could not find the node name.
 *         Note: Further errnos might be reported depending on the inner
 *               instrumentation of the API. Use gpfs_watch_strerror to learn
 *               more about an error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 */
  /* gpfs_add_watch restriction -- all watches added to a
     given inotify fd must be for the same file system */
  int gpfs_add_watch(int fd, const char* pathname, int mask); /* returning an inotify wd */

/* NAME: gpfs_add_fset_watch
 *
 * FUNCTION: The gpfs_add_fset_watch subroutine watches all files and directories
 *           in the fileset specified by pathname. The watch is recursive in that
 *           subdirectories in the fileset and their contents are watched. You do
 *           not have to set up additional watches to watch the subdirectories.
 *           However, nested dependent or independent filesets under the fileset
 *           at pathname are not watched.
 *
 * PARAMETERS:
 *             pwd
 *               The parent watch descriptor that is returned by gpfs_init_watch.
 *               You can set up multiple child watches (directory, fileset, or
 *               inode space) under the same parent watch as long as they are
 *               watching the same file system.
 *             pathname
 *               The root of the fileset that is being watched.
 *             event_mask
 *               One or more of the events {IN_ACCESS,IN_ATTRIB,IN_CLOSE_NOWRITE,
 *                                        IN_CLOSE_WRITE,IN_CREATE,IN_DELETE,
 *                                        IN_DELETE_SELF,IN_MODIFY,IN_MOVED_FROM,
 *                                        IN_MOVE_SELF}
 *
 * RETURNS: The gpfs_add_fset_watch subroutine returns the child watch descriptor
 *          (cwd) on success or -1 on failure.
 *          The gpfs_add_fset_watch subroutine fails if pathname does not point
 *          to the root of a fileset.
 *
 * Errno: Errno is set if -1 is returned.
 *        EBADF
 *          Invalid pwd was passed.
 *         ENODEV
 *           The path is not a mounted IBM Spectrum Scale™ file system.
 *         EXDEV
 *           The pathname is not the root of a fileset.
 *         ENOSYS
 *            This cluster is not the owning cluster for this file system.
 *         EINTR
 *            Exceeded the number of watches allowed for a file system (25).
 *         EDOM
 *            The file system level needs to be upgraded. Watch folder is
 *            not supported.
 *         EDESTADDRREQ
 *            The message queue for this cluster is not ready. Enable the
 *            message queue before starting a watch.
 *         ENODATA
 *             Message queue error.
 *         EHOSTUNREACH
 *             Could not find the node name.
 *         Note: Further errnos might be reported depending on the inner
 *               instrumentation of the API. Use gpfs_watch_strerror to learn
 *               more about an error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 */
  int gpfs_add_fset_watch(int fd, const char* pathname, int mask);

/* NAME: gpfs_add_inodespace_watch
 *
 * FUNCTION: The gpfs_add_inodespace_watch subroutine watches all files and
 *           directories in the inode space specified by pathname. This is a
 *           recursive watch, so subdirectories and their contents in the inode
 *           space are also watched. Nested dependent filesets are watched;
 *           however, nested independent filesets are not watched.
 *
 * PARAMETERS:
 *             pwd
 *               The parent watch descriptor that is returned by gpfs_init_watch.
 *               You can set up multiple child watches (directory, fileset, or
 *               inode space) under the same parent watch as long as they are
 *               watching the same file system.
 *             pathname
 *               The root of the fileset of the corresponding inode space that
 *               is being watched. The pathname is expected to point to the root
 *               of an independent fileset.
 *             event_mask
 *               One or more of the events {IN_ACCESS,IN_ATTRIB,IN_CLOSE_NOWRITE,
 *                                        IN_CLOSE_WRITE,IN_CREATE,IN_DELETE,
 *                                        IN_DELETE_SELF,IN_MODIFY,IN_MOVED_FROM,
 *                                        IN_MOVE_SELF}
 *
 * RETURNS: The gpfs_add_inodespace_watch subroutine returns the child watch
 *          descriptor (cwd) on success or -1 on failure.
 *
 * Errno: Errno is set if -1 is returned.
 *        EBADF
 *          Invalid pwd was passed.
 *         ENODEV
 *           The path is not a mounted IBM Spectrum Scale™ file system.
 *         EXDEV
 *           The pathname is not the root of an independent fileset.
 *         ENOSYS
 *            This cluster is not the owning cluster for this file system.
 *         EINTR
 *            Exceeded the number of watches allowed for a file system (25).
 *         EDOM
 *            The file system level needs to be upgraded. Watch folder is
 *            not supported.
 *         EDESTADDRREQ
 *            The message queue for this cluster is not ready. Enable the
 *            message queue before starting a watch.
 *         ENODATA
 *             Message queue error.
 *         EHOSTUNREACH
 *             Could not find the node name.
 *         Note: Further errnos might be reported depending on the inner
 *               instrumentation of the API. Use gpfs_watch_strerror to learn
 *               more about an error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 *
 */
  int gpfs_add_inodespace_watch(int fd, const char* pathname, int mask);

/* NAME: gpfs_read_watch
 *
 * FUNCTION: The gpfs_read_watch subroutine reads a file access event.
 *           The metadata for the event is populated in buf in the inotify_struct
 *           format:
 *
 *           struct inotify_event {
 *               int      cwd;      // Child watch descriptor
 *               uint32_t mask;     // Mask describing event
 *               uint32_t cookie;   // Unique cookie associating related
 *                                  // events such as rename
 *               uint32_t len;      // Size of file path
 *               char     name[];   // Optional null-terminated file path
 *           };
 *
 *           The gpfs_read_watch subroutine tries to fill up buf with as
 *           many events as it can.
 *
 * PARAMETERS:
 *             pwd
 *               The parent watch descriptor that is returned by gpfs_init_watch.
 *             buf
 *               Pointer to a preallocated buffer.
 *             count
 *               Number of bytes in buf.
 *
 * RETURNS: The gpfs_read_watch subroutine returns -1 on failure.
 *
 * Errno: Errno is set if -1 is returned.
 *        Note: Further errnos might be reported depending on the inner
 *              instrumentation of the API. Use gpfs_watch_strerror to learn
 *              more about an error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 *
 */

  ssize_t gpfs_read_watch(int fd, void* buf, size_t count); /* read one or more inotify structs (layed end-to-end) */

/* NAME: gpfs_rm_watch
 *
 * FUNCTION: The gpfs_rm_watch subroutine stops the watch for the specified cwd.
 *
 * PARAMETERS:
 *             pwd
 *               The parent watch descriptor that is returned by gpfs_init_watch.
 *             cwd
 *               The child watch descriptor that is returned by gpfs_add_*_watch.
 *
 * RETURNS: The gpfs_rm_watch subroutine returns 0 on success or -1 on error.
 *
 * Errno: Errno is set if -1 is returned.
 *        Note: Further errnos might be reported depending on the inner
 *              instrumentation of the API. Use gpfs_watch_strerror to learn
 *              more about an error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 *
 */
  int gpfs_rm_watch(int fd, int wd); /*removing the wd from the inotify fd */

/* NAME: gpfs_watch_strerror
 *
 * FUNCTION: The gpfs_watch_strerror subroutine provides some additional
 *           information for the last error encountered.
 *
 * PARAMETERS:
 *             pwd
 *               The parent watch descriptor that is returned by gpfs_init_watch.
 *
 * RETURNS: The gpfs_watch_strerror subroutine returns the character string with
 *           the error message or NULL if there is no descriptive error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 *
 */
  const char* gpfs_watch_strerror(int fd); /* C-string describing last error  */

/* NAME: gpfs_close_watch
 *
 * FUNCTION: The gpfs_close_watch subroutine destroys resources that are
 *           associated with a parent watch descriptor (pwd).
 *
 * PARAMETERS:
 *             pwd
 *               The parent watch descriptor that is returned by gpfs_init_watch.
 *
 * RETURNS: The gpfs_close_watch subroutine returns 0 on success or -1 on failure.
 *
 * Errno: Errno is set if -1 is returned.
 *        Note: Further errnos might be reported depending on the inner
 *              instrumentation of the API. Use gpfs_watch_strerror to learn
 *              more about an error.
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 *
 */
  int gpfs_close_watch(int fd); /* destroying the inotify fd and all associated wds and any other resources */

/* NAME: gpfs_diag_watch
 *
 * FUNCTION: The gpfs_diag_watch subroutine provides some additional diagnostics
 *
 * RETURNS:
 *
 * EXAMPLES: For an example using gpfs_*_watch,
 *           see /usr/lpp/mmfs/samples/util/tswf.C.
 */
  int gpfs_diag_watch(int fd, int dflags); /* set diagnostics */

# ifdef __cplusplus
}
# endif
#endif /* _h_gpfs_watch */
