#ifndef CROSSLIB_H_INCLUDED
#define CROSSLIB_H_INCLUDED

typedef void* CrossLib;

#define CROSSLIB_OK			(0)
#define CROSSLIB_BADARGUMENT		(-1)
#define CROSSLIB_OUT_OF_MEMORY		(-2)
#define CROSSLIB_NOT_PUZZLE_FILE	(-3)

#define CROSSLIB_MARKED			(1)
#define CROSSLIB_NOT_MARKED		(0)

//////////////////////////////////////////////
//Initalization/Error checking/Mode functions
//////////////////////////////////////////////
int CrossLibCreate(CrossLib* api, const char* pstrFile);
int CrossLibFree(CrossLib* api);

int GetCrossLibError(CrossLib api);
void ClearCrossLibError(CrossLib api);

//////////////////////////////////////////////
//CrossLib related functions
//////////////////////////////////////////////
int GetCrossWidth(CrossLib api);
int GetCrossHeight(CrossLib api);
int GetCrossCellValueCount(CrossLib api, int nX, int nY);
int GetCrossCellValue(CrossLib api, int nX, int nY, int nIndex);
int GetCrossCellMarked(CrossLib api, int nX, int nY);

int ToggleCrossCellMarking(CrossLib api, int nX, int nY);
int ToggleCrossCellValue(CrossLib api, int nX, int nY);
#endif
