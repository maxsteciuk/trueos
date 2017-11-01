#	@(#)Makefile	8.1 (Berkeley) 7/19/93
# $FreeBSD$

FILESGROUPS=	FILESETC FILESETCDEFAULTS
FILESETCDIR=	/etc
FILESETC=	rc rc.resume rc.subr rc.shutdown rc.suspend
FILESETCDEFAULTSDIR=	/etc/defaults
FILESETCDEFAULTS=	rc.conf
PACKAGE=runtime
PROG=	init
SRCS=	init.c getmntopts.c
MAN=	init.8
PRECIOUSPROG=
INSTALLFLAGS=-b -B.bak
CFLAGS+=-DDEBUGSHELL -DSECURE -DLOGIN_CAP -DCOMPAT_SYSV_INIT
LIBADD=	util crypt

# Needed for getmntopts.c
MOUNT=	${SRCTOP}/sbin/mount
CFLAGS+=-I${MOUNT}
.PATH:	${MOUNT}

NO_SHARED?=	YES

.include <bsd.prog.mk>
