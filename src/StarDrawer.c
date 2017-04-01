#include "StarDrawer.h"
#include "StarGraphic.h"

void CreateStarDrawer(struct StarDrawer** ppDrawer)
{
   *ppDrawer = malloc(sizeof(struct StarDrawer));
   struct StarDrawer* pDrawer = (*ppDrawer);

#ifdef _TINSPIRE
   pDrawer->m_pStar = nSDL_LoadImage(image_Star);
   SDL_SetColorKey(pDrawer->m_pStar, SDL_SRCCOLORKEY, SDL_MapRGB(pDrawer->m_pStar->format, 0, 0, 0));
#endif
}

void FreeStarDrawer(struct StarDrawer** ppDrawer)
{
   struct StarDrawer* pDrawer = (*ppDrawer);

#ifdef _TINSPIRE
   SDL_FreeSurface(pDrawer->m_pStar);
#endif

   free(*ppDrawer);
   *ppDrawer = NULL;
}

void DrawStar(struct StarDrawer* pDrawer, SDL_Surface* pScreen, int x, int y)
{
   SDL_Rect rectStar;
   rectStar.x = x;
   rectStar.y = y;
   rectStar.w = 16;
   rectStar.h = 16;
   SDL_BlitSurface(pDrawer->m_pStar, NULL, pScreen, &rectStar);
}
