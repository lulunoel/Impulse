#include "stdafx.h"
#include <format>

namespace rage {
	#pragma pack(pop)
	class sysMemAllocator {
	public:
		virtual sysMemAllocator* GetIdentifier() { return nullptr; };
		virtual sysMemAllocator* GetIdentifier_2() { return nullptr; };
		virtual uint32_t GetTypeHash() { return NULL; };
		virtual sysMemAllocator* GetIfIsOfType(sysMemAllocator* vft) { return vft; };
		virtual bool IsOfType(sysMemAllocator* vft) { return false; };
		virtual bool IsOfTypeObject(sysMemAllocator* object) { return false; };
		virtual ~sysMemAllocator() = 0;
		virtual void SetQuitOnFail(bool) = 0;
		virtual void* Allocate(size_t size, size_t align, int subAllocator) = 0;
		virtual void* TryAllocate(size_t size, size_t align, int subAllocator) = 0;
		virtual void Free(void* pointer) = 0;
		virtual void TryFree(void* pointer) = 0;
		virtual void Resize(void* pointer, size_t size) = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) const = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) = 0;
		virtual sysMemAllocator* GetPointerOwner(void* pointer) = 0;
		virtual size_t GetSize(void* pointer) const = 0;
		virtual size_t GetMemoryUsed(int memoryBucket) = 0;
		virtual size_t GetMemoryAvailable() = 0;
	public:
		static sysMemAllocator* UpdateAllocatorValue() {
			auto tls = *getPointer();
			auto gtaTlsEntry = *reinterpret_cast<sysMemAllocator**>(uintptr_t(tls) + 0x00B8);
			if (!gtaTlsEntry)
				*(sysMemAllocator**)((uint64_t)tls + 0x00B8)  = gtaTlsEntry;
			*(sysMemAllocator**)((uint64_t)tls + 0x00C0) = gtaTlsEntry;
			return gtaTlsEntry;
		}
		static sysMemAllocator* get() {
			auto allocValue = *getPointer();
			if (!allocValue)
				allocValue = UpdateAllocatorValue();
			return allocValue;
		}
		static sysMemAllocator** getPointer() {
			auto tls = uintptr_t(*(uintptr_t*)__readgsqword(0x58));
			return reinterpret_cast<sysMemAllocator**>(tls + 0x00B8);
		}
		static sysMemAllocator* getEntry() {
			auto tls = uintptr_t(*(uintptr_t*)__readgsqword(0x58));
			return *reinterpret_cast<sysMemAllocator**>(tls + 0x00C0);
		}
		static sysMemAllocator** getEntryPointer() {
			auto tls = uintptr_t(*(uintptr_t*)__readgsqword(0x58));
			return reinterpret_cast<sysMemAllocator**>(tls + 0x00C0);
		}
	};
}

SystemData g_systemdata;


bool SystemData::Initialize()
{
	///*Main Data*/
	//if (!Hooking::ServerPatternCallback<char>("SDMD", [&](Hooking::CallbackData<char> data) {
	//	m_operatingSystem =		(char*)(GetAddressFromInstruction(data.m_address, 0x56));
	//	m_CPUSpeed =			(char*)(GetAddressFromInstruction(data.m_address, 0x6F));
	//	m_CPUBrand =			(char*)(GetAddressFromInstruction(data.m_address, 0x7D));
	//	m_directXVersion =		(char*)(GetAddressFromInstruction(data.m_address, 0x8F));
	//	m_VRam =				(char*)(GetAddressFromInstruction(data.m_address, 0xA4));
	//	m_GPU =					(char*)(GetAddressFromInstruction(data.m_address, 0xAB));
	//	m_motherBoard =			(char*)(GetAddressFromInstruction(data.m_address, 0xD2));
	//	m_gameLanguage =		(char*)(GetAddressFromInstruction(data.m_address, 0xED));
	//})) return false;

	///*Title Data*/
	//if (!Hooking::ServerPatternCallback<char>("SDT", [&](Hooking::CallbackData<char> data) {
	//	m_gameName =			(char*)(GetAddressFromInstruction(data.m_address, 0x1A8));
	//})) return false;

	///*Version Data*/
	//if (!Hooking::ServerPatternCallback<char>("SDV", [&](Hooking::CallbackData<char> data) {
	//	m_gameBuild =			(char*)(GetAddressFromInstruction(data.m_address, 0x61));
	//	m_gameOnlineVersion =	(char*)(GetAddressFromInstruction(data.m_address, 0x109));
	//})) return false;

	///*Exe Data*/
	//if (!Hooking::ServerPatternCallback<char>("SDEN", [&](Hooking::CallbackData<char> data) {
	//	m_gameLauncherName =	(char*)(GetAddressFromInstruction(data.m_address, 0xC7));
	//	m_gameExecutableName =	(char*)(GetAddressFromInstruction(data.m_address, 0XEE));
	//})) return false;

	///*Social Club Data*/
	//if (!Hooking::ServerPatternCallback<char>("SDSC", [&](Hooking::CallbackData<char> data) {
	//	m_socialClubVersion =	(char*)(GetAddressFromInstruction(data.m_address, 0x11));
	//	m_socialClubEmail =		(char*)(GetAddressFromInstruction(data.m_address, 0x17));
	//})) return false;

	m_operatingSystem = "";
	m_CPUSpeed = "";
	m_CPUBrand = "";
	m_directXVersion = "";
	m_VRam = std::string(std::to_string(rage::sysMemAllocator::get()->GetMemoryAvailable()) + "MB / " + std::to_string(rage::sysMemAllocator::get()->GetMemoryUsed(0)) + "MB").c_str();
	m_GPU = "";
	m_motherBoard = "";
	m_gameLanguage = Socialclub::GetInfo()->m_language_subtag;

	m_gameName = "";

	m_gameBuild = Inventory::GetGameVersion();
	m_gameOnlineVersion = NETWORK::_GetOnlineVersion();

	m_gameLauncherName = "";
	m_gameExecutableName = "";

	m_socialClubVersion = "";
	m_socialClubEmail = Socialclub::GetInfo()->m_email_address;
	return true;
}

SystemData* GetSystemdata() { return &g_systemdata; }