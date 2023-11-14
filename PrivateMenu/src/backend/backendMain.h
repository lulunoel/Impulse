#pragma once

namespace rage {
#pragma pack(push, 8)
	class rlGamerHandle {
	public:
		rlGamerHandle(uint64_t rockstar_id, uint8_t platform) : m_rockstar_id(rockstar_id), m_platform(platform) {}
		rlGamerHandle(uint64_t rockstar_id) : rlGamerHandle(0, 3) {}
		rlGamerHandle() : rlGamerHandle(0) {}
	public:
		uint64_t m_rockstar_id; //0x0000
		uint8_t m_platform; //0x0008
		uint8_t m_flag; //0x0009
	}; //Size: 0x0010
	static_assert(sizeof(rlGamerHandle) == 0x10);
#pragma pack(pop)
	class netTextMsg {
	public:
		char m_message[256]; //0x0000
		rage::rlGamerHandle m_handle; //0x0100
	}; //Size: 0x0110
	static_assert(sizeof(netTextMsg) == 0x110);
}

class Backend {
public:
	static bool DevMode;
	static uint64_t m_eventPoolPtr;
	static int m_frameCounter;

	typedef __int64(*pScriptVirtualMachineHook)(__int64 rcx, __int64 global, __int64 script, __int64 pThread);
	static pScriptVirtualMachineHook OriginalScriptVirtualMachine;

	static void IncrementPlayerStat(Player player, Hash stat, int value);
	static void SendClearTasksEvent(Entity entity, uint8_t something);

	typedef void(*pRoadSlipperiness)(WorldManager* worldManager);
	static pRoadSlipperiness OriginalRoadSlipperiness;
	static void RoadSlipperinessHook(WorldManager* worldManager);

	typedef int*(*pRegisterFileFn)(int* outIdx, const char* filename, bool one, const char* registerAs, bool errorIfNotFound);
	static int RegisterCStreamingFile(char *filename, bool appdata = true);
	static pRegisterFileFn RegisterFileFn;

	typedef bool(*pHandleChat)(rage::netTextMsg* msg, uint64_t buffer);
	static pHandleChat OriginalHandleChat;
	static bool HandleChatHook(rage::netTextMsg* msg, uint64_t buffer);

	typedef CVehicleModelInfo*(*pGetModelInfo)(unsigned int modelHash, int* index);
	static pGetModelInfo GetModelInfo;

	typedef int64_t(*pProcessChatMessage)(int64_t a1, const void *a2, size_t a3, const void *a4, size_t size);
	static int64_t ProcessChatMessageHook(int64_t a1, const void *a2, size_t a3, const void *a4, size_t size);
	static pProcessChatMessage OriginalProcessChatMessage;

	static void Start(HMODULE hModule);
	static void Cleanup() { if (!m_cleaning) CreateThread(0, 0, CleanupThread, 0, 0, 0); }

	static bool IsHooking() { return m_isHooking; };
	static void SetHooking(bool status) { m_isHooking = status; };
	static bool IsLoaded() { return m_loaded; }
	static HWND GetWindow() { return m_hWindow; }
	static HANDLE GetProcess() { return m_process; }
	static HMODULE GetModule() { return m_hModule; } 
	static void SetModule(HMODULE mod) { m_hModule = mod; };
	static float GetDeltaTime() { return m_deltaTime; }
	static vector<char> GetModulePE() { return m_modulePE; }
	static HMODULE GetNTDLLModule() { return m_NTDLLModule; }
	static uint64_t GetModuleBase() { return m_moduleBaseAddr; }
	static DWORD64 GetGameBase() { return m_gameBase; }
	static DWORD64 GetGameSize() { return m_gameSize; }
	static uint64_t GetModuleSize() { return m_moduleSize; }
	static uint64_t GetWorldPtr() { return m_worldPtr; }
	static uint64_t GetTunablesPtr() { return m_tunables; }
	static __int64** GetGlobalPtr() { return m_globalPtr; }
	static GameState GetGameState() { return *m_gameState; }
	static GameState* GetGameStatePointer() { return m_gameState; }
	static Script::ScriptTable* GetScriptTable() { return m_scriptTable; }
	static uint64_t GetNetworkPlayerManagerPtr() { return m_networkPlayerManager; }
	static void SetNTDLLModule(HMODULE ntdll) { m_NTDLLModule = ntdll; }
	static void GetModuleInfo();
	static bool NetworkIsInSession() { return m_isInSession ? true : false; }
	static bool IsCleaning() { return m_cleaning;}
	static NetCatalog* GetNetCatalog() { return m_netCatalog; }
	static Tunables* GetTunables() { return m_tunableStruct; };
	static __int64 GetRoutingDataAddress() { return reinterpret_cast<__int64(*)(int)>(m_getRoutingData)(0); }

	static vector<DWORD64> GetMemoryNameAddresses() { return m_nameAddresses; };
	static vector<char> m_modulePE;

	static __int64 m_originalRID;
	static __int64 m_spoofingRID;
private:

	static bool m_isHooking;
	static bool m_loaded;
	static bool m_cleaning;
	static HWND m_hWindow;
	static HANDLE m_process;
	static HMODULE m_hModule;

	static DWORD64 m_gameBase;
	static DWORD64 m_gameSize;
	
	static vector<uint64_t> m_nameAddresses;
	static HMODULE m_NTDLLModule;
	static uint64_t m_moduleBaseAddr;
	static uint64_t m_moduleSize;
	static uint64_t m_worldPtr;
	static uint64_t m_tunables;
	static __int64** m_globalPtr;
	static GameState* m_gameState;
	static NativeRegistration** m_registrationTable;
	static Script::ScriptTable* m_scriptTable;
	static uint64_t	m_gameplayCam;
	static uint64_t	m_networkPlayerData;
	static int m_networkPlayerIsOnlineOffset;
	static uint64_t m_networkPlayerManager;
	static DWORD64 m_applyWindElementsSetup;
	static float m_deltaTime;
	static DWORD m_lastFrameTime;
	static uint8_t m_isInSession;
	static NetCatalog* m_netCatalog;
	static Tunables* m_tunableStruct;
	static void *m_getRoutingData;

	static void ScriptThreadInit();
	static bool PreGameBackend();
	static bool InGameBackend();

	typedef void(*pApplyWindElements)(CWorldManager*);
	static pApplyWindElements OriginalApplyWindElements;
	static void ApplyWindElementsHook(CWorldManager* worldManager);

	typedef void(__cdecl * pSendIncrementStatEvent)(Hash stat, int value, CNetGamePlayer* netGamePlayer);
	static pSendIncrementStatEvent fSendIncrementStatEvent;

	typedef void(*pSendClearTasksEvent)(uint64_t entity, uint8_t something);
	static pSendClearTasksEvent fSendClearTasksEvent;
	static int GetStatIntHook(Hash statHash, int* outValue, int p2);
	static bool IsEntityUpsideDown(Entity entity);
	//static BOOL NetworkIsSignedOnlineHook();
	static BOOL IsRecordingHook();
	static void WaitHook(NativeContext* cxt);
	static int StatGetIntHook(NativeContext* cxt);
	static __int64 ScriptVirtualMachineHook(__int64 rcx, __int64 global, __int64 script, __int64 thread);

	static DWORD WINAPI CleanupThread(LPVOID lparam);
};