#ifndef JCONFIG_H_MULTILIB
#define JCONFIG_H_MULTILIB

#include <bits/wordsize.h>

#if __WORDSIZE == 32
# include "jconfig-32.h"
#elif __WORDSIZE == 64
# include "jconfig-64.h"
#else
# error "unexpected value for __WORDSIZE macro"
#endif

#endif
