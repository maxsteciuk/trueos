#	from: @(#)Makefile	8.1 (Berkeley) 6/4/93
# $FreeBSD$

CONFS=	gettytab
PROG=	getty
SRCS=	main.c init.c subr.c chat.c
LIBADD=	util
MAN=	gettytab.5 ttys.5 getty.8

WARNS?=	6
WFORMAT=0

.if exists(${.CURDIR}/etc.${MACHINE}/ttys)
CONFS+=	etc.${MACHINE}/ttys
.elif exists(${.CURDIR}/etc.${MACHINE_ARCH}/ttys)
CONFS+=	etc.${MACHINE_ARCH}/ttys
.elif exists(${.CURDIR}/etc.${MACHINE_CPUARCH}/ttys)
CONFS+=	etc.${MACHINE_CPUARCH}/ttys
.else
.error etc.MACHINE/ttys missing
.endif

.include <bsd.prog.mk>
