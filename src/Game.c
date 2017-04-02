#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include "Game.h"
#include "Replacements.h"
#include "YouWinGraphic.h"

void CreateGame(struct Game** ppGame, const char* pstrLevelData, int nLevelNum, struct Config* pConfig, struct SDL_Surface* pScreen)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   CrossLibCreate(&(pGame->m_Cross), pstrLevelData);
   pGame->m_nLevelNum = nLevelNum;
   pGame->m_pConfig = pConfig;
   pGame->m_bWon = IsCrossGameOver(pGame->m_Cross);

#ifdef _TINSPIRE
   pGame->m_pYouWinGraphic = nSDL_LoadImage(image_YouWin);
   SDL_SetColorKey(pGame->m_pYouWinGraphic, SDL_SRCCOLORKEY, SDL_MapRGB(pGame->m_pYouWinGraphic->format, 255, 255, 255));
#endif

   pGame->m_pScreen = pScreen;
   CreateBackground(&(pGame->m_pBackground), pGame->m_pScreen, pGame->m_pConfig, 1);
   pGame->m_pMetrics = NULL;
   CreateMetrics(&pGame->m_pMetrics, pGame->m_Cross);

   int nWidth = GetCrossWidth(pGame->m_Cross);
   int nHeight = GetCrossHeight(pGame->m_Cross);
   int nNumPtrs = nWidth * nHeight;
   pGame->m_apPieces = malloc(nNumPtrs*sizeof(struct Piece));
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         CreatePiece(pPiece, x, y, pGame->m_Cross, pGame->m_pMetrics, pConfig);
      }
   }

   pGame->m_pSelector = NULL;
   CreateSelector(&pGame->m_pSelector, pGame->m_pScreen, pGame->m_pConfig, pGame->m_pMetrics, pGame->m_Cross);

   pGame->m_bShouldQuit = 0;
}

void FreeGame(struct Game** ppGame)
{
   struct Game* pGame = *ppGame;

   int nWidth = GetCrossWidth(pGame->m_Cross);
   int nHeight = GetCrossHeight(pGame->m_Cross);
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         FreePiece(pPiece);
      }
   }
   free(pGame->m_apPieces);

#ifdef _TINSPIRE
   SDL_FreeSurface(pGame->m_pYouWinGraphic);
#endif
   FreeSelector(&pGame->m_pSelector);
   FreeBackground(&pGame->m_pBackground);
   FreeMetrics(&pGame->m_pMetrics);

   pGame->m_pConfig = NULL;//Does not own
   pGame->m_pScreen = NULL;//Does not own

   free(pGame);
   *ppGame = NULL;
}

void DrawBoard(struct Game* pGame)
{
   DrawBackground(pGame->m_pBackground);
#if 1
   int nWidth = GetCrossWidth(pGame->m_Cross);
   int nHeight = GetCrossHeight(pGame->m_Cross);

   //Draw pieces
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         PieceDraw(pPiece, pGame->m_pScreen);
      }
   }

   //Draw selector
   DrawSelector(pGame->m_pSelector);
   
   if( pGame->m_bWon == 1 ) {
      SDL_Rect rectYouWin;
      rectYouWin.x = (SCREEN_WIDTH - pGame->m_pYouWinGraphic->w)/2;
      rectYouWin.y = (SCREEN_HEIGHT - pGame->m_pYouWinGraphic->h)/2;
      rectYouWin.w = pGame->m_pYouWinGraphic->w;
      rectYouWin.h = pGame->m_pYouWinGraphic->h;
      SDL_BlitSurface(pGame->m_pYouWinGraphic, NULL, pGame->m_pScreen, &rectYouWin);
   }
#endif
   
   SDL_UpdateRect(pGame->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void UpdateGameWon(struct Game* pGame)
{
   if( pGame->m_bWon && pGame->m_nLevelNum > 0 && pGame->m_nLevelNum <= 56 ) {
#ifdef _TINSPIRE
      SetBeatLevel(pGame->m_pConfig, pGame->m_nLevelNum-1/*To 0-base*/, 1);
#endif
   }
}

int GamePollEvents(struct Game* pGame)
{
   SDL_Event event;
   while( SDL_PollEvent( &event ) ) {
      switch( event.type ) {
         case SDL_KEYDOWN:
            switch( event.key.keysym.sym) {
              case SDLK_ESCAPE:
                  return 0;
                  break;

               case SDLK_UP:
               case SDLK_8:
		  if( pGame->m_bWon != 1 ) {
                     Move(pGame->m_pSelector, Up);
		  }
                  break;

	       case SDLK_DOWN:
               case SDLK_2:
		  if( pGame->m_bWon != 1 ) {
                     Move(pGame->m_pSelector, Down);
		  }
                  break;

               case SDLK_LEFT:
               case SDLK_4:
		  if( pGame->m_bWon != 1 ) {
                     Move(pGame->m_pSelector, Left);
		  }
                  break;

               case SDLK_RIGHT:
               case SDLK_6:
		  if( pGame->m_bWon != 1 ) {
                     Move(pGame->m_pSelector, Right);
		  }
                  break;

               case SDLK_RETURN:
               case SDLK_LCTRL:
               case SDLK_RCTRL:
		  if( pGame->m_bWon != 1 ) {
                     ToggleCrossCellValue(pGame->m_Cross, GetCurrentX(pGame->m_pSelector), GetCurrentY(pGame->m_pSelector));

		     pGame->m_bWon = IsCrossGameOver(pGame->m_Cross);
		     UpdateGameWon(pGame);
		  }
                  break;

               case SDLK_LSHIFT:
               case SDLK_RSHIFT:
		  if( pGame->m_bWon != 1 ) {
                     ToggleCrossCellMarking(pGame->m_Cross, GetCurrentX(pGame->m_pSelector), GetCurrentY(pGame->m_pSelector));
		  }
                  break;

               case SDLK_a:
		  if( pGame->m_bWon != 1 ) {
                     CrossDoSolveStep(pGame->m_Cross);
		  }
                  break;

               default:
                  break;
            }
          default:
             break;
      }
   }
   return 1;
}

int GameLoop(struct Game* pGame)
{
   if( GamePollEvents(pGame) == 0 )
      return 0;

   DrawBoard(pGame);

   SDL_Delay(30);

   return 1;//pGame->m_bWon != CROSSLIB_GAMEOVER;
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

