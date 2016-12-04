#ifndef FONT_H
#define FONT_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"

#ifndef _TINSPIRE
#include <SDL/SDL_ttf.h>
#endif

#ifdef _TINSPIRE
typedef nSDL_Font Font;
#else
typedef TTF_Font  Font;
#define NSDL_FONT_THIN  (-1)
#endif

Font* LoadFont(char* pstrName, int nID, int r, int g, int b, int size);
void FreeFont(Font* pFont);
void DrawText(SDL_Surface* pSurface, Font* pFont, int x, int y, char* pstrBuffer, int r, int g, int b);

#endif

