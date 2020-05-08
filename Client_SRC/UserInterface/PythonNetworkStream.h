// FIND:
		void SetWaitFlag();

// ADD UNDER:
#ifdef ENABLE_DISCORD_RPC
		void Discord_Start();
		void Discord_Close();
		void Discord_Update(const bool ingame, const bool select, const bool loading);
#endif