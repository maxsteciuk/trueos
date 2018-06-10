#	@(#)Makefile	8.19 (Berkeley) 1/14/97
# $FreeBSD$

.PATH: ${.CURDIR}

M4=		m4
CHMOD=		chmod
ROMODE=		444
RM=		rm -f

SENDMAIL_DIR=	${SRCTOP}/contrib/sendmail
SMDIR=		${SENDMAIL_DIR}/src
SENDMAIL_CF_DIR?=${SENDMAIL_DIR}/cf

# this is overkill, but....
M4FILES!=	find ${SENDMAIL_CF_DIR} -type f -name '*.m4' -print

.SUFFIXES: .mc .cf

.mc.cf: ${M4FILES}
	${RM} ${.TARGET}
	${M4} -D_CF_DIR_=${SENDMAIL_CF_DIR}/ -D_NO_MAKEINFO_ \
	    ${SENDMAIL_M4_FLAGS} \
	    ${SENDMAIL_CF_DIR}/m4/cf.m4 ${.IMPSRC} > ${.TARGET}
	${CHMOD} ${ROMODE} ${.TARGET}

DEST_CF=	${DESTDIR}/etc/mail/sendmail.cf
DEST_SUBMIT_CF=	${DESTDIR}/etc/mail/submit.cf

ETC_MAIL=	/etc/mail
CONFSDIR=	ETC_MAIL
CONFS=		access.sample \
		freebsd.cf \
		freebsd.submit.cf \
		mailertable.sample \
		virtusertable.sample
FILESGROUPS=	M_README M_MAKEFILE
M_READMEDIR=	ETC_MAIL
M_README=	README
M_READMEMODE=	644
M_MAKEFILEDIR=	ETC_MAIL
M_MAKEFILE=	mail.Makefile
M_MAKEFILENAME=	Makefile
M_MAKEFILEMODE=	644
CLEANFILES=	freebsd.cf freebsd.submit.cf

.if !defined(SENDMAIL_MC) && !defined(SENDMAIL_CF)
SENDMAIL_MC=		sendmail.mc

${SENDMAIL_MC}: freebsd.mc
	${CP} $> ${SENDMAIL_MC}
.endif

.ifndef SENDMAIL_SUBMIT_MC
SENDMAIL_SUBMIT_MC=	submit.mc

${SENDMAIL_SUBMIT_MC}: freebsd.submit.mc
	${CP} $> ${SENDMAIL_SUBMIT_MC}
.endif

.if defined(SENDMAIL_MC) && defined(SENDMAIL_CF)
.error Both SENDMAIL_MC and SENDMAIL_CF cannot be set.
.elif defined(SENDMAIL_MC)
INSTALL_CF=	${SENDMAIL_MC:T:R}.cf
CONFS+=		${INSTALL_CF}
CLEANFILES+=	${SENDMAIL_MC:T:R}.cf
${INSTALL_CF}: ${SENDMAIL_MC}
.elif defined(SENDMAIL_CF)
CONFS+=		${SENDMAIL_CF}
INSTALL_CF=	${SENDMAIL_CF}
.endif

.if !defined(SENDMAIL_SET_USER_ID)
INSTALL_SUBMIT_CF= ${SENDMAIL_SUBMIT_MC:T:R}.cf
CONFS+=		${INSTALL_SUBMIT_CF}
CLEANFILES+=	${INSTALL_SUBMIT_CF}
${INSTALL_SUBMIT_CF}: ${SENDMAIL_SUBMIT_MC}
.endif

# Additional .cf files to build.
.if defined(SENDMAIL_ADDITIONAL_MC)
SENDMAIL_ADDITIONAL_CF= ${SENDMAIL_ADDITIONAL_MC:T:S/.mc$/.cf/}
CONFS+=		${SENDMAIL_ADDITIONAL_CF}
CLEANFILES+=	${SENDMAIL_ADDITIONAL_CF}
.for mc in ${SENDMAIL_ADDITIONAL_MC}
${mc:T:R}.cf: ${mc}
.endfor
.endif

.include <bsd.prog.mk>
