# $FreeBSD$

SHLIBDIR?=	/lib/casper

.include <src.opts.mk>

CONFS=	system.sysctl
PACKAGE=libcasper

SHLIB_MAJOR=	0
INCSDIR?=	${INCLUDEDIR}/casper

.if ${MK_CASPER} != "no"
SHLIB=	cap_sysctl

SRCS=	cap_sysctl.c
.endif

INCS=	cap_sysctl.h

LIBADD=	nv

CFLAGS+=-I${.CURDIR}

HAS_TESTS=
SUBDIR.${MK_TESTS}+= tests

.include <bsd.lib.mk>
