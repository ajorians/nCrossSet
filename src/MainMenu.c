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

void UpdateSelectedItems(struct MainMenu* pMenu);
void FreeLevelMenuItems(struct MainMenu* pMenu);
void CreateLevelMenuItems(struct MainMenu* pMenu);

void CreateMainMenu(struct MainMenu** ppMenu, int nLevelNum, struct Config* pConfig, struct SDL_Surface* pScreen)
{
   *ppMenu = malloc(sizeof(struct MainMenu));
   struct MainMenu* pMenu = (*ppMenu);
   pMenu->m_eChoice = Play;
   pMenu->m_eSelection = Levels;
   pMenu->m_nLevelNum = nLevelNum >= 1 ? nLevelNum : 1;
   pMenu->m_nCurrentCategory = (pMenu->m_nLevelNum-1) / 8;
   pMenu->m_nCurrentLevel = (pMenu->m_nLevelNum-1) - (pMenu->m_nCurrentCategory * 8);

   CreateLevelMenuItems(pMenu);

   CreateMenuItem(&pMenu->m_Options, 0, "Options", "", Configuration);
   CreateMenuItem(&pMenu->m_Help, 1, "Help", "", Configuration);

   UpdateSelectedItems(pMenu);

   //pMenu->m_pBackground = NULL;
   pMenu->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);

   pMenu->m_pConfig = pConfig;
   pMenu->m_pScreen = pScreen;
}

void FreeMainMenu(struct MainMenu** ppMenu)
{
   struct MainMenu* pMenu = *ppMenu;
 
   FreeLevelMenuItems(pMenu);

   FreeMenuItem(&pMenu->m_Options);
   FreeMenuItem(&pMenu->m_Help);
   
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
                  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel > 0 ) {
                        pMenu->m_nCurrentLevel--;
                        pMenu->m_nLevelNum--;
			UpdateSelectedItems(pMenu);
		     } 
		  }
		  else if( pMenu->m_eSelection == Categories ) {
                     if( pMenu->m_nCurrentCategory > 0 ) {
                        pMenu->m_nCurrentCategory--;
                        pMenu->m_nCurrentLevel = 0;
                        UpdateSelectedItems(pMenu);
                     }
                  }
                  else if( pMenu->m_eSelection == Other && pMenu->m_eChoice == Help ) {
                      pMenu->m_eChoice = Options;
                      UpdateSelectedItems(pMenu);
                  }
                  break;

               case SDLK_RIGHT:
		  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel < 7 ) {
                        pMenu->m_nCurrentLevel++;
                        pMenu->m_nLevelNum++;
			UpdateSelectedItems(pMenu);
                     }
		  }
		  else if( pMenu->m_eSelection == Categories ) {
                     if( pMenu->m_nCurrentCategory < 6 ) {
                        pMenu->m_nCurrentCategory++;
			pMenu->m_nCurrentLevel = 0;
			UpdateSelectedItems(pMenu);
		     }
		  }
		  else if( pMenu->m_eSelection == Other && pMenu->m_eChoice == Options ) {
                      pMenu->m_eChoice = Help;
                      UpdateSelectedItems(pMenu);
                  }
                  break;

	       case SDLK_UP:
		  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel < 4 ) {
                        pMenu->m_eSelection = Categories;
                        UpdateSelectedItems(pMenu);
		     }
		     else {
                        pMenu->m_nCurrentLevel -= 4;
			UpdateSelectedItems(pMenu);
		     }
		  }
                  else if( pMenu->m_eSelection == Categories ) {
		  }
		  else if( pMenu->m_eSelection == Other )
                  {
                      pMenu->m_eSelection = Levels;
                      UpdateSelectedItems(pMenu);
                  }
		  break;

	       case SDLK_DOWN:
		  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel < 4 ) {
                        pMenu->m_nCurrentLevel += 4;
			UpdateSelectedItems(pMenu);
		     }
		     else {
                        pMenu->m_eSelection = Other;
                        pMenu->m_eChoice = Options;
                        UpdateSelectedItems(pMenu);
		     }
                  }
		  else if( pMenu->m_eSelection == Categories ) {
                     pMenu->m_eSelection = Levels;
                     FreeLevelMenuItems(pMenu);
                     CreateLevelMenuItems(pMenu);
		     UpdateSelectedItems(pMenu);
                  }
		  break;

               case SDLK_SPACE:
               case SDLK_RETURN:
               case SDLK_LCTRL:
		  if( pMenu->m_eSelection == Levels ) {
                     return 0;
		  }
		  else if( pMenu->m_eSelection == Categories ) {
                     pMenu->m_eSelection = Levels;
                     FreeLevelMenuItems(pMenu);
                     CreateLevelMenuItems(pMenu);
		     UpdateSelectedItems(pMenu);
		  }
		  else if( pMenu->m_eSelection == Other ) {
                      return 0;
                  }
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

   if( pMenu->m_eSelection != Categories ) {
      for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
         MenuItemDraw(&pMenu->m_ChoiceLevels[i], pMenu->m_pScreen);
      }
   }

   MenuItemDraw(&pMenu->m_Options, pMenu->m_pScreen);
   MenuItemDraw(&pMenu->m_Help, pMenu->m_pScreen);

   /*char buffer[5];
   IntToA(buffer, 5, pMenu->m_nLevelNum);
   DrawText(pMenu->m_pScreen, pMenu->m_pFont, 50, 50, buffer, 0, 0, 0);

   if( pMenu->m_eChoice == Play )
      draw_rectangle(pMenu->m_pScreen, SDL_MapRGB(pMenu->m_pScreen->format, 255, 0, 0), 160, 145, 95, 26, 1);
   //else if( m_eChoice == HighScore )
      //draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 160, 172, 106, 24, 1);
   else if( pMenu->m_eChoice == Help )
      draw_rectangle(pMenu->m_pScreen, SDL_MapRGB(pMenu->m_pScreen->format, 255, 0, 0), 160, 199, 52, 25, 1);
*/
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

void UpdateSelectedItems(struct MainMenu* pMenu)
{
   for(unsigned int i=0; i<sizeof(pMenu->m_Levels)/sizeof(pMenu->m_Levels[0]); i++) {
      SetMenuItemSelected(&pMenu->m_Levels[i], 0);
   }

   for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
      SetMenuItemSelected(&pMenu->m_ChoiceLevels[i], 0);
   }
   
   SetMenuItemSelected(&pMenu->m_Options, 0);
   SetMenuItemSelected(&pMenu->m_Help,  0);

   if( pMenu->m_eSelection == Levels || pMenu->m_eSelection == Categories ) {
      SetMenuItemSelected(&pMenu->m_Levels[pMenu->m_nCurrentCategory], pMenu->m_eSelection == Levels ? 2 : 1);
      SetMenuItemSelected(&pMenu->m_ChoiceLevels[pMenu->m_nCurrentLevel], 1);
   }
   else if( pMenu->m_eSelection == Other ) {
       SetMenuItemSelected(&pMenu->m_Options, pMenu->m_eChoice == Options ? 1 : 0);
       SetMenuItemSelected(&pMenu->m_Help, pMenu->m_eChoice == Help ? 1 : 0);
   }
}

void FreeLevelMenuItems(struct MainMenu* pMenu)
{
    for(unsigned int i=0; i<sizeof(pMenu->m_Levels)/sizeof(pMenu->m_Levels[0]); i++) {
      FreeMenuItem(&pMenu->m_Levels[i]);
   }
   
   for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
      FreeMenuItem(&pMenu->m_ChoiceLevels[i]);
   }
}

void CreateLevelMenuItems(struct MainMenu* pMenu)
{
   static char buffer[8]; 
   for(unsigned int i=0; i<sizeof(pMenu->m_Levels)/sizeof(pMenu->m_Levels[0]); i++) {
      buffer[0] = i+1 + '0';
      buffer[1] = '\0';
      CreateMenuItem(&pMenu->m_Levels[i], i, buffer, "8/8", Category);
   }
   
   for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
      buffer[0] = pMenu->m_nCurrentCategory+1 + '0';
      buffer[1] = '-';
      buffer[2] = i+1 + '0';
      buffer[3] = '\0';
      CreateMenuItem(&pMenu->m_ChoiceLevels[i], i, buffer, "4x4", Level);
   }
}
