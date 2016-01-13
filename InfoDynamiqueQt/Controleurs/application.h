#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "Controleurs/controleuractions.h"
#include "Controleurs/controleurappareils.h"
#include "Controleurs/controleurbd.h"
#include "Controleurs/controleurclients.h"
#include "Controleurs/controleurfiches.h"

#include "Mappeurs/mappeuractions.h"
#include "Mappeurs/mappeurappareils.h"
#include "Mappeurs/mappeurclients.h"
#include "Mappeurs/mappeurfabricants.h"
#include "Mappeurs/mappeurpieces.h"
#include "Mappeurs/mappeurstatuts.h"
#include "Mappeurs/mappeurtaches.h"
#include "Mappeurs/mappeurtechniciens.h"
#include "Mappeurs/mappeurtypeappareils.h"

class Application : public QApplication
{
    Q_OBJECT

public:

    explicit Application(int &argc, char **argv);
    static Application *getInstance();

    QSqlDatabase* bd;
    ControleurBD* controleurBD;
    MappeurActions* actions;
    MappeurAppareils* appareils;
    MappeurClients* clients;
    MappeurFabricants* fabricants;
    MappeurPieces* pieces;
    MappeurStatuts* statuts;
    MappeurTechniciens* techniciens;
    MappeurTypeAppareils* typesAppareils;

    void demarrer();
    void debug();

private:

    static Application *m_instance;

    // La vue principale de l'application
    VuePrincipale* vuePrincipale;

    // Le contrôleur de la vue des clients
    ControleurClients* controleurClients;

    bool clientsCharges;

    // Le contrôleur de la vue des fiches
    ControleurFiches* controleurFiches;

    bool fichesChargees;

    // Le contrôleur de la vue des appareils
    ControleurAppareils* controleurAppareils;

    bool appareilsCharges;

    // Le contrôleur de la vue des actions
    ControleurActions* controleurActions;

    bool actionsChargees;

    QMetaObject::Connection paresseux;

    void verifierParesseux();

    void creerFenetre();
signals:

    /**
     * @brief executer
     * Lance l'exécution de l'application
     */
    void executer();

public slots:

    void chargerOnglet();

};

#endif // APPLICATION_H
