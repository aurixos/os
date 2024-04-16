#ifndef _ASSERT_H
#define _ASSERT_H

#ifdef NDEBUG
# define assert(expr) ((void)0)
#else
# define _VAL(x) #x
# define _STR(x) _VAL(x)
# define assert(expr) ((expr) ? (void)0 : _Assert(__FILE__ ":" _STR(__LINE__) "" #expr))

void _Assert(char *);
#endif

#endif /* _ASSERT_H */
