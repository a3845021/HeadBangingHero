#pragma once
#include "GlobalDef.h"
#include "cocos2d.h"

class CDataManager
{
public:
	CDataManager();
	~CDataManager();

	static CDataManager* getInstance();

	void LoadData();

	int GetStageCount(int iSongID);

	StageData* GetStageData(int iSongID, int iStageIndex);

	float GetStageDelay(int iSongID, int iStageIndex);

	ArrowData* GetArrowData(int iSongID, int iStageIndex, int iArrowIndex);

private:
	typedef std::map<int, SongData> TMAP_SONGDATA;
	typedef TMAP_SONGDATA::iterator TMAP_SONGDATA_ITER;
	typedef std::map<int, StageData> TMAP_STAGEDATA;
	typedef TMAP_STAGEDATA::iterator TMAP_STAGEDATA_ITER;
	typedef std::map<int, ArrowData> TMAP_ARROWDATA;
	typedef TMAP_ARROWDATA::iterator TMAP_ARROWDATA_ITER;

private:
	std::map<int, SongData> m_mapSongData;
};

