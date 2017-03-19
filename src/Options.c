#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#else
#endif
#include "Options.h"
#include "Replacements.h"
//#include "StarDrawer.h"
//#include "LevelColors.h"

#ifndef _TINSPIRE
#define SCREEN_WIDTH	(320)
#define SCREEN_HEIGHT	(240)
#endif

void CreateOptions(struct Options** ppOptions, struct Config* pConfig, struct SDL_Surface* pScreen)
{
   *ppOptions = malloc(sizeof(struct Options));
   struct Options* pOptions = (*ppOptions);

   //pMenu->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);

   pOptions->m_pConfig = pConfig;
   pOptions->m_pScreen = pScreen;
}

void FreeOptions(struct Options** ppOptions)
{
    struct Options* pOptions = *ppOptions;
    
   pOptions->m_pConfig = NULL;//Does not own
   pOptions->m_pScreen = NULL;//Does not own

   free(*ppOptions);
   *ppOptions = NULL; 
}

int PollOptionsEvents(struct Options* pOptions)
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
                  return 0;
                  break;

               case SDLK_LEFT:
                  break;

               case SDLK_RIGHT:
                  break;

	       case SDLK_UP:
		  break;

	       case SDLK_DOWN:
		  break;

               case SDLK_SPACE:
               case SDLK_RETURN:
               case SDLK_LCTRL:
                  break;

               default:
                  break;
            }
      }
   }

   return 1;
}

void UpdateOptionsDisplay(struct Options* pOptions)
{
   SDL_Rect DestRect;
   DestRect.x = 0;
   DestRect.y = 0;
   DestRect.w = SCREEN_WIDTH;
   DestRect.h = SCREEN_HEIGHT;
   SDL_FillRect(pOptions->m_pScreen, &DestRect, SDL_MapRGB(pOptions->m_pScreen->format, 0, 0, 255));

   SDL_UpdateRect(pOptions->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int OptionsLoop(struct Options* pOptions)
{
   if( PollOptionsEvents(pOptions) == 0 )
      return 0;

   UpdateOptionsDisplay(pOptions);

   return 1;
}

