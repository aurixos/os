#include <debug/klog.h>

void aurix_print_version(void)
{
	_klog("LuxeOS version:\n%s (%s/%s)\n", AURIXOS_VERSION, AURIXOS_CONFIGURATION, AURIXOS_ARCH);
}