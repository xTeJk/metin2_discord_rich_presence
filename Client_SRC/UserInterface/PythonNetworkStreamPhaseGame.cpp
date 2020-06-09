// ADD AT THE END OF FILE:
#ifdef ENABLE_DISCORD_RPC
#include "discord_rpc.h"
#pragma comment(lib, "discord_rpc.lib")

static int64_t StartTime;
void CPythonNetworkStream::Discord_Start()
{
	StartTime = time(0);
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	// set your discord app id 
	// registered here: https://discord.com/developers/applications/
	Discord_Initialize("571993654902784004", &handlers, 1, nullptr);
	Discord_Update(false, false, false);
}
void CPythonNetworkStream::Discord_Update(const bool ingame, const bool select, const bool loading)
{
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	//
	// put <filename> inside <directory> to disable rpc
	FILE *file;
	if (file = fopen("configs/calios_dev", "r")) {
		fclose(file);
		TraceError("calios dev file detected, discord rich presence disabled");
	}
	else {
		if (ingame) {
			DWORD race = CPythonPlayer::Instance().GetRace();
			const char * name = CPythonPlayer::Instance().GetName();
			const char * map = CPythonBackground::Instance().GetWarpMapName();
			const char * map_name = "";
			//
			// here you can define your own names of maps
			// eg. calios_eu_valley_map => Giant Valley
			if (strcmp("metin2_map_a1", map) == 0)
				map_name = "1st City of Shinsoo";
			else if (strcmp("metin2_map_b1", map) == 0)
				map_name = "1st City of Chunjo";
			else if (strcmp("metin2_map_c1", map) == 0)
				map_name = "1st City of Jinno";
			else
				// get default map name (directory name in files)
				map_name = CPythonBackground::Instance().GetWarpMapName();
			//
			discordPresence.details = (std::string("Nick: ") += name).c_str();
			discordPresence.state = (std::string("Map: ") += map_name).c_str();
			//
			discordPresence.largeImageKey = "calios";
			discordPresence.largeImageText = "CALIOS.EU - METIN2 INTERNATIONAL SERVER";
			//
			// use ultoa buffer to transfer DWORD into char*
			char buffer[sizeof(unsigned long) * 8 + 1];
			const char * race_name = _ultoa(race, buffer, 2);
			// and then check if GetRace DWORD is equal to buffer to get player's character race
			//
			// how to get race ID in different way:
			//	CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
			//	int race = pInstance->GetRace();
			//
			//	if (race == 0) {
			//		discordPresence.smallImageKey = "warriorm";
			//		discordPresence.smallImageText = "Explores the world of Calios as male Warrior!";
			//	} else if (race == 4) {
			//		discordPresence.smallImageKey = "warriorf";
			//		discordPresence.smallImageText = "Explores the world of Calios as female Warrior!";
			//	}
			//
			// ... etc...
			// 0 - warrior_m // 2 - sura_m // 5 - ninja_m // 7 - shaman_m // WOLFMAN: 8
			// 1 - ninja_w // 3 - shaman_w // 4 - warrior_w // 6 - sura_w
			//
			if (strcmp("0", buffer) == 0) {
				discordPresence.smallImageKey = "warriorm";
				discordPresence.smallImageText = "Explores the world of Calios as male Warrior!";
			} else if (strcmp("100", buffer) == 0) {
				discordPresence.smallImageKey = "warriorf";
				discordPresence.smallImageText = "Explores the world of Calios as female Warrior!";
			} else if (strcmp("101", buffer) == 0) {
				discordPresence.smallImageKey = "ninjam";
				discordPresence.smallImageText = "Explores the world of Calios as male Ninja!";
			} else if (strcmp("1", buffer) == 0) {
				discordPresence.smallImageKey = "ninjaf";
				discordPresence.smallImageText = "Explores the world of Calios as female Ninja!";
			} else if (strcmp("10", buffer) == 0) {
				discordPresence.smallImageKey = "suram";
				discordPresence.smallImageText = "Explores the world of Calios as male Sura!";
			} else if (strcmp("110", buffer) == 0) {
				discordPresence.smallImageKey = "suraf";
				discordPresence.smallImageText = "Explores the world of Calios as female Sura!";
			} else if (strcmp("111", buffer) == 0) {
				discordPresence.smallImageKey = "shamanm";
				discordPresence.smallImageText = "Explores the world of Calios as male Shaman!";
			} else if (strcmp("11", buffer) == 0) {
				discordPresence.smallImageKey = "shamanf";
				discordPresence.smallImageText = "Explores the world of Calios as female Shaman!";
			} else {
				discordPresence.smallImageKey = "mt2";
				discordPresence.smallImageText = "INTERNATIONAL PRIVATE METIN2 SERVER";
			}
		} else if (select) {
			// text lines
			discordPresence.details = "Entering the game!";
			discordPresence.state = "Selecting character...";
			// large image
			discordPresence.largeImageKey = "calios";
			discordPresence.largeImageText = "CALIOS.EU";
			// small image
			discordPresence.smallImageKey = "mt2";
			discordPresence.smallImageText = "INTERNATIONAL PRIVATE METIN2 SERVER";
		} else if (loading) {
			// text lines
			discordPresence.details = "Entering the game!";
			discordPresence.state = "Loading...";
			// large image
			discordPresence.largeImageKey = "calios";
			discordPresence.largeImageText = "CALIOS.EU";
			// small image
			discordPresence.smallImageKey = "mt2";
			discordPresence.smallImageText = "INTERNATIONAL PRIVATE METIN2 SERVER";
		} else {
			// text lines
			discordPresence.details = "Entering the game!";
			discordPresence.state = "Logging in...";
			// large image
			discordPresence.largeImageKey = "calios";
			discordPresence.largeImageText = "CALIOS.EU";
			// small image
			discordPresence.smallImageKey = "mt2";
			discordPresence.smallImageText = "INTERNATIONAL PRIVATE METIN2 SERVER";
		}

		discordPresence.startTimestamp = StartTime;
		Discord_UpdatePresence(&discordPresence);
	}
}
void CPythonNetworkStream::Discord_Close()
{
	Discord_Shutdown();
}
#endif
