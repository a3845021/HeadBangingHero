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

private:
	std::vector<SongData> m_vecSongData;
};

