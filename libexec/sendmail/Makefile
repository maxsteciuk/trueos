# $FreeBSD$

SUBDIR=	mail.local \
	smrsh

FILES=	rc.sendmail
FILESDIR=	/etc

DIRS+=	VAR_SPOOL_CLIENTMQUEUE
VAR_SPOOL_CLIENTMQUEUE=	/var/spool/clientmqueue
VAR_SPOOL_CLIENTMQUEUE_MODE=	770
VAR_SPOOL_CLIENTMQUEUE_OWN=	smmsp
VAR_SPOOL_CLIENTMQUEUE_GRP=	smmsp

.include <bsd.prog.mk>
