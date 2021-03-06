import sys
import ldtp
import Image
import ImageChops
from commandes_bases import *

connecter()

traiterFiche()

fenetre = "*Traitement d'une fiche de maintenance*"
ldtp.waittillguiexist(fenetre)

ldtp.mouseleftclick(fenetre, 'txtFiche#13')
ldtp.keypress('<ctrl>')
ldtp.keypress('a')
ldtp.keyrelease('<ctrl>')
ldtp.keypress('<bksp>')
ldtp.keyrelease('<bksp>')
ldtp.enterstring(fenetre, 'txtFiche#13', 'allo mon grand')
ldtp.click(fenetre, 'btnCancel')

ldtp.click('*Gestion de dossiers*', 'btnTraiter')
ldtp.waittillguiexist(fenetre)

coordinate = ldtp.getwindowsize(fenetre)
if (len(sys.argv) > 1) and (sys.argv[1] == 'origin'):
	ldtp.imagecapture(fenetre, 'images/traiter_fiche_commentaire_basse_origin.png',
                      coordinate[0], coordinate[1], coordinate[2], coordinate[3])
else:
    ldtp.imagecapture(fenetre, 'images/traiter_fiche_commentaire_basse.png',
                      coordinate[0], coordinate[1], coordinate[2], coordinate[3])
    im1 = Image.open("images/traiter_fiche_commentaire_basse.png")
    im2 = Image.open("images/traiter_fiche_commentaire_basse_origin.png")
    diff = ImageChops.difference(im2, im1)
    if diff.getbbox():
        print("Erreur possible dans 'Traitement fiche test: commentaire basse'")

ldtp.click(fenetre, 'btnSaveEnter')
fermer()
