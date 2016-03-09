import sys
import ldtp
import Image
import ImageChops
from connexionBD import *
from fermer_fenetre import *

connecter()

ldtp.waittillguiexist('*Gestion de dossiers*')
coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'tbl0')
ldtp.generatemouseevent(coordinate[0]+116, coordinate[1]+30, 'b1c')
coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'tbl0')
ldtp.generatemouseevent(coordinate[0]+116, coordinate[1]+30, 'b1c')

ldtp.click('*Gestion de dossiers*', 'btnAjouter')
ldtp.waittillguiexist('*une nouvelle fiche*')
ldtp.mouseleftclick('*une nouvelle fiche*', 'txt0')
ldtp.enterstring('*une nouvelle fiche*', 'txt0', "bonjour comment ca va")
ldtp.mouseleftclick('*une nouvelle fiche*', 'cboDown')
ldtp.mouseleftclick('*une nouvelle fiche*', 'lstInstallationavecbackup')
ldtp.mouseleftclick('*une nouvelle fiche*', 'sldr0')
ldtp.enterstring('*une nouvelle fiche*', 'sldr0', "<del>2")
ldtp.click('*une nouvelle fiche*', 'btnSaveEnter')

coordinate = ldtp.getobjectsize('*Gestion de dossiers*', 'pane0')
if (len(sys.argv) > 1) and (sys.argv[1] == 'origin'):
    ldtp.imagecapture('*Gestion de dossiers*', 'images/creer_fiche_test_priorite2_origin.png',
                      coordinate[0], coordinate[1], coordinate[2], coordinate[3])
else:
    ldtp.imagecapture('*Gestion de dossiers*', 'images/creer_fiche_test_priorite2.png',
                      coordinate[0], coordinate[1], coordinate[2], coordinate[3])
    im1 = Image.open("images/creer_fiche_test_priorite2.png")
    im2 = Image.open("images/creer_fiche_test_priorite2_origin.png")
    diff = ImageChops.difference(im2, im1)
    if diff.getbbox():
        print("Erreur possible dans 'Creation Fiche'")

fermer()