#ifndef MAPPEURCLIENTS_H
#define MAPPEURCLIENTS_H

#include <QObject>

#include "Modeles/client.h"

#include <QSqlDatabase>
#include <QSqlRecord>


class MappeurClients : public QObject
{
    Q_OBJECT

    // Extrait des objets Client de la base de données

public:

    /**
     * @brief MappeurClients
     * @param a_bd La base de données à utiliser
     * @param parent
     */
    explicit MappeurClients(QObject* parent = 0);

    /**
     * @brief getClient
     * @param id Le numéro du client à mapper
     * @return Le client s'il existe, NULL autrement
     */
    Client* getClient(int id);

    /**
     * @brief inserer
     * @param client Le client a insérer dans la base de donnée
     * @return succes
     */
    bool inserer(const Client* client);

    /**
     * @brief mettreAJour
     * Met à jour un client dans la base de données
     * @param client Le client à mettre à jour
     * @return Succès
     */
<<<<<<< HEAD
    bool mettreAJour(const Client* client);
=======
    Client* getClient(const int id);
>>>>>>> 45d7d11832c9fc05d5ca2bc845a62be9588290fd

private:

    /**
     * @brief mapper
     * @param ligne La ligne de la base de données à mapper en client
     * @return Le client
     */
    Client* mapper(const QSqlRecord ligne);

    /**
     * @brief preparerRequete Assigne les valeurs d'un client à une requête préparée
     * @param appareil Le client source
     * @param commande La commande SQL à préparer
     * @return La commande préparée
     */
    QSqlQuery* preparerRequete(const Client* client, const QString* commande);
};

#endif // MAPPEURCLIENTS_H
