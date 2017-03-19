#ifndef HELP_H
#define HELP_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"
//#include "Background.h"
#include "Config.h"
#include "Font.h"

struct Help
{
   struct SDL_Surface* m_pScreen;//Does not own
};

void CreateHelp(struct Help** ppHelp, struct SDL_Surface* pScreen);
void FreeHelp(struct Help** ppHelp);
int HelpLoop(struct Help* pHelp);

#endif
