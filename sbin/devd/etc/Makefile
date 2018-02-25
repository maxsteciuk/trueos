# Generally, new devd configs should be located alongside what
# installs them rather than this directory.  The exception are
# hardware-related configs, or examples, or if there are no more
# specific userland applications involved.

.include <src.opts.mk>

CONFS=
CONFDIR=	/etc/devd

.if ${MACHINE} == "amd64" || ${MACHINE} == "i386"
.if ${MK_ACPI} != "no"
CONFS+=	asus.conf
.endif
.if ${MK_HYPERV} != "no"
CONFS+=	hyperv.conf
.endif
.endif

.if ${MK_USB} != "no"
CONFS+=	ulpt.conf
.endif

.if ${MACHINE} == "powerpc"
CONFS+=	apple.conf
.endif

.if ${MK_ZFS} != "no"
CONFS+=	zfs.conf
.endif

.include <bsd.prog.mk>
