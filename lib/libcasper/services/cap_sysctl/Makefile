# $FreeBSD$

SHLIBDIR?=	/lib/casper

.include <src.opts.mk>

CONFS=	system.sysctl
PACKAGE=libcasper
LIB=	cap_sysctl

SHLIB_MAJOR=	0
INCSDIR?=	${INCLUDEDIR}/casper

SRCS=	cap_sysctl.c

INCS=	cap_sysctl.h

LIBADD=	nv

CFLAGS+=-I${.CURDIR}

HAS_TESTS=
SUBDIR.${MK_TESTS}+= tests

.include <bsd.lib.mk>
