#include <arch/x86_64/cpu/gdt.h>
#include <aurix.h>

#include <stdint.h>

#define GDT_ENTRIES 5

void gdt_init(void)
{
	struct gdt_entry entries[GDT_ENTRIES] = {0};

	gdt_set_entry(&entries[0], 0, 0, 0, 0); // = null descriptor
	gdt_set_entry(&entries[1], 0, 0xfffff, 0x9a, 0x0a); // = kernel cs
	gdt_set_entry(&entries[2], 0, 0xfffff, 0x92, 0x0c); // = kernel ds
	gdt_set_entry(&entries[3], 0, 0xfffff, 0xfa, 0x0a); // = user cs
	gdt_set_entry(&entries[4], 0, 0xfffff, 0xf2, 0x0c); // = user ds

	struct gdtr gdtr;
	gdtr.size = sizeof(entries) - 1;
	gdtr.offset = (uint64_t)&entries;
	gdt_load(&gdtr);

	klog("done");
}

void gdt_set_entry(struct gdt_entry *entry, uint32_t base, uint32_t limit, uint8_t access,
				   uint8_t flags)
{
	entry->limit_low = (limit >> 8) & 0xff;
	entry->base_low = (base >> 8) & 0xff;
	entry->base_mid = (base >> 16) & 0xff;
	entry->access = access;
	entry->limit_high = (limit >> 16) & 0xf;
	entry->flags = flags;
	entry->base_high = (base >> 24) & 0xff;
}
