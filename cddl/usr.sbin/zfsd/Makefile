# $FreeBSD$

.include "Makefile.common"

PROG_CXX=	zfsd
MAN=		zfsd.8

DIRS+=	VAR_DB_ZFSD
VAR_DB_ZFSD=	/var/db/zfsd

DIRS+=	VAR_DB_ZFSD_CASES
VAR_DB_ZFSD_CASES=	/var/db/zfsd/cases

.include <bsd.prog.mk>

# The unittests require devel/googletest and devel/googlemock from ports.
# Don't automatically build them.
SUBDIR=
