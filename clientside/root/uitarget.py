	# [ADD INSIDE OF THIS]
	BUTTON_NAME_LIST = ( 
		localeInfo.TARGET_BUTTON_DICE,
	)
	
	# [SEARCH]
		EXCHANGE_LIMIT_RANGE = 3000
	# [ADD UNDER]
		DICE_LIMIT_RANGE = 3000
	
	# [SEARCH]
		self.buttonDict[localeInfo.TARGET_BUTTON_EXCHANGE].SetEvent(ui.__mem_func__(self.OnExchange))
	# [ADD UNDER]
		self.buttonDict[localeInfo.TARGET_BUTTON_DICE].SetEvent(ui.__mem_func__(self.OnDice))
		
	# [FIND]
		distance = player.GetCharacterDistance(self.vid)
		if distance > self.EXCHANGE_LIMIT_RANGE:
			self.__HideButton(localeInfo.TARGET_BUTTON_EXCHANGE)
			self.__ArrangeButtonPosition()
	# [ADD UNDER]
		if distance > self.DICE_LIMIT_RANGE:
			self.__HideButton(localeInfo.TARGET_BUTTON_DICE)
			self.__ArrangeButtonPosition()
		
	# [SEARCH]
		self.showingButtonList.append(self.buttonDict[localeInfo.TARGET_BUTTON_EXCHANGE])
	# [ADD UNDER]
		self.showingButtonList.append(self.buttonDict[localeInfo.TARGET_BUTTON_DICE])
		
	# [SEARCH]
		def OnExchange(self):
			net.SendExchangeStartPacket(self.vid)
	# [ADD UNDER]
		def OnDice(self):
			net.SendDiceStartPacket(self.vid)
	
	# [FIND]
		distance = player.GetCharacterDistance(self.vid)

		if distance < 0:
			return
	# [ADD UNDER]
		diceButton = self.buttonDict[localeInfo.TARGET_BUTTON_DICE]
		if diceButton.IsShow():
			if distance > self.DICE_LIMIT_RANGE:
				self.RefreshButton()

		else:
			if distance < self.DICE_LIMIT_RANGE:
				self.RefreshButton()
		