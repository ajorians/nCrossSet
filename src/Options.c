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

   pOptions->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 0x00/*R*/, 0x00/*G*/, 0x00/*B*/, 12);
   pOptions->m_nCurrentOption = 0;

   pOptions->m_pConfig = pConfig;
   pOptions->m_pScreen = pScreen;
}

void FreeOptions(struct Options** ppOptions)
{
    struct Options* pOptions = *ppOptions;
    
    FreeFont(pOptions->m_pFont);
    
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
		  if( pOptions->m_nCurrentOption > 0 )
                     pOptions->m_nCurrentOption--;
		  break;

	       case SDLK_DOWN:
		  if( pOptions->m_nCurrentOption < 1 )
                     pOptions->m_nCurrentOption++;
		  break;

               case SDLK_SPACE:
               case SDLK_RETURN:
               case SDLK_LCTRL:
		  if( pOptions->m_nCurrentOption == 0 ) {
                     SetLockHint(pOptions->m_pConfig, GetLockHint(pOptions->m_pConfig) == 1 ? 0 : 1);
		  }
		  else if( pOptions->m_nCurrentOption == 1 ) {
                     SetDrawBackground(pOptions->m_pConfig, GetDrawBackground(pOptions->m_pConfig) == 1 ? 0 : 1);
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

void UpdateOptionsDisplay(struct Options* pOptions)
{
   SDL_Rect DestRect;
   DestRect.x = 0;
   DestRect.y = 0;
   DestRect.w = SCREEN_WIDTH;
   DestRect.h = SCREEN_HEIGHT;
   SDL_FillRect(pOptions->m_pScreen, &DestRect, SDL_MapRGB(pOptions->m_pScreen->format, 0x87, 0xCE, 0xEB));
   
    DrawText(pOptions->m_pScreen, pOptions->m_pFont, 10, 10,  "Options:", 255, 255, 255);
    
    DrawText(pOptions->m_pScreen, pOptions->m_pFont, 10, 30,  "Red text lock hints:", 255, 255, 255);
    if( GetLockHint(pOptions->m_pConfig) == 1 ) {
       DrawText(pOptions->m_pScreen, pOptions->m_pFont, 180, 30,  "On", 255, 255, 255);
    } else {
       DrawText(pOptions->m_pScreen, pOptions->m_pFont, 180, 30,  "Off", 255, 255, 255);
    }
    
    if( pOptions->m_nCurrentOption == 0 )
       draw_rectangle(pOptions->m_pScreen, SDL_MapRGB(pOptions->m_pScreen->format, 255, 0, 0), 8, 25, 210, 22, 1);
    
    DrawText(pOptions->m_pScreen, pOptions->m_pFont, 10, 50,  
"When you lock a cell's value\n\
numbers on cells in that row/column\n\
are marked red.", 255, 255, 255);

    DrawText(pOptions->m_pScreen, pOptions->m_pFont, 10, 110, "Animated background:", 255, 255, 255);
    if( GetDrawBackground(pOptions->m_pConfig) == 1 ) {
       DrawText(pOptions->m_pScreen, pOptions->m_pFont, 180, 110, "On", 255, 255, 255);
    } else {
       DrawText(pOptions->m_pScreen, pOptions->m_pFont, 180, 110, "Off", 255, 255, 255);
    }
    
    DrawText(pOptions->m_pScreen, pOptions->m_pFont, 10, 130,
"Whether the background moves\n\
during the game.", 255, 255, 255);

    if( pOptions->m_nCurrentOption == 1 )
       draw_rectangle(pOptions->m_pScreen, SDL_MapRGB(pOptions->m_pScreen->format, 255, 0, 0), 8, 105, 210, 22, 1);

   SDL_UpdateRect(pOptions->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int OptionsLoop(struct Options* pOptions)
{
   if( PollOptionsEvents(pOptions) == 0 )
      return 0;

   UpdateOptionsDisplay(pOptions);

   return 1;
}

