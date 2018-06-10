# $FreeBSD$

CONFS=	crontab
PROG=	cron
MAN=	cron.8
SRCS=	cron.c database.c do_command.c job.c user.c popen.c

CFLAGS+= -DLOGIN_CAP -DPAM

LIBADD=	cron pam util

WARNS?=	2

DIRS+=	VAR_CRON
VAR_CRON=	/var/cron
VAR_CRON_MODE=	750

DIRS+=	VAR_CRON_TABS
VAR_CRON_TABS=	/var/cron/tabs
VAR_CRON_TABS_MODE=	700

.include <bsd.prog.mk>
