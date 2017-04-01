#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#else
#endif
#include "MainMenu.h"
#include "Replacements.h"
#include "Levels.h"
#include "MenuGraphic.h"

void UpdateSelectedItems(struct MainMenu* pMenu);
void FreeLevelMenuItems(struct MainMenu* pMenu);
void CreateLevelMenuItems(struct MainMenu* pMenu);

void CreateMainMenu(struct MainMenu** ppMenu, int nLevelNum, struct Config* pConfig, struct SDL_Surface* pScreen)
{
   *ppMenu = malloc(sizeof(struct MainMenu));
   struct MainMenu* pMenu = (*ppMenu);

   pMenu->m_pConfig = pConfig;
   pMenu->m_pScreen = pScreen;

   pMenu->m_eChoice = Play;
   pMenu->m_eSelection = Levels;
   pMenu->m_nLevelNum = nLevelNum >= 1 ? nLevelNum : 1;
   pMenu->m_nCurrentCategory = (pMenu->m_nLevelNum-1) / 8;
   pMenu->m_nCurrentLevel = (pMenu->m_nLevelNum-1) - (pMenu->m_nCurrentCategory * 8);

   CreateLevelMenuItems(pMenu);

   CreateMenuItem(&pMenu->m_Options, 0, "Options", "", Configuration);
   CreateMenuItem(&pMenu->m_Help, 1, "Help", "", Configuration);

   UpdateSelectedItems(pMenu);

   CreateBackground(&(pMenu->m_pBackground), pMenu->m_pScreen, pMenu->m_pConfig, 0);
   pMenu->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);

   CreateStarDrawer( &pMenu->m_pStarDrawer );

#ifdef _TINSPIRE
   pMenu->m_pTitle = nSDL_LoadImage(image_Title);
#endif
}

void FreeMainMenu(struct MainMenu** ppMenu)
{
   struct MainMenu* pMenu = *ppMenu;
 
   FreeLevelMenuItems(pMenu);

   FreeMenuItem(&pMenu->m_Options);
   FreeMenuItem(&pMenu->m_Help);
   
   FreeBackground(&pMenu->m_pBackground);
   FreeFont(pMenu->m_pFont);

   FreeStarDrawer( &pMenu->m_pStarDrawer );

   pMenu->m_pConfig = NULL;//Does not own
   pMenu->m_pScreen = NULL;//Does not own

#ifdef _TINSPIRE
   SDL_FreeSurface(pMenu->m_pTitle);
   pMenu->m_pTitle = NULL;
#endif

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
			pMenu->m_nLevelNum -= 4;
			UpdateSelectedItems(pMenu);
		     }
		  }
                  else if( pMenu->m_eSelection == Categories ) {
		  }
		  else if( pMenu->m_eSelection == Other )
                  {
                      pMenu->m_eSelection = Levels;
		      pMenu->m_eChoice = Play;
                      UpdateSelectedItems(pMenu);
                  }
		  break;

	       case SDLK_DOWN:
		  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel < 4 ) {
                        pMenu->m_nCurrentLevel += 4;
			pMenu->m_nLevelNum += 4;
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
		     pMenu->m_nLevelNum = pMenu->m_nCurrentCategory * 8 + 1;
		     pMenu->m_nCurrentLevel = 0;
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
		     pMenu->m_nLevelNum = pMenu->m_nCurrentCategory * 8 + 1;
		     pMenu->m_nCurrentLevel = 0;
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

void UpdateDisplay(struct MainMenu* pMenu)
{
   DrawBackground(pMenu->m_pBackground);

#if 0
   SDL_Rect DestRect;
   DestRect.x = 0;
   DestRect.y = 0;
   DestRect.w = SCREEN_WIDTH;
   DestRect.h = SCREEN_HEIGHT;
   SDL_FillRect(pMenu->m_pScreen, &DestRect, SDL_MapRGB(pMenu->m_pScreen->format, 255, 255, 255));
#endif

#ifdef _TINSPIRE
   SDL_Rect rectSrc, rectDst;

   rectSrc.w = 320;
   rectSrc.h = 240;
   rectSrc.x = 0;
   rectSrc.y = 0;

   rectDst.w = 320;
   rectDst.h = 240;
   rectDst.x = 0;
   rectDst.y = 0;

   SDL_BlitSurface(pMenu->m_pTitle, &rectSrc, pMenu->m_pScreen, &rectDst);
#endif

   for(unsigned int i=0; i<sizeof(pMenu->m_Levels)/sizeof(pMenu->m_Levels[0]); i++) {
      MenuItemDraw(&pMenu->m_Levels[i], pMenu->m_pScreen, NULL);
   }

   if( pMenu->m_eSelection != Categories ) {
      for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
         int nLevel = (pMenu->m_nCurrentCategory*8)+i;
         int nBeatLevel =
#ifdef _TINSPIRE
            GetBeatLevel(pMenu->m_pConfig, nLevel);
#else
            0;
#endif
         MenuItemDraw(&pMenu->m_ChoiceLevels[i], pMenu->m_pScreen, nBeatLevel == 1 ? pMenu->m_pStarDrawer : NULL );
      }
   }

   MenuItemDraw(&pMenu->m_Options, pMenu->m_pScreen, NULL);
   MenuItemDraw(&pMenu->m_Help, pMenu->m_pScreen, NULL);

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
   static char bufferLevel[2048];

   for(unsigned int i=0; i<sizeof(pMenu->m_Levels)/sizeof(pMenu->m_Levels[0]); i++) {
      buffer[0] = i+1 + '0';
      buffer[1] = '\0';

      int nLevelsBeaten = 0;
      for(int j=0; j<(int)(sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0])); j++) {
         int nLevel = (i*8) + j;
#ifdef _TINSPIRE
         if( GetBeatLevel( pMenu->m_pConfig, nLevel) == 1 )
            nLevelsBeaten++;
#endif
      }
   
      char bufferLevelsBeaten[8];
      bufferLevelsBeaten[0] = nLevelsBeaten + '0';
      bufferLevelsBeaten[1] = '/';
      bufferLevelsBeaten[2] = '8';
      bufferLevelsBeaten[3] = '\0';
      CreateMenuItem(&pMenu->m_Levels[i], i, buffer, bufferLevelsBeaten, Category);
   }
   
   for(unsigned int i=0; i<sizeof(pMenu->m_ChoiceLevels)/sizeof(pMenu->m_ChoiceLevels[0]); i++) {
      buffer[0] = pMenu->m_nCurrentCategory+1 + '0';
      buffer[1] = '-';
      buffer[2] = i+1 + '0';
      buffer[3] = '\0';
      
      char bufferDimensions[8];

      LevelLoad(bufferLevel, (pMenu->m_nCurrentCategory*8)+i+1);
      CrossLib api;
      CrossLibCreate(&api, bufferLevel);
      bufferDimensions[0] = GetCrossWidth(api) + '0';
      bufferDimensions[1]='x';
      bufferDimensions[2] = GetCrossHeight(api) + '0';
      bufferDimensions[3] = '\0';
      CrossLibFree(&api);
      
      CreateMenuItem(&pMenu->m_ChoiceLevels[i], i, buffer, bufferDimensions, Level);
   }
}
