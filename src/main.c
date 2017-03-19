#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include <SDL/SDL.h>
#include "Startup.h"
#include "MainMenu.h"
#include "Game.h"
#include "Options.h"
#include "Help.h"
#include "Config.h"
#include "Levels.h"
#ifndef _TINSPIRE
#include <SDL/SDL_ttf.h>
#endif

#ifdef _WIN32
#define SCREEN_WIDTH	(320)
#define SCREEN_HEIGHT	(240)
#endif

#define SCREEN_BIT_DEPTH        (16)
#ifdef _TINSPIRE
#define SCREEN_VIDEO_MODE (SDL_SWSURFACE|SDL_FULLSCREEN|SDL_HWPALETTE)
#else
#define SCREEN_VIDEO_MODE (SDL_SWSURFACE|SDL_HWPALETTE)
#endif

#ifdef _WIN32
int WinMain(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
#ifdef _TINSPIRE
   ArchiveSetCurrentDirectory( argv[0] );
   if( argc != 2 ) {
      if( !config_file_already_written() ) {
         write_config_file();
      }
   }
#endif

   printf("Initializing SDL.\n");

   /* Initialize the SDL library (starts the event loop) */
   if ( SDL_Init(SDL_INIT_VIDEO ) < 0 )
   {
      fprintf(stderr,
              "Couldn't initialize SDL: %s\n", SDL_GetError());
      exit(1);
   }

   printf("SDL initialized.\n");

   SDL_Surface* pScreen = NULL;
   pScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SCREEN_VIDEO_MODE);

   //HSSetCurrentDirectory(argv[0]);

   if( pScreen == NULL )
   {
      fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SDL_GetError());
      exit(1);
   }
   else
   {
      /* Hides the cursor */
      SDL_ShowCursor(SDL_DISABLE);
   }

#ifndef _TINSPIRE
   //Initialize SDL_ttf
   if (TTF_Init() == -1)
   {
      exit(1);
   }
#endif

   int nLevelNumber = -1;
   char strLevelData[2048];
   struct Config* pConfig = NULL;
#ifdef _TINSPIRE
   CreateConfig(&pConfig);
#endif
   while(1) {
      int bShowHelp = 0, bShowOptions = 0;
      /*if( argc != 2 )*/ {
         struct MainMenu* pMenu = NULL;
         int bShouldQuit = 0;
         CreateMainMenu(&pMenu, nLevelNumber, pConfig, pScreen);
         while(MainMenuLoop(pMenu)){}
         bShouldQuit = MainMenuShouldQuit(pMenu);
         bShowOptions = MainMenuShowOptions(pMenu);
         bShowHelp = MainMenuShowHelp(pMenu);
         if( bShouldQuit == 0 && bShowOptions == 0 && bShowHelp == 0 ) {
            nLevelNumber = MainMenuGetLevelNum(pMenu);
	    printf("Loading level: %d\n", nLevelNumber);
            LevelLoad(strLevelData, nLevelNumber);
         }
         FreeMainMenu(&pMenu);

         if( bShouldQuit )
            break;
      }
      /*else {
         FILE *fp = fopen(argv[1], "r");
         if (!fp) { return 0; }
         struct stat filestat;
         if (stat(argv[1],&filestat) == -1) { fclose(fp); return 0; }

         fread(strLevelData, 1, filestat.st_size, fp);

         strLevelData[filestat.st_size] = 0;

         fclose(fp);
      }*/

      if( bShowOptions ) {
         struct Options* pOptions = NULL;
         CreateOptions(&pOptions, pConfig, pScreen);
         while(OptionsLoop(pOptions)){}
         FreeOptions(&pOptions);
         continue;
      }
      else if( bShowHelp ) {
         struct Help* pHelp = NULL;
         CreateHelp(&pHelp, pScreen);
         while(HelpLoop(pHelp)){}
         FreeHelp(&pHelp);
         continue;
      }
      else {
         struct Game* pGame = NULL;
         int bShouldQuit = 0;
         CreateGame(&pGame, strLevelData, nLevelNumber, pConfig, pScreen);
         while(GameLoop(pGame)){}
         bShouldQuit = GameShouldQuit(pGame);
         FreeGame(&pGame);

         if( bShouldQuit )
            break;
         if( nLevelNumber == -1 )
            break;
      }
   }

#ifdef _TINSPIRE
   FreeConfig(&pConfig);
#endif

   printf("Quitting SDL.\n");

#ifndef _TINSPIRE
   //Quit SDL_ttf
   TTF_Quit();
#endif

   /* Shutdown all subsystems */
   SDL_Quit();

   printf("Quitting...\n");

   return 0;
}
