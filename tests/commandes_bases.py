import os
import ldtp

def connecter():
	ldtp.launchapp('C:\Program Files (x86)\InfoDynamiqueQT\InfoDynamiqueQt.exe')
	ldtp.waittillguiexist('*Connexion*')
	#ldtp.mouseleftclick('*Connexion*', 'txt0')
	#ldtp.enterstring('*Connexion*', 'txt0', "<bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp>localhost")
	#ldtp.mouseleftclick('*Connexion*', 'sldr0')
	#ldtp.enterstring('*Connexion*', 'sldr0', "<del><del><del><del><del><del>3307")
	#ldtp.mouseleftclick('*Connexion*', 'txt1')
	#ldtp.enterstring('*Connexion*', 'txt1', "<bksp><bksp><bksp><bksp><bksp><bksp>root")
	ldtp.mouseleftclick('*Connexion*', 'txt2')
	ldtp.enterstring('*Connexion*', 'txt2', "<bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp><bksp>patate")
	ldtp.click('*Connexion*', 'btnConnecterEnter')
	ldtp.click('*Connexion*', 'lstinfodynamiquedossiers')
	ldtp.click('*Connexion*', 'btnOKEnter')

def fermer():
	ldtp.click("*Gestion de dossiers*", 'btnFermer')
	ldtp.waittillguiexist('*Connexion*')
	ldtp.click('*Connexion*', 'btnFermer')
	
def traiterFiche():
	ldtp.waittillguiexist('*Gestion de dossiers*')
	coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'tbl0')
	ldtp.generatemouseevent(coordinate[0]+116, coordinate[1]+35, 'b1c')
	coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'tbl0')
	ldtp.generatemouseevent(coordinate[0]+116, coordinate[1]+35, 'b1c')
	coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'tbl0')
	ldtp.generatemouseevent(coordinate[0]+116, coordinate[1]+35, 'b1c')
	ldtp.click('*Gestion de dossiers*', 'btnTraiter')
	
def ajouterFiche():
	ldtp.waittillguiexist('*Gestion de dossiers*')
	coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'tbl0')
	ldtp.generatemouseevent(coordinate[0]+116, coordinate[1]+35, 'b1c')
	coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'tbl0')
	ldtp.generatemouseevent(coordinate[0]+116, coordinate[1]+35, 'b1c')
	ldtp.click('*Gestion de dossiers*', 'btnAjouter')
	
def ajouterPressePapier(texte):
	commande = 'echo ' + texte.strip() + '| clip'
	os.system(commande)