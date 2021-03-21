>InstanceBase.cpp
// FIND:
DWORD CInstanceBase::GetRace()
{
	...
}

// ADD BELOW:
DWORD CInstanceBase::GetLevel()
{
	return m_dwLevel;
}


>InstanceBase.h
// FIND:
		DWORD					GetRace();

// ADD BELOW:
		DWORD					GetLevel();


>PythonNetworkStreamPhaseGameActor.cpp
// IF YOU WANT AUTOREFRESH FIND:
bool CPythonNetworkStream::RecvCharacterUpdatePacket()

// AND ABOVE:
__RecvCharacterUpdatePacket(&kNetUpdateActorData);

// ADD:
#ifdef ENABLE_DISCORD_RPC
			Discord_Update(true, false, false);
#endif


>PythonNetworkStreamPhaseGame.cpp

// FIND:
void CPythonNetworkStream::Discord_Update

// BELOW:
if (ingame)

// ADD:
			CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
			DWORD level = pInstance->GetLevel();

// DEPENDING WHERE EXACTLY YOU WANT IT:
			std::string rpc_level = "Level: ";
			rpc_level += std::to_string(level);

			discordPresence.details = (rpc_level).c_str();
// OR
			discordPresence.state = (rpc_level).c_str();

// YOU CAN ALSO DO SOMETHING WITH NICK + LVL
			std::string name_lv = "Name: ";
			name_lv += name;
			name_lv += " | ";
			name_lv += std::to_string(level);
			name_lv += "Lv";

// THEN IT WILL LOOK LIKE THIS: https://gyazo.com/2a16f01e9717a2f850cce877b7e16d38