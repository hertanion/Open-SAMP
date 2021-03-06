/*

SA:MP Multiplayer Modification
Copyright 2004-2005 SA:MP Team

*/

#include "../main.h"
#include "../game/util.h"

CObjectPool::CObjectPool()
{
	for(BYTE byteObjectID = 0; byteObjectID < MAX_OBJECTS; byteObjectID++)
	{
		m_bObjectSlotState[byteObjectID]	= false;
		m_pObjects[byteObjectID]			= NULL;
	}
};

CObjectPool::~CObjectPool()
{
	for(int i = 0; i < MAX_OBJECTS; i++)
	{
		Delete(i);
	}
}

bool CObjectPool::Delete(BYTE byteObjectID)
{
	if(!GetSlotState(byteObjectID) || !m_pObjects[byteObjectID])
	{
		return false; // Vehicle already deleted or not used.
	}

	m_bObjectSlotState[byteObjectID] = false;
	delete m_pObjects[byteObjectID];
	m_pObjects[byteObjectID] = NULL;

	return true;
}

bool CObjectPool::New(byte byteObjectID, int iModel, VECTOR vecPos, VECTOR vecRot, float fDrawDist)
{
	if (m_pObjects[byteObjectID] != NULL)
	{
		Delete(byteObjectID);
	}

	m_pObjects[byteObjectID] = pGame->NewObject(iModel, vecPos.X, vecPos.Y, vecPos.Z, vecRot, fDrawDist);

	if (m_pObjects[byteObjectID])
	{
		m_bObjectSlotState[byteObjectID] = true;

		return true;
	}

	return false; // Will only be called if m_pObjects[byteObjectID] is null
}

//----------------------------------------------------

int CObjectPool::FindIDFromGtaPtr(ENTITY_TYPE * pGtaObject)
{
	int x=1;

	while(x!=MAX_OBJECTS) {
		if(pGtaObject == m_pObjects[x]->m_pEntity) return x;
		x++;
	}

	return (-1);
}

void CObjectPool::Process()
{
	static unsigned long s_ulongLastCall = 0;
	if (!s_ulongLastCall) s_ulongLastCall = GetTickCount();
	unsigned long ulongTick = GetTickCount();
	float fElapsedTime = ((float)(ulongTick - s_ulongLastCall)) / 1000.0f;
	// Get elapsed time in seconds
	for (BYTE i = 0; i < MAX_OBJECTS; i++)
	{
		if (m_bObjectSlotState[i]) m_pObjects[i]->Process(fElapsedTime);
	}
	s_ulongLastCall = ulongTick;
}