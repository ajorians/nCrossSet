#include "Piece.h"

#define PIECE_BORDER_SIZE	(4)

#define USE_DIFFERENT_FONT

#ifdef USE_DIFFERENT_FONT
static nSDL_Font* g_pFontBig = NULL;
#endif
static nSDL_Font* g_pFont = NULL;

void CreatePiece(struct Piece* pPiece, int x, int y, CrossLib cross, struct Metrics* pMetrics)
{
   pPiece->m_nX = x;
   pPiece->m_nY = y;
   pPiece->m_Cross = cross;
   pPiece->m_pMetrics = pMetrics;

   if( g_pFont == NULL ) {
#ifdef USE_DIFFERENT_FONT
      g_pFontBig = nSDL_LoadFont(NSDL_FONT_THIN, 255/*R*/, 255/*G*/, 255/*B*/);
#endif
      g_pFont = nSDL_LoadFont(NSDL_FONT_THIN, 127/*R*/, 127/*G*/, 127/*B*/);
   }
}

void FreePiece(struct Piece* pPiece)
{
   pPiece->m_Cross = NULL;//Does not own
   pPiece->m_pMetrics = NULL;//Does not own

   if( g_pFont != NULL ) {
#ifdef USE_DIFFERENT_FONT
      nSDL_FreeFont(g_pFontBig);
      g_pFontBig = NULL;
#endif

      nSDL_FreeFont(g_pFont);
      g_pFont = NULL;
   }
}

void PieceDraw(struct Piece* pPiece, struct SDL_Surface* pScreen)
{
   SDL_Rect rect;
   rect.w = GetPieceWidth(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   rect.h = GetPieceHeight(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   rect.x = GetPieceLeft(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   rect.y = GetPieceTop(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);

   int r = 68, g = 175, b = 195;
   if( GetCrossCellMarked(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY) == CROSSLIB_MARKED ) {
      r = 254;
      g = 110;
      b = 110;
   }

   SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 255));

   rect.w -= PIECE_BORDER_SIZE;
   rect.h -= PIECE_BORDER_SIZE;
   rect.x += (PIECE_BORDER_SIZE/2);
   rect.y += (PIECE_BORDER_SIZE/2);

   SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, r, g, b));

   static char buffer[2];
   buffer[1] = '\0';

   int top = GetPieceTextTop(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   int left = GetPieceTextLeft(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);

   int nNumbers = GetCrossCellValueCount(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY);

   int i=0;
   for(; i<nNumbers; i++) {
      buffer[0] = GetCrossCellValue(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY, i) + '0';

      nSDL_Font* pFont = g_pFont;
#ifdef USE_DIFFERENT_FONT
      if( i == 0 ) {
         pFont = g_pFontBig;
      }
#endif

      nSDL_DrawString(pScreen, pFont, left, top, buffer);

      int nCharWidth = nSDL_GetStringWidth( pFont, buffer );

      if( nCharWidth <= 0 ) {
	      printf("Less than 0: %d\n", nCharWidth);
	      }

      left += nCharWidth;
   }
}

 
