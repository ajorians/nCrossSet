#ifndef CONFIG_H
#define CONFIG_H

#ifdef _TINSPIRE
#include "ArchiveLib/ArchiveLib.h"

struct Config
{
   ArchiveLib m_Archive;
   int m_nBeatLevels[56];
   int m_nDrawBackground;
   int m_nLockHint;
};

void CreateConfig(struct Config** ppConfig);
void FreeConfig(struct Config** ppConfig);
void SetBeatLevel(struct Config* pConfig, int nLevelNum, int nBeat);
int GetBeatLevel(struct Config* pConfig, int nLevelNum);
int GetDrawBackground(struct Config* pConfig);
void SetDrawBackground(struct Config* pConfig, int nOn);

int GetLockHint(struct Config* pConfig);
void SetLockHint(struct Config* pConfig, int nOn);
#endif

#endif
