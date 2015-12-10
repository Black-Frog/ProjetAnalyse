#ifndef CONTROLEURCLIENTS_H
#define CONTROLEURCLIENTS_H

#include <QObject>
#include <QSqlQuery>
#include <QSplitter>

#include "Controleurs/controleurgestionappareil.h"
#include "Controleurs/controleurgestionclient.h"
#include "Controleurs/controleurgestionfiche.h"
#include "Vues/vuefragment.h"
#include "Vues/vueprincipale.h"

class ControleurClients : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief ControleurClients
     * @param vuePrincipale
     * @param parent
     */
    explicit ControleurClients(VuePrincipale* vuePrincipale, QObject* parent = 0);

private:

    // Le séparateur redimensionnable contenant les fragments
    QSplitter* splitter;

    // Le contrôleur de gestion de clients
    ControleurGestionClient *controleurGestionClient;

    // Le contrôleur de gestion d'appareils
    ControleurGestionAppareil *controleurGestionAppareil;

    // Le contrôleur de gestion de fiches
    ControleurGestionFiche *controleurGestionFiche;

    // Le fragment des clients
    VueFragment *fragmentClients;

    // Le fragment des appareils
    VueFragment *fragmentAppareils;

    // Le fragment des fiches
    VueFragment *fragmentFiches;

    /**
     * @brief configurerFragmentClients
     * Configure fragmentClients
     */
    void configurerFragmentClients();

    /**
     * @brief configurerFragmentClients
     * Configure fragmentAppareils
     */
    void configurerFragmentAppareils();

    /**
     * @brief configurerFragmentClients
     * Configure fragmentFiches
     */
    void configurerFragmentFiches();

    // La requête utilisée pour peupler les clients
    const QString* requeteClients;

    /**
     * @brief requeteAppareils
     * @param idClient Le client dont on souhaite afficher les appareils
     * @return La requête utilisée pour peupler les appareils
     */
    QSqlQuery requeteAppareils(int idClient) const;

    /**
     * @brief requeteFiches
     * @param idAppareil L'appareil dont on souhaite afficher les fiches
     * @return La requête utilisée pour peupler les fiches
     */
    QSqlQuery requeteFiches(int idAppareil) const;

public slots:

    /**
     * @brief peuplerClients
     * Peuple la table du fragmentClients avec tous les clients
     */
    void peuplerClients();

    /**
     * @brief peuplerAppareils
     * Peuple la table de fragmentAppareils avec tous les appareils du client donné
     * @param int L'id du client
     */
    void peuplerAppareils(int idClient);

    /**
     * @brief peuplerFiches
     * Peuple la table de fragmentFiches avec toutes les fiches de l'appareil donné
     * @param int L'id de l'appareil
     */
    void peuplerFiches(int idAppareil);

    /**
     * @brief modifierClient
     * Lance la modification du client sélectionné
     */
    void modifierClient();

    /**
     * @brief modifierClient
     * Lance la visualisation du client sélectionné
     */
    void voirClient();
};

#endif // CONTROLEURCLIENTS_H
