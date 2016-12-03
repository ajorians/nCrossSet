//Public domain :)

#ifdef _TINSPIRE
#include <os.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#endif
#include "CrossLib/CrossLib.h"
#include "Defines.h"

#define CROSSLIB_RUN_SAFE

//#define DEBUG_DETAILS

#define MAX_CELL_VALUES	(10)

struct Cell
{
   int m_nMarked;
   int m_aValues[MAX_CELL_VALUES];
};

struct CrossBoard
{
   int m_nWidth;
   int m_nHeight;
   struct Cell* m_pItems;
};

struct Cell* GetAt(struct CrossBoard* pBoard, int nX, int nY)
{
#ifdef CROSSLIB_RUN_SAFE
   if( nX < 0 || nY < 0 || (nX >= pBoard->m_nWidth) || (nY >= pBoard->m_nHeight)) {
      printf("Accessing non-existing element %d,%d\n", nX, nY);
      return NULL;
   }
#endif

   struct Cell* pItem = pBoard->m_pItems + (pBoard->m_nWidth * nY + nX);

   return pItem;
}

struct CrossSet
{
   int m_nLastError;
   struct CrossBoard* m_pBoard;
};

void Cleanup(struct CrossSet** ppC)
{
   if( *ppC != NULL ) {
      struct CrossSet* pC = *ppC;
      if( pC->m_pBoard != NULL ) {
         if( pC->m_pBoard->m_pItems != NULL ) {
            free(pC->m_pBoard->m_pItems);
            pC->m_pBoard->m_pItems = NULL;
         }
         free(pC->m_pBoard);
         pC->m_pBoard = NULL;
      }
   }
}

int CrossLibCreate(CrossLib* api, const char* pstrFile)
{
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = malloc(sizeof(struct CrossSet));
   if( pC == NULL ){//Out of memory
      return CROSSLIB_OUT_OF_MEMORY;
   }
   pC->m_pBoard = NULL;

   pC->m_pBoard = malloc(sizeof(struct CrossBoard));
   if( pC->m_pBoard == NULL ){//Out of memory
      Cleanup(&pC);
      return CROSSLIB_OUT_OF_MEMORY;
   }

   pC->m_pBoard->m_pItems = NULL;

   if( strstr(pstrFile, "CrossSet ") != pstrFile ) {//SquareCells file version check
      printf("Not CrossSet data\n");
      Cleanup(&pC);
      return CROSSLIB_NOT_PUZZLE_FILE;
   }

   if( strstr(pstrFile, "1 ") != (pstrFile + strlen("CrossSet ")) ) {//Version check
      printf("Unable to read CrossSet data\n");
      Cleanup(&pC);
      return CROSSLIB_NOT_PUZZLE_FILE;
   }

   char* pstr = pstrFile + strlen("CrossSet 1 ");

   char buffer[16];
   int nSpotInBuffer = 0;

   int nSpotInMessage = 0;

   int nWidth = -1, nHeight = -1;
   int nMarked = -1, nNum = -1;
   while(pstr != '\0') {
      char ch = *pstr; pstr++;
      if( isdigit(ch) ) {
         buffer[nSpotInBuffer++] = ch;
      }
      else {
         if( ch != ' ' && ch != '\n' && ch != '\r' )
            break;
         if( nSpotInBuffer == 0 )
            continue;
         buffer[nSpotInBuffer] = '\0';
         nSpotInBuffer = 0;
         int nValue = atoi(buffer);

#ifdef DEBUG_DETAILS
         printf("Value %d\n", nValue);
#endif

         if( nWidth < 0 ) {
#ifdef CROSSLIB_RUN_SAFE
            if( nValue < 0 || nValue > 20 ) {
               printf("Bad value for width of value %d\n", nValue);
            }
#endif
            nWidth = nValue;
            pC->m_pBoard->m_nWidth = nWidth;
         }
         else if( nHeight < 0 ) {
            int x, y;

#ifdef CROSSLIB_RUN_SAFE
            if( nValue < 0 || nValue > 20 ) {
               printf("Bad value for height of value %d\n", nValue);
            }
#endif

            nHeight = nValue;
            pC->m_pBoard->m_nHeight = nHeight;

            pC->m_pBoard->m_pItems = malloc(nWidth*nHeight*sizeof(struct Cell));

            if( pC->m_pBoard->m_pItems == NULL ) {//Out of memory
               Cleanup(&pC);
               return CROSSLIB_OUT_OF_MEMORY;
            }

            for(x=0; x<nWidth; x++) {
               for(y=0; y<nHeight; y++) {
                  int n;
                  struct Cell* pCell = GetAt(pC->m_pBoard, x, y);

                  pCell->m_nMarked = CROSSLIB_NOT_MARKED;
                  for(n=0; n<MAX_CELL_VALUES; n++)
                     pCell->m_aValues[n] = -1;
               }
            }

            for(x=0; x<nWidth; x++) {
               for(y=0; y<nHeight; y++) {
                  int nMarked = -1;

                  struct Cell* pCell = GetAt(pC->m_pBoard, x, y);

                  nSpotInBuffer = 0;
                  while(pstr != '\0') {
                     ch = *pstr; pstr++;
                     if( isdigit(ch) ) {
                        buffer[nSpotInBuffer++] = ch;
                     }
                     else {
                        if (ch != ' ' && ch != '\n' && ch != '\r') {
                           pstr--;
                           break;
                        }
                        if( nSpotInBuffer == 0 )
                           continue;
                        buffer[nSpotInBuffer] = '\0';
                        nSpotInBuffer = 0;
                        nValue = atoi(buffer);

                        //printf("Value for cell: %d\n", nValue);

                        if( nMarked < 0 ) {
                           nMarked = nValue;

                           pCell->m_nMarked = nValue;
                           //printf("Used as marking value\n");
                        }
                        else {
                           int n;

                           if( nValue == 0 )
                              break;

                           for(n=0; n<MAX_CELL_VALUES; n++) {
                              if( pCell->m_aValues[n] == -1 ) {
                                 pCell->m_aValues[n] = nValue;
                                 //printf("Put %d in position %d for %d,%d\n", nValue, n, x, y);
                                 break;
                              }
                              else {
                                 //printf("Position %d is currently: %d\n", n, pCell->m_aValues[n]);
                              }
                           }
                        }
                     }
                  }
              }
           }
         }
      }
   }

   pC->m_nLastError = CROSSLIB_OK;
   *api = pC;

   return CROSSLIB_OK;
}

int CrossLibFree(CrossLib* api)
{
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = *api;

   if( pC->m_pBoard != NULL ) {
      free(pC->m_pBoard);
      pC->m_pBoard = NULL;
   }

   free(pC);
   *api = NULL;
   return CROSSLIB_OK;
}

int GetCrossLibError(CrossLib api)
{
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   return pC->m_nLastError;
}

void ClearCrossLibError(CrossLib api)
{
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   pC->m_nLastError = CROSSLIB_OK;
}

//CrossLib related functions
int GetCrossWidth(CrossLib api)
{
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   return pC->m_pBoard->m_nWidth;
}

int GetCrossHeight(CrossLib api)
{
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   return pC->m_pBoard->m_nHeight;
}

int GetCrossCellValueCount(CrossLib api, int nX, int nY)
{
   struct CrossSet* pC;
   struct Cell* pCell;
   int n;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   pCell = GetAt(pC->m_pBoard, nX, nY);
   for(n=0; n<MAX_CELL_VALUES; n++) {
      //printf("For X: %d; Y: %d; value is: %d\n", nX, nY, pCell->m_aValues[n]);
      if( pCell->m_aValues[n] < 0 )
         break;
   }

   return n;
}

int GetCrossCellValue(CrossLib api, int nX, int nY, int nIndex)
{
   struct CrossSet* pC;
   struct Cell* pCell;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   pCell = GetAt(pC->m_pBoard, nX, nY);
   return pCell->m_aValues[nIndex];
}

int GetCrossCellMarked(CrossLib api, int nX, int nY)
{
   struct CrossSet* pC;
   struct Cell* pCell;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   pCell = GetAt(pC->m_pBoard, nX, nY);
   return pCell->m_nMarked;
}

int IsCrossGameOver(CrossLib api)
{
   struct CrossSet* pC;
   int i,j,k;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   for(i=0; i<GetCrossWidth(api); i++) {
      for(j=0; j<GetCrossHeight(api); j++) {
         for(k=0; k<GetCrossHeight(api); k++) {
            if( j == k )
               continue;

#ifdef DEBUG_DETAILS
	    printf("Comparing (%d,%d):%d to (%d,%d):%d\n", i,j,GetCrossCellValue(api, i, j, 0),  i,k,GetCrossCellValue(api, i, k, 0));
#endif
	    if( GetCrossCellValue(api, i, j, 0) == GetCrossCellValue(api, i, k, 0) ) {
               return CROSSLIB_NOT_GAMEOVER;
            }
         }
      }
   }

   for(i=0; i<GetCrossHeight(api); i++) {
      for(j=0; j<GetCrossWidth(api); j++) {
         for(k=0; k<GetCrossWidth(api); k++) {
            if( j == k )
               continue;

#ifdef DEBUG_DETAILS
	    printf("Comparing (%d,%d):%d to (%d,%d):%d\n", j,i,GetCrossCellValue(api, j, i, 0), k,i,GetCrossCellValue(api, k, i, 0));
#endif
	    if( GetCrossCellValue(api, j, i, 0) == GetCrossCellValue(api, k, i, 0) ) {
               return CROSSLIB_NOT_GAMEOVER;
            }
         }
      }
   }

   //printf("Game over\n");
   return CROSSLIB_GAMEOVER;
}

int ToggleCrossCellMarking(CrossLib api, int nX, int nY)
{
   struct CrossSet* pC;
   struct Cell* pCell;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;
   pCell = GetAt(pC->m_pBoard, nX, nY);
   pCell->m_nMarked = !pCell->m_nMarked;

   return CROSSLIB_OK;
}

int ToggleCrossCellValue(CrossLib api, int nX, int nY)
{
   struct CrossSet* pC;
   struct Cell* pCell;
   int nValue;
   int nValueCount;
   int n;
   DEBUG_FUNC_NAME;

   nValue = GetCrossCellValue(api, nX, nY, 0);
   nValueCount = GetCrossCellValueCount(api, nX, nY);

   pC = (struct CrossSet*)api;
   pCell = GetAt(pC->m_pBoard, nX, nY);
   for(n=0; n<MAX_CELL_VALUES-1; n++) {
      pCell->m_aValues[n] = pCell->m_aValues[n+1];
   }
   pCell->m_aValues[nValueCount-1] = nValue;
   return CROSSLIB_OK;
}

int SetCrossCellValue(CrossLib api, int nX, int nY, int nIndex)
{
   int numbers, n;
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;

   numbers = GetCrossCellValueCount(api, nX, nY);
   if( nIndex >= numbers )
      return CROSSLIB_BADARGUMENT;

   for(n=0; n<nIndex; n++)
      ToggleCrossCellValue(api, nX, nY);

   return CROSSLIB_OK;
}

int IsCrossNumberLockedOnRowColumn(CrossLib api, int nX, int nY, int nNumber)
{
   struct CrossSet* pC;
   int x, y;
   int width, height;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;

   width = GetCrossWidth(api);
   height = GetCrossHeight(api);

   for(x=0; x<width; x++) {
      if( x == nX )
         continue;

      if( GetCrossCellMarked(api, x, nY) == CROSSLIB_MARKED &&
          GetCrossCellValue(api, x, nY, 0) == nNumber )
         return CROSSLIB_HAS_VALUE;
   }

   for(y=0; y<height; y++) {
      if( y == nY )
         continue;

      if( GetCrossCellMarked(api, nX, y) == CROSSLIB_MARKED &&
          GetCrossCellValue(api, nX, y, 0) == nNumber )
         return CROSSLIB_HAS_VALUE;
   }

   return CROSSLIB_NOT_HAS_VALUE;
}

int CrossDoSolveStep(CrossLib api)
{
   int x,y,width,height;
   int nX, nY, nPotentialIndex, n, numbers, value;
   struct CrossSet* pC;
   DEBUG_FUNC_NAME;

   pC = (struct CrossSet*)api;

   width = GetCrossWidth(api); 
   height = GetCrossHeight(api);

   for(x=0; x<width; x++) {
      for(y=0; y<height; y++) {
         if( CROSSLIB_MARKED != GetCrossCellMarked( api, x, y ) )
            continue;

	 //Check Row
         for(nX=0; nX < width; nX++) {
            if( nX == x )
               continue;

            if( CROSSLIB_MARKED == GetCrossCellMarked( api, nX, y ) )
               continue;

	    numbers = GetCrossCellValueCount(api, nX, y);
	    nPotentialIndex = -1;
	    for(n=0; n<numbers; n++) {
               value = GetCrossCellValue(api, nX, y, n);
	       if( CROSSLIB_HAS_VALUE == IsCrossNumberLockedOnRowColumn(api, nX, y, value) )
                  continue;

               if( nPotentialIndex == -1 ) {
                  nPotentialIndex = n;
               }
	       else {
                  nPotentialIndex = -1;
		  break;
               }
	    }

	    if( nPotentialIndex == -1 )
               continue;

	    SetCrossCellValue(api, nX, y, nPotentialIndex);
            ToggleCrossCellMarking(api, nX, y);
            return CROSSLIB_OK;
         }

         //Check Column
	 for(nY=0; nY < height; nY++) {
	    if( nY == y )
	       continue;

	    if( CROSSLIB_MARKED == GetCrossCellMarked( api, x, nY ) )
	       continue;

	    numbers = GetCrossCellValueCount(api, x, nY);
	    nPotentialIndex = -1;
	    for(n=0; n<numbers; n++) {
	       value = GetCrossCellValue(api, x, nY, n);
	       if( CROSSLIB_HAS_VALUE == IsCrossNumberLockedOnRowColumn(api, x, nY, value) )
	           continue;

              if( nPotentialIndex == -1 ) {
                 nPotentialIndex = n;
              }
              else {
	         nPotentialIndex = -1;
	         break;
	      }
	    }

   	    if( nPotentialIndex == -1 )
               continue;

  	    SetCrossCellValue(api, x, nY, nPotentialIndex);
	    ToggleCrossCellMarking(api, x, nY);
	    return CROSSLIB_OK;
         }
      }
   }
   return CROSSLIB_UNABLE;
}


