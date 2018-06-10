# $FreeBSD$

.include <src.opts.mk>

PROG=	newsyslog
CONFS=	newsyslog.conf
MAN=	newsyslog.8 newsyslog.conf.5
SRCS=	newsyslog.c ptimes.c
FILES=	rc.d/newsyslog
FILESDIR=	/etc/rc.d
FILESMODE=	${BINMODE}

HAS_TESTS=
SUBDIR.${MK_TESTS}+= tests
SUBDIR+=	newsyslog.conf.d

.include <bsd.prog.mk>
