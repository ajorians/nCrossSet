#ifndef DEFINES_H
#define DEFINES_H

#ifndef DEBUG_MSG
#define DEBUG_MSG//     printf
#endif

#ifndef DEBUG_FUNC_NAME
#ifdef _TINSPIRE
#define DEBUG_FUNC_NAME	DEBUG_MSG("%s: %s (%d)\n", __FILE__, __func__, __LINE__);
#else
#define DEBUG_FUNC_NAME ;
#endif
#endif


#endif

