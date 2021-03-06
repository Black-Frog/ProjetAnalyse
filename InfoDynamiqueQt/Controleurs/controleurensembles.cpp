#include "controleurensembles.h"

#include "Controleurs/application.h"
#include "Mappeurs/mappeuractions.h"
#include "Mappeurs/mappeurensembles.h"
#include "Modeles/ensembleactions.h"
#include "Vues/vueensemble.h"
#include "Vues/vuegestionensemble.h"
#include "Vues/vueprincipale.h"

#include <QMessageBox>

int ControleurEnsembles::creerEnsemble()
{
    int id = -1;
    VueGestionEnsemble* vue = new VueGestionEnsemble(Application::vuePrincipale());
    vue->setWindowTitle(tr("Créer un nouvel ensemble d'actions"));
    vue->setActions(MappeurActions::get());
    if (vue->exec() == vue->Accepted) {
        EnsembleActions* ensemble = new EnsembleActions(vue);
        extraireEnsemble(ensemble, vue);
        if (MappeurEnsembles::inserer(ensemble)) {
            id = ensemble->id();
            emit Application::get()->nombreEnsemblesModifie();
        }
    }
    vue->deleteLater();
    return id;
}

void ControleurEnsembles::modifierEnsemble(const int &idEnsemble)
{
    EnsembleActions* ensemble = MappeurEnsembles::get(idEnsemble);
    if (ensemble != NULL) {
        VueGestionEnsemble* vue = new VueGestionEnsemble(Application::vuePrincipale());
        vue->setWindowTitle(tr("Modifier un ensemble d'actions"));
        assignerEnsemble(vue, ensemble);
        if (vue->exec() == vue->Accepted) {
            extraireEnsemble(ensemble, vue);
            if (MappeurEnsembles::mettreAJour(ensemble)) {
                emit Application::get()->ensembleModifie();
            }
        }
        vue->deleteLater();
        ensemble->deleteLater();
    }
}

void ControleurEnsembles::voirEnsemble(const int &idEnsemble, const bool &modal)
{
    EnsembleActions* ensemble = MappeurEnsembles::get(idEnsemble);
    if (ensemble != NULL) {
        VueEnsemble* vue = new VueEnsemble(Application::vuePrincipale());
        vue->setModal(modal);
        vue->setWindowTitle(tr("Ensemble d'actions"));
        assignerEnsemble(vue, ensemble);
        vue->setActions(ensemble->actions());
        ensemble->deleteLater();
        connect(vue, SIGNAL(finished(int)), vue, SLOT(deleteLater()));
        vue->show();
    }
}

void ControleurEnsembles::supprimerEnsemble(const int &idEnsemble)
{
    EnsembleActions* ensemble = MappeurEnsembles::get(idEnsemble);
    if (ensemble != NULL) {
        QMessageBox* confirmation = new QMessageBox(QMessageBox::Warning,
                        tr("Confirmation de la suppression"),
                        tr("Supprimer l'ensemble «") + ensemble->nom()+"» ?",
                        QMessageBox::Yes | QMessageBox::No);
        confirmation->setDefaultButton(QMessageBox::No);
        if (confirmation->exec() == confirmation->Yes) {
            if (MappeurEnsembles::supprimer(ensemble)) {
                emit Application::get()->nombreEnsemblesModifie();
            }
        }
        confirmation->deleteLater();
        ensemble->deleteLater();
    }
}

void ControleurEnsembles::assignerEnsemble(VueGestionEnsemble* vue, const EnsembleActions* ensemble)
{
    vue->setNom(ensemble->nom());
    vue->setDescription(ensemble->description());
    vue->setActions(MappeurActions::horsEnsemble(ensemble->id()), MappeurActions::dansEnsemble(ensemble->id()));
}

void ControleurEnsembles::assignerEnsemble(VueEnsemble* vue, const EnsembleActions* ensemble)
{
    vue->setNom(ensemble->nom());
    vue->setDescription(ensemble->description());
    vue->setActions(ensemble->actions());
}

void ControleurEnsembles::extraireEnsemble(EnsembleActions* ensemble, const VueGestionEnsemble* vue)
{
    ensemble->setNom(vue->getNom());
    ensemble->setDescription(vue->getDescription());
    ensemble->setActions(MappeurActions::get(vue->getActionsSelectionnees()));
}
