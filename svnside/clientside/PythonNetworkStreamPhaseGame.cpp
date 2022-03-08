// [SEARCH]
bool CPythonNetworkStream::SendExchangeStartPacket(DWORD vid)
	
	// [FIND THIS]
	packet.arg1			= vid;
	// [ADD UNDER]
	packet.dice			= 0;
	
// [ADD UNDER AS NEW FUNCTION]
bool CPythonNetworkStream::SendDiceStartPacket(DWORD vid)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGExchange	packet;

	packet.header		= HEADER_CG_EXCHANGE;
	packet.subheader	= EXCHANGE_SUBHEADER_CG_START;
	packet.arg1			= vid;
	packet.dice			= 1;

	if (!Send(sizeof(packet), &packet))
	{
		Tracef("send_dice_start_packet Error\n");
		return false;
	}

	Tracef("send_dice_start_packet   vid %d \n", vid);
	return SendSequence();
}

// [SEARCH]
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "StartExchange", Py_BuildValue("()"));
// [REPLACE]
	if (exchange_packet.dice == 1)
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "StartDice", Py_BuildValue("()"));
	else
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "StartExchange", Py_BuildValue("()"));
	
// [SEARCH]
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "EndExchange", Py_BuildValue("()"));
// [REPLACE]
	if (exchange_packet.dice == 1)
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "EndDice", Py_BuildValue("()"));
	else
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "EndExchange", Py_BuildValue("()"));

// [SEARCH ALL CALL ABOUT]
	// [THERE ARE 4 TIMES ON THAT CALL]
	__RefreshExchangeWindow();
// [REPLACE ALL WITH]
	if (exchange_packet.dice == 1)
		__RefreshDiceWindow();
	else
		__RefreshExchangeWindow();
	
// [SEARCH]
void CPythonNetworkStream::__InitializeGamePhase()
	// [FIND]
		m_isRefreshExchangeWnd=false;
	// [ADD UNDER]
		m_isRefreshDiceWnd=false;
		
// [FIND]
	if (m_isRefreshExchangeWnd)
	{
		m_isRefreshExchangeWnd=false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshExchange", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}

// [ADD UNDER]
	if (m_isRefreshDiceWnd)
	{
		m_isRefreshDiceWnd=false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshDice", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}

	
// [FIND]
void CPythonNetworkStream::__RefreshExchangeWindow()
{
	m_isRefreshExchangeWnd=true;
}
// [ADD UNDER]
void CPythonNetworkStream::__RefreshDiceWindow()
{
	m_isRefreshDiceWnd=true;
}