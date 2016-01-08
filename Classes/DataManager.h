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
	typedef std::vector<SongData> VECTOR_SONGDATA;
	typedef VECTOR_SONGDATA::iterator VECTOR_SONGDATA_ITER;
	typedef std::vector<StageData> VECTOR_STAGEDATA;
	typedef VECTOR_STAGEDATA::iterator VECTOR_STAGEDATA_ITER;
	typedef std::vector<ArrowData> VECTOR_ARROWDATA;
	typedef VECTOR_ARROWDATA::iterator VECTOR_ARROWDATA_ITER;

private:
	std::vector<SongData> m_vecSongData;
};

