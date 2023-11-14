#pragma once

namespace SocialclubData
{

	class RockstarAccount {

	private:
		uint32_t m_rockstarId;
		std::string m_name;
		std::string m_displayName;
		std::string m_email; // pretty much never set
		std::string m_countryCode;
		uint32_t m_mutualFriendCount;
		bool m_profileHidden;
		bool m_friendsHidden;
		uint32_t m_friendCount;
		uint8_t m_lastUgcPlatform; // !hidden
		uint8_t m_lastUgcTitle; // !hidden
		uint8_t m_lastOnlineService; // !hidden
		bool m_wallHidden;
		bool m_allowWallPost;
		bool m_allowStatCompare;
		std::string m_inviteMessage;
		bool m_allowBlock;
		bool m_allowReport;
		std::string m_status;
		int32_t m_background;
		bool m_isGamertagHidden;
		std::string m_gamertag;
		uint32_t m_userId;
		std::string m_languageCode;
		std::string m_createdDate;
		std::string m_createdDateStr; // human readable
		bool m_isOnline;
		bool m_isPlaceholder;

	public:
		RockstarAccount() : RockstarAccount(0, "", "", "", "", 0, false, false, 0, 0, 0, 0, false, false, false, "", false, false, "", 0, false, "", 0, "", "", "", false, true) {}
		RockstarAccount(uint32_t rockstarId, std::string name, std::string displayName, std::string email, std::string countryCode, uint32_t mutualFriendCount, bool profileHidden, bool friendsHidden,
			uint32_t friendCount, uint8_t lastUgcPlatform, uint8_t lastUgcTitle, uint8_t lastOnlineService, bool wallHidden, bool allowWallPost, bool allowStatCompare,
			std::string inviteMessage, bool allowBlock, bool allowReport, std::string status, int32_t background, bool isGamertagHidden, std::string gamertag, uint32_t userId,
			std::string languageCode, std::string createdDate, std::string createdDateStr, bool isOnline, bool isPlaceholder = false) :

			m_rockstarId(rockstarId),
			m_name(name),
			m_displayName(displayName),
			m_email(email),
			m_countryCode(countryCode),
			m_mutualFriendCount(mutualFriendCount),
			m_profileHidden(profileHidden),
			m_friendsHidden(friendsHidden),
			m_friendCount(friendCount),
			m_lastUgcPlatform(lastUgcPlatform),
			m_lastUgcTitle(lastUgcTitle),
			m_lastOnlineService(lastOnlineService),
			m_wallHidden(wallHidden),
			m_allowWallPost(allowWallPost),
			m_allowStatCompare(allowStatCompare),
			m_inviteMessage(inviteMessage),
			m_allowBlock(allowBlock),
			m_allowReport(allowReport),
			m_status(status),
			m_background(background),
			m_isGamertagHidden(isGamertagHidden),
			m_gamertag(gamertag),
			m_userId(userId),
			m_languageCode(languageCode),
			m_createdDate(createdDate),
			m_createdDateStr(createdDateStr),
			m_isOnline(isOnline),
			m_isPlaceholder(isPlaceholder) {}

		uint32_t getRockstarId() {
			return m_rockstarId;
		}

		const char* getName() {
			return m_name.c_str();
		}

		const char* getDisplayName() {
			return m_displayName.c_str();
		}

		const char* getEmail() {
			return m_email.c_str();
		}

		const char* getCountryCode() {
			return m_countryCode.c_str();
		}

		uint32_t getMutualFriendCount() {
			return m_mutualFriendCount;
		}

		bool getProfileHidden() {
			return m_profileHidden;
		}

		bool getFriendsHidden() {
			return m_friendsHidden;
		}

		uint32_t getFriendCount() {
			return m_friendCount;
		}

		uint8_t getLastUgcPlatform() {
			return m_lastUgcPlatform;
		}

		uint8_t getLastUgcTitle() {
			return m_lastUgcTitle;
		}

		uint8_t getLastOnlineService() {
			return m_lastOnlineService;
		}

		bool getWallHidden() {
			return m_wallHidden;
		}

		bool getAllowWallPost() {
			return m_allowWallPost;
		}

		bool getAllowStatCompare() {
			return m_allowStatCompare;
		}

		const char* getInviteMessage() {
			return m_inviteMessage.c_str();
		}

		bool getAllowBlock() {
			return m_allowBlock;
		}

		bool getAllowReport() {
			return m_allowReport;
		}

		const char* getStatus() {
			return m_status.c_str();
		}

		int32_t getBackground() {
			return m_background;
		}

		bool getIsGamertagHidden() {
			return m_isGamertagHidden;
		}

		const char* getGamertag() {
			return m_gamertag.c_str();
		}

		uint32_t getUserId() {
			return m_userId;
		}

		const char* getLanguageCode() {
			return m_languageCode.c_str();
		}

		const char* getCreatedDate() {
			return m_createdDate.c_str();
		}

		const char* getCreatedDateStr() {
			return m_createdDateStr.c_str();
		}

		bool isOnline() {
			return m_isOnline;
		}

		bool isPlaceholder() {
			return m_isPlaceholder;
		}

	};

	class BasicAccount {
	private:
		uint32_t m_rockstarId;
		std::string m_nickname;
		std::string m_service;
		std::string m_serviceNickname;
		std::string m_relationship;

	public:

		BasicAccount(uint32_t rockstarId, std::string nickname, std::string service, std::string serviceNickname, std::string relationship) :
			m_rockstarId(rockstarId), m_nickname(nickname), m_service(service), m_serviceNickname(serviceNickname), m_relationship(relationship) {}

		uint32_t getRockstarId() {
			return m_rockstarId;
		}

		const char* getNickname() {
			return m_nickname.c_str();
		}

		const char* getService() {
			return m_service.c_str();
		}

		const char* getServiceNickname() {
			return m_serviceNickname.c_str();
		}

		const char* getRelationship() {
			return m_relationship.c_str();
		}
	};

	class SearchResult {

	private:

		uint32_t m_total;
		uint32_t m_nextOffset;
		bool m_hasMore;
		uint32_t m_blockedCount;
		std::vector<BasicAccount> m_accounts;

	public:

		SearchResult() : SearchResult(0, 0, false, 0, std::vector<BasicAccount>()) {}
		SearchResult(uint32_t total, uint32_t nextOffset, bool hasMore, uint32_t blockedCount, std::vector<BasicAccount> accounts) :
			m_total(total), m_nextOffset(nextOffset), m_hasMore(hasMore), m_blockedCount(blockedCount), m_accounts(accounts) {}

		uint32_t getTotal() {
			return m_total;
		}

		uint32_t getNextOffset() {
			return m_nextOffset;
		}

		bool getHasMore() {
			return m_hasMore;
		}

		uint32_t getBlockedCount() {
			return m_blockedCount;
		}

		std::vector<BasicAccount> getAccounts() {
			return m_accounts;
		}

		BasicAccount getAccount(int index) {
			return m_accounts[index];
		}
	};

}

#pragma pack(push, 1)
class ScInfo {
public:
	char m_ticket[208]; //0x0000
	char pad_00D0[304]; //0x00D0
	char m_session_ticket[88]; //0x0200 - rlSessionInfo base64 serialized?
	char pad_0258[40]; //0x0258
	uint32_t m_nonce; //0x0280
	char pad_0284[4]; //0x0284
	uint32_t m_account_id; //0x0288
	char pad_028C[16]; //0x028C
	char m_profile_pic[128]; //0x029C
	char pad_031C[32]; //0x031C
	char m_country_code[4]; //0x033C
	char pad_0340[31]; //0x0340
	char m_email_address[96]; //0x035F
	char pad_03BF[6]; //0x03BF
	char m_language_subtag[8]; //0x03C5
	char pad_03CD[2]; //0x03CD
	char m_sc_name[20]; //0x03CF
	char pad_03E3[533]; //0x03E3
	char m_session_key[16]; //0x05F8
	char pad_0608[2296]; //0x0608
}; //Size: 0x0F00
static_assert(sizeof(ScInfo) == 0xF00);
#pragma pack(pop)

class Socialclub {

	static ScInfo* m_ticketAddress;

	template<class T>
	static std::enable_if_t<std::is_arithmetic<T>::value, T> SafeRead(nlohmann::json json, const char* key) {
		return json[key].is_null() ? 0 : json[key].get<T>();
	}

	template<class T>
	static std::enable_if_t < std::is_same<T, std::string>::value || std::is_same<T, char*>::value || std::is_same<T, const char*>::value, T> SafeRead(nlohmann::json json, const char* key) {
		return json[key].is_null() ? "null" : json[key].get<T>();
	}

	static std::vector<std::pair<std::string, std::string>> GetRequiredHeaders();

public:

	static void Initialize();

	static void GetProfile(const int32_t rockstarId, std::function<void(bool, SocialclubData::RockstarAccount)> callback);
	static void SearchAccount(const char* name, std::function<void(bool, SocialclubData::SearchResult)> callback, uint16_t pageIndex = 0);
	static void GetRockstarIdByName(const char* name, std::function<void(uint32_t)> callback);

	static const char* GetTicket();

	static ScInfo* GetInfo();
};