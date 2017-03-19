#ifndef MENUITEM_H
#define MENUITEM_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"
#include <CrossLib/CrossLib.h>
#include "StarDrawer.h"

enum MenuItemType
{
   Category,
   Level,
   Configuration
};

struct MenuItem
{
   int m_nX;
   enum MenuItemType m_eMenuType;
   int m_nSelected;
   char m_Text[8];
   char m_SubText[8];
};

void CreateMenuItem(struct MenuItem* pMenuItem, int x, char* pstrText, char* pstrSubText, enum MenuItemType eMenuType);
void FreeMenuItem(struct MenuItem* pMenuItem);
void SetMenuItemSelected(struct MenuItem* pMenuItem, int nSelected);
void MenuItemDraw(struct MenuItem* pMenuItem, struct SDL_Surface* pScreen, struct StarDrawer* pStarDrawer);

#endif

