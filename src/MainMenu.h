#ifndef MAINMENU_H
#define MAINMENU_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"
//#include "Background.h"
#include "Config.h"
#include "MenuItem.h"
#include "Font.h"

//#define SHOW_LEVEL_DIMENSIONS

enum MenuChoice
{
   Play,
   Options,
   Help,
   Quit
};

struct MainMenu
{
   enum MenuChoice m_eChoice;
   int m_nLevelNum;
   struct MenuItem m_Levels[7];
   struct MenuItem m_ChoiceLevels[8];
   //struct Background* m_pBackground;
   Font *m_pFont;
   struct Config* m_pConfig;//Does not own
   struct SDL_Surface* m_pScreen;//Does not own
};

void CreateMainMenu(struct MainMenu** ppMenu, int nLevelNum, struct Config* pConfig, struct SDL_Surface* pScreen);
void FreeMainMenu(struct MainMenu** ppMenu);
int MainMenuLoop(struct MainMenu* pMenu);
int MainMenuShouldQuit(struct MainMenu* pMenu);
int MainMenuShowOptions(struct MainMenu* pMenu);
int MainMenuShowHelp(struct MainMenu* pMenu);
int MainMenuGetLevelNum(struct MainMenu* pMenu);

#endif
