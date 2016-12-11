#include "Levels.h"
#include "Levels.h"
#include "Replacements.h"

#define LEVEL(x) case x: StringCopy(pstr, 2048, LEVEL_ ## x ); break;

void LevelLoad(char* pstr, int nLevelNum)
{
   switch( nLevelNum ) {
   LEVEL(1);
   LEVEL(2);
   LEVEL(3);
   LEVEL(4);
   LEVEL(5);
   LEVEL(6);
   LEVEL(7);
   LEVEL(8);
   /*   LEVEL(9);
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
   LEVEL(28);*/
   LEVEL(29);
   LEVEL(30);
   LEVEL(31);
   LEVEL(32);
   /*LEVEL(33);
   LEVEL(34);
   LEVEL(35);
   LEVEL(36);*/
   LEVEL(37);
   LEVEL(38);
   LEVEL(39);
   LEVEL(40);
   LEVEL(41);
   /*LEVEL(42);
   LEVEL(43);
   LEVEL(44);*/
   LEVEL(45);
   LEVEL(46);
   LEVEL(47);
   /*LEVEL(48);*/
   LEVEL(49);
   /*LEVEL(50);
   LEVEL(51);
   LEVEL(52);*/
   LEVEL(53);
   LEVEL(54);
   LEVEL(55);
   /*LEVEL(56);*/
   LEVEL(57);
   LEVEL(58);
   }
}

