#include <debug/klog.h>
#include <aurix.h>

void aurix_print_version(void)
{
	_klog("LuxeOS version:\n%s (%s/%s)\n",
		STRINGIZE(AURIXOS_VERSION),
		STRINGIZE(AURIXOS_CONFIGURATION),
		STRINGIZE(AURIXOS_ARCH));
}