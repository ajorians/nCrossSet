#include "MenuItem.h"

#include "Font.h"

#define PIECE_BORDER_SIZE	(4)

#define USE_DIFFERENT_FONT

#ifdef USE_DIFFERENT_FONT
static Font* g_pFontBig = NULL;
static Font* g_pFontUsed = NULL;
#endif
static Font* g_pFont = NULL;

void CreateMenuItem(struct MenuItem* pMenuItem, int x, enum MenuItemType eMenuType)
{
   pMenuItem->m_nX = x;
   pMenuItem->m_eMenuType = eMenuType;

   if( g_pFont == NULL ) {
#ifdef USE_DIFFERENT_FONT
      g_pFontBig = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 255/*G*/, 255/*B*/, 12);
      g_pFontUsed = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);
#endif
      g_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 127/*R*/, 127/*G*/, 127/*B*/, 12);
   }
}

void FreeMenuItem(struct MenuItem* pMenuItem)
{
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

void MenuItemDraw(struct MenuItem* pMenuItem, struct SDL_Surface* pScreen)
{
   SDL_Rect rect;
   rect.w = 43;

   if( pMenuItem->m_eMenuType == Category ) {
      rect.h = 50;
      int nNumLevels = 7;
      int nRemainder = SCREEN_WIDTH - (nNumLevels*rect.w);
      int nSlice = nRemainder / (nNumLevels+1);
      rect.x = nSlice*(pMenuItem->m_nX+1) + rect.w*(pMenuItem->m_nX);
      rect.y = 30;
   }
   else {
      rect.h = 40;
      int nNumPerRow = 4;
      int nRemainder = SCREEN_WIDTH - (nNumPerRow*rect.w);
      int nSlice = nRemainder / (nNumPerRow+1);
      int nSpot = pMenuItem->m_nX > 3 ? pMenuItem->m_nX - 4 : pMenuItem->m_nX;
      int nY = pMenuItem->m_nX > 3 ? 150 : 100;
      rect.x = nSlice*(nSpot+1) + rect.w*(nSpot);
      rect.y = nY;
   }

   //if(  ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 255));
   //} else {
   //   SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 255));
   //}

   rect.w -= PIECE_BORDER_SIZE;
   rect.h -= PIECE_BORDER_SIZE;
   rect.x += (PIECE_BORDER_SIZE/2);
   rect.y += (PIECE_BORDER_SIZE/2);

   if( pMenuItem->m_eMenuType == Category ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 0, 255));
   } else {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 255, 0));
   }

   rect.h -= 10;
   if( pMenuItem->m_eMenuType == Category ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 0, 200));
   } else {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 200, 0));
   }

   static char buffer[8];

   Font* pFont = g_pFont;
   if( pMenuItem->m_eMenuType == Category ) {
      DrawText(pScreen, pFont, rect.x + 2, rect.y+3, "Level", 255, 255, 255);

     buffer[0] = (pMenuItem->m_nX+1) + '0';
     buffer[1] = '\0';
     DrawText(pScreen, pFont, rect.x+14, rect.y+20, buffer, 255, 255, 255);
   } else {
      DrawText(pScreen, pFont, rect.x + 7, rect.y+8, "1-1", 255, 255, 255);
   }

   if( pMenuItem->m_eMenuType == Category ) {
      strcpy(buffer, "8/8");
      DrawText(pScreen, pFont, rect.x+7, rect.y+rect.h, buffer, 255, 255, 255);
   } else {
      strcpy(buffer, "4x4");
      DrawText(pScreen, pFont, rect.x+7, rect.y+rect.h, buffer, 255, 255, 255);
   }
}

 
