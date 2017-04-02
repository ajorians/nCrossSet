#include "Piece.h"

#include "Font.h"

#define PIECE_BORDER_SIZE	(4)

#define USE_DIFFERENT_FONT

#ifdef USE_DIFFERENT_FONT
static Font* g_pFontBig = NULL;
static Font* g_pFontUsed = NULL;
#endif
static Font* g_pFont = NULL;

void CreatePiece(struct Piece* pPiece, int x, int y, CrossLib cross, struct Metrics* pMetrics, struct Config* pConfig)
{
   pPiece->m_nX = x;
   pPiece->m_nY = y;
   pPiece->m_Cross = cross;
   pPiece->m_pMetrics = pMetrics;
   pPiece->m_pConfig = pConfig;

   if( g_pFont == NULL ) {
#ifdef USE_DIFFERENT_FONT
      g_pFontBig = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 255/*G*/, 255/*B*/, 12);
      g_pFontUsed = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);
#endif
      g_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 127/*R*/, 127/*G*/, 127/*B*/, 12);
   }
}

void FreePiece(struct Piece* pPiece)
{
   pPiece->m_Cross = NULL;//Does not own
   pPiece->m_pMetrics = NULL;//Does not own
   pPiece->m_pConfig = NULL;//Does not own

   if( g_pFont != NULL ) {
#ifdef USE_DIFFERENT_FONT
      FreeFont(g_pFontBig);
      g_pFontBig = NULL;
      FreeFont(g_pFontUsed);
      g_pFontUsed = NULL;
#endif

      FreeFont(g_pFont);
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

   int nOriginalLeft = GetPieceTextLeft(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);

   int top = GetPieceTextTop(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   int left = nOriginalLeft;

   int nNumbers = GetCrossCellValueCount(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY);

   int i=0;
   for(; i<nNumbers; i++) {
      int n = GetCrossCellValue(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY, i);
      buffer[0] = n + '0';

      Font* pFont = g_pFont;
      int nR = 127, nG = 127, nB = 127;
#ifdef USE_DIFFERENT_FONT
      if( CROSSLIB_HAS_VALUE == IsCrossNumberLockedOnRowColumn( pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY, n )
#ifdef _TINSPIRE
          && GetLockHint(pPiece->m_pConfig) == 1 
#endif
         ) {
         pFont = g_pFontUsed;
         nR = 255, nG = 0, nB = 0;
      }
      else if( i == 0 ) {
         pFont = g_pFontBig;
         nR = 255, nG = 255, n = 255;
      }
#endif

   DrawText(pScreen, pFont, left, top, buffer, nR, nG, nB);

#ifdef _TINSPIRE
      int nCharWidth = nSDL_GetStringWidth( pFont, buffer );
#else
   int nCharWidth = 8;
#endif

      left += nCharWidth;

      if( left >= (rect.x+rect.w) ) {
         left = nOriginalLeft;
	 top += 8;
      }
   }
}

 
