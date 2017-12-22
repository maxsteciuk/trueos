#	from: @(#)Makefile	5.11 (Berkeley) 5/21/91
# $FreeBSD$

.include <src.opts.mk>

FILESGROUPS=	FILES

# No need as it is empty and just causes rebuilds since this file does so much.
UPDATE_DEPENDFILE=	no

BIN1=

OPENBSMDIR=			${SRCTOP}/contrib/openbsm
BSM_ETC_OPEN_FILES=		${OPENBSMDIR}/etc/audit_class \
				${OPENBSMDIR}/etc/audit_event
BSM_ETC_RESTRICTED_FILES=	${OPENBSMDIR}/etc/audit_control \
				${OPENBSMDIR}/etc/audit_user
BSM_ETC_EXEC_FILES=		${OPENBSMDIR}/etc/audit_warn
BSM_ETC_DIR=			${DESTDIR}/etc/security

# NB: keep these sorted by MK_* knobs

.if ${MK_MAIL} != "no"
BIN1+=	${SRCTOP}/usr.bin/mail/misc/mail.rc
.endif

ETCMAIL=Makefile README mailer.conf access.sample virtusertable.sample \
	mailertable.sample aliases

# Special top level files for FreeBSD
FREEBSD=COPYRIGHT

# Sanitize DESTDIR
DESTDIR:=	${DESTDIR:C://*:/:g}

distribute:
	# Avoid installing tests here; "make distribution" will do this and
	# correctly place them in the right location.
	${_+_}cd ${.CURDIR} ; ${MAKE} MK_TESTS=no install \
	    DESTDIR=${DISTDIR}/${DISTRIBUTION}
	${_+_}cd ${.CURDIR} ; ${MAKE} distribution DESTDIR=${DISTDIR}/${DISTRIBUTION}

.include <bsd.endian.mk>
.if ${TARGET_ENDIANNESS} == "1234"
CAP_MKDB_ENDIAN?= -l
.elif ${TARGET_ENDIANNESS} == "4321"
CAP_MKDB_ENDIAN?= -b
.else
CAP_MKDB_ENDIAN?=
.endif

.if defined(NO_ROOT)
METALOG.add?=	cat -l >> ${METALOG}
.endif

distribution:
.if !defined(DESTDIR)
	@echo "set DESTDIR before running \"make ${.TARGET}\""
	@false
.endif
.if !defined(METALOG)
	cd ${.CURDIR}; \
	    ${INSTALL} -o ${BINOWN} -g ${BINGRP} -m 644 \
		${BIN1} ${DESTDIR}/etc; \
	    cap_mkdb ${CAP_MKDB_ENDIAN} ${DESTDIR}/etc/login.conf; \
	    services_mkdb ${CAP_MKDB_ENDIAN} -q -o ${DESTDIR}/var/db/services.db \
		${DESTDIR}/etc/services
.endif
	${_+_}cd ${SRCTOP}/share/termcap; ${MAKE} etc-termcap
	${_+_}cd ${SRCTOP}/usr.sbin/rmt; ${MAKE} etc-rmt
	cd ${.CURDIR}; ${INSTALL} -o ${BINOWN} -g ${BINGRP} -m 0444 \
	    ${BSM_ETC_OPEN_FILES} ${BSM_ETC_DIR}
	cd ${.CURDIR}; ${INSTALL} -o ${BINOWN} -g ${BINGRP} -m 0600 \
	    ${BSM_ETC_RESTRICTED_FILES} ${BSM_ETC_DIR}
	cd ${.CURDIR}; ${INSTALL} -o ${BINOWN} -g ${BINGRP} -m 0500 \
	    ${BSM_ETC_EXEC_FILES} ${BSM_ETC_DIR}
.if ${MK_UNBOUND} != "no"
	if [ ! -e ${DESTDIR}/etc/unbound ]; then \
		${INSTALL_SYMLINK} ../var/unbound ${DESTDIR}/etc/unbound; \
	fi
.endif
.if ${MK_MAIL} != "no"
	${INSTALL} -d ${DESTDIR}/etc/mail
	cd ${.CURDIR}/mail; ${INSTALL} -o ${BINOWN} -g ${BINGRP} -m 644 \
	    ${ETCMAIL} ${DESTDIR}/etc/mail
	if [ -f ${DESTDIR}/etc/mail/aliases -a ! -f ${DESTDIR}/etc/aliases ]; then \
		ln -s mail/aliases ${DESTDIR}/etc/aliases; \
	fi
.endif
.if ${MK_LOCATE} != "no"
	${INSTALL} -o nobody -g ${BINGRP} -m 644 /dev/null \
	    ${DESTDIR}/var/db/locate.database
.endif
	cd ${.CURDIR}/..; ${INSTALL} -o ${BINOWN} -g ${BINGRP} -m 444 \
		${FREEBSD} ${DESTDIR}/
.if ${MK_BOOT} != "no"
.if exists(${SRCTOP}/sys/${MACHINE}/conf/GENERIC.hints)
	${INSTALL} -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${SRCTOP}/sys/${MACHINE}/conf/GENERIC.hints \
	    ${DESTDIR}/boot/device.hints
.endif
.endif
.if ${MK_NIS} == "no"
	sed -i "" -e 's/.*_compat:/# &/' -e 's/compat$$/files/' \
		${DESTDIR}/etc/nsswitch.conf
.endif

# Clean up some directories that where mistakenly created as files that
# should not have been as part of the nvi update in r281994.
# This should be removed after 11.0-RELEASE.
DISTRIB_CLEANUP_SHARE_FILES=	${SHAREDIR}/doc/usd/10.exref ${SHAREDIR}/doc/usd/11.edit
DISTRIB_CLEANUP_SHARE_FILES+=	${SHAREDIR}/doc/usd/12.vi ${SHAREDIR}/doc/usd/13.viref
distrib-cleanup: .PHONY
	for file in ${DISTRIB_CLEANUP_SHARE_FILES}; do \
		if [ -f ${DESTDIR}/$${file} ]; then \
			rm -f ${DESTDIR}/$${file}; \
		fi; \
	done

distrib-dirs: ${MTREES:N/*} distrib-cleanup .PHONY
	@set ${MTREES}; \
	while test $$# -ge 2; do \
		m=${.CURDIR}/$$1; \
		shift; \
		d=${DESTDIR}$$1; \
		shift; \
		test -d $$d || mkdir -p $$d; \
		${ECHO} ${MTREE_CMD} -deU ${MTREE_FSCHG} \
		    ${MTREE_FOLLOWS_SYMLINKS} -f $$m -p $$d; \
		${MTREE_FILTER} $$m | \
		${MTREE_CMD} -deU ${MTREE_FSCHG} ${MTREE_FOLLOWS_SYMLINKS} \
		    -p $$d; \
	done; true
.if defined(NO_ROOT)
	@set ${MTREES}; \
	while test $$# -ge 2; do \
		m=${.CURDIR}/$$1; \
		shift; \
		d=$$1; \
		test "$$d" == "/" && d=""; \
		d=${DISTBASE}$$d; \
		shift; \
		test -d ${DESTDIR}/$$d || mkdir -p ${DESTDIR}/$$d; \
		${ECHO} "${MTREE_CMD:N-W} -C -f $$m -K uname,gname | " \
		    "sed s#^\.#.$$d# | ${METALOG.add}" ; \
		${MTREE_FILTER} $$m | \
		${MTREE_CMD:N-W} -C -K uname,gname | sed s#^\.#.$$d# | \
		    ${METALOG.add} ; \
	done; true
.endif
	${INSTALL_SYMLINK} usr/src/sys ${DESTDIR}/sys
.if ${MK_NLS} != "no"
	set - `grep "^[a-zA-Z]" ${.CURDIR}/nls.alias`; \
	while [ $$# -gt 0 ] ; do \
		${INSTALL_SYMLINK} "$$2" "${DESTDIR}${SHAREDIR}/nls/$$1"; \
		shift; shift; \
	done
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
