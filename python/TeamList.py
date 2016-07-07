from Team import Team
noneTeam= Team("", 0, 0, False)
class TeamList(object):
	def __init__(self, numTeams, teams= []):
		self.teams= teams
		self.numTeams= numTeams
		self.teams.append(noneTeam)
#The function adds a new team in the end of the list.		
	def addTeam(self, newTeam):		 
			self.numTeams+= 1
			self.teams.append(newTeam)
#The function sorts the list by the points.			
	def rankSort(self):
		k=0
		for i in range(2, self.numTeams):
			aux= self.teams[i]
			j=i-1
			self.teams[0]= aux
			while aux.points>=self.teams[j].points and j>0 and k!=1:
				if aux.points==self.teams[j].points and aux.name<self.teams[j].name:
					self.teams[j+1]= self.teams[j]
					j-=1
				elif aux.points>self.teams[j].points:
					self.teams[j+1]= self.teams[j]
					j-=1
				else:
					k=1
			self.teams[j+1]= aux
			k=0
# The function is a binary search to check the team ranking
	def rankSearch(self, team_a):	
		if self.numTeams==0:
			return -1
		else:
				Esq=1
				Dir= self.numTeams
				i= (Esq+Dir)/2
				while team_a.points != self.teams[i].points and Esq <=Dir:
						if team_a.points < self.teams[i].points:
							Esq= i+1
						else:
							Dir= i-1
						i= (Esq+Dir)/2
				while team_a.points== self.teams[i-1].points and i>1:
						i-=1
				j=i
				while team_a.points== self.teams[i].points and j<=self.numTeams:
					if team_a.name==self.teams[j].name:
						return j
					j+=1
				return (-1)
# The function sorts the list by the name.
	def nameSort(self):
		for i in range(2, self.numTeams):
			aux= self.teams[i]
			j=i-1
			self.teams[0]= aux;			
			while aux.name < self.teams[j].name and j>0: 
				self.teams[j+1]= self.teams[j]
				j-=1
			self.teams[j+1]= aux	
#The function is a binary search to check the team name.
	def nameSearch(self, team_a):
		if self.numTeams==0:
			return -1
		else:
				Esq=1
				Dir= self.numTeams
				i= (Esq+Dir)/2
				while team_a.name!=self.teams[i].name and Esq<=Dir:
					if team_a.name>self.teams[i].name:
						Esq=i+1
					else:
						Dir= i-1
					i=(Dir+Esq)/2
				if team_a.name==self.teams[i].name:
					return i
				return -1	
#The function prints the Championship ranking.				
	def printRanking(self):
		i=1
		while i<=self.numTeams:
			print "%d,%s,%d" %(i, self.teams[i].name, self.teams[i].points)
			i+=1

















							
