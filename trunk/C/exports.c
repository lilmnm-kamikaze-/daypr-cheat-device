#include <pspmoduleexport.h>
#define NULL ((void *) 0)

extern void module_start;
extern void module_stop;
extern void module_reboot_before;
extern void module_info;
static const unsigned int __syslib_exports[8] __attribute__((section(".rodata.sceResident"))) = {
	0xD632ACDB,
	0xCEE8593C,
	0x2F064FA6,
	0xF01D73A7,
	(unsigned int) &module_start,
	(unsigned int) &module_stop,
	(unsigned int) &module_reboot_before,
	(unsigned int) &module_info,
};

const struct _PspLibraryEntry __library_exports[1] __attribute__((section(".lib.ent"), used)) = {
	{ NULL, 0x0000, 0x8000, 4, 1, 3, &__syslib_exports },
};
