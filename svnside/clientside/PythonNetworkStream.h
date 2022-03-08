	// [SEARCH]
		bool SendExchangeExitPacket();
	// [ADD UNDER]
		bool SendDiceStartPacket(DWORD vid);
		
	// [SEARCH]
		void __RefreshExchangeWindow();
	// [ADD UNDER]
		void __RefreshDiceWindow();
		
	// [SEARCH]
		bool m_isRefreshExchangeWnd;
	// [ADD UNDER]
		bool m_isRefreshDiceWnd;