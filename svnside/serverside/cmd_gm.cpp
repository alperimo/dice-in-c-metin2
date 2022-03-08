// [SEARCH]
ACMD(do_xmas)
{
	// [...]
	// [...]
	// [...]
}

// [ADD UNDER AS NEW]
ACMD(do_dice_new)
{
	char arg1[256];

	one_argument(argument, arg1, sizeof(arg1));
	
	if (*arg1)
	{
		int flag = 0;
		str_to_number(flag, arg1);
		
		if (flag != 0 && flag != 1)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "Usage : /dice_system <0 or 1> (1 to disable)");
			return;
		}

		quest::CQuestManager::instance().RequestSetEventFlag("dice_system", flag);
		
	}
}