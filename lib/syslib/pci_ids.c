/*
pci_ids.c
*/

#include "syslib.h"
#include <minix/sysutil.h>

/*===========================================================================*
 *				pci_ids					     *
 *===========================================================================*/
PUBLIC void pci_ids(devind, vidp, didp)
int devind;
u16_t *vidp;
u16_t *didp;
{
	int r;
	message m;

	m.m_type= BUSC_PCI_IDS;
	m.m1_i1= devind;

	r= sendrec(PCI_PROC_NR, &m);
	if (r != 0)
		panic("pci", "pci_ids: can't talk to PCI", r);

	if (m.m_type != 0)
		panic("pci", "pci_ids: got bad reply from PCI", m.m_type);
	*vidp= m.m1_i1;
	*didp= m.m1_i2;
	printf("pci_ids: %04x/%04x\n", *vidp, *didp);
}
