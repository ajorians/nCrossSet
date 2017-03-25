#ifndef BACKGROUND_H
#define BACKGROUND_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"
#include "Config.h"

struct Background
{
   struct SDL_Surface* m_pScreen;//Does not own
   struct Config*      m_pConfig;//Does not own
   int m_nX;
   int* m_nArr;
   int m_nNumSquares;
   int m_nAllowMovement;
};

void CreateBackground(struct Background** ppBackground, struct SDL_Surface* pScreen, struct Config* pConfig, int nAllowMovement);
void FreeBackground(struct Background** ppBackground);
void DrawBackground(struct Background* pBackground);

#endif

