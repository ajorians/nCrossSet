#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#else
#endif
#include "Help.h"
#include "Replacements.h"

void CreateHelp(struct Help** ppHelp, struct SDL_Surface* pScreen)
{
   *ppHelp = malloc(sizeof(struct Help));
   struct Help* pHelp = (*ppHelp);

   pHelp->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 0x00/*R*/, 0x00/*G*/, 0x00/*B*/, 12);

   pHelp->m_pScreen = pScreen;
}

void FreeHelp(struct Help** ppHelp)
{
   struct Help* pHelp = *ppHelp;
   
   FreeFont(pHelp->m_pFont);
   pHelp->m_pScreen = NULL;//Does not own

   free(*ppHelp);
   *ppHelp = NULL; 
}

int PollHelpEvents(struct Help* pHelp)
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

void UpdateHelpDisplay(struct Help* pHelp)
{
   SDL_Rect DestRect;
   DestRect.x = 0;
   DestRect.y = 0;
   DestRect.w = SCREEN_WIDTH;
   DestRect.h = SCREEN_HEIGHT;
   SDL_FillRect(pHelp->m_pScreen, &DestRect, SDL_MapRGB(pHelp->m_pScreen->format, 0x87, 0xCE, 0xEB));

   DrawText(pHelp->m_pScreen, pHelp->m_pFont, 10, 10, 
"Help:\n\
\n\
To play use the ctrl key to toggle the \n\
cell's value.  Use the shift key to lock\n\
a cell's value to prevent accidental\n\
changes.\n\
\n\
You win when every row and column are\n\
set to contain unique values", 255, 255, 255);

   SDL_UpdateRect(pHelp->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int HelpLoop(struct Help* pHelp)
{
   if( PollHelpEvents(pHelp) == 0 )
      return 0;

   UpdateHelpDisplay(pHelp);

   return 1;
}

