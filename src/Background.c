#include "Background.h"
#include "GameBackgroundWide.h"

#define GRAPHIC_WIDTH	(384)

void CreateBackground(struct Background** ppBackground, struct SDL_Surface* pScreen, struct Config* pConfig) {
   *ppBackground = malloc(sizeof(struct Background));
   struct Background* pBackground = *ppBackground;
   pBackground->m_pScreen = pScreen;
   pBackground->m_pConfig = pConfig;
   pBackground->m_pBackground = nSDL_LoadImage(image_BackGroundWide);
   pBackground->m_nX = 0;
}

void FreeBackground(struct Background** ppBackground) {
  struct Background* pBackground = *ppBackground;
  pBackground->m_pScreen = NULL;//Does not own
  pBackground->m_pConfig = NULL;//Does not own
  SDL_FreeSurface(pBackground->m_pBackground);
  pBackground->m_pBackground = NULL;

  free(pBackground);
}

void DrawBackground(struct Background* pBackground) {
   if( !is_classic ) {
       SDL_Rect rectSrc, rectDst, rectDst2;
       rectSrc.w = GRAPHIC_WIDTH;
       rectSrc.h = 240;
       rectSrc.x = 0;
       rectSrc.y = 0;

       rectDst.w = GRAPHIC_WIDTH;
       rectDst.h = 240;
       rectDst.x = pBackground->m_nX;
       rectDst.y = 0;

       rectDst2.w = GRAPHIC_WIDTH;
       rectDst2.h = 240;
       rectDst2.x = GRAPHIC_WIDTH + pBackground->m_nX;
       rectDst2.y = 0;

       SDL_BlitSurface(pBackground->m_pBackground, &rectSrc, pBackground->m_pScreen, &rectDst);
       SDL_BlitSurface(pBackground->m_pBackground, &rectSrc, pBackground->m_pScreen, &rectDst2);

       if( 1 ) {//pBackground->m_pConfig->GetBackgroundMoves() ) {
          pBackground->m_nX--;
          if( (pBackground->m_nX + GRAPHIC_WIDTH) <= 0 )
             pBackground->m_nX = 0;
       }
   } else {
       SDL_FillRect(pBackground->m_pScreen, NULL, SDL_MapRGB(pBackground->m_pScreen->format, 255, 255, 255));
   }
}

 
