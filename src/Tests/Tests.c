#ifdef _TINSPIRE
#include <nspireio/nspireio.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif
#include "CrossLib/CrossLib.h"
#include "../Levels.h"

#ifdef _TINSPIRE
#define PRINT  nio_printf
#else
#define PRINT  printf
#endif

#ifdef _TINSPIRE
#define PRINT_FUNC PRINT("%s", __func__);
#else
#define PRINT_FUNC PRINT("%s", __FUNCTION__);
#endif

#define TEST_SUCCEEDED	(0)
#define TEST_FAILED	(1)

#define TEST_PERSISTING

#if 0
#ifdef _TINSPIRE
int g_nRelocatedGlobals = 0;
#endif
#endif

//CrossSet VerNum Width Height
//Marked Nums... 0
#define LEVEL_TEST "CrossSet 1 4 4 \
0 1 3 0  0 2 3 0  0 3 4 0  0 4 2 0 \
0 4 2 0  1 1 0    1 2 0    0 3 4 0 \
0 2 4 0  1 3 0    1 4 0    0 1 2 0 \
0 3 2 0  0 4 2 0  0 1 4 0  0 2 4 0"

int TestConstruction()
{
   CrossLib api;
   PRINT_FUNC;
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_TEST) )
      return TEST_FAILED;

   if( CROSSLIB_OK != CrossLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestWidthAndHeight()
{
   CrossLib api;
   PRINT_FUNC;
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_TEST) )
      return TEST_FAILED;

   if( 4 != GetCrossWidth(api) )
      return TEST_FAILED;

   if( 4 != GetCrossHeight(api) )
      return TEST_FAILED;

   if( CROSSLIB_OK != CrossLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestCellValueCount()
{
   CrossLib api;
   int n=0;
   PRINT_FUNC;
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_TEST) )
      return TEST_FAILED;

   int arrCounts[] = { 2, 2, 2, 2,
                       2, 1, 1, 2,
                       2, 1, 1, 2,
                       2, 2, 2, 2};

   if( 4 != GetCrossWidth(api) )
      return TEST_FAILED;

   if( 4 != GetCrossHeight(api) )
      return TEST_FAILED;

   for(int x=0; x<GetCrossWidth(api); x++) {
      for(int y=0; y<GetCrossHeight(api); y++) {
         if( GetCrossCellValueCount(api, x, y) != arrCounts[n++] )
            return TEST_FAILED;
      }
   }

   if( CROSSLIB_OK != CrossLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestCellValue()
{
   CrossLib api;
   int n=0;
   PRINT_FUNC;
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_TEST) )
      return TEST_FAILED;

   int arrValues[] = { 1, 2, 3, 4,
                       4, 1, 2, 3,
                       2, 3, 4, 1,
                       3, 4, 1, 2};

   if( 4 != GetCrossWidth(api) )
      return TEST_FAILED;

   if( 4 != GetCrossHeight(api) )
      return TEST_FAILED;

   for(int y=0; y<GetCrossHeight(api); y++) {
      for(int x=0; x<GetCrossWidth(api); x++) {
         int nValue = GetCrossCellValue(api, x, y, 0);
         int nExpected = arrValues[n++];
         if( nValue != nExpected ) {
            //printf("At %dx%d expected was: %d but got %d\n", x, y, nExpected, nValue);
            return TEST_FAILED;
	 }
      }
   }

   if( CROSSLIB_OK != CrossLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestCellMarked()
{
   CrossLib api;
   int n=0;
   PRINT_FUNC;
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_TEST) )
      return TEST_FAILED;

   int arrMarked[] = { 0, 0, 0, 0,
                       0, 1, 1, 0,
                       0, 1, 1, 0,
                       0, 0, 0, 0};

   if( 4 != GetCrossWidth(api) )
      return TEST_FAILED;

   if( 4 != GetCrossHeight(api) )
      return TEST_FAILED;

   for(int x=0; x<GetCrossWidth(api); x++) {
      for(int y=0; y<GetCrossHeight(api); y++) {
         if( GetCrossCellMarked(api, x, y) != arrMarked[n++] )
            return TEST_FAILED;
      }
   }

   if( CROSSLIB_OK != CrossLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

#define TESTFORLEVEL(x) \
int TestBeatableLevel ## x () \
{ \
   CrossLib api; \
   int n; \
   PRINT_FUNC; \
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_ ## x ) ) \
      return TEST_FAILED; \
\
   n = GetCrossWidth(api) * GetCrossHeight(api); \
\
   for(int i=0; i<n; i++) { \
      CrossDoSolveStep( api ); \
   } \
\
   if( CROSSLIB_NOT_GAMEOVER == IsCrossGameOver(api) ) \
      return TEST_FAILED; \
\
   if( CROSSLIB_OK != CrossLibFree(&api) ) \
      return TEST_FAILED; \
\
   return TEST_SUCCEEDED; \
}

TESTFORLEVEL(1);
TESTFORLEVEL(2);
TESTFORLEVEL(3);
TESTFORLEVEL(4);
TESTFORLEVEL(5);
TESTFORLEVEL(6);
TESTFORLEVEL(7);
TESTFORLEVEL(8);
TESTFORLEVEL(9);
TESTFORLEVEL(10);
TESTFORLEVEL(11);
TESTFORLEVEL(12);
TESTFORLEVEL(13);
TESTFORLEVEL(14);
TESTFORLEVEL(15);
TESTFORLEVEL(16);
TESTFORLEVEL(17);
TESTFORLEVEL(18);
TESTFORLEVEL(19);
TESTFORLEVEL(20);
TESTFORLEVEL(21);
TESTFORLEVEL(22);
TESTFORLEVEL(23);
TESTFORLEVEL(24);
TESTFORLEVEL(25);
TESTFORLEVEL(26);
TESTFORLEVEL(27);
TESTFORLEVEL(28);
TESTFORLEVEL(29);
TESTFORLEVEL(30);
TESTFORLEVEL(31);
TESTFORLEVEL(32);
TESTFORLEVEL(33);
TESTFORLEVEL(34);
TESTFORLEVEL(35);
TESTFORLEVEL(36);
TESTFORLEVEL(37);
TESTFORLEVEL(38);
TESTFORLEVEL(39);
TESTFORLEVEL(40);
TESTFORLEVEL(41);
TESTFORLEVEL(42);
TESTFORLEVEL(43);
TESTFORLEVEL(44);
TESTFORLEVEL(45);
TESTFORLEVEL(46);
TESTFORLEVEL(47);
TESTFORLEVEL(48);
TESTFORLEVEL(49);
TESTFORLEVEL(50);
TESTFORLEVEL(51);
TESTFORLEVEL(52);
TESTFORLEVEL(53);
TESTFORLEVEL(54);
TESTFORLEVEL(55);
TESTFORLEVEL(56);
TESTFORLEVEL(57);
TESTFORLEVEL(58);

typedef int (*testfunc)();
   testfunc g_Tests[] =
   {
      TestConstruction,
      TestWidthAndHeight,
      TestCellValueCount,
      TestCellValue,
      TestCellMarked,
      TestBeatableLevel1,
      TestBeatableLevel2,
      TestBeatableLevel3,
      TestBeatableLevel4,
      TestBeatableLevel5,
      TestBeatableLevel6,
      TestBeatableLevel7,
      TestBeatableLevel8,
      TestBeatableLevel9,
      TestBeatableLevel10,
      TestBeatableLevel11,
      TestBeatableLevel12,
      TestBeatableLevel13,
      TestBeatableLevel14,
      TestBeatableLevel15,
      TestBeatableLevel16,
      TestBeatableLevel17,
      TestBeatableLevel18,
      TestBeatableLevel19,
      TestBeatableLevel20,
      TestBeatableLevel21,
      TestBeatableLevel22,
      TestBeatableLevel23,
      TestBeatableLevel24,
      TestBeatableLevel25,
      TestBeatableLevel26,
      TestBeatableLevel27,
      TestBeatableLevel28,
      TestBeatableLevel29,
      TestBeatableLevel30,
      TestBeatableLevel31,
      TestBeatableLevel32,
      TestBeatableLevel33,
      TestBeatableLevel34,
      TestBeatableLevel35,
      TestBeatableLevel36,
      TestBeatableLevel37,
      TestBeatableLevel38,
      TestBeatableLevel39,
      TestBeatableLevel40,
      TestBeatableLevel41,
      TestBeatableLevel42,
      TestBeatableLevel43,
      TestBeatableLevel44,
      TestBeatableLevel45,
      TestBeatableLevel46,
      TestBeatableLevel47,
      TestBeatableLevel48,
      TestBeatableLevel49,
      TestBeatableLevel50,
      TestBeatableLevel51,
      TestBeatableLevel52,
      TestBeatableLevel53,
      TestBeatableLevel54,
      TestBeatableLevel55,
      TestBeatableLevel56,
      TestBeatableLevel57,
      TestBeatableLevel58
   };

void RunTests()
{
#if 0
#ifdef _TINSPIRE
   if( !g_nRelocatedGlobals ) {
      nl_relocdata((unsigned*)g_Tests, sizeof(g_Tests)/sizeof(g_Tests[0]));
      g_nRelocatedGlobals = 1;
   }
#endif
#endif

   unsigned i;
   for(i=0; i<sizeof(g_Tests)/sizeof(testfunc); i++) {

      int nRet = g_Tests[i]();
      if( nRet == TEST_SUCCEEDED ) {
         PRINT("........OK\n");
      } else {
         PRINT("........FAIL\n");
      }
   }
}


