#ifndef MAPPEURAPPAREILS_H
#define MAPPEURAPPAREILS_H

#include <QObject>

#include "Mappeurs/mappeurtypeappareils.h"

#include "Modeles/action.h"
#include "Modeles/appareil.h"
#include "Modeles/client.h"

#include <QSqlDatabase>
#include <QSqlRecord>

class MappeurAppareils : public QObject
{
    Q_OBJECT

    // Extrait des objets Appareil de la base de données

public:

    /**
     * @brief MappeurAppareils
     * @param a_bd La base de données à utiliser
     * @param parent
     */
    explicit MappeurAppareils(QObject* parent = 0);

    /**
     * @brief getAppareil
     * @param id Le numéro de l'appareil à mapper
     * @return L'appareil s'il existe, NULL autrement
     */
    static Appareil* getAppareil(const int &id);

    /**
     * @brief appareilsPourClient
     * Trouve les appareils appartenant à un client
     * @param client Le client cible
     * @return La liste des appareils appartenant au client
     */
    static QList<Appareil*>* appareilsPourClient(const int &idClient);

    /**
     * @brief mettreAJour
     * Met à jour un appareil dans la base de données
     * @param appareil L'appareil à mettre à jour
     * @return Succès
     */
    static bool mettreAJour(const Appareil* appareil);

    /**
     * @brief inserer
     * Insère un nouvel appareil dans la base de données
     * @param appareil L'appareil à ajouter
     * @return Succès
     */
    static bool inserer(const Appareil* appareil);

private:

    /**
     * @brief mapper
     * @param ligne La ligne de la base de données à mapper en appareil
     * @return L'appareil
     */
    static Appareil* mapper(const QSqlRecord &ligne);


    /**
     * @brief mapper
     * Construit tous les appareils se retrouvant dans les résulats d'une requête SQL
     * @param requete La requête à mapper
     * @return Les appareils présents dans la requête
     */
    static QList<Appareil*>* mapper(QSqlQuery &requete);

    /**
     * @brief preparerRequete Assigne les valeurs d'un appareil à une requête préparée
     * @param appareil L'appareil source
     * @param commande La commande SQL à préparer
     * @return La commande préparée
     */
    static QSqlQuery* preparerRequete(const Appareil* appareil, const QString &commande);

    /**
     * @brief ecrire
     * Effectue une opération SQL à l'intérieur d'une transaction
     * La transaction est annulée si l'opération échoue et validée autrement
     * @param appareil L'appareil à inclure dans l'opération SQL
     * @param commande La commande à exécuter
     * @return Succès de l'opération
     */
    static bool ecrire(const Appareil* appareil, const QString &commande);

};

#endif // MAPPEURAPPAREILS_H
