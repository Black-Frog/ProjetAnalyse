#include "Controleurs/controleurappareils.h"

#include "Controleurs/application.h"
#include "Mappeurs/mappeurappareils.h"
#include "Mappeurs/mappeurfabricants.h"
#include "Mappeurs/mappeurfiches.h"
#include "Mappeurs/mappeurtypeappareils.h"
#include "Modeles/appareil.h"
#include "Vues/vueappareil.h"
#include "Vues/vuegestionappareil.h"
#include "Vues/vueprincipale.h"

#include <QMessageBox>

int ControleurAppareils::ajouterAppareil(const int &idClient)
{
    int id = -1;
    VueGestionAppareil* vue = new VueGestionAppareil(Application::vuePrincipale());
    vue->setWindowTitle(tr("Créer un nouvel appareil"));
    vue->setTypes(MappeurTypeAppareils::get());
    vue->setFabricants(MappeurFabricants::get());
    if (vue->exec() == vue->Accepted) {
        Appareil* appareil = new Appareil(vue);
        appareil->setIdClient(idClient);
        extraireAppareil(appareil, vue);
        if (MappeurAppareils::inserer(appareil)) {
            id = appareil->id();
            emit Application::get()->nombreAppareilsChange();
        }
        vue->deleteLater();
    }
    return id;
}

void ControleurAppareils::modifierAppareil(const int &idAppareil)
{
    Appareil* appareil = MappeurAppareils::get(idAppareil);
    if (appareil != NULL) {
        VueGestionAppareil* vue = new VueGestionAppareil(Application::vuePrincipale());
        vue->setWindowTitle(tr("Modifier un appareil"));
        assignerAppareil(vue, appareil);
        if (vue->exec() == vue->Accepted) {
            extraireAppareil(appareil, vue);
            if (MappeurAppareils::mettreAJour(appareil)) {
                emit Application::get()->appareilModifie();
            }
        }
        vue->deleteLater();
        appareil->deleteLater();
    }
}

void ControleurAppareils::voirAppareil(const int &idAppareil, QWidget* parent)
{
    Appareil* appareil = MappeurAppareils::get(idAppareil);
    if (appareil != NULL) {
        VueAppareil* vue;
        if (parent) {
            vue = new VueAppareil(parent);
        } else {
            vue = new VueAppareil(Application::vuePrincipale());
        }
        assignerAppareil(vue, appareil);
        appareil->deleteLater();
        connect(vue, SIGNAL(finished(int)), vue, SLOT(deleteLater()));
        vue->show();
    }
}

void ControleurAppareils::effacerAppareil(const int &idAppareil)
{
    int usages = MappeurFiches::pourAppareil(idAppareil);
    if (usages == 0) {
        Appareil* appareil = MappeurAppareils::get(idAppareil);
        QMessageBox* confirmation = new QMessageBox(QMessageBox::Warning,
                        tr("Confirmation de la suppression"),
                        tr("Supprimer l'appareil?\n") + appareil->joliOut(),
                        QMessageBox::Yes | QMessageBox::No);
        confirmation->setDefaultButton(QMessageBox::No);
        if (confirmation->exec() == confirmation->Yes) {
            if (MappeurAppareils::supprimer(appareil)) {
                emit Application::get()->nombreAppareilsChange();
            }
        }
        confirmation->deleteLater();
        appareil->deleteLater();
    }
}

void ControleurAppareils::assignerAppareil(VueGestionAppareil* vue, const Appareil* appareil)
{
    vue->setTypes(MappeurTypeAppareils::get(), appareil->nomType());
    vue->setFabricants(MappeurFabricants::get(), appareil->nomFabricant());
    vue->setMotDePasse(appareil->motDePasse());
    vue->setDescription(appareil->description());
}

void ControleurAppareils::assignerAppareil(VueAppareil* vue, const Appareil* appareil)
{
    vue->setType(appareil->nomType());
    vue->setFabricant(appareil->nomFabricant());
    vue->setMotDePasse(appareil->motDePasse());
    vue->setDescription(appareil->description());
}

void ControleurAppareils::extraireAppareil(Appareil* appareil, const VueGestionAppareil* vue)
{
    appareil->setMotDePasse(vue->getMotDePasse());
    appareil->setType(MappeurTypeAppareils::get(vue->getType()));
    appareil->setFabricant(MappeurFabricants::get(vue->getFabricant()));
    appareil->setDescription(vue->getDescription());
}
