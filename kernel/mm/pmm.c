#include <mm/pmm.h>

void *freelist[MM_MAX_LEVEL];

aurix_status pmm_init(void)
{
	return AURIX_SUCCESS;
}
