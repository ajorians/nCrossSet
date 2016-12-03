#include "Levels.h"
#include <string.h>

#ifndef _WIN32
#define LEVEL(x) case x: strcpy(pstr, LEVEL_ ## x ); break;
#else
#define LEVEL(x) case x: strcpy_s(pstr, 2048, LEVEL_ ## x ); break;
#endif
void LevelLoad(char* pstr, int nLevelNum)
{
   switch( nLevelNum ) {
   LEVEL(1);
/*   LEVEL(2);
   LEVEL(3);
   LEVEL(4);
   LEVEL(5);
   LEVEL(6);
   LEVEL(7);
   LEVEL(8);
   LEVEL(9);
   LEVEL(10);
   LEVEL(11);
   LEVEL(12);
   LEVEL(13);
   LEVEL(14);
   LEVEL(15);
   LEVEL(16);
   LEVEL(17);
   LEVEL(18);
   LEVEL(19);
   LEVEL(20);
   LEVEL(21);
   LEVEL(22);
   LEVEL(23);
   LEVEL(24);
   LEVEL(25);
   LEVEL(26);
   LEVEL(27);
   LEVEL(28);
   LEVEL(29);
   LEVEL(30);
   LEVEL(31);
   LEVEL(32);
   LEVEL(33);
   LEVEL(34);
   LEVEL(35);
   LEVEL(36);*/
   }
}

