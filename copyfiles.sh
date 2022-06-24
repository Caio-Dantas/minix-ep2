#!/bin/sh
# Script para ler automaticamente os arquivos da iso para os lugares adequados
# do sistema
ISO_PATH="/dev/c0d2"
SRC="/usr/src"

isoread $ISO_PATH callnr.h > $SRC/include/minix/callnr.h
isoread $ISO_PATH unistd.h > $SRC/include/unistd.h
isoread $ISO_PATH Makefile.in > $SRC/lib/posix/Makefile.in
isoread $ISO_PATH alloc.c > $SRC/servers/pm/alloc.c
isoread $ISO_PATH misc.c > $SRC/servers/pm/misc.c
isoread $ISO_PATH proto.h > $SRC/servers/pm/proto.h
isoread $ISO_PATH table.c > $SRC/servers/pm/table.c
isoread $ISO_PATH _changea.c > $SRC/lib/posix/_changealoc.c

isoread $ISO_PATH change_a.c > /root/change_allocation_policy.c &&
    echo -n "Compilando change_allocation_policy... " &&
    cc /root/change_allocation_policy.c -o change_allocation_policy &&
    echo [OK] || echo [ERR]
