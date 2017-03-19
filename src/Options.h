#ifndef OPTIONS_H
#define OPTIONS_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"
//#include "Background.h"
#include "Config.h"
#include "Font.h"

struct Options
{
   struct Config* m_pConfig;//Does not own
   struct SDL_Surface* m_pScreen;//Does not own
};

void CreateOptions(struct Options** ppOptions, struct Config* pConfig, struct SDL_Surface* pScreen);
void FreeOptions(struct Options** ppOptions);
int OptionsLoop(struct Options* pOptions);

#endif
