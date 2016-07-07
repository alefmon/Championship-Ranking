import csv
import sys
from Team import Team
from TeamList import TeamList

if len(sys.argv)!=3:
		print "INVALID COMMAND! 2 files should be given as arguments in command-line."
		exit()
import csv
	
with open(sys.argv[1], 'rb') as inputFile:	
		Championship= TeamList(0, teams=[])
		ChampionshipList= TeamList(0, teams= [])
		reader= csv.reader(inputFile)
		for row in reader:
			if(len(row[1])>63 or len(row[2])>63):
				print "INVALID INPUT FILE! The name of the team must be smaller than 63 characters. "
				exit()
			operation= row[0]
			if operation == 'CONSULTA':
					newTeam= Team(row[2], 0, 0, False)
					searchType= row[1]
					posit1= ChampionshipList.nameSearch(newTeam)
					if(posit1== -1):
						newTeam.rank= Championship.numTeams +1
						ChampionshipList.teams.append(newTeam) 
						posit1=ChampionshipList.numTeams
					if searchType== 'RANKING':
						if newTeam.played:
							pos=Championship.rankSearch(newTeam)	
    						print "RANKING,%s,%d" %(newTeam.name, pos)
						else:
							print "RANKING,%s,%d" %(newTeam.name, newTeam1Team.rank)	
					elif searchType== 'PONTUACAO':
						print "PONTUACAO,%s,%d" %(newTeam.name, ChampionshipList.teams[posit1].points)
					else: 
						print "INVALID INPUT FILE! You can only search for 'RANKING' or 'PONTUACAO'." 	
						exit()
					ChampionshipList.nameSort		
					
			elif operation== 'VITORIA':	
				#Get the team`s name.	
					newTeam1= Team(row[1], 0, 0, False)
					newTeam2= Team(row[2], 0, 0, False)
				#Search for the team`s position in the Championship List.	
					posit1= ChampionshipList.nameSearch(newTeam1)
					posit2= ChampionshipList.nameSearch(newTeam2)
				#if Team1 is already in the Championship List.	
					if posit1!= -1:
						newTeam1.points= ChampionshipList.teams[posit1].points
						pos1= Championship.rankSearch(newTeam1)
				#if Team2 is already in the Championship List.	
					if posit2 != -1:
						newTeam2.points= ChampionshipList.teams[posit2].points
						pos2= Championship.rankSearch(newTeam2)
				#if Team1 is not in the Championship List yet.	
					if posit1==-1:
						Championship.addTeam(newTeam1)
						ChampionshipList.addTeam(newTeam1)
						pos1= Championship.numTeams
						posit1= ChampionshipList.numTeams

				#if Team2 is not in the Championship List yet.			
					if posit2==-1:
						Championship.addTeam(newTeam2)
						ChampionshipList.addTeam(newTeam2)
						pos2= Championship.numTeams
						posit2= ChampionshipList.numTeams

				# if the first match of the Team1 is this one.		
					if pos1== -1:
						Championship.addTeam(newTeam1)
						pos1= Championship.numTeams
				# if the first match of the Team2 is this one.			
					if pos2== -1:
						Championship.addTeam(newTeam2)
						pos2= Championship.numTeams
				# Change the team`s points.
					Championship.teams[pos1].changePoints(3)
				#Sort the ranking and the Championship List.
					Championship.rankSort()
					for i in range(1, Championship.numTeams):
						ChampionshipList.teams[i].rank=i
					ChampionshipList.nameSort()		

			elif operation== 'EMPATE':
			#Get the team`s name.	
				newTeam1= Team(row[1], 0, 0, False)
				newTeam2= Team(row[2], 0, 0, False)
			#Search for the team`s position in the Championship List.	
				posit1= ChampionshipList.nameSearch(newTeam1)
				posit2= ChampionshipList.nameSearch(newTeam2)
			#if Team1 is already in the Championship List.	
				if posit1!= -1:
					newTeam1.points= ChampionshipList.teams[posit1].points
					pos1= Championship.rankSearch(newTeam1)
			#if Team2 is already in the Championship List.	
				if posit2 != -1:
					newTeam2.points= ChampionshipList.teams[posit2].points
					pos2= Championship.rankSearch(newTeam2)
			#if Team1 is not in the Championship List yet.	
				if posit1==-1:
					Championship.addTeam(newTeam1)
					ChampionshipList.addTeam(newTeam1)
					pos1= Championship.numTeams
					posit1= ChampionshipList.numTeams

			#if Team2 is not in the Championship List yet.						if posit2==-1:
					Championship.addTeam(newTeam2)
					ChampionshipList.addTeam(newTeam2)
					pos2= Championship.numTeams
					posit2= ChampionshipList.numTeams

			# if the first match of the Team1 is this one.		
				if pos1== -1:
					Championship.addTeam(newTeam1)
					pos1= Championship.numTeams
			# if the first match of the Team2 is this one.			
				if pos2== -1:
					Championship.addTeam(newTeam2)
					pos2= Championship.numTeams
			# Change the team`s points.
				Championship.teams[pos1].changePoints(1)
				Championship.teams[pos2].changePoints(1)
			#Sort the ranking and the Championship List.
				Championship.rankSort()
				for i in range(1, Championship.numTeams):
					Championship.teams[i].rank=i
				ChampionshipList.nameSort()			

			else:
				print "INVALID INPUT FILE! The valid operations are: CONSULTA, VITORIA and EMPATE."
				exit()		

