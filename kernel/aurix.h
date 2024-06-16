#ifndef _AURIX_H
#define _AURIX_H

#define STRINGIZE_HELPER(x...) #x
#define STRINGIZE(x...) STRINGIZE_HELPER(x)

#define ARCH_INCLUDE(hdr) STRINGIZE(arch/AURIXOS_ARCH/hdr)

#endif /* _AURIX_H */
