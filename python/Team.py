class Team(object):
	def __init__(self, name, rank, points, played):
		self.name= name
		self.rank= rank
		self.points= points
		self.played= played
	def changePoints(self, addPoint):
		self.points +=addPoint
