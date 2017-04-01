#include "Background.h"
#include "Replacements.h"

const int g_nSquaresAcross = 10;
const int g_nSquaresPerColumn = 10;
void CreateBackground(struct Background** ppBackground, struct SDL_Surface* pScreen, struct Config* pConfig, int nAllowMovement) {
   *ppBackground = malloc(sizeof(struct Background));
   struct Background* pBackground = *ppBackground;
   pBackground->m_pScreen = pScreen;
   pBackground->m_pConfig = pConfig;
   pBackground->m_nX = 0;

   pBackground->m_nNumSquares = (g_nSquaresAcross * g_nSquaresPerColumn) + g_nSquaresPerColumn;
   pBackground->m_nArr = malloc(pBackground->m_nNumSquares * sizeof(int));

   for( int i=0; i<pBackground->m_nNumSquares; i++ ) {
      int r = rand() % 255;
      int g = rand() % 255;
      int b = rand() % 255;
      pBackground->m_nArr[i] = ((r<<16)&0xFF0000) | ((g<<8)&0x00FF00) | b;
   }

   pBackground->m_nAllowMovement = nAllowMovement;
}

void FreeBackground(struct Background** ppBackground) {
  struct Background* pBackground = *ppBackground;
  pBackground->m_pScreen = NULL;//Does not own
  pBackground->m_pConfig = NULL;//Does not own

  free(pBackground->m_nArr);

  free(pBackground);
}

void DrawBackground(struct Background* pBackground) {
   int nSquaresWide = SCREEN_WIDTH / g_nSquaresAcross;
   int nSquaresTall = SCREEN_HEIGHT / g_nSquaresPerColumn;

   for(int i=0; i<pBackground->m_nNumSquares; i++) {
      int nCol = i / g_nSquaresPerColumn;
      int nRow = i % g_nSquaresPerColumn;

      SDL_Rect rectDst;
      rectDst.w = nSquaresWide;
      rectDst.h = nSquaresTall;
      rectDst.x = pBackground->m_nX + (nCol * nSquaresWide);
      rectDst.y = ( nRow * nSquaresTall );

      int clr = pBackground->m_nArr[i];
      int r = (clr >> 16) & 0x0000FF;
      int g = (clr >> 8) & 0x0000FF;
      int b = (clr & 0x0000FF);

      SDL_FillRect(pBackground->m_pScreen, &rectDst, SDL_MapRGB(pBackground->m_pScreen->format, r, g, b));
   }

   if( pBackground->m_nAllowMovement == 1 
#ifdef _TINSPIRE
      && GetDrawBackground(pBackground->m_pConfig) == 1
#endif
      ) {
      pBackground->m_nX = pBackground->m_nX-1;
      if( pBackground->m_nX <= (-nSquaresWide) ) {
         pBackground->m_nX = 0;

         for(int i=g_nSquaresPerColumn; i<pBackground->m_nNumSquares; i++)
            pBackground->m_nArr[i-g_nSquaresPerColumn] = pBackground->m_nArr[i];

         for(int i=(pBackground->m_nNumSquares-g_nSquaresPerColumn); i<pBackground->m_nNumSquares; i++) {
            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;
            pBackground->m_nArr[i] = ((r<<16)&0xFF0000) | ((g<<8)&0x00FF00) | b;
	 }
      }
   }
}

 
