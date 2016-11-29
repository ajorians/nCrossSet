#ifndef PIECE_H
#define PIECE_H

#include <os.h>
#include "SDL/SDL.h"
#include <CrossLib/CrossLib.h>
#include "Metrics.h"

struct Piece
{
   int m_nX;
   int m_nY;
   CrossLib m_Cross;//Does not own
   struct Metrics* m_pMetrics;//Does not own
//#ifdef USE_DIFFERENT_FONT
//   nSDL_Font    *m_pFontBig;
//#endif
//   nSDL_Font    *m_pFont;
};

void CreatePiece(struct Piece* pPiece, int x, int y, CrossLib cross, struct Metrics* pMetrics);
void FreePiece(struct Piece* pPiece);
void PieceDraw(struct Piece* pPiece, struct SDL_Surface* pScreen);

#endif

