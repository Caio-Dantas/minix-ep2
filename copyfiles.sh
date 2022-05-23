#!/bin/sh
# Script para ler automaticamente os arquivos da iso para os lugares adequados
# do sistema
ISO_PATH="/dev/c0d2"
SRC="/usr/src"

# Parte 1
isoread $ISO_PATH dmp_kern.c > $SRC/servers/is/dmp_kernel.c

# Parte 2
isoread $ISO_PATH callnr.h   > $SRC/include/minix/callnr.h
isoread $ISO_PATH lockprio.h > $SRC/include/lockprioritylib.h

isoread $ISO_PATH misc.c  > $SRC/servers/pm/misc.c
isoread $ISO_PATH mproc.h > $SRC/servers/pm/mproc.h
isoread $ISO_PATH proto.h > $SRC/servers/pm/proto.h
isoread $ISO_PATH table.c > $SRC/servers/pm/table.c

isoread $ISO_PATH proc.c > $SRC/kernel/proc.c
isoread $ISO_PATH proc.h > $SRC/kernel/proc.h

isoread $ISO_PATH sys_nice.c > $SRC/lib/syslib/sys_nice.c
isoread $ISO_PATH do_nice.c > $SRC/kernel/system/do_nice.c

isoread $ISO_PATH testeloc.c > /root/testelock.c
