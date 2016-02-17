#include "controleurensembles.h"

#include "Controleurs/application.h"
#include "Mappeurs/mappeuractions.h"
#include "Mappeurs/mappeurensembles.h"

#include <QMessageBox>

void ControleurEnsembles::creerEnsemble()
{
    VueGestionEnsemble* vue = new VueGestionEnsemble(Application::vuePrincipale());
    vue->setWindowTitle(tr("Créer un nouvel ensemble de tâches"));
    vue->setActions(MappeurActions::getActions());
    if (vue->exec() == vue->Accepted) {
        EnsembleActions* ensemble = new EnsembleActions(vue);
        extraireEnsemble(ensemble, vue);
        if (MappeurEnsembles::inserer(ensemble)) {
            emit Application::getInstance()->nombreEnsemblesModifie();
        }
    }
    vue->deleteLater();
}

void ControleurEnsembles::modifierEnsemble(const int &idEnsemble)
{
    EnsembleActions* ensemble = MappeurEnsembles::getEnsemble(idEnsemble);
    if (ensemble != NULL) {
        VueGestionEnsemble* vue = new VueGestionEnsemble(Application::vuePrincipale());
        vue->setWindowTitle(tr("Modifier un ensemble de tâches"));
        assignerEnsemble(vue, ensemble);
        if (vue->exec() == vue->Accepted) {
            extraireEnsemble(ensemble, vue);
            if (MappeurEnsembles::mettreAJour(ensemble)) {
                emit Application::getInstance()->ensembleModifie();
            }
        }
        vue->deleteLater();
    }
    ensemble->deleteLater();
}

void ControleurEnsembles::voirEnsemble(const int &idEnsemble, const bool &modal)
{
    EnsembleActions* ensemble = MappeurEnsembles::getEnsemble(idEnsemble);
    if (ensemble != NULL) {
        VueEnsemble* vue = new VueEnsemble(Application::vuePrincipale());
        vue->setModal(modal);
        vue->setWindowTitle(tr("Ensemble de tâches"));
        assignerEnsemble(vue, ensemble);
        vue->setActions(ensemble->actions());
        QObject::connect(vue, SIGNAL(finished(int)), vue, SLOT(deleteLater()));
        vue->show();
    }
    ensemble->deleteLater();
}

void ControleurEnsembles::supprimerEnsemble(const int &idEnsemble)
{
    EnsembleActions* ensemble = MappeurEnsembles::getEnsemble(idEnsemble);
    if (ensemble != NULL) {
        QMessageBox* confirmation = new QMessageBox(QMessageBox::Warning,
                        tr("Confirmation de la suppression"),
                        tr("Supprimer l'ensemble «") + ensemble->nom()+"» ?",
                        QMessageBox::Ok | QMessageBox::Cancel);
        confirmation->setDefaultButton(QMessageBox::Cancel);
        if (confirmation->exec() == confirmation->Ok) {
            if (MappeurEnsembles::supprimer(ensemble)) {
                emit Application::getInstance()->nombreEnsemblesModifie();
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
    vue->setActions(MappeurActions::actionsHorsEnsemble(ensemble->id()), MappeurActions::actionsDansEnsemble(ensemble->id()));
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
    ensemble->setActions(MappeurActions::getActions(vue->getActionsSelectionnees()));
}
