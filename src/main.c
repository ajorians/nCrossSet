#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Startup.h"
/*#include "MainMenu.h"
#include "Game.h"
#include "Options.h"
#include "Help.h"
#include "Config.h"
#include "Levels.h"*/

int main(int argc, char *argv[])
{
   ArchiveSetCurrentDirectory( argv[0] );
   if( argc != 2 ) {
      if( !config_file_already_written() ) {
         write_config_file();
      }
   }

/*   int nLevelNumber = -1;
   char strLevelData[2048];
   struct Config* pConfig = NULL;
   CreateConfig(&pConfig);
   while(1) {
      int bShowHelp = 0, bShowOptions = 0;
      if( argc != 2 ) {
         struct MainMenu* pMenu = NULL;
         int bShouldQuit = 0;
         CreateMainMenu(&pMenu, nLevelNumber, pConfig);
         while(MainMenuLoop(pMenu)){}
         bShouldQuit = MainMenuShouldQuit(pMenu);
         bShowOptions = MainMenuShowOptions(pMenu);
         bShowHelp = MainMenuShowHelp(pMenu);
         if( bShouldQuit == 0 && bShowOptions == 0 && bShowHelp == 0 ) {
            nLevelNumber = MainMenuGetLevelNum(pMenu);
            LevelLoad(strLevelData, nLevelNumber);
         }
         FreeMainMenu(&pMenu);

         if( bShouldQuit )
            break;
      }
      else {
         FILE *fp = fopen(argv[1], "r");
         if (!fp) { return 0; }
         struct stat filestat;
         if (stat(argv[1],&filestat) == -1) { fclose(fp); return 0; }

         fread(strLevelData, 1, filestat.st_size, fp);

         strLevelData[filestat.st_size] = 0;

         fclose(fp);
      }

      if( bShowOptions ) {
         struct Options* pOptions = NULL;
         CreateOptions(&pOptions, pConfig);
         while(OptionsLoop(pOptions)){}
         FreeOptions(&pOptions);
         continue;
      }
      else if( bShowHelp ) {
         struct Help* pHelp = NULL;
         CreateHelp(&pHelp, pConfig);
         while(HelpLoop(pHelp)){}
         FreeHelp(&pHelp);
         continue;
      }
      else {
         struct Game* pGame = NULL;
         int bShouldQuit = 0;
         CreateGame(&pGame, strLevelData, nLevelNumber, pConfig);
         while(GameLoop(pGame)){}
         bShouldQuit = GameShouldQuit(pGame);
         FreeGame(&pGame);

         if( bShouldQuit )
            break;
         if( nLevelNumber == -1 )
            break;
      }
   }

   FreeConfig(&pConfig);
*/
   return 0;
}
