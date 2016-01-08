#include "DataManager.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"

USING_NS_CC;

CDataManager* _dataManager = NULL;

CDataManager::CDataManager()
{
}


CDataManager::~CDataManager()
{
}


CDataManager* CDataManager::getInstance()
{
	if (_dataManager == NULL)
	{
		_dataManager = new CDataManager();
	}

	return _dataManager;
}


void CDataManager::LoadData()
{
	std::string strContent = FileUtils::getInstance()->getStringFromFile(SONG_CONFIG_PATH);
	
	rapidjson::Document oDoc;
	oDoc.Parse<0>(strContent.c_str());
	if (oDoc.HasParseError())
	{
		log("Parse Error: %s\n", oDoc.GetParseError());
		return;
	}

	for (int i = 0; i < oDoc["songs"].Size(); ++i)
	{
		SongData stSongData;
		stSongData.iSongID = oDoc["songs"][i]["id"].GetInt();
		stSongData.strSongName = oDoc["songs"][i]["name"].GetString();
		stSongData.strAuthor = oDoc["songs"][i]["author"].GetString();

		if (!oDoc["songs"][i]["data"].IsNull())
		{
			for (int j = 0; j < oDoc["songs"][i]["data"].Size(); ++j)
			{
				StageData stStageData;
				stStageData.fDelay = oDoc["songs"][i]["data"][j]["delay"].GetDouble();

				for (int k = 0; k < oDoc["songs"][i]["data"][j]["stage"].Size(); ++k)
				{
					ArrowData stArrow;
					for (int l = 0; l < oDoc["songs"][i]["data"][j]["stage"][k].Size(); ++l)
					{
						stArrow.arrArrow[l] = oDoc["songs"][i]["data"][j]["stage"][k][l].GetInt();
					}

					stStageData.vecArrowData.push_back(stArrow);
				}

				stSongData.vecStageData.push_back(stStageData);
			}
		}

		m_vecSongData.push_back(stSongData);
	}
}


int CDataManager::GetStageCount(int iSongID)
{
	VECTOR_SONGDATA_ITER pIter = m_vecSongData.begin();
	for (; pIter != m_vecSongData.end(); ++pIter)
	{
		if (pIter->iSongID == iSongID)
		{
			return pIter->vecStageData.size();
		}
	}

	return 0;
}


StageData* CDataManager::GetStageData(int iSongID, int iStageIndex)
{
	VECTOR_SONGDATA_ITER pIter = m_vecSongData.begin();
	for (; pIter != m_vecSongData.end(); ++pIter)
	{
		if (pIter->iSongID == iSongID)
		{
			VECTOR_STAGEDATA_ITER pStageIter = pIter->vecStageData.begin();
			int iIndex = 0;
			while (pStageIter != pIter->vecStageData.end())
			{
				if (iIndex == iStageIndex)
				{
					return &(*pStageIter);
				}

				++pStageIter;
				++iIndex;
			}
		}
	}

	return NULL;
}


float CDataManager::GetStageDelay(int iSongID, int iStageIndex)
{
	StageData* pStageData = GetStageData(iSongID, iStageIndex);
	assert(pStageData != NULL);
	return pStageData->fDelay;
}


ArrowData* CDataManager::GetArrowData(int iSongID, int iStageIndex, int iArrowIndex)
{
	StageData* pStageData = GetStageData(iSongID, iStageIndex);
	assert(pStageData != NULL);

	VECTOR_ARROWDATA_ITER pArrowIter = pStageData->vecArrowData.begin();
	int iIndex= 0;
	while (pArrowIter != pStageData->vecArrowData.end())
	{
		if (iArrowIndex == iIndex)
		{
			return &(*pArrowIter);
		}

		++pArrowIter;
		++iIndex;
	}

	return NULL;
}
