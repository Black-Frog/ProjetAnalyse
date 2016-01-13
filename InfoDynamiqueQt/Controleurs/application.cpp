#include "application.h"

#include <QDebug>

#include "Controleurs/controleuractions.h"
#include "Controleurs/controleurappareils.h"
#include "Controleurs/controleurclients.h"
#include "Controleurs/controleurfiches.h"
#include "Vues/vueprincipale.h"

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv)
{
    m_instance = this;
    controleurBD = new ControleurBD(this);
    controleurBD->connecterDossiers();
    bd = controleurBD->getBd();
    actions = new MappeurActions(bd, this);
    appareils = new MappeurAppareils(bd, this);
    clients = new MappeurClients(bd, this);
    fabricants = new MappeurFabricants(bd, this);
    pieces = new MappeurPieces(bd, this);
    statuts = new MappeurStatuts(bd, this);
    techniciens = new MappeurTechniciens(bd, this);
    typesAppareils = new MappeurTypeAppareils(bd, this);
}

Application* Application::m_instance = NULL;

Application* Application::getInstance()
{
    return m_instance;
}

void Application::demarrer()
{
    creerFenetre();
    chargerOnglet();
    vuePrincipale->show();
}

void Application::debug()
{
    QList<Action*>* listeActions = actions->getActions();
    for (QList<Action*>::const_iterator i = listeActions->constBegin(); i != listeActions->constEnd(); ++i)
    {
        qDebug() << (*i)->out();
    }
}

void Application::creerFenetre() {
    vuePrincipale = new VuePrincipale();
    controleurClients = new ControleurClients(vuePrincipale, this);
    controleurFiches = new ControleurFiches(vuePrincipale, this);
    controleurAppareils = new ControleurAppareils(vuePrincipale, this);
    controleurActions = new ControleurActions(vuePrincipale, this);
    clientsCharges = false;
    fichesChargees = false;
    appareilsCharges = false;
    actionsChargees = false;
    paresseux = QObject::connect(vuePrincipale->getOnglets(), SIGNAL(currentChanged(int)), this, SLOT(chargerOnglet()));
}

void Application::chargerOnglet() {
    QWidget* onglet = vuePrincipale->getOnglets()->currentWidget();
    if (onglet == vuePrincipale->getOngletClients() && !clientsCharges) {
        controleurClients->peuplerClients();
        clientsCharges = true;
    } else if (onglet == vuePrincipale->getOngletFiches() && !fichesChargees) {
        controleurFiches->peuplerFiches();
        fichesChargees = true;
    } else if (onglet == vuePrincipale->getOngletAppareils() && !appareilsCharges) {
        controleurAppareils->peuplerAppareils();
        appareilsCharges = true;
    } else if (onglet == vuePrincipale->getOngletActions() && !actionsChargees) {
        controleurActions->peuplerActions();
        controleurActions->peuplerEnsembles();
        actionsChargees = true;
    }
    verifierParesseux();
}

void Application::verifierParesseux() {
    if (clientsCharges && fichesChargees && appareilsCharges && actionsChargees) {
        QObject::disconnect(paresseux);
    }
}
