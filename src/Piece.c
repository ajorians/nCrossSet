#include "Piece.h"

#define PIECE_BORDER_SIZE	(4)

void CreatePiece(struct Piece* pPiece, int x, int y, CrossLib cross, struct Metrics* pMetrics)
{
   printf("CreatePiece\n");
   pPiece->m_nX = x;
   pPiece->m_nY = y;
   pPiece->m_Cross = cross;
   pPiece->m_pMetrics = pMetrics;

#ifdef DIFFERENT_FONT_FOR_MAIN_PIECE
   pPiece->m_pFontBig = nSDL_LoadFont(NSDL_FONT_FANTASY, 255/*R*/, 255/*G*/, 255/*B*/);
#endif
   pPiece->m_pFont = nSDL_LoadFont(NSDL_FONT_THIN, 255/*R*/, 255/*G*/, 255/*B*/);
}

void FreePiece(struct Piece* pPiece)
{
   printf("FreePiece\n");
   pPiece->m_Cross = NULL;//Does not own
   pPiece->m_pMetrics = NULL;//Does not own

#ifdef DIFFERENT_FONT_FOR_MAIN_PIECE
   nSDL_FreeFont(pPiece->m_pFontBig);
   pPiece->m_pFontBig = NULL;
#endif

   nSDL_FreeFont(pPiece->m_pFont);
   pPiece->m_pFont = NULL;
}

void PieceDraw(struct Piece* pPiece, struct SDL_Surface* pScreen)
{
   //printf("PieceDraw\n");
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

   static char buffer[10];

   buffer[0] = GetCrossCellValue(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY, 0) + '0';
   buffer[1] = '\0';

   int top = GetPieceTextTop(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   int left = GetPieceTextLeft(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   nSDL_DrawString(pScreen,
#ifdef DIFFERENT_FONT_FOR_MAIN_PIECE 
		   pPiece->m_pFontBig
#else
		   pPiece->m_pFont
#endif
		   , left + rect.w/2 - 8, top + rect.h/2 - 8, buffer);

   int nNumbers = GetCrossCellValueCount(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY);
   if( nNumbers >= 2 ) {
      int i=1;
      for(; i<nNumbers; i++) {
         buffer[i-1] = GetCrossCellValue(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY, i) + '0';
      }
      buffer[i-1] = '\0';
      nSDL_DrawString(pScreen, pPiece->m_pFont, left, top, buffer);
   }
#if 0
   buffer[0] = nNumbers + '0';
   buffer[1] = '\0';
   nSDL_DrawString(pScreen, pPiece->m_pFont, left+5, top + 15, buffer);
#endif
}

 
