#ifndef STAR_DRAWER_H
#define STAR_DRAWER_H

#ifdef NSPIRE
#include <os.h>
#endif

#include "SDL/SDL.h"

struct StarDrawer
{
   SDL_Surface	*m_pStar;
};

void CreateStarDrawer(struct StarDrawer** ppDrawer);
void FreeStarDrawer(struct StarDrawer** ppDrawer);
void DrawStar(struct StarDrawer* pDrawer, SDL_Surface	*pScreen, int x, int y);

#endif

