#ifndef _ARCH_ARCH_H
#define _ARCH_ARCH_H

#define STRINGIZE_HELPER(x...) #x
#define STRINGIZE(x...) STRINGIZE_HELPER(x)
#define ARCH_INCLUDE(hdr) STRINGIZE(arch/AURIXOS_ARCH/hdr)

#endif /* _ARCH_ARCH_H */
