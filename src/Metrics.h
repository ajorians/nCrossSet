#ifndef METRICS_H
#define METRICS_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include <CrossLib/CrossLib.h>

struct Metrics
{
   int m_nPieceWidth;
   int m_nPieceHeight;
   int m_nLeft;
   int m_nTop;
   CrossLib m_Cross;//Does not own
};

void CreateMetrics(struct Metrics** ppMetrics, CrossLib cross);
void FreeMetrics(struct Metrics** ppMetrics);
int GetPieceLeft(struct Metrics* pMetrics, int x, int y);
int GetPieceTop(struct Metrics* pMetrics, int x, int y);
int GetPieceWidth(struct Metrics* pMetrics, int x, int y);
int GetPieceHeight(struct Metrics* pMetrics, int x, int y);
int GetPieceTextLeft(struct Metrics* pMetrics,int x, int y);
int GetPieceTextTop(struct Metrics* pMetrics,int x, int y);

#endif

