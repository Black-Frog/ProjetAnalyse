#ifndef MAPPEURACTIONS_H
#define MAPPEURACTIONS_H

class Action;

template <class T> class QList;
class QString;
class QSqlQuery;
class QSqlRecord;

class MappeurActions {

    // Lit et écrit des objets Action dans la base de données

public:

    /**
     * @brief get
     * @param id Le numéro de l'action à mapper
     * @return L'action si elle existe, NULL autrement
     */
    static Action* get(const int &id);

    /**
     * @brief get
     * @return La liste de toutes les actions de la base de données.
     */
    static QList<Action*>* get();

    /**
     * @brief getActions
     * Mappe une liste d'actions possédant les id donnés
     * Ne retourne pas d'objets invalide
     * @param listeId La liste d'id d'actions à mapper
     * @return La liste des actions mappées
     */
    static QList<Action*>* get(const QList<int>* listeId);

    /**
     * @brief sauf
     * Retourne toutes les actions dont l'id ne fait pas partie de la liste
     * @param idExclus La liste d'id d'actions à exclure
     * @return Les actions restantes
     */
    static QList<Action*>* sauf(const QList<int>* idExclus);

    /**
     * @brief dansEnsemble
     * Trouve les actions faisant partie d'un ensemble donné
     * @param idEnsemble L'id de l'ensemble à chercher
     * @return Toutes les actions qui font partie de l'ensemble
     */
    static QList<Action*>* dansEnsemble(const int &idEnsemble);

    /**
     * @brief horsEnsemble
     * Trouve les actions ne faisant pas partie d'un ensemble donné
     * @param idEnsemble L'id de l'ensemble à chercher
     * @return Toutes les actions qui ne font pas partie de l'ensemble
     */
    static QList<Action*>* horsEnsemble(const int &idEnsemble);

    /**
     * @brief mettreAJour
     * Met à jour une action dans la base de données
     * @param action L'action à mettre à jour
     * @return Succès de l'écriture
     */
    static bool mettreAJour(const Action* action);

    /**
     * @brief inserer
     * Inscrit une nouvelle action dans la base de données
     * @param action L'action à inscrire
     * @return Succès de l'écriture
     */
    static bool inserer(Action* action);

    /**
     * @brief supprimer
     * Efface une action de la base de données
     * @param action L'action à effacer
     * @return Succès de l'écriture
     */
    static bool supprimer(const Action* action);

    /**
     * @brief nombreTachesPourAction
     * Retourne le nombre de tâches utilisant une action donnée
     * @param idAction L'action à chercher
     * @return Le nombre de tâches
     */
    static int tachesPourAction(const int &idAction);

private:

    /**
     * @brief mapper
     * Extrait les informations d'un résultat d'une requête vers une action
     * @param ligne La ligne de la base de données à mapper en action
     * @return L'action
     */
    static Action* mapper(const QSqlRecord &ligne);

    /**
     * @brief mapper
     * Construit toutes les actions se retrouvant dans les résultats d'une requête SQL
     * @param requete La requête à mapper
     * @return Les actions présentes dans la requête
     */
    static QList<Action*>* mapper(QSqlQuery &requete);

    /**
     * @brief preparerRequete Assigne les valeurs d'une action à une requête préparée
     * @param action L'action source
     * @param commande La commande SQL à préparer
     * @return La commande préparée
     */
    static QSqlQuery* preparerRequete(const Action* action, const QString &commande);

    /**
     * @brief ecrire
     * Effectue une opération SQL à l'intérieur d'une transaction
     * La transaction est annulée si l'opération échoue et validée autrement
     * @param action L'action à inclure dans l'opération SQL
     * @param commande La commande à exécuter
     * @return Succès de l'opération
     */
    static bool ecrire(const Action* action, const QString &commande);

};

#endif // MAPPEURACTIONS_H
