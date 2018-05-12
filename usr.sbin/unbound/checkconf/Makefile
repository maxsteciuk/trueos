# $FreeBSD$

# Vendor sources and generated files
LDNSDIR= ${SRCTOP}/contrib/ldns
UNBOUNDDIR= ${SRCTOP}/contrib/unbound

.PATH: ${UNBOUNDDIR} ${UNBOUNDDIR}/smallapp ${UNBOUNDDIR}/util ${UNBOUNDDIR}/doc

PROG=	unbound-checkconf
SRCS=	ub_event.c unbound-checkconf.c worker_cb.c
CFLAGS+=	-I${UNBOUNDDIR} -I${LDNSDIR}
LIBADD=	unbound pthread
MAN=	unbound-checkconf.8
SYMLINKS=	../var/unbound /etc/unbound

DIRS+=	VAR_UNBOUND
VAR_UNBOUND=	/var/unbound
VAR_UNBOUND_OWN=	unbound
VAR_UNBOUND_GRP=	unbound

DIRS+=	VAR_UNBOUND_CONF
VAR_UNBOUND_CONF=	/var/unbound/conf.d
VAR_UNBOUND_CONF_OWN=	unbound
VAR_UNBOUND_CONF_GRP=	unbound

.include <bsd.prog.mk>
