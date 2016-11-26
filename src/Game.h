#ifndef GAME_H
#define GAME_H

#include <CrossLib/CrossLib.h>
#include <SDL/SDL.h>
#include "Background.h"
//#include "StarDrawer.h"
#include "Config.h"
#include "Metrics.h"
#include "Piece.h"
#include "Selector.h"
//struct Metrics;
//struct Piece;
//struct Selector;
//struct Indicators;

struct Game
{
   CrossLib m_Cross;
   int m_nLevelNum;
   struct Config* m_pConfig;//Does not own
   int m_bWon;
   struct Metrics* m_pMetrics;
   struct Piece* m_apPieces;
   struct Selector* m_pSelector;
   //struct Indicators* m_pIndicators;
   int m_bShouldQuit;
   struct SDL_Surface* m_pScreen;//Does not own
   struct Background* m_pBackground;
   //struct StarDrawer* m_pStarDrawer;
};

void CreateGame(struct Game** ppGame, const char* pstrLevelData, int nLevelNum, struct Config* pConfig, struct SDL_Surface* pScreen);
void FreeGame(struct Game** ppGame);
int GameLoop(struct Game* pGame);
int GameShouldQuit(struct Game* pMenu);

#endif
