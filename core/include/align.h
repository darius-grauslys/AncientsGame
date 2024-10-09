#ifndef ALIGN_H
#define ALIGN_H

#define ALIGN(alignment, type, name)\
           char __align_ ## name[sizeof(type) + alignment];\
           type *p_ ## name = (type*)(((intptr_t)__align_ ## name) +\
                    (alignment - ((intptr_t)__align_ ## name % alignment)));

#endif
