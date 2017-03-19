#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#else
#endif
#include "MainMenu.h"
#include "Replacements.h"
//#include "StarDrawer.h"
//#include "LevelColors.h"

#ifndef _TINSPIRE
#define SCREEN_WIDTH	(320)
#define SCREEN_HEIGHT	(240)
#endif

void CreateMainMenu(struct MainMenu** ppMenu, int nLevelNum, struct Config* pConfig, struct SDL_Surface* pScreen)
{
   *ppMenu = malloc(sizeof(struct MainMenu));
   struct MainMenu* pMenu = (*ppMenu);
   pMenu->m_eChoice = Play;
   pMenu->m_nLevelNum = nLevelNum >= 1 ? nLevelNum : 1;

   for(unsigned int i=0; i<sizeof(pMenu->m_Levels)/sizeof(pMenu->m_Levels[0]); i++) {
      CreateMenuItem(&pMenu->m_Levels[i], i, Category);
   }
   
   for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
      CreateMenuItem(&pMenu->m_ChoiceLevels[i], i, Level);
   }

   //pMenu->m_pBackground = NULL;
   pMenu->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);

   pMenu->m_pConfig = pConfig;
   pMenu->m_pScreen = pScreen;
}

void FreeMainMenu(struct MainMenu** ppMenu)
{
   struct MainMenu* pMenu = *ppMenu;
   //FreeBackground(&pMenu->m_pBackground);
   FreeFont(pMenu->m_pFont);

   pMenu->m_pConfig = NULL;//Does not own
   pMenu->m_pScreen = NULL;//Does not own

   free(*ppMenu);
   *ppMenu = NULL;
}

int PollEvents(struct MainMenu* pMenu)
{
   SDL_Event event;
   while( SDL_PollEvent( &event ) )
   {
      switch( event.type )
      {
         case SDL_KEYDOWN:
            printf( "Key press detected\n" );
            switch( event.key.keysym.sym )
            {
               case SDLK_ESCAPE:
                  printf("Hit Escape!n");
                  pMenu->m_eChoice = Quit;
                  return 0;
                  break;

               case SDLK_LEFT:
                  pMenu->m_nLevelNum--;
                  break;

               case SDLK_RIGHT:
                  pMenu->m_nLevelNum++;
                  break;

               case SDLK_SPACE:
               case SDLK_RETURN:
               case SDLK_LCTRL:
                  return 0;
                  break;

               default:
                  break;
            }
      }
   }

   return 1;
}

void draw_rectangle(SDL_Surface* Surface, Uint32 color, Uint16 x, Uint16 y, Uint16 width, Uint16 height, Uint8 lnpx )
{
   SDL_Rect DestRect;

   // Draw the top line
   DestRect.x = x;
   DestRect.y = y;
   DestRect.w = width;
   DestRect.h = 1;
   SDL_FillRect (Surface, &DestRect, color);

   // Draw the bottum line
   DestRect.y = y+height-1;
   SDL_FillRect (Surface, &DestRect, color);

   // Draw the left line
   DestRect.y = y;
   DestRect.w = 1;
   DestRect.h = height;
   SDL_FillRect (Surface, &DestRect, color);

   // Draw the left line
   DestRect.x = x+width-1;
   SDL_FillRect (Surface, &DestRect, color);
}

void UpdateDisplay(struct MainMenu* pMenu)
{
   SDL_Rect DestRect;
   DestRect.x = 0;
   DestRect.y = 0;
   DestRect.w = SCREEN_WIDTH;
   DestRect.h = SCREEN_HEIGHT;
   SDL_FillRect(pMenu->m_pScreen, &DestRect, SDL_MapRGB(pMenu->m_pScreen->format, 255, 255, 255));

   for(unsigned int i=0; i<sizeof(pMenu->m_Levels)/sizeof(pMenu->m_Levels[0]); i++) {
      MenuItemDraw(&pMenu->m_Levels[i], pMenu->m_pScreen);
   }

   for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
      MenuItemDraw(&pMenu->m_ChoiceLevels[i], pMenu->m_pScreen);
   }

   char buffer[5];
   IntToA(buffer, 5, pMenu->m_nLevelNum);
   DrawText(pMenu->m_pScreen, pMenu->m_pFont, 50, 50, buffer, 0, 0, 0);

   if( pMenu->m_eChoice == Play )
      draw_rectangle(pMenu->m_pScreen, SDL_MapRGB(pMenu->m_pScreen->format, 255, 0, 0), 160, 145, 95, 26, 1);
   //else if( m_eChoice == HighScore )
      //draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 160, 172, 106, 24, 1);
   else if( pMenu->m_eChoice == Help )
      draw_rectangle(pMenu->m_pScreen, SDL_MapRGB(pMenu->m_pScreen->format, 255, 0, 0), 160, 199, 52, 25, 1);

   SDL_UpdateRect(pMenu->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int MainMenuLoop(struct MainMenu* pMenu)
{
   if( PollEvents(pMenu) == 0 )
      return 0;

   UpdateDisplay(pMenu);

   return 1;
}

int MainMenuShouldQuit(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Quit;
}

int MainMenuShowOptions(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Options;
}

int MainMenuShowHelp(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Help;
}

int MainMenuGetLevelNum(struct MainMenu* pMenu)
{
   return pMenu->m_nLevelNum;
}

