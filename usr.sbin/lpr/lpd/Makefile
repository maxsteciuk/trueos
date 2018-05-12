#	From: @(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

PROG=	lpd
CONFS=	hosts.lpd printcap
MAN=	lpd.8
SRCS=	lpd.c printjob.c recvjob.c lpdchar.c modes.c

CFLAGS+= -I${.CURDIR:H}/common_source

WARNS?=	1

LIBADD=	lpr

DIRS+=	VAR_SPOOL_LPD
VAR_SPOOL_LPD=	/var/spool/lpd
VAR_SPOOL_LPD_GRP=	daemon

.include <bsd.prog.mk>
