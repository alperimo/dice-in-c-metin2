// [SEARCH]
#include "config.h"
// [ADD UNDER]
#include "questmanager.h"

// [SEARCH]
void exchange_packet(LPCHARACTER ch, BYTE sub_header, bool is_me, DWORD arg1, TItemPos arg2, DWORD arg3, void * pvData = NULL);
// [REPLACE]
void exchange_packet(LPCHARACTER ch, BYTE sub_header, bool is_me, DWORD arg1, TItemPos arg2, DWORD arg3, BYTE dice, void * pvData = NULL);

// [SEARCH]
void exchange_packet(LPCHARACTER ch, BYTE sub_header, bool is_me, DWORD arg1, TItemPos arg2, DWORD arg3, void * pvData)
// [REPLACE]
void exchange_packet(LPCHARACTER ch, BYTE sub_header, bool is_me, DWORD arg1, TItemPos arg2, DWORD arg3, BYTE dice, void * pvData)

	// [SEARCH]
	pack_exchg.arg3		= arg3;
	// [ADD UNDER]
	pack_exchg.dice		= dice;

// [SEARCH]
bool CHARACTER::ExchangeStart(LPCHARACTER victim)
// [REPLACE]
bool CHARACTER::ExchangeStart(LPCHARACTER victim, BYTE dice)

// [SEARCH]
bool CExchange::AddGold(long gold)
	// [FIND]
	if (gold <= 0)
		return false;
	
	// [ADD UNDER]
	if (m_lDice == 1)
		return false;
	
// [SEARCH]
bool CExchange::Accept(bool bAccept)
	// [FIND]
		if (Done())
		{
			if (m_lGold) // µ·ÀÌ ÀÖÀ» ‹š¸¸ ÀúÀå
				GetOwner()->Save();

			if (GetCompany()->Done())
			{
				if (GetCompany()->m_lGold) // µ·ÀÌ ÀÖÀ» ¶§¸¸ ÀúÀå
					victim->Save();

				// INTERNATIONAL_VERSION
				GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s ´Ô°úÀÇ ±³È¯ÀÌ ¼º»ç µÇ¾ú½À´Ï´Ù."), victim->GetName());
				victim->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s ´Ô°úÀÇ ±³È¯ÀÌ ¼º»ç µÇ¾ú½À´Ï´Ù."), GetOwner()->GetName());
				// END_OF_INTERNATIONAL_VERSION
			}
		}
	
	// [THEN REPLACE ALL AS]
		if (m_lDice == 1)
		{
			int myNumber = 0, targetNumber = 0, diceHasDone = 0;
			myNumber = number(1,100); targetNumber = number(1, 100);
			if (myNumber > targetNumber)
			{
				if (GetCompany()->Done())
					diceHasDone = 1;
				
				GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("diceWon"));
				victim->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("diceLoss"));
			}
			else if (myNumber < targetNumber)
			{
				if (Done())
					diceHasDone = 1;
				
				GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("diceLoss"));
				victim->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("diceWon"));
			}
			else
			{
				diceHasDone = 1;
				GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("diceNoWinner"));
				victim->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("diceNoWinner"));
			}
			
			if (diceHasDone)
			{
				GetOwner()->ChatPacket(CHAT_TYPE_COMMAND, "DiceDone %d %d", myNumber, targetNumber);
				victim->ChatPacket(CHAT_TYPE_COMMAND, "DiceDone %d %d", targetNumber, myNumber);
				
				GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s diceDone"), victim->GetName());
				victim->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s diceDone"), GetOwner()->GetName());
			}
		}else
		{
			if (Done())
			{
				if (m_lGold) // µ·ÀÌ ÀÖÀ» ‹š¸¸ ÀúÀå
					GetOwner()->Save();

				if (GetCompany()->Done())
				{
					if (GetCompany()->m_lGold) // µ·ÀÌ ÀÖÀ» ¶§¸¸ ÀúÀå
						victim->Save();

					// INTERNATIONAL_VERSION
					GetOwner()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s ´Ô°úÀÇ ±³È¯ÀÌ ¼º»ç µÇ¾ú½À´Ï´Ù."), victim->GetName());
					victim->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s ´Ô°úÀÇ ±³È¯ÀÌ ¼º»ç µÇ¾ú½À´Ï´Ù."), GetOwner()->GetName());
					// END_OF_INTERNATIONAL_VERSION
				}
			}
		}
		
// [FIND THIS]
	if (victim->IsBlockMode(BLOCK_EXCHANGE))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("»ó´ë¹æÀÌ ±³È¯ °ÅºÎ »óÅÂÀÔ´Ï´Ù."));
		return false;
	}
// [ADD UNDER]
	int dice_system = quest::CQuestManager::instance().GetEventFlag("dice_system");
	if (dice == 1 && dice_system == 1)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("diceDISABLE"));
		return false;
	}
	
// [SEARCH]
SetExchange(M2_NEW CExchange(this));
// [REPLACE]
SetExchange(M2_NEW CExchange(this, dice));

// [SEARCH]
victim->SetExchange(M2_NEW CExchange(victim));
// [REPLACE]
victim->SetExchange(M2_NEW CExchange(victim, dice));

// [SEARCH]
CExchange::CExchange(LPCHARACTER pOwner)
// [REPLACE]
CExchange::CExchange(LPCHARACTER pOwner, BYTE dice)

// [SEARCH]
	m_lGold = 0;
// [ADD UNDER]
	m_lDice = dice;
	
// [SEARCH]
	exchange_packet(this, EXCHANGE_SUBHEADER_GC_ALREADY, 0, 0, NPOS, 0);
// [REPLACE]
	exchange_packet(this, EXCHANGE_SUBHEADER_GC_ALREADY, 0, 0, NPOS, 0, dice);
	
// [SEARCH]
	exchange_packet(victim, EXCHANGE_SUBHEADER_GC_START, 0, GetVID(), NPOS, 0);
// [REPLACE]
	exchange_packet(victim, EXCHANGE_SUBHEADER_GC_START, 0, GetVID(), NPOS, 0, dice);
	
// [SEARCH]
	exchange_packet(this, EXCHANGE_SUBHEADER_GC_START, 0, victim->GetVID(), NPOS, 0);
// [REPLACE]
	exchange_packet(this, EXCHANGE_SUBHEADER_GC_START, 0, victim->GetVID(), NPOS, 0, dice);

// [FIND]
		exchange_packet(m_pOwner, 
				EXCHANGE_SUBHEADER_GC_ITEM_ADD,
				true,
				item->GetVnum(),
				TItemPos(RESERVED_WINDOW, display_pos),
				item->GetCount(),
				item);
// [REPLACE]
		exchange_packet(m_pOwner, 
				EXCHANGE_SUBHEADER_GC_ITEM_ADD,
				true,
				item->GetVnum(),
				TItemPos(RESERVED_WINDOW, display_pos),
				item->GetCount(), 
				m_lDice,
				item);
				
// [FIND]
		exchange_packet(GetCompany()->GetOwner(),
				EXCHANGE_SUBHEADER_GC_ITEM_ADD, 
				false, 
				item->GetVnum(),
				TItemPos(RESERVED_WINDOW, display_pos),
				item->GetCount(),
				item);
// [REPLACE]
		exchange_packet(GetCompany()->GetOwner(),
				EXCHANGE_SUBHEADER_GC_ITEM_ADD, 
				false, 
				item->GetVnum(),
				TItemPos(RESERVED_WINDOW, display_pos),
				item->GetCount(), 
				m_lDice,
				item);
				
// [SEARCH]
	exchange_packet(GetOwner(),	EXCHANGE_SUBHEADER_GC_ITEM_DEL, true, pos, NPOS, 0);
// [REPLACE]
	exchange_packet(GetOwner(),	EXCHANGE_SUBHEADER_GC_ITEM_DEL, true, pos, NPOS, 0, m_lDice);
	
// [SEARCH]
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_ITEM_DEL, false, pos, PosOfInventory, 0);
// [REPLACE]
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_ITEM_DEL, false, pos, PosOfInventory, 0, m_lDice);
	
// [SEARCH]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_LESS_GOLD, 0, 0, NPOS, 0);
// [REPLACE]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_LESS_GOLD, 0, 0, NPOS, 0, m_lDice);
	
// [SEARCH]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_GOLD_ADD, true, m_lGold, NPOS, 0);
// [REPLACE]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_GOLD_ADD, true, m_lGold, NPOS, 0, m_lDice);
	
// [SEARCH]
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_GOLD_ADD, false, m_lGold, NPOS, 0);
// [REPLACE]
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_GOLD_ADD, false, m_lGold, NPOS, 0, m_lDice);
	
// [SEARCH]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_ACCEPT, true, m_bAccept, NPOS, 0);
// [REPLACE]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_ACCEPT, true, m_bAccept, NPOS, 0, m_lDice);
	
// [SEARCH]
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_ACCEPT, false, m_bAccept, NPOS, 0);
// [REPLACE]
	exchange_packet(GetCompany()->GetOwner(), EXCHANGE_SUBHEADER_GC_ACCEPT, false, m_bAccept, NPOS, 0, m_lDice);
	
// [SEARCH]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_END, 0, 0, NPOS, 0);
// [REPLACE]
	exchange_packet(GetOwner(), EXCHANGE_SUBHEADER_GC_END, 0, 0, NPOS, 0, m_lDice);