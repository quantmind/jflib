/* Copyright Tue Mar 19 16:39:03 EST 2002 by Bloomberg, L.P. All rights reserved.
 *
 * $Header: /bbinc/Cinclude/RCS/bbunix.h,v 1.10 2003/09/23 02:21:47 mponomar Exp $
 *
 */

#ifndef __BBUNIX_H
#define __BBUNIX_H

#ifndef lint
static char RCSid_bbunix_h[] = "$Id: $ $CCId: /bbcm/api_backend/bbcomm_user/bbapit/bbunix.h /main/bb/14 2006/11/10 17:46:50 ksaxena $";
#endif

/*
*** bbunix.h
***
*** Bloomberg Open Systems
***
*** Unix System Headers
***
**/

/*
** COMMON DEFINES
*/

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (!FALSE)
#endif


/*
** If none of the BB_PLATFORM_??? is defined define DGUX as a default platform, unless
** we're on windows.
*/

#if !defined(BB_PLATFORM_SOLARIS) && !defined(BB_PLATFORM_SUNOS) && \
    !defined(BB_PLATFORM_HPUX) && !defined(BB_PLATFORM_AIX) && \
    !defined(BB_PLATFORM_DECAXP) && !defined(BB_PLATFORM_LINUX_INTEL) && \
    !defined(BB_PLATFORM_LINUX_ALPHA) && !defined(BB_PLATFORM_WINDOWS_NT) && \
    !defined(BB_PLATFORM_DGUX_INTEL) && !defined(BB_PLATFORM_DGUX)

#if defined(WIN32)
#define BB_PLATFORM_WINDOWS_NT

#elif defined(__DGUX__)
#define BB_PLATFORM_DGUX 

#elif defined(__sun)
#define BB_PLATFORM_SOLARIS 

#elif defined(_AIX)
#define BB_PLATFORM_AIX 

#elif defined(__hpux)
#define BB_PLATFORM_HPUX 

#elif defined(__linux__) && defined(__i386__)
#define BB_PLATFORM_LINUX_INTEL

#elif defined(__linux__) && defined(__alpha__)
#define BB_PLATFORM_LINUX_ALPHA

#else
    #error "A platform type could not be determined!"	
    char assertion[0];                     // stop non-compliant compilers
#endif

#endif

/*****************************************************************************/


#ifdef  BB_PLATFORM_DGUX

#include <sys/ioctl.h>				/* ioctl()       */
#include <stropts.h>				/* streamio      */
#include <unistd.h>                             /* select        */
#include <sys/types.h>				/* _t types      */
#include <sys/stream.h>
#include <sys/systeminfo.h>                     /* sysinfo()     */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>				/* perror()      */
#include <stdio.h>				/* printf()      */
#include <stdlib.h>				/* malloc()      */
#include <stdarg.h>				/* va_start()    */
#include <string.h>				/* strncmp()     */
#include <ctype.h>				/* C types       */
#include <time.h>                               /* time()        */
#include <fcntl.h>                              /* I/O           */
#include <signal.h>				/* sigaction()   */
#include <siginfo.h>				/* siginfo_t     */
#include <netdb.h>				/* TCP/IP        */
#include <netinet/in.h>				/* TCP/IP        */
#include <arpa/inet.h>				/* TCP/IP        */
#include <sys/param.h>				/* gethostname() */
#include <sys/socket.h>				/* socket()      */
#include <sys/signal.h>				/* siginfo_t     */
#include <sys/time.h>				/* setitimer()   */
#include <sys/times.h>            		/* times()       */
#include <sys/ipc.h>				/* ipcs          */
#include <sys/shm.h>				/* shmget()      */
#include <sys/msg.h>				/* msgget()      */
#include <sys/resource.h>                       /* get/set rlimit*/
#include <X11/Xlib.h>				/* X Display     */

#define  float4           float
#define  float8           double
#define  int2             short
#define  int4             int
#define  int8             long long

#ifndef  NOTRACE
#define  BTRACE           bTrace
#else
#define  BTRACE           if (0) bTrace
#endif

#define  BPRINT           bTrace2

#define  BOOL             int

#define  bIOctl           ioctl
#define  bWouldBlock      (errno == EAGAIN)
#define  bSleep(x)                    sleep(x/1000)
#define  pError                       perror
#define  SocketIsInvalid(x)           (x < 0)
#define  SocketClose                  close
#define  ntohd(x)                     (x)
#define  _strnicmp(x,y,z) strncmp(x,y,z)
#define  INADDR_NONE      -1

typedef  void (*pTIMERHANDLER)();

typedef int socklen_t;

#endif  /* BB_PLATFORM_DGUX */

/*****************************************************************************/


#ifdef  BB_PLATFORM_SOLARIS

#ifndef BB_SIGNING_TOOL
#ifdef   FD_SETSIZE
#undef   FD_SETSIZE
#endif
#define  FD_SETSIZE                      16384  /* Enlarge select mask */
#endif /* #ifndef  BB_SIGNING_TOOL*/

#include <sys/types.h>				/* _t types      */
#include <sys/stream.h>
#include <sys/systeminfo.h>                     /* sysinfo()     */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>				/* perror()      */
#include <stdio.h>				/* printf()      */
#include <stdlib.h>				/* malloc()      */
#include <stdarg.h>				/* va_start()    */
#include <unistd.h>
#include <string.h>				/* strncmp()     */
#include <ctype.h>				/* C types       */
#include <time.h>                               /* time()        */
#include <fcntl.h>                              /* I/O           */
#include <signal.h>				/* sigaction()   */
#include <siginfo.h>				/* siginfo_t     */
#include <netdb.h>				/* TCP/IP        */
#include <netinet/in.h>				/* TCP/IP        */
#include <arpa/inet.h>				/* TCP/IP        */
#include <sys/filio.h>              /* I/O    */
#include <sys/ioctl.h>				/* ioctl()       */
#include <sys/param.h>				/* gethostname() */
#include <sys/socket.h>				/* socket()      */
#include <sys/signal.h>				/* siginfo_t     */
#include <sys/time.h>				/* setitimer()   */
#include <sys/times.h>            		/* times()       */
#include <sys/ipc.h>				/* ipcs          */
#include <sys/shm.h>				/* shmget()      */
#include <sys/msg.h>				/* msgget()      */
#include <sys/resource.h>           /* get & set rlimit */
#include <X11/Xlib.h>				/* X Display     */
#include <dlfcn.h>                  /* V.B. support for .so files */

#define  float4           float
#define  float8           double
#define  int2             short
#define  int4             int
#define  int8             long long

#ifndef  NOTRACE
#define  BTRACE           bTrace
#else
#define  BTRACE           if (0) bTrace
#endif

#define  BPRINT           bTrace2


#define  BOOL             int

#define  bIOctl           ioctl
#define  bWouldBlock      (errno == EAGAIN)
#define  bSleep(x)                    sleep(x/1000)
#define  pError                       perror
#define  SocketIsInvalid(x)           (x < 0)
#define  SocketClose                  close
#define  _snprintf(a,b,c,d,e,f,g)     sprintf(a,c,d,e,f,g)
#define  ntohd(x)                     (x)
#define  _strnicmp(x,y,z)              strncasecmp(x, y, z)

#define  INADDR_NONE     -1

typedef  void (*pTIMERHANDLER)();

#endif  /* BB_PLATFORM_SOLARIS */

/*****************************************************************************/


#ifdef BB_PLATFORM_SUNOS

#ifndef _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#define _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#endif
#define _INCLUDE_SUNOS_SOURCE
#define _USING_SYSV4_OR_DGUX
#define _POSIX_C_SOURCE         4
#define SNI_SVR4
#ifndef SI_HW_SERIAL
#define SI_HW_SERIAL            7               /* Hardware serial number */
#define SI_HW_PROVIDER          8               /* Hardware manufacturer */
#endif

#ifdef   FD_SETSIZE
#undef   FD_SETSIZE
#endif
#define  FD_SETSIZE             512             /* Enlarge select mask */

#include <sys/types.h>                          /* _t types      */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>                              /* perror()      */
#include <stdio.h>                              /* printf()      */
#include <stdlib.h>                             /* malloc()      */
#include <stdarg.h>                             /* va_start()    */
#include <string.h>                             /* strncmp()     */
#include <ctype.h>                              /* C types       */
#include <unistd.h>                             /* getpid()      */
#include <time.h>                               /* time()        */
#include <signal.h>                             /* sigaction()   */
#include <netdb.h>                              /* TCP/IP        */
#include <netinet/in.h>                         /* TCP/IP        */
#include <arpa/inet.h>                          /* TCP/IP        */
#include <fcntl.h>                              /* I/O           */
#include <sys/ioctl.h>                          /* ioctl()       */
#include <sys/param.h>                          /* gethostname() */
#include <sys/socket.h>                         /* socket()      */
#include <sys/signal.h>                         /* siginfo_t     */
#include <sys/time.h>                           /* setitimer()   */
#include <sys/times.h>                          /* times()       */
#include <sys/ipc.h>                            /* ipcs          */
#include <sys/shm.h>                            /* shmget()      */
#include <sys/msg.h>                            /* msgget()      */
#include <sys/resource.h>                       /* get & set rlimit */
#include <X11/Xlib.h>                           /* X Display     */
#include <dlfcn.h>                              /* V.B. support for .so files */

#define float4                        float
#define float8                        double
#define int2                          short
#define int4                          int
#define int8                          long long

#ifndef NOTRACE
#define BTRACE                        bTrace
#else
#define BTRACE                        if (0) bTrace
#endif
#define BPRINT                        bTrace2

#define BOOL                          int
#define bIOctl                        ioctl
#define bWouldBlock                   (errno == EAGAIN)
#define bbExit                        exit
#define bSleep(x)                     sleep(x/1000)
#define pError                        perror
#define RawLineOut(x)                 fprintf(stderr, x)
#define ntohd(x)                      (x)
#define SocketIsInvalid(x)            (x < 0)
#define SocketClose                   close
#define Error_SHARED_MEMORY_ID        -1
#define Error_SHARED_MEMORY_ADDRESS   -1
#define  INADDR_NONE     -1
#define  _strnicmp(x,y,z)              strncasecmp(x, y, z)
#define _putw(x,y)                    putw(x, y)

#ifndef KandR
int4    sysinfo                       (int, char *, int4);
int     gethostname                   (char *, int );
void    bzero                         (void *, size_t);
#else
int4    sysinfo                       ();
int     ioctl                         ();
int     gethostname                   ();
void    bzero                         ();
#endif

typedef  struct sockaddr  *pSocketData;
typedef  void  (*pFUNC)();
typedef  void  (*pTIMERHANDLER)();

#endif /* BB_PLATFORM_SUNOS */

/*****************************************************************************/


#ifdef BB_PLATFORM_HPUX

#ifndef _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#define _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#endif
#define _INCLUDE_HPUX_SOURCE
#define _INCLUDE_XOPEN_SOURCE
#define _INCLUDE__STDC__
#define _POSIX_SOURCE
#define _USING_SYSV4_OR_DGUX
#define _XOPEN_SOURCE_EXTENDED                  /* X/Open Unix extensions. */
#define SNI_SVR4
#ifndef SI_HW_SERIAL
#define SI_HW_SERIAL            7               /* Hardware serial number */
#define SI_HW_PROVIDER          8               /* Hardware manufacturer */
#endif

#ifdef   FD_SETSIZE
#undef   FD_SETSIZE
#endif
#define  FD_SETSIZE             512             /* Enlarge select mask */

#include <sys/types.h>                          /* _t types      */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>                              /* perror()      */
#include <stdio.h>                              /* printf()      */
#include <stdlib.h>                             /* malloc()      */
#include <stdarg.h>                             /* va_start()    */
#include <string.h>                             /* strncmp()     */
#include <ctype.h>                              /* C types       */
#include <ulimit.h>                             /* ulimit()      */
#include <unistd.h>                             /* getpid()      */
#include <time.h>                               /* time()        */
#include <signal.h>                             /* sigaction()   */
#include <netdb.h>                              /* TCP/IP        */
#include <netinet/in.h>                         /* TCP/IP        */
#include <arpa/inet.h>                          /* TCP/IP        */
#include <fcntl.h>                              /* I/O           */
#include <sys/ioctl.h>                          /* ioctl()       */
#include <sys/param.h>                          /* gethostname() */
#include <sys/socket.h>                         /* socket()      */
#include <sys/signal.h>                         /* siginfo_t     */
#include <sys/time.h>                           /* setitimer()   */
#include <sys/times.h>                          /* times()       */
#include <sys/ipc.h>                            /* ipcs          */
#include <sys/shm.h>                            /* shmget()      */
#include <sys/msg.h>                            /* msgget()      */
#include <sys/resource.h>                       /* get & set rlimit */
#include <X11/Xlib.h>                           /* X Display     */

#define float4                        float
#define float8                        double
#define int2                          short
#define int4                          int
#define int8                          long long

#define BOOL                          int
#define bIOctl                        ioctl
#define bWouldBlock                   (errno == EAGAIN)
#define bbExit                        exit
#define bSleep(x)                     sleep(x/1000)
#define pError                        perror
#define RawLineOut(x)                 fprintf(stderr, x)
#define ntohd(x)                      (x)
#define SocketIsInvalid(x)            (x < 0)
#define SocketClose                   close
#define Error_SHARED_MEMORY_ID        -1
#define Error_SHARED_MEMORY_ADDRESS   -1
#define  _strnicmp(x,y,z)              strncasecmp(x, y, z)

#ifndef  NOTRACE
#define  BTRACE           bTrace
#else
#define  BTRACE           if (0) bTrace
#endif
#define  BPRINT           bTrace2

#ifndef KandR
int4     sysinfo    (int, char *, int4);
#else
int4     sysinfo    ();
#endif

typedef  struct sockaddr  *pSocketData;
typedef  void (*pTIMERHANDLER)(int);
typedef  void (*pFUNC)();

#endif   /* BB_PLATFORM_HPUX */


/*****************************************************************************/


#ifdef BB_PLATFORM_LINUX_INTEL

#define _USING_BSD_OR_DGUX
#define _USING_POSIX_OR_XPG3_OR_SYSV3_OR_BSD_OR_DGUX
#define _USING_POSIX_OR_XPG3_OR_SYSV4_OR_DGUX
#define _USING_POSIX_OR_XPG3_OR_DGUX
#define _USING_M88KBCS_OR_DGUX
#define _USING_SYSV3_OR_BSD_OR_DGUX
#define _USING_SYSV3_OR_DGUX
#define _USING_SYSV4_OR_BSD_OR_DGUX
#define _USING_SYSV4_OR_DGUX
#define _USING_XPG3_OR_SYSV3_OR_BSD_OR_DGUX
#define _USING_XPG3_OR_SYSV3_OR_DGUX
#define _USING_XPG3_OR_SYSV4_OR_DGUX
#define _USING_XPG4_OR_SYSV3_OR_BSD_OR_DGUX

#include <sys/types.h>                          /* _t types      */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>                              /* perror()      */
#include <stdio.h>                              /* printf()      */
#include <stdlib.h>                             /* malloc()      */
#include <stdarg.h>                             /* va_start()    */
#include <string.h>                             /* strncmp()     */
#include <ctype.h>                              /* C types       */
#include <unistd.h>                             /* gettimeofday()*/
#include <time.h>                               /* time()        */
#include <fcntl.h>                              /* I/O           */
#include <signal.h>                             /* sigaction()   */
#include <netdb.h>                              /* TCP/IP        */
#include <netinet/in.h>                         /* TCP/IP        */
#include <arpa/inet.h>                          /* TCP/IP        */
#include <sys/ioctl.h>                          /* ioctl()       */
#include <sys/param.h>                          /* gethostname() */
#include <sys/socket.h>                         /* socket()      */
#include <sys/signal.h>                         /* siginfo_t     */
#include <sys/time.h>                           /* setitimer()   */
#include <sys/times.h>                          /* times()       */
#include <sys/ipc.h>                            /* ipcs          */
#include <sys/shm.h>                            /* shmget()      */
#include <sys/msg.h>                            /* msgget()      */
#include <sys/resource.h>                       /* get & set rlimit */

#define  float4           float
#define  float8           double
#define  int2             short
#define  int4             int
#define  int8             long long

#ifndef  NOTRACE
#define  BTRACE           bTrace
#else
#define  BTRACE           if (0) bTrace
#endif

#define  BPRINT           bTrace2

#define  BOOL             int

#define  bIOctl           ioctl
#define  bWouldBlock      (errno == EAGAIN)
#define  bSleep(x)                    sleep(x/1000)
#define  pError                       perror
#define  SocketIsInvalid(x)           (x < 0)
#define  SocketClose                  close
#define  _snprintf        snprintf
#define  _strnicmp(x,y,z) strncmp(x,y,z)
#define _putw(x,y)                    putw(x, y)

typedef  void             (*pTIMERHANDLER)();
double   ntohd            (double);

#endif   /* BB_PLATFORM_LINUX_INTEL */


/*****************************************************************************/


#ifdef  BB_PLATFORM_LINUX_ALPHA

#define _POSIX_SOURCE                           /* IEEE Std 1003.1. */
#define _XOPEN_SOURCE                           /* Includes POSIX and XPG things. */
#define _XOPEN_SOURCE_EXTENDED                  /* XPG things and X/Open Unix extensions. */
#define _BSD_SOURCE                             /* ANSI, POSIX, and 4.3BSD things. */
#define _SVID_SOURCE                            /* ANSI, POSIX, and SVID things. */

#ifndef _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#define _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#endif
#define _XOPEN_SOURCE
#define _OSF_SOURCE
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE         4
#define _USING_SYSV4_OR_DGUX
#define SNI_SVR4
#ifndef SI_HW_SERIAL
#define SI_HW_SERIAL            7               /* Hardware serial number */
#define SI_HW_PROVIDER          8               /* Hardware manufacturer */
#endif

#if 0
#ifdef   FD_SETSIZE
#undef   FD_SETSIZE
#endif
#define  FD_SETSIZE             512             /* Enlarge select mask */
#endif

#include <gnu/types.h>
#include <sys/types.h>                          /* _t types      */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>                              /* perror()      */
#include <stdio.h>                              /* printf()      */
#include <stdlib.h>                             /* malloc()      */
#include <stdarg.h>                             /* va_start()    */
#include <string.h>                             /* strncmp()     */
#include <ctype.h>                              /* C types       */
#include <unistd.h>                             /* getpid()      */
#include <time.h>                               /* time()        */
#include <signal.h>                             /* sigaction()   */
#include <netdb.h>                              /* TCP/IP        */
#include <netinet/in.h>                         /* TCP/IP        */
#include <arpa/inet.h>                          /* TCP/IP        */
#include <fcntl.h>                              /* I/O           */
#include <sys/ioctl.h>                          /* ioctl()       */
#include <sys/param.h>                          /* gethostname() */
#include <sys/socket.h>                         /* socket()      */
#include <sys/signal.h>                         /* siginfo_t     */
#include <sys/time.h>                           /* setitimer()   */
#include <sys/times.h>                          /* times()       */
#include <sys/ipc.h>                            /* ipcs          */
#include <sys/shm.h>                            /* shmget()      */
#include <sys/msg.h>                            /* msgget()      */
#include <sys/resource.h>                       /* get & set rlimit */
#include <X11/Xlib.h>                           /* X Display     */

#define float4                       float
#define float8                       double
#define int2                         short
#define int4                         int
#define int8                         long long

#define BOOL                         int
#define bIOctl                       ioctl
#define bWouldBlock                  (errno == EAGAIN)
#define bbExit                       exit
#define bSleep(x)                    sleep(x/1000)
#define pError                       perror
#define RawLineOut(x)                fprintf(stderr, x)
#define SocketIsInvalid(x)           (x < 0)
#define SocketClose                  close
#define Error_SHARED_MEMORY_ID       -1
#define Error_SHARED_MEMORY_ADDRESS  -1

#ifndef  NOTRACE
#define  BTRACE           bTrace
#else
#define  BTRACE           if (0) bTrace
#endif
#define  BPRINT           bTrace2

#ifndef KandR
int4     sysinfo    (int, char *, int4);
double   ntohd      (double);
unsigned
 int     ntohi      (unsigned int);
#else
int4     sysinfo    ();
double   ntohd      ();
unsigned
 int     ntohi      ();
#endif

typedef struct sockaddr  *pSocketData;
typedef void (*pTIMERHANDLER)();
typedef void (*pFUNC)();

#define  _snprintf        snprintf
#define  _strnicmp(x,y,z) strncmp(x,y,z)
#define _putw(x,y)                    putw(x, y)
#define  ntohl            ntohi
#define  htonl            ntohi

#endif   /* BB_PLATFORM_LINUX_ALPHA */


/*****************************************************************************/


#ifdef BB_PLATFORM_AIX

#define _USING_BSD_OR_DGUX
#define _USING_POSIX_OR_XPG3_OR_SYSV3_OR_BSD_OR_DGUX
#define _USING_POSIX_OR_XPG3_OR_SYSV4_OR_DGUX
#define _USING_POSIX_OR_XPG3_OR_DGUX
#define _USING_M88KBCS_OR_DGUX
#define _USING_SYSV3_OR_BSD_OR_DGUX
#define _USING_SYSV3_OR_DGUX
#define _USING_SYSV4_OR_BSD_OR_DGUX
#define _USING_SYSV4_OR_DGUX
#define _USING_XPG3_OR_SYSV3_OR_BSD_OR_DGUX
#define _USING_XPG3_OR_SYSV3_OR_DGUX
#define _USING_XPG3_OR_SYSV4_OR_DGUX
#define _USING_XPG4_OR_SYSV3_OR_BSD_OR_DGUX

#include <sys/types.h>                          /* _t types      */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>                              /* perror()      */
#include <stdio.h>                              /* printf()      */
#include <stdlib.h>                             /* malloc()      */
#include <stdarg.h>                             /* va_start()    */
#include <string.h>                             /* strncmp()     */
#include <ctype.h>                              /* C types       */
#include <unistd.h>                             /* gettimeofday()*/
#include <time.h>                               /* time()        */
#include <fcntl.h>                              /* I/O           */
#include <signal.h>                             /* sigaction()   */
#include <netdb.h>                              /* TCP/IP        */
#include <netinet/in.h>                         /* TCP/IP        */
#include <arpa/inet.h>                          /* TCP/IP        */
#include <sys/ioctl.h>                          /* ioctl()       */
#include <sys/param.h>                          /* gethostname() */
#include <sys/socket.h>                         /* socket()      */
#include <sys/signal.h>                         /* siginfo_t     */
#include <sys/time.h>                           /* setitimer()   */
#include <sys/times.h>                          /* times()       */
#include <sys/ipc.h>                            /* ipcs          */
#include <sys/shm.h>                            /* shmget()      */
#include <sys/msg.h>                            /* msgget()      */
#include <sys/resource.h>                       /* get & set rlimit */
#include <X11/Xlib.h>                           /* X Display     */

#define  float4           float
#define  float8           double
#define  int2             short
#define  int4             int

#ifndef  NOTRACE
#define  BTRACE           bTrace
#else
#define  BTRACE           if (0) bTrace
#endif

#define  BPRINT           bTrace2

#define  BOOL             int

#define  bIOctl           ioctl
#define  bWouldBlock      (errno == EAGAIN)
#define  bSleep(x)                    sleep(x/1000)
#define  pError                       perror
#define  SocketIsInvalid(x)           (x < 0)
#define  SocketClose                  close
#define  _snprintf        snprintf
#define  _strnicmp(x,y,z) strncmp(x,y,z)
#define _putw(x,y)                    putw(x, y)

typedef  void             (*pTIMERHANDLER)();
double   ntohd            (double);

#endif   /* BB_PLATFORM_AIX */

/*****************************************************************************/


#ifdef  BB_PLATFORM_DECAXP

#ifndef _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#define _TARGETTING_M88KBCS_OR_M88KOCS_OR_DGUX
#endif
#define _XOPEN_SOURCE
#define _OSF_SOURCE
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE         4
#define _USING_SYSV4_OR_DGUX
#define SNI_SVR4
#ifndef SI_HW_SERIAL
#define SI_HW_SERIAL		7               /* Hardware serial number */
#define SI_HW_PROVIDER		8               /* Hardware manufacturer */
#endif

#ifdef   FD_SETSIZE
#undef   FD_SETSIZE
#endif
#define  FD_SETSIZE             512             /* Enlarge select mask */

#include <sys/types.h>				/* _t types      */
#include <sys/stat.h>                           /* stat()        */
#include <errno.h>				/* perror()      */
#include <stdio.h>				/* printf()      */
#include <stdlib.h>				/* malloc()      */
#include <stdarg.h>				/* va_start()    */
#include <string.h>				/* strncmp()     */
#include <ctype.h>				/* C types       */
#include <ulimit.h>				/* ulimit()      */
#include <unistd.h>				/* getpid()      */
#include <time.h>				/* time()        */
#include <signal.h>				/* sigaction()   */
#include <siginfo.h>				/* siginfo_t     */
#include <netdb.h>				/* TCP/IP        */
#include <netinet/in.h>				/* TCP/IP        */
#include <arpa/inet.h>				/* TCP/IP        */
#include <fcntl.h>				/* I/O           */
#include <sys/ioctl.h>				/* ioctl()       */
#include <sys/param.h>				/* gethostname() */
#include <sys/socket.h>				/* socket()      */
#include <sys/signal.h>				/* siginfo_t     */
#include <sys/siginfo.h>			/* siginfo_t     */
#include <sys/time.h>				/* setitimer()   */
#include <sys/times.h>            		/* times()       */
#include <sys/ipc.h>				/* ipcs          */
#include <sys/shm.h>				/* shmget()      */
#include <sys/msg.h>				/* msgget()      */
#include <sys/resource.h>           /* get & set rlimit */
#include <X11/Xlib.h>				/* X Display     */

#define float4                       float
#define float8                       double
#define int2                         short
#define int4                         int
#define int8                         long long

#define BOOL                         int
#define bIOctl                       ioctl
#define bWouldBlock                  (errno == EAGAIN)
#define bbExit                       exit
#define bSleep(x)                    sleep(x/1000)
#define pError                       perror
#define RawLineOut(x)                fprintf(stderr, x)
#define SocketIsInvalid(x)           (x < 0)
#define SocketClose                  close
#define Error_SHARED_MEMORY_ID       -1
#define Error_SHARED_MEMORY_ADDRESS  -1

#ifndef  NOTRACE
#define  BTRACE           bTrace
#else
#define  BTRACE           if (0) bTrace
#endif
#define  BPRINT           bTrace2

#ifndef KandR
int4     sysinfo    (int, char *, int4);
double   ntohd      (double);
#else
int4     sysinfo    ();
double   ntohd      ();
#endif

typedef unsigned int     uint_t;
typedef unsigned long    ulong_t;
typedef unsigned short   ushort_t;
typedef unsigned int     u_int;
typedef unsigned long    u_long;
typedef unsigned short   u_short;
typedef long             mtyp_t;

typedef struct sockaddr  *pSocketData;
typedef void (*pTIMERHANDLER)();
typedef void (*pFUNC)();

#endif   /* BB_PLATFORM_DECAXP */

/*****************************************************************************/


#ifdef   BB_PLATFORM_WINDOWS_NT

#define vsnprintf	_vsnprintf    /*ILR, item 3*/
#define float4           float
#define float8           double
#define int2             short
#define int4             long
#define int8             __int64

#define  MAXHOSTNAMELEN                  256
#define  Display                         int4
#define  ConnectionNumber(x)             0
#define  DefaultScreen(x)                0
#define  XOpenDisplay(x)                 0
#define  pid_t                           int4
#define  SocketIsInvalid(x)              ((x < 0)  ||  (x == INVALID_SOCKET))
#define  SocketClose                     closesocket
#define  RawLineOut(x)                   fprintf(stderr, x)
#define  pthread_t                       HANDLE
#define  pthread_attr_t                  int4
#define  pthread_cond_t                  int4
#define  pthread_mutex_t                 HANDLE
#define  pthread_mutex_init(x,y)         (0==((int4)(*x=CreateMutex(NULL,FALSE,NULL))))
#define  pthread_mutex_lock(x)           (WAIT_FAILED==WaitForSingleObject(*x,INFINITE))
#define  pthread_mutex_unlock(x)         (FALSE==ReleaseMutex(*x))
#define  pthread_attr_init(x)            *x=0
#define  pthread_attr_setstacksize(x,y)  (0==(*x=y))
#define  pthread_create(x,y,p,a)         (0==((int4)(*x=CreateThread(NULL,*y,(LPTHREAD_START_ROUTINE)p,a,(unsigned int4)0,(unsigned int4 *)&Result))))
#define  pthread_self()                  GetCurrentThreadId()
#define  pthread_join(x,y)               (WAIT_FAILED==WaitForSingleObject(x,INFINITE))

#define  shmget(x,y,z)                   ((int4)CreateFileMapping((HANDLE)0xFFFFFFFF,0,PAGE_READWRITE,0,(DWORD)(y),LongToString(x)))
#define  shmat(x,y,z)                    ((void *)MapViewOfFileEx((HANDLE)x,FILE_MAP_ALL_ACCESS,0,0,0,(LPVOID)(y)))
#define  shmctl(x,y,z)                   0
#define  bSleep(x)                       Sleep(x)
#define  IPC_CREAT                       0001000
/* File type that exists in unix but doesn't matter for NT */
#define  O_SYNC                             0
#define  bIOctl                          ioctlsocket
#define  bWouldBlock                     (WSAGetLastError() == WSAEWOULDBLOCK)

#define  Error_SHARED_MEMORY_ID          0
#define  Error_SHARED_MEMORY_ADDRESS     0

#ifdef   FD_SETSIZE
#undef   FD_SETSIZE
#endif
#define  FD_SETSIZE                      512      /* Enlarge select mask */

#define  W_OK                            2        /* So access() call works like unix */

#include <windows.h>                              /* Windows general */
#include <winuser.h>                              /* Windows general */
#include <winsock.h>                              /* Windows sockets */
#include <ctype.h>                                /* types           */
#include <sys/types.h>                            /* _t types        */
#include <sys/stat.h>                             /* stat()          */
#include <errno.h>                                /* perror()        */
#include <stdio.h>                                /* printf()        */
#include <stdlib.h>                               /* malloc()        */
#include <string.h>                               /* strncmp()       */
#include <time.h>                                 /* time()          */
#include <signal.h>                               /* sigaction()     */
#include <io.h>                                   /* open()          */
#include <fcntl.h>                                /* I/O             */
#include <process.h>				/* Threads         */
#include <math.h>

void     sleep      (int);
int4     fcntl      (int4, int, int);
double   ntohd      (double);
void     bbExit     (int);
void     pError     (char *);
void     pause      ();

struct   itimerval
{
  struct timeval  it_interval;
  struct timeval  it_value;
};


#define pTIMERHANDLER TIMERPROC      /* See WINUSER.H */

typedef int socklen_t;
#ifndef NOTRACE
#define BTRACE        bTrace
#else
#define BTRACE        if (0) bTrace
#endif
#define BPRINT	    bTrace2

#define snprintf _snprintf

#endif  /* BB_PLATFORM_WINDOWS_NT */

/* COMMON Functions Prototypes */
void   *bMalloc(int);
void    bFree(void *);
int     LineOut(char *);

#endif /* ifndef __BBUNIX_H */
