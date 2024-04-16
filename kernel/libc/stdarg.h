#ifndef _STDARG_H
#define _STDARG_H

typedef __builtin_va_list va_list;

#define va_start(ap, last_arg) __builtin_va_start(ap, last_arg)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) (type)(__builtin_va_arg((ap), (type)))
#define va_copy(dest, start) __builtin_va_copy(dest, start)

#endif /* _STDARG_H */
