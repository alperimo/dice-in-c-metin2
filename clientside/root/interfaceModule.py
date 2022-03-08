import uiDice

	
	# [SEARCH]
		self.dlgExchange.Hide()
	# [ADD UNDER]
		self.dlgDice = uiDice.DiceDialog()
		self.dlgDice.LoadWindow()
		self.dlgDice.SetCenterPosition()
		self.dlgDice.Hide()
		
	# [SEARCH]
		self.dlgExchange.SetItemToolTip(self.tooltipItem)
	# [ADD UNDER]
		self.dlgDice.SetItemToolTip(self.tooltipItem)
		
	# [FIND]
		if self.dlgExchange:
			self.dlgExchange.Destroy()
	# [ADD UNDER]
		if self.dlgDice:
			self.dlgDice.Destroy()
			
	# [SEARCH]
		del self.dlgExchange
	# [ADD UNDER]
		del self.dlgDice
		
	# [FIND]
		def RefreshExchange(self):
			self.dlgExchange.Refresh()
	# [ADD UNDER AS NEW]
		def StartDice(self):
			self.dlgDice.OpenDialog()
			self.dlgDice.Refresh()

		def EndDice(self):
			self.dlgDice.CloseDialog()

		def RefreshDice(self):
			self.dlgDice.Refresh()
		
		def AddDiceNumber(self, myNumber, targetNumber):
			self.dlgDice.DiceAddNumber(myNumber, targetNumber)