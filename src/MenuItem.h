#ifndef MENUITEM_H
#define MENUITEM_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"
#include <CrossLib/CrossLib.h>
#include "Metrics.h"

enum MenuItemType
{
   Category,
   Level
};

struct MenuItem
{
   int m_nX;
   enum MenuItemType m_eMenuType;
   int m_nSelected;
};

void CreateMenuItem(struct MenuItem* pMenuItem, int x, enum MenuItemType eMenuType);
void FreeMenuItem(struct MenuItem* pMenuItem);
void SetMenuItemSelected(struct MenuItem* pMenuItem, int nSelected);
void MenuItemDraw(struct MenuItem* pMenuItem, struct SDL_Surface* pScreen);

#endif

