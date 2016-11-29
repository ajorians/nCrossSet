#include "Selector.h"
#include "SDL/SDL_gfxPrimitives.h"

#define SELECTOR_LINE_WIDTH     (4)

void CreateSelector(struct Selector** ppSelector, struct SDL_Surface* pScreen, struct Config* pConfig, struct Metrics* pMetrics, CrossLib cross)
{
   *ppSelector = malloc(sizeof(struct Selector));
   struct Selector* pSelector = *ppSelector;
   pSelector->m_nCurrentX = pSelector->m_nCurrentY = 0;
   pSelector->m_Cross = cross;
   pSelector->m_pScreen = pScreen;
   pSelector->m_pConfig = pConfig;
   pSelector->m_pMetrics = pMetrics;
}

void FreeSelector(struct Selector** ppSelector)
{
   struct Selector* pSelector = *ppSelector;
   pSelector->m_Cross = NULL;//Does not own
   pSelector->m_pScreen = NULL;//Does not own
   pSelector->m_pConfig = NULL;//Does not own
   pSelector->m_pMetrics = NULL;//Does not own

   free(pSelector);
}

void DrawSelector(struct Selector* pSelector)
{
   int r=255, g=0, b=0, a=200;

   int left = GetPieceLeft(pSelector->m_pMetrics, pSelector->m_nCurrentX, pSelector->m_nCurrentY);
   int top = GetPieceTop(pSelector->m_pMetrics, pSelector->m_nCurrentX, pSelector->m_nCurrentY);
   int right = left + GetPieceWidth(pSelector->m_pMetrics, pSelector->m_nCurrentX, pSelector->m_nCurrentY);
   int bottom = top + GetPieceHeight(pSelector->m_pMetrics, pSelector->m_nCurrentX, pSelector->m_nCurrentY);

   //Top
   thickLineRGBA(pSelector->m_pScreen, left, top, right, top, SELECTOR_LINE_WIDTH, r, g, b, a);
   //Left
   thickLineRGBA(pSelector->m_pScreen, left, top, left, bottom, SELECTOR_LINE_WIDTH, r, g, b, a);
   //Bottom
   thickLineRGBA(pSelector->m_pScreen, left, bottom, right, bottom, SELECTOR_LINE_WIDTH, r, g, b, a);
   //Right
   thickLineRGBA(pSelector->m_pScreen, right, top, right, bottom, SELECTOR_LINE_WIDTH, r, g, b, a);
}

void Move(struct Selector* pSelector, enum Direction eDirection)
{
   switch( eDirection ) {
      default:
      case Up:
         if( pSelector->m_nCurrentY > 0 ) pSelector->m_nCurrentY--;
         break;
      case Down:
         if( pSelector->m_nCurrentY < (GetCrossHeight(pSelector->m_Cross)-1) ) pSelector->m_nCurrentY++;
         break;
      case Left:
         if( pSelector->m_nCurrentX > 0 ) pSelector->m_nCurrentX--;
         break;
      case Right:
	 if( pSelector->m_nCurrentX < (GetCrossWidth(pSelector->m_Cross)-1) ) pSelector->m_nCurrentX++;
         break;
   }
}

int GetCurrentX(struct Selector* pSelector)
{
   return pSelector->m_nCurrentX;
}

int GetCurrentY(struct Selector* pSelector)
{
   return pSelector->m_nCurrentY;
}

