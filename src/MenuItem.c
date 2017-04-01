#include "MenuItem.h"

#include "Font.h"
#include "Replacements.h"

#define PIECE_BORDER_SIZE	(4)

#define USE_DIFFERENT_FONT

static Font* g_pFontMenuItem = NULL;

void CreateMenuItem(struct MenuItem* pMenuItem, int x, char* pstrText, char* pstrSubText, enum MenuItemType eMenuType)
{
   pMenuItem->m_nX = x;
   StringCopy(pMenuItem->m_Text, sizeof(pMenuItem->m_Text)/sizeof(pMenuItem->m_Text[0]), pstrText);
   StringCopy(pMenuItem->m_SubText, sizeof(pMenuItem->m_SubText)/sizeof(pMenuItem->m_SubText[0]), pstrSubText);
   pMenuItem->m_eMenuType = eMenuType;
   pMenuItem->m_nSelected = 0;

   if( g_pFontMenuItem == NULL ) {
      g_pFontMenuItem = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 127/*R*/, 127/*G*/, 127/*B*/, 12);
   }
}

void FreeMenuItem(struct MenuItem* pMenuItem)
{
   if( g_pFontMenuItem != NULL ) {

      FreeFont(g_pFontMenuItem);
      g_pFontMenuItem = NULL;
   }
}

void SetMenuItemSelected(struct MenuItem* pMenuItem, int nSelected)
{
   pMenuItem->m_nSelected = nSelected;
}

void MenuItemDraw(struct MenuItem* pMenuItem, struct SDL_Surface* pScreen, struct StarDrawer* pStarDrawer)
{
   SDL_Rect rect;

   if( pMenuItem->m_eMenuType == Category ) {
      rect.w = 43;
      rect.h = 50;
      int nNumLevels = 7;
      int nRemainder = SCREEN_WIDTH - (nNumLevels*rect.w);
      int nSlice = nRemainder / (nNumLevels+1);
      rect.x = nSlice*(pMenuItem->m_nX+1) + rect.w*(pMenuItem->m_nX);
      rect.y = 53;
   }
   else if( pMenuItem->m_eMenuType == Level ) {
      rect.w = 43;
      rect.h = 40;
      int nNumPerRow = 4;
      int nRemainder = SCREEN_WIDTH - (nNumPerRow*rect.w);
      int nSlice = nRemainder / (nNumPerRow+1);
      int nSpot = pMenuItem->m_nX > 3 ? pMenuItem->m_nX - 4 : pMenuItem->m_nX;
      int nY = pMenuItem->m_nX > 3 ? 165 : 115;
      rect.x = nSlice*(nSpot+1) + rect.w*(nSpot);
      rect.y = nY;
   }
   else {
      rect.w = 80;
      rect.h = 25;
      int nNumPerRow = 2;
      int nRemainder = SCREEN_WIDTH - (nNumPerRow*rect.w);
      int nSlice = nRemainder / (nNumPerRow+1);
      rect.x = nSlice*(pMenuItem->m_nX+1) + rect.w*(pMenuItem->m_nX);
      rect.y = 212;
   }

   if( pMenuItem->m_nSelected == 0 ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 255));
   } else if( pMenuItem->m_nSelected == 2 ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 0, 255));
   } else {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 0, 0));
   }

   rect.w -= PIECE_BORDER_SIZE;
   rect.h -= PIECE_BORDER_SIZE;
   rect.x += (PIECE_BORDER_SIZE/2);
   rect.y += (PIECE_BORDER_SIZE/2);

   if( pMenuItem->m_eMenuType == Category ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 0, 255));
   } else if( pMenuItem->m_eMenuType == Level ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 255, 0));
   } else {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 255, 255, 0));
   }

   rect.h -= 10;
   if( pMenuItem->m_eMenuType == Category ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 0, 200));
   } else if( pMenuItem->m_eMenuType == Level ) {
      SDL_FillRect(pScreen, &rect, SDL_MapRGB(pScreen->format, 0, 200, 0));
   }

   Font* pFont = g_pFontMenuItem;
   if( pMenuItem->m_eMenuType == Category ) {
      DrawText(pScreen, pFont, rect.x + 2, rect.y+3, "Level", 255, 255, 255);

     DrawText(pScreen, pFont, rect.x+14, rect.y+20, pMenuItem->m_Text, 255, 255, 255);
   } else if( pMenuItem->m_eMenuType == Level ) {
      DrawText(pScreen, pFont, rect.x + 7, rect.y+8, pMenuItem->m_Text, 255, 255, 255);
   } else {
      DrawText(pScreen, pFont, rect.x + 7, rect.y+8, pMenuItem->m_Text, 255, 255, 255);
   }

   if( pMenuItem->m_eMenuType == Category ) {
      DrawText(pScreen, pFont, rect.x+7, rect.y+rect.h, pMenuItem->m_SubText, 255, 255, 255);
   } else if( pMenuItem->m_eMenuType == Level ) {
      if( pStarDrawer != NULL )
         DrawStar(pStarDrawer, pScreen, rect.x-10, rect.y+rect.h/2-2);
      DrawText(pScreen, pFont, rect.x+7, rect.y+rect.h, pMenuItem->m_SubText, 255, 255, 255);
   }
}

 
