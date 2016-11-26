#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <os.h>
#include "SDL/SDL.h"
#include "Config.h"

struct Background
{
   struct SDL_Surface* m_pScreen;//Does not own
   struct Config*      m_pConfig;//Does not own
   struct SDL_Surface* m_pBackground;
   int m_nX;
};

void CreateBackground(struct Background** ppBackground, struct SDL_Surface* pScreen, struct Config* pConfig);
void FreeBackground(struct Background** ppBackground);
void DrawBackground(struct Background* pBackground);

#endif

