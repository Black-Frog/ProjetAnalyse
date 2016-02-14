#include "Controleurs/controleurongletclients.h"

#include "Controleurs/application.h"
#include "Controleurs/requetessql.h"
#include "Controleurs/controleurappareils.h"
#include "Controleurs/controleurclients.h"
#include "Controleurs/controleurfiches.h"

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
    QObject::connect(Application::getInstance(), SIGNAL(clientModifie()), this, SLOT(rafraichirClients()));
    QObject::connect(Application::getInstance(), SIGNAL(nombreAppareilsChange()), this, SLOT(rafraichirClients()));
    QObject::connect(Application::getInstance(), SIGNAL(nombreClientsChange()), this, SLOT(rechargerClients()));
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
    QObject::connect(Application::getInstance(), SIGNAL(appareilModifie()), this, SLOT(rafraichirAppareils()));
    QObject::connect(Application::getInstance(), SIGNAL(nombreFichesChange()), this, SLOT(rafraichirAppareils()));
    QObject::connect(Application::getInstance(), SIGNAL(nombreAppareilsChange()), this, SLOT(rechargerAppareils()));
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
    fragmentFiches->boutonModifier()->deleteLater();
    fragmentFiches->boutonVoir()->deleteLater();
    boutonTraiter = fragmentFiches->ajouterBouton(4);
    boutonTraiter->setText(tr("Traiter"));
    boutonTraiter->setIcon(QIcon(":/Images/document-edit-sign"));
    QObject::connect(fragmentFiches, SIGNAL(clicCreer()), this, SLOT(ajouterFiche()));
    QObject::connect(fragmentFiches, SIGNAL(caseCochee()), this, SLOT(desactiverCritereFiches()));
    QObject::connect(fragmentFiches, SIGNAL(caseDecochee()), this, SLOT(activerCritereFiches()));
    QObject::connect(fragmentFiches, SIGNAL(doubleClicModele()), this, SLOT(voirFiche()));
    QObject::connect(fragmentAppareils, SIGNAL(modeleSelectionne(int)), this, SLOT(peuplerFiches(int)));
    QObject::connect(fragmentAppareils, SIGNAL(modeleSelectionne(int)), fragmentFiches, SLOT(show()));
    QObject::connect(fragmentAppareils, SIGNAL(modeleRelache()), fragmentFiches, SLOT(relacherModele()));
    QObject::connect(fragmentAppareils, SIGNAL(modeleRelache()), fragmentFiches, SLOT(hide()));
    QObject::connect(Application::getInstance(), SIGNAL(ficheModifiee()), this, SLOT(rafraichirFiches()));
    QObject::connect(Application::getInstance(), SIGNAL(nombreFichesChange()), this, SLOT(rechargerFiches()));
}

// Clients

void ControleurOngletClients::peuplerClients()
{
    QSqlQueryModel* clients = new QSqlQueryModel(this);
    clients->setQuery(*RequetesSQL::afficherClients, *Application::bd);
    fragmentClients->peuplerTableau(clients);
    fragmentClients->tableau()->hideColumn(fragmentClients->colonneId());
}

void ControleurOngletClients::ajouterClient() const
{
    ControleurClients::ajouterClient();
}

void ControleurOngletClients::modifierClient() const
{
    if (fragmentClients->idModele() != -1) {
        ControleurClients::modifierClient(fragmentClients->idModele());
    }
}

void ControleurOngletClients::voirClient() const
{
    if (fragmentClients->idModele() != -1) {
        ControleurClients::voirClient(fragmentClients->idModele());
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
        fragmentClients->tableau()->hideColumn(fragmentClients->colonneId());
    }
}

void ControleurOngletClients::rechargerClients()
{
    filtrerClients(fragmentClients->filtre());
}

void ControleurOngletClients::rafraichirClients()
{
    int selection = fragmentClients->rangeeSelectionnee();
    rechargerClients();
    fragmentClients->selectionnerRangee(selection);
}

// Appareils

void ControleurOngletClients::peuplerAppareils(const int &idClient)
{
    QSqlQueryModel* appareils = new QSqlQueryModel(this);
    appareils->setQuery(requeteAppareils(idClient));
    fragmentAppareils->peuplerTableau(appareils);
    fragmentAppareils->tableau()->hideColumn(fragmentAppareils->colonneId());
}

void ControleurOngletClients::ajouterAppareil() const
{
    if (fragmentClients->idModele() != -1) {
        ControleurAppareils::ajouterAppareil(fragmentClients->idModele());
    }
}

void ControleurOngletClients::modifierAppareil() const
{
    if (fragmentAppareils->idModele() != -1) {
        ControleurAppareils::modifierAppareil(fragmentAppareils->idModele());
    }
}

void ControleurOngletClients::activerBoutonEffacerAppareil(const bool &actif) const
{
    if (!actif) {
        boutonEffacerAppareil->setEnabled(false);
    } else {
        boutonEffacerAppareil->setEnabled(MappeurFiches::nombreFiches(fragmentAppareils->idModele()) == 0);
    }
}

void ControleurOngletClients::effacerAppareil() const
{
    if (fragmentAppareils->idModele() != -1) {
        ControleurAppareils::effacerAppareil(fragmentAppareils->idModele());
    }
}

void ControleurOngletClients::voirAppareil() const
{
    if (fragmentAppareils->idModele() != -1) {
        ControleurAppareils::voirAppareil(fragmentAppareils->idModele());
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
        peuplerAppareils(fragmentClients->idModele());
    } else {
        QSqlQuery requete = QSqlQuery(*Application::bd);
        requete.prepare(*RequetesSQL::filtrerAppareils);
        const QString meta = *ControleurBD::meta;
        requete.bindValue(":filtre", meta + filtre + meta);
        requete.exec();
        QSqlQueryModel* resultats = new QSqlQueryModel(this);
        resultats->setQuery(requete);
        fragmentAppareils->peuplerTableau(resultats);
        fragmentAppareils->tableau()->hideColumn(fragmentAppareils->colonneId());
    }
}

void ControleurOngletClients::rechargerAppareils()
{
    filtrerAppareils("");
}

void ControleurOngletClients::rafraichirAppareils()
{
    int selection = fragmentAppareils->rangeeSelectionnee();
    rechargerAppareils();
    fragmentAppareils->selectionnerRangee(selection);
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
    if (fragmentAppareils->idModele() != -1) {
        ControleurFiches::ajouterFiche(fragmentAppareils->idModele());
    }
}

void ControleurOngletClients::voirFiche() const
{
    if (fragmentAppareils->idModele() != -1) {
        ControleurFiches::voirFiche(fragmentAppareils->idModele());
    }
}

void ControleurOngletClients::activerCritereFiches()
{
    commandeFiches = RequetesSQL::fichesActivesPourAppareil;
    peuplerFiches(fragmentAppareils->idModele());
}

void ControleurOngletClients::desactiverCritereFiches()
{
    commandeFiches = RequetesSQL::toutesFichesPourAppareil;
    peuplerFiches(fragmentAppareils->idModele());
}

QSqlQuery ControleurOngletClients::requeteFiches(const int &idAppareil) const
{
    QSqlQuery requete = QSqlQuery(*Application::bd);
    requete.prepare(*commandeFiches);
    requete.bindValue(":idAppareil", idAppareil);
    requete.exec();
    return requete;
}

void ControleurOngletClients::rechargerFiches()
{
    peuplerFiches(fragmentAppareils->idModele());
}

void ControleurOngletClients::rafraichirFiches()
{
    int selection = fragmentFiches->rangeeSelectionnee();
    rechargerFiches();
    fragmentFiches->selectionnerRangee(selection);
}
