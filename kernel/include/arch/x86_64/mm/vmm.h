#ifndef _ARCH_MM_VMM_H
#define _ARCH_MM_VMM_H

#include <stdint.h>

// pte flags
#define PTE_PRESENT (1)
#define PTE_READ_WRITE (1 << 1)
#define PTE_USER (1 << 2)
#define PTE_WRITE_THROUGH (1 << 3)
#define PTE_CACHE_DISABLE (1 << 4)
#define PTE_ACCESSED (1 << 5)
#define PTE_DIRTY (1 << 6)
#define PTE_PAT (1 << 7)
#define PTE_GLOBAL (1 << 8)
#define PTE_NOEXEC (1ull << 63)

// flag combinations
#define VMM_FLAGS_KERNEL_RO (PTE_PRESENT)
#define VMM_FLAGS_KERNEL_RW (PTE_PRESENT | PTE_READ_WRITE)
#define VMM_FLAGS_USER_RO (PTE_PRESENT | PTE_USER)
#define VMM_FLAGS_USER_RW (PTE_PRESENT | PTE_READ_WRITE | PTE_USER)

// type combinations
#define VMM_TYPE_UNCACHEABLE (0)
#define VMM_TYPE_WRITE_THROUGH (PTE_PAT)
#define VMM_TYPE_WRITE_COMBINING (PTE_WRITE_THROUGH)
#define VMM_TYPE_WRITE_PROTECTED (PTE_PAT | PTE_WRITE_THROUGH)
#define VMM_TYPE_WRITE_BACK (PTE_PAT | PTE_CACHE_DISABLE)
#define VMM_TYPE_UNCACHED (PTE_PAT | PTE_CACHE_DISABLE | PTE_WRITE_THROUGH)

typedef uint64_t page_map_t;

void vmm_map(page_map_t *page_table, uintptr_t phys, uintptr_t virt, uint64_t flags);
void vmm_unmap(page_map_t *page_table, uintptr_t virt);

#endif /* _ARCH_MM_VMM_H */
