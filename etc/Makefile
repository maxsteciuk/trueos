#	from: @(#)Makefile	5.11 (Berkeley) 5/21/91
# $FreeBSD$

.include <src.opts.mk>

FILESGROUPS=	FILES

# No need as it is empty and just causes rebuilds since this file does so much.
UPDATE_DEPENDFILE=	no

BIN1=

# NB: keep these sorted by MK_* knobs

# Sanitize DESTDIR
DESTDIR:=	${DESTDIR:C://*:/:g}

distribute:
	# Avoid installing tests here; "make distribution" will do this and
	# correctly place them in the right location.
	${_+_}cd ${.CURDIR} ; ${MAKE} MK_TESTS=no install \
	    DESTDIR=${DISTDIR}/${DISTRIBUTION}
	${_+_}cd ${.CURDIR} ; ${MAKE} distribution DESTDIR=${DISTDIR}/${DISTRIBUTION}

.if defined(NO_ROOT)
METALOG.add?=	cat -l >> ${METALOG}
.endif

distribution:
.if !defined(DESTDIR)
	@echo "set DESTDIR before running \"make ${.TARGET}\""
	@false
.endif
.if defined(NO_ROOT)
	( \
		echo "./etc/login.conf.db type=file mode=0644 uname=root gname=wheel"; \
		echo "./etc/pwd.db type=file mode=0644 uname=root gname=wheel"; \
		echo "./etc/spwd.db type=file mode=0600 uname=root gname=wheel"; \
	) | ${METALOG.add}
.endif
.if ${MK_NIS} == "no"
	sed -i "" -e 's/.*_compat:/# &/' -e 's/compat$$/files/' \
		${DESTDIR}/etc/nsswitch.conf
.endif

.include <bsd.prog.mk>

.if ${MK_INSTALL_AS_USER} == "yes" && ${_uid} != 0
MTREE_FILTER= sed -e 's,\([gu]\)name=,\1id=,g' \
	-e 's,\(uid=\)[^ ]* ,\1${_uid} ,' \
	-e 's,\(gid=\)[^ ]* ,\1${_gid} ,' \
	-e 's,\(uid=\)[^ ]*$$,\1${_uid},' \
	-e 's,\(gid=\)[^ ]*$$,\1${_gid},'
.else
MTREE_FILTER= cat
.if !defined(NO_FSCHG)
MTREE_FSCHG=	-i
.endif
.endif
