// FIND:
	if (m_pySystem.IsUseDefaultIME())
	{
		CPythonIME::Instance().UseDefaultIME();
	}
	
// ADD UNDER:
#ifdef ENABLE_DISCORD_RPC
	m_pyNetworkStream.Discord_Start();
#endif


// FIND:
	m_pyGraphic.Destroy();
	
// ADD UNDER:
#ifdef ENABLE_DISCORD_RPC
	m_pyNetworkStream.Discord_Close();
#endif