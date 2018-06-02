#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

.include <src.opts.mk>

.PATH: ${SRCTOP}/usr.bin/wall

CONFS=	syslog.conf
PROG=	syslogd
MAN=	syslog.conf.5 syslogd.8
SRCS=	syslogd.c ttymsg.c
FILES=	rc.d/syslogd
FILESDIR=	/etc/rc.d
FILESMODE=	${BINMODE}

DIRS+=	VAR_LOG
VAR_LOG=	/var/log

LIBADD=	util

.if ${MK_INET_SUPPORT} != "no"
CFLAGS+= -DINET
.endif
.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+= -DINET6
.endif

CFLAGS+= -I${SRCTOP}/usr.bin/wall

DIRS=	ETC_SYSLOGD
ETC_SYSLOGD=	/etc/syslog.d

.include <bsd.prog.mk>
