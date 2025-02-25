#pragma once
#include "r2engine.h"
#include "convar.h"
#include <unordered_map>

struct PlayerLimitData
{
	double lastClientCommandQuotaStart = -1.0;
	int numClientCommandsInQuota = 0;

	double lastNetChanProcessingLimitStart = -1.0;
	double netChanProcessingLimitTime = 0.0;

	double lastSayTextLimitStart = -1.0;
	int sayTextLimitCount = 0;

	float flFrameUserCmdBudget = 0.0;
};

struct UnconnectedPlayerLimitData
{
	char ip[16];
	double lastQuotaStart = 0.0;
	int packetCount = 0;
	double timeoutEnd = -1.0;
};

class ServerLimitsManager
{
  public:
	ConVar* CVar_sv_quota_stringcmdspersecond;
	ConVar* Cvar_net_chan_limit_mode;
	ConVar* Cvar_net_chan_limit_msec_per_sec;
	ConVar* Cvar_sv_querylimit_per_sec;
	ConVar* Cvar_sv_max_chat_messages_per_sec;
	ConVar* Cvar_sv_antispeedhack_enable;
	ConVar* Cvar_sv_antispeedhack_maxtickbudget;
	ConVar* Cvar_sv_antispeedhack_budgetincreasemultiplier;

	std::unordered_map<R2::CBaseClient*, PlayerLimitData> m_PlayerLimitData;
	std::vector<UnconnectedPlayerLimitData> m_UnconnectedPlayerLimitData;

  public:
	void RunFrame(double flCurrentTime, float flFrameTime);
	void AddPlayer(R2::CBaseClient* player);
	void RemovePlayer(R2::CBaseClient* player);
	bool CheckStringCommandLimits(R2::CBaseClient* player);
	bool CheckChatLimits(R2::CBaseClient* player);
};

extern ServerLimitsManager* g_pServerLimits;
