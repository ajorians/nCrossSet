#ifndef SELECTOR_H
#define SELECTOR_H

#include <os.h>
#include <CrossLib/CrossLib.h>
#include "Metrics.h"

struct Selector
{
   int m_nCurrentX;
   int m_nCurrentY;
   CrossLib m_Cross;//Does not own
   struct SDL_Surface* m_pScreen;//Does not own
   struct Config* m_pConfig;//Does not own
   struct Metrics* m_pMetrics;//Does not own
};

void CreateSelector(struct Selector** ppSelector, struct SDL_Surface* pScreen, struct Config* pConfig, struct Metrics* pMetrics, CrossLib cross);
void FreeSelector(struct Selector** ppSelector);
void DrawSelector(struct Selector* pSelector);

enum Direction{Up, Down, Left, Right};
void Move(struct Selector* pSelector, enum Direction eDirection);

int GetCurrentX(struct Selector* pSelector);
int GetCurrentY(struct Selector* pSelector);
#endif

