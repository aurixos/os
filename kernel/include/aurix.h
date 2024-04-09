#ifndef _AURIX_H
#define _AURIX_H

#include <debug/klog.h>

#define STRINGIZE_HELPER(x...) #x
#define STRINGIZE(x...) STRINGIZE_HELPER(x)
#define ARCH_INCLUDE(hdr) STRINGIZE(arch/AURIXOS_ARCH/hdr)

typedef enum {
	AURIX_SUCCESS,
	AURIX_ERROR,
} aurix_status;

void aurix_print_version(void);

#endif /* _AURIX_H */
