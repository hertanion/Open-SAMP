//----------------------------------------------------------
//
// SA:MP Multiplayer Modification For GTA:SA
// Copyright 2004-2005 SA:MP team
//
// Version: $Id: netgame.h,v 1.12 2006/04/05 21:39:54 kyeman Exp $
//
//----------------------------------------------------------

#pragma once

#define GAMESTATE_NONE			0 // used for debugging modes and such
#define GAMESTATE_CONNECTING	1
#define GAMESTATE_CONNECTED		2
#define GAMESTATE_AWAIT_JOIN	3
#define GAMESTATE_DISCONNECTED  4
#define GAMESTATE_RESTARTING	5
#define GAMESTATE_WAIT_CONNECT	6

#define LOCAL_CLIENT_PORT		8150

//----------------------------------------------------

class CNetGame
{
private:

	void UpdateNetwork();

	// Packet handlers
	void Packet_AimSync(Packet *p);
	void Packet_PlayerSync(Packet *p);
	void Packet_VehicleSync(Packet *p);
	void Packet_PassengerSync(Packet *p);
	void Packet_ConnectionSucceeded(Packet *p);
	void Packet_RSAPublicKeyMismatch(Packet* packet);
	void Packet_ConnectionBanned(Packet* packet);
	void Packet_ConnectionRequestAccepted(Packet* packet);
	void Packet_NoFreeIncomingConnections(Packet* packet);
	void Packet_DisconnectionNotification(Packet* packet);
	void Packet_ConnectionLost(Packet* packet);
	void Packet_InvalidPassword(Packet* packet);
	void Packet_ModifiedPacket(Packet* packet);
	void Packet_AuthKey(Packet* packet);
	void Packet_ConnectAttemptFailed(Packet* packet);
	void Packet_TrailerSync(Packet *p);

public:

	CObjectPool			*m_pObjectPool;
	CMenuPool			*m_pMenuPool;
	CTextDrawPool		*m_pTextDrawPool;
	CGangZonePool		*m_pGangZonePool;
	CPlayerPool			*m_pPlayerPool;
	CPickupPool			*m_pPickupPool;
	CVehiclePool		*m_pVehiclePool;
	CActorPool			*m_pActorPool;
	CLabelPool			*m_pLabelPool;
	RakClientInterface	*m_pRakClient;	

	char m_szHostName[0xFF];
	char m_szHostOrIp[0x7F];
	int m_iPort;

	int					m_iGameState;
	uint32_t			m_dwLastConnectAttempt;
	uint32_t			m_dwMapIcons[200];

	bool		m_bZoneNames;
	bool		m_bUseCJWalk;
	bool		m_bAllowWeapons;
	bool		m_bLimitGlobalChatRadius;
	float		m_fGlobalChatRadius;
	float 		m_fNameTagDrawDistance;
	bool		m_bDisableEnterExits;
	bool		m_bNameTagLOS;
	bool		m_bManualVehicleEngineAndLight;
	int 		m_iSpawnsAvailable;
	bool 		m_bShowPlayerTags;
	int 		m_iShowPlayerMarkers;
	bool		m_bHoldTime;
	uint8_t		m_byteWorldTime;
	uint8_t		m_byteWorldMinute;
	uint8_t		m_byteWeather;
	float 		m_fGravity;
	int 		m_iDeathDropMoney;
	bool 		m_bInstagib;
	int 		m_iLagCompensation;
	int 		m_iVehicleFriendlyFire;
	bool		m_bLanMode;
	bool		m_bStuntBonus;
	bool		m_bDisableVehicleCollision;
	bool		m_bDisableVehMapIcons;
	bool		m_bTirePopping;
	int			m_iDeathMoneyDrop;
	uint8_t		m_byteFriendlyFire;
	uint8_t     m_byteHoldTime;
	float		m_WorldBounds[4];
	bool		m_bLimitGlobalMarkerRadius;
	float		m_fGlobalMarkerRadius;

	/*float		m_fGravity;
	int			m_iDeathDropMoney;
	BYTE		m_byteHoldTime;
	bool		m_bInstagib;
	bool		m_bZoneNames;
	bool		m_bLimitGlobalMarkerRadius;
	bool		m_bUseCJWalk;
	float		m_fGlobalChatRadius;
	bool		m_bManualVehicleEngineAndLight;
	int 		m_iLagCompensation;
	float		m_fGlobalMarkerRadius;
	bool		m_bLimitGlobalChatRadius;
	float		m_fNameTagDrawDistance; // The distance which players will start rendering nametags
	bool		m_bDisableEnterExits; // Interior enter/exits disabled?
	bool		m_bDisableVehMapIcons; // Disable vehicle map markers/ icons
	int			m_iSpawnsAvailable;
	bool		m_bShowPlayerMarkers;
	bool		m_bShowPlayerTags;
	bool		m_bTirePopping;
	BYTE		m_byteWorldTime;
	BYTE		m_byteWorldMinute;
	BYTE		m_byteWeather;
	float		m_WorldBounds[4];
	BYTE		m_byteFriendlyFire;
	bool		m_bAllowWeapons;	
	DWORD		m_dwLastConnectAttempt;
	int			m_iCheckLoadedStuff;
	int			m_iGameState;
	bool		m_bLanMode;
	bool		m_bNameTagLOS;
	bool		m_bManualEngineAndLights;
	bool		m_bDisableVehicleCollision;
	int 		m_iVehicleFriendlyFire;
	bool		m_bEnableStuntBonus;

	char		m_szHostName[256];
	char		m_szHostOrIp[256];
	int			m_iPort;

	DWORD		m_dwMapIcon[MAX_MAP_ICON];*/

	CNetGame(PCHAR szHostOrIp,int iPort,PCHAR szPlayerName,PCHAR szPass);
	~CNetGame();
	
	CPlayerPool * GetPlayerPool() { return m_pPlayerPool; };
	CVehiclePool * GetVehiclePool() { return m_pVehiclePool; };
	CPickupPool * GetPickupPool() { return m_pPickupPool; };
	CObjectPool	* GetObjectPool() { return m_pObjectPool; };
	CMenuPool * GetMenuPool() { return m_pMenuPool; };
	CTextDrawPool * GetTextDrawPool() { return m_pTextDrawPool; };
	CGangZonePool * GetGangZonePool() { return m_pGangZonePool; };
	CActorPool * GetActorPool() { return m_pActorPool; };
	CLabelPool * GetLabelPool() { return m_pLabelPool; };
	RakClientInterface * GetRakClient() { return m_pRakClient; };

	int GetGameState() { return m_iGameState; };
	void SetGameState(int iGameState) { m_iGameState = iGameState; };
	bool IsLanMode() { return m_bLanMode; };
	bool GetWalkStyle() { return m_bUseCJWalk; };
	void SetLanMode(bool bMode) { m_bLanMode = bMode; };

	//void InitGameLogic();
	void Process();

	void UpdatePlayerPings();
	void ResetVehiclePool();
	void ResetPlayerPool();
	void ResetPickupPool();
	void ResetObjectPool();
	void ResetMenuPool();
	void ResetTextDrawPool();
	void ResetGangZonePool();
	void ResetActorPool();
	void ResetLabelPool();
	void ShutdownForGameModeRestart();

	void  ResetMapIcons();
	void  SetMapIcon(BYTE byteIndex, float fX, float fY, float fZ, BYTE byteIcon, DWORD dwColor, BYTE byteStyle);
	void  DisableMapIcon(BYTE byteIndex);

	//bool Send(UniqueID nUniqueID, RakNet::BitStream* pBitStream);
};

//----------------------------------------------------
