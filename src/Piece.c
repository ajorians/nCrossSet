#include "Piece.h"

void CreatePiece(struct Piece* pPiece, int x, int y, CrossLib cross, struct Metrics* pMetrics)
{
   pPiece->m_nX = x;
   pPiece->m_nY = y;
   pPiece->m_Cross = cross;
   pPiece->m_pMetrics = pMetrics;

   pPiece->m_pFont = nSDL_LoadFont(NSDL_FONT_THIN, 0/*R*/, 0/*G*/, 0/*B*/);
}

void FreePiece(struct Piece* pPiece)
{
   pPiece->m_Cross = NULL;//Does not own
   pPiece->m_pMetrics = NULL;//Does not own

   nSDL_FreeFont(pPiece->m_pFont);
   pPiece->m_pFont = NULL;
}

void PieceDraw(struct Piece* pPiece, struct SDL_Surface* pScreen)
{
   SDL_Rect rect;
   rect.w = GetPieceWidth(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   rect.h = GetPieceHeight(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   rect.x = GetPieceLeft(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   rect.y = GetPieceTop(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);
   SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 0));

   char buffer[10];
   int nNumbers = GetCrossCellValueCount(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY);
   int i=0;
   for(; i<nNumbers; i++) {
      buffer[i] = GetCrossCellValue(pPiece->m_Cross, pPiece->m_nX, pPiece->m_nY, i) + '0';
   }
   buffer[i] = '\0';
   nSDL_DrawString(pScreen, pPiece->m_pFont, rect.x, rect.y, buffer);
}

 
