	# [FIND]
	def __ServerCommand_Build(self):
		serverCommandList={
			#[...]
			
			# [ADD THIS]
			"DiceDone"			: self.__DiceHasDone,
			
		}
	
	# [FIND]
	def StartExchange(self):
		self.interface.StartExchange()
	# [ADD TOP]
	def StartDice(self):
		self.interface.StartDice()

	def EndDice(self):
		self.interface.EndDice()

	def RefreshDice(self):
		self.interface.RefreshDice()
		
	def __DiceHasDone(self, myNumber, targetNumber):
		self.interface.AddDiceNumber(myNumber, targetNumber)