#include "Controleurs/controleurongletclients.h"

#include "Controleurs/application.h"
#include "Controleurs/requetessql.h"

#include <QDebug>
#include <QLayout>
#include <QSqlQueryModel>

ControleurOngletClients::ControleurOngletClients(QWidget* vue)
    : QObject(vue)
{
    splitter = new QSplitter(Qt::Vertical, vue);
    vue->layout()->addWidget(splitter);
    splitter->setChildrenCollapsible(false);
    configurerFragmentClients();
    configurerFragmentAppareils();
    configurerFragmentFiches();
    fragmentClients->champ()->setFocus();
}

// Configuration

void ControleurOngletClients::configurerFragmentClients()
{
    fragmentClients = new Fragment(splitter);
    fragmentClients->setEtiquette(tr("Clients"));
    fragmentClients->retirerCaseCocher();
    QObject::connect(fragmentClients, SIGNAL(clicCreer()), this, SLOT(ajouterClient()));
    QObject::connect(fragmentClients, SIGNAL(clicEditer()), this, SLOT(modifierClient()));
    QObject::connect(fragmentClients, SIGNAL(clicVoir()), this, SLOT(voirClient()));
    QObject::connect(fragmentClients, SIGNAL(rechercher(QString)), this, SLOT(filtrerClients(QString)));
    QObject::connect(fragmentClients, SIGNAL(doubleClicModele()), this, SLOT(voirClient()));
    QObject::connect(Application::getInstance(), SIGNAL(clientsModifies()), this, SLOT(rechargerClients()));
}

void ControleurOngletClients::configurerFragmentAppareils()
{
    fragmentAppareils = new Fragment(splitter);
    fragmentAppareils->setEtiquette(tr("Appareils"));
    fragmentAppareils->retirerCaseCocher();
    fragmentAppareils->retirerChamp();
    boutonEffacerAppareil = fragmentAppareils->ajouterBoutonNonConnecte(4, tr("Effacer"), QIcon(":/Images/edit-delete"));
    QObject::connect(boutonEffacerAppareil, SIGNAL(clicked()), this, SLOT(effacerAppareil()));
    QObject::connect(fragmentAppareils, SIGNAL(selectionValide(bool)), this, SLOT(activerBoutonEffacerAppareil(bool)));
    QObject::connect(fragmentAppareils, SIGNAL(clicCreer()), this, SLOT(ajouterAppareil()));
    QObject::connect(fragmentAppareils, SIGNAL(clicEditer()), this, SLOT(modifierAppareil()));
    QObject::connect(fragmentAppareils, SIGNAL(clicVoir()), this, SLOT(voirAppareil()));
    QObject::connect(fragmentAppareils, SIGNAL(doubleClicModele()), this, SLOT(voirAppareil()));
    QObject::connect(Application::getInstance(), SIGNAL(appareilsModifies()), this, SLOT(rechargerAppareils()));
    QObject::connect(Application::getInstance(), SIGNAL(nombreAppareilsChange()), this, SLOT(rechargerNombreAppareils()));
    QObject::connect(fragmentClients, SIGNAL(modeleSelectionne(int)), this, SLOT(peuplerAppareils(int)));
    QObject::connect(fragmentClients, SIGNAL(modeleSelectionne(int)), fragmentAppareils, SLOT(show()));
    QObject::connect(fragmentClients, SIGNAL(modeleRelache()), fragmentAppareils, SLOT(relacherModele()));
    QObject::connect(fragmentClients, SIGNAL(modeleRelache()), fragmentAppareils, SLOT(hide()));
}

void ControleurOngletClients::configurerFragmentFiches()
{
    commandeFiches = RequetesSQL::toutesFichesPourAppareil;
    fragmentFiches = new Fragment(splitter);
    fragmentFiches->setEtiquette(tr("Fiches"));
    fragmentFiches->caseCocher()->setChecked(true);
    fragmentFiches->caseCocher()->setText(tr("Afficher toutes les fiches"));
    fragmentFiches->retirerChamp();
    gestionFiche = new ControleurFiches(fragmentFiches);
    QObject::connect(fragmentFiches, SIGNAL(clicCreer()), this, SLOT(ajouterFiche()));
    QObject::connect(fragmentFiches, SIGNAL(clicEditer()), this, SLOT(modifierFiche()));
    QObject::connect(fragmentFiches, SIGNAL(caseCochee()), this, SLOT(desactiverCritereFiches()));
    QObject::connect(fragmentFiches, SIGNAL(caseDecochee()), this, SLOT(activerCritereFiches()));
    QObject::connect(fragmentFiches, SIGNAL(doubleClicModele()), this, SLOT(voirFiche()));
    QObject::connect(fragmentAppareils, SIGNAL(modeleSelectionne(int)), this, SLOT(peuplerFiches(int)));
    QObject::connect(fragmentAppareils, SIGNAL(modeleSelectionne(int)), fragmentFiches, SLOT(show()));
    QObject::connect(fragmentAppareils, SIGNAL(modeleRelache()), fragmentFiches, SLOT(relacherModele()));
    QObject::connect(fragmentAppareils, SIGNAL(modeleRelache()), fragmentFiches, SLOT(hide()));
}

// Clients

void ControleurOngletClients::peuplerClients()
{
    QSqlQueryModel* clients = new QSqlQueryModel(this);
    clients->setQuery(*RequetesSQL::afficherClients, *Application::bd);
    fragmentClients->peuplerTableau(clients);
    fragmentClients->getTableau()->hideColumn(fragmentClients->getColonneId());
}

void ControleurOngletClients::modifierClient() const
{
    if (fragmentClients->getIdModele() != -1) {
        ControleurClients::modifierClient(fragmentClients->getIdModele());
    }
}

void ControleurOngletClients::voirClient() const
{
    if (fragmentClients->getIdModele() != -1) {
        ControleurClients::voirClient(fragmentClients->getIdModele());
    }
}

void ControleurOngletClients::filtrerClients(const QString &filtre)
{
    if (filtre.isEmpty()) {
        peuplerClients();
    } else {
        QSqlQuery requete = QSqlQuery(*Application::bd);
        requete.prepare(*RequetesSQL::filtrerClients);
        const QString meta = *ControleurBD::meta;
        requete.bindValue(":filtre", meta + filtre + meta);
        requete.exec();
        QSqlQueryModel* resultats = new QSqlQueryModel(this);
        resultats->setQuery(requete);
        fragmentClients->peuplerTableau(resultats);
        fragmentClients->getTableau()->hideColumn(fragmentClients->getColonneId());
    }
}

void ControleurOngletClients::rechargerClients()
{
    filtrerClients(fragmentClients->getFiltre());
}

// Appareils

void ControleurOngletClients::peuplerAppareils(const int &idClient)
{
    QSqlQueryModel* appareils = new QSqlQueryModel(this);
    appareils->setQuery(requeteAppareils(idClient));
    fragmentAppareils->peuplerTableau(appareils);
    fragmentAppareils->getTableau()->hideColumn(fragmentAppareils->getColonneId());
}

void ControleurOngletClients::ajouterAppareil() const
{
    if (fragmentClients->getIdModele() != -1) {
        ControleurAppareils::ajouterAppareil(fragmentClients->getIdModele());
    }
}

void ControleurOngletClients::modifierAppareil() const
{
    if (fragmentAppareils->getIdModele() != -1) {
        ControleurAppareils::modifierAppareil(fragmentAppareils->getIdModele());
    }
}

void ControleurOngletClients::activerBoutonEffacerAppareil(const bool &actif) const
{
    if (!actif) {
        boutonEffacerAppareil->setEnabled(false);
    } else if (MappeurFiches::fichesPourAppareil(fragmentAppareils->getIdModele())->isEmpty()) {
        boutonEffacerAppareil->setEnabled(true);
    }
}

void ControleurOngletClients::effacerAppareil() const
{
    if (fragmentAppareils->getIdModele() != -1) {
        ControleurAppareils::effacerAppareil(fragmentAppareils->getIdModele());
    }
}

void ControleurOngletClients::voirAppareil() const
{
    if (fragmentAppareils->getIdModele() != -1) {
        ControleurAppareils::voirAppareil(fragmentAppareils->getIdModele());
    }
}

QSqlQuery ControleurOngletClients::requeteAppareils(const int &idClient) const
{
    QSqlQuery requete = QSqlQuery(*Application::bd);
    requete.prepare(*RequetesSQL::appareilsPourClient);
    requete.bindValue(":idClient", idClient);
    requete.exec();
    return requete;
}

void ControleurOngletClients::filtrerAppareils(const QString &filtre)
{
    if (filtre.isEmpty()) {
        peuplerAppareils(fragmentClients->getIdModele());
    } else {
        QSqlQuery requete = QSqlQuery(*Application::bd);
        requete.prepare(*RequetesSQL::filtrerAppareils);
        const QString meta = *ControleurBD::meta;
        requete.bindValue(":filtre", meta + filtre + meta);
        requete.exec();
        QSqlQueryModel* resultats = new QSqlQueryModel(this);
        resultats->setQuery(requete);
        fragmentAppareils->peuplerTableau(resultats);
        fragmentAppareils->getTableau()->hideColumn(fragmentAppareils->getColonneId());
    }
}

void ControleurOngletClients::rechargerAppareils()
{
    filtrerAppareils("");
}

void ControleurOngletClients::rechargerNombreAppareils()
{
    int dernierIndex = fragmentClients->getDernierIndexSelectionne();
    rechargerClients();
    fragmentClients->getTableau()->selectRow(dernierIndex);
}

// Fiches

void ControleurOngletClients::peuplerFiches(const int &idAppareil)
{
    QSqlQueryModel* fiches = new QSqlQueryModel(this);
    fiches->setQuery(requeteFiches(idAppareil));
    fragmentFiches->peuplerTableau(fiches);
}

void ControleurOngletClients::ajouterFiche() const
{
    if (fragmentAppareils->getIdModele() != -1) {
        gestionFiche->ajouterFiche(fragmentAppareils->getIdModele());
    }
}

void ControleurOngletClients::ajouterClient() const
{
    ControleurClients::ajouterClient();
}

void ControleurOngletClients::modifierFiche() const
{
    if (fragmentFiches->getIdModele() != -1) {
        gestionFiche->modifierFiche(fragmentFiches->getIdModele());
    }
}

void ControleurOngletClients::voirFiche() const
{
    if (fragmentFiches->getIdModele() != -1) {
        gestionFiche->modifierFiche(fragmentFiches->getIdModele());
    }
}

void ControleurOngletClients::activerCritereFiches()
{
    commandeFiches = RequetesSQL::fichesActivesPourAppareil;
    peuplerFiches(fragmentAppareils->getIdModele());
}

void ControleurOngletClients::desactiverCritereFiches()
{
    commandeFiches = RequetesSQL::toutesFichesPourAppareil;
    peuplerFiches(fragmentAppareils->getIdModele());
}

QSqlQuery ControleurOngletClients::requeteFiches(const int &idAppareil) const
{
    QSqlQuery requete = QSqlQuery(*Application::bd);
    requete.prepare(*commandeFiches);
    requete.bindValue(":idAppareil", idAppareil);
    requete.exec();
    return requete;
}