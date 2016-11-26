#include "Metrics.h"

void CreateMetrics(struct Metrics** ppMetrics, CrossLib cross)
{
   *ppMetrics = malloc(sizeof(struct Metrics));
   struct Metrics* pMetrics = *ppMetrics;
   pMetrics->m_Cross = cross;

   int nWidth = GetCrossWidth(cross);
   int nHeight = GetCrossHeight(cross);

   int nMaxPieceWidth = (SCREEN_WIDTH - 10) / nWidth;
   int nMaxPieceHeight = (SCREEN_HEIGHT - 10) / nHeight;

   pMetrics->m_nPieceWidth = nMaxPieceWidth;
   pMetrics->m_nPieceHeight = nMaxPieceHeight;
   pMetrics->m_nLeft = 5;
   pMetrics->m_nTop = 5;
}

void FreeMetrics(struct Metrics** ppMetrics)
{
   struct Metrics* pMetrics = *ppMetrics;
   pMetrics->m_Cross = NULL;//Does not own

   free(pMetrics);
}

int GetPieceLeft(struct Metrics* pMetrics, int x, int y)
{
   return pMetrics->m_nLeft + x*pMetrics->m_nPieceWidth;
}

int GetPieceTop(struct Metrics* pMetrics, int x, int y)
{
   return pMetrics->m_nTop + y*pMetrics->m_nPieceHeight;
}

int GetPieceWidth(struct Metrics* pMetrics, int x, int y)
{
   return pMetrics->m_nPieceWidth;
}

int GetPieceHeight(struct Metrics* pMetrics, int x, int y)
{
   return pMetrics->m_nPieceHeight;
}
