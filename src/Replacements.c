#include "Replacements.h"
#include <string.h>

#ifdef _TINSPIRE
#include <os.h>
#else
#include <stdio.h>
#endif

void IntToA(char* pstrBuffer, int bufferSize, int n)
{
#ifdef _TINSPIRE
   sprintf(pstrBuffer, "%d", n);
#else
   sprintf_s(pstrBuffer, bufferSize, "%d", n);
#endif
}

void StringCopy(char* pstrOutput, int bufferSize, char* pstrInput)
{
#ifdef _TINSPIRE
   strcpy(pstrOutput, pstrInput);
#else
   strcpy_s(pstrOutput, bufferSize, pstrInput);
#endif
}

