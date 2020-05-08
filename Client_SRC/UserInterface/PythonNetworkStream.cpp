// FIND:
			SetSelectPhase();

// ADD UNDER:
#ifdef ENABLE_DISCORD_RPC
			Discord_Update(false, true, false);
#endif


// FIND:
			SetLoadingPhase();

// ADD UNDER:
#ifdef ENABLE_DISCORD_RPC
			Discord_Update(false, false, true);
#endif


// FIND:
			SetGamePhase();

// ADD:
#ifdef ENABLE_DISCORD_RPC
			Discord_Update(true, false, false);
#endif


// FIND:
	Tracen("");
	Tracen("## Network - OffLine Phase ##");
	Tracen("");

// ADD UNDER:
#ifdef ENABLE_DISCORD_RPC
	Discord_Update(false, false, false);
#endif