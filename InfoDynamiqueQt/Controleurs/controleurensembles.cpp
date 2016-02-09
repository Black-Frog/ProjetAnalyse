#include "controleurensembles.h"

#include "Controleurs/application.h"
#include "Mappeurs/mappeuractions.h"
#include "Mappeurs/mappeurensembles.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlQueryModel>

ControleurGestionEnsemble::ControleurGestionEnsemble(QObject *parent) : QObject(parent) {}

void ControleurGestionEnsemble::creerEnsemble()
{
    VueGestionEnsemble* vue = new VueGestionEnsemble(Application::vuePrincipale());
    vue->setWindowTitle(tr("Créer un nouvel ensemble de tâches"));
    vue->setActionsHorsEnsemble(MappeurActions::getActions());
    if (vue->exec() == vue->Accepted) {
        EnsembleActions* ensemble = new EnsembleActions(vue);
        extraireEnsemble(ensemble, vue);
        if (MappeurEnsembles::inserer(ensemble)) {
            emit ensemblesModifies();
        } else {
            qDebug() << "Pas marché :(";
        }
        vue->deleteLater();
    }
}

void ControleurGestionEnsemble::modifierEnsemble(const int &idEnsemble)
{
    EnsembleActions* ensemble = MappeurEnsembles::getEnsemble(idEnsemble);
    VueGestionEnsemble* vue = new VueGestionEnsemble(Application::vuePrincipale());
    vue->setWindowTitle(tr("Modifier un ensemble de tâches"));
    QList<Action*>* actionsHorsEnsemble = MappeurActions::actionsHorsEnsemble(ensemble->id());
    vue->setActionsHorsEnsemble(actionsHorsEnsemble);
    vue->setActionsDansEnsemble(MappeurActions::actionsDansEnsemble(ensemble->id()));
    assignerEnsemble(vue, ensemble);
    if (vue->exec() == vue->Accepted) {
        extraireEnsemble(ensemble, vue);
        if (MappeurEnsembles::mettreAJour(ensemble)) {
            emit ensemblesModifies();
        } else {
            qDebug() << "Pas marché :(";
        }
        vue->deleteLater();
    }
}

void ControleurGestionEnsemble::voirEnsemble(const int &idEnsemble) const
{
    VueEnsemble* vue = new VueEnsemble(Application::vuePrincipale());
    vue->setWindowTitle(tr("Ensemble de tâches"));
    EnsembleActions* ensemble = MappeurEnsembles::getEnsemble(idEnsemble);
    QObject::connect(vue, SIGNAL(finished(int)), vue, SLOT(deleteLater()));
    assignerEnsemble(vue, ensemble);
    vue->setActions(ensemble->actions());
    vue->show();
    ensemble->deleteLater();
}

void ControleurGestionEnsemble::assignerEnsemble(VueGestionEnsemble* vue, const EnsembleActions* ensemble) const
{
    vue->setNom(ensemble->nom());
    vue->setDescription(ensemble->description());
}

void ControleurGestionEnsemble::assignerEnsemble(VueEnsemble* vue, const EnsembleActions* ensemble) const
{
    vue->setNom(ensemble->nom());
    vue->setDescription(ensemble->description());
    vue->setActions(ensemble->actions());
}

void ControleurGestionEnsemble::extraireEnsemble(EnsembleActions* ensemble, const VueGestionEnsemble* vue) const
{
    ensemble->setNom(vue->getNom());
    ensemble->setDescription(vue->getDescription());
    ensemble->setActions(vue->getActionsDansEnsemble());
}

void ControleurGestionEnsemble::supprimerEnsemble(const int &idEnsemble)
{
    EnsembleActions* ensemble = MappeurEnsembles::getEnsemble(idEnsemble);
    QMessageBox* confirmation = new QMessageBox(QMessageBox::Warning,
                    tr("Confirmation de la suppression"),
                    tr("Supprimer l'ensemble «") + ensemble->nom()+"» ?",
                    QMessageBox::Apply | QMessageBox::Cancel);
    if (confirmation->exec() == confirmation->Apply) {
        if (MappeurEnsembles::supprimer(ensemble)) {
            emit ensemblesModifies();
        }
    }
    confirmation->deleteLater();
    ensemble->deleteLater();
}
