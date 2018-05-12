#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

.include <src.opts.mk>

PROG=	calendar
SRCS=	calendar.c locale.c events.c dates.c parsedata.c io.c day.c \
	ostern.c paskha.c pom.c sunpos.c
LIBADD=	m
INTER=          de_AT.ISO_8859-15 de_DE.ISO8859-1 fr_FR.ISO8859-1 \
		hr_HR.ISO8859-2 hu_HU.ISO8859-2 pt_BR.ISO8859-1 \
		pt_BR.UTF-8 ru_RU.KOI8-R ru_RU.UTF-8 uk_UA.KOI8-U
DE_LINKS=       de_DE.ISO8859-15
FR_LINKS=       fr_FR.ISO8859-15

FILESGROUPS+=	CALS
CALS=	calendars/calendar.all \
	calendars/calendar.australia \
	calendars/calendar.birthday \
	calendars/calendar.brazilian \
	calendars/calendar.christian \
	calendars/calendar.computer \
	calendars/calendar.croatian \
	calendars/calendar.dutch \
	calendars/calendar.freebsd \
	calendars/calendar.french \
	calendars/calendar.german \
	calendars/calendar.history \
	calendars/calendar.holiday \
	calendars/calendar.hungarian \
	calendars/calendar.judaic \
	calendars/calendar.lotr \
	calendars/calendar.music \
	calendars/calendar.newzealand \
	calendars/calendar.russian \
	calendars/calendar.southafrica \
	calendars/calendar.ukrainian \
	calendars/calendar.usholiday \
	calendars/calendar.world
CALSDIR=	${SHAREDIR}/calendar

.for lang in ${INTER}
FILESGROUPS+=	CAL_${lang}
CAL_${lang}!=	echo ${.CURDIR}/calendars/${lang}/calendar.*
CAL_${lang}DIR=	${SHAREDIR}/calendar/${lang}
.endfor

.for link in ${DE_LINKS}
SYMLINKS+=	de_DE.ISO8859-1 ${SHAREDIR}/calendar/${link}
.endfor
.for link in ${FR_LINKS}
SYMLINKS+=	fr_FR.ISO8859=1 ${SHAREDIR}/calendar/${link}
.endfor

HAS_TESTS=
SUBDIR.${MK_TESTS}+= tests

.include <bsd.prog.mk>
