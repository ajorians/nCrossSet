#ifdef _TINSPIRE
#include <nspireio/nspireio.h>
#else
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#endif
#include "CrossLib/CrossLib.h"

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
#define LEVEL_1 "CrossSet 1 4 4 \
0 1 3 0  0 2 3 0  0 3 4 0  0 4 2 0 \
0 4 2 0  1 1 0    1 2 0    0 3 4 0 \
0 2 4 0  1 3 0    1 4 0    0 1 2 0 \
0 3 2 0  0 4 2 0  0 1 4 0  0 2 4 0"

int TestConstruction()
{
   CrossLib api;
   PRINT_FUNC;
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_1) )
      return TEST_FAILED;

   if( CROSSLIB_OK != CrossLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestWidthAndHeight()
{
   CrossLib api;
   PRINT_FUNC;
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_1) )
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
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_1) )
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
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_1) )
      return TEST_FAILED;

   int arrValues[] = { 1, 2, 3, 4,
                       4, 1, 2, 3,
                       2, 3, 4, 1,
                       3, 4, 1, 2};

   if( 4 != GetCrossWidth(api) )
      return TEST_FAILED;

   if( 4 != GetCrossHeight(api) )
      return TEST_FAILED;

   for(int x=0; x<GetCrossWidth(api); x++) {
      for(int y=0; y<GetCrossHeight(api); y++) {
         if( GetCrossCellValue(api, x, y, 0) != arrValues[n++] )
            return TEST_FAILED;
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
   if( CROSSLIB_OK != CrossLibCreate(&api, LEVEL_1) )
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

typedef int (*testfunc)();
   testfunc g_Tests[] =
   {
      TestConstruction,
      TestWidthAndHeight,
      TestCellValueCount,
      TestCellValue,
      TestCellMarked
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


