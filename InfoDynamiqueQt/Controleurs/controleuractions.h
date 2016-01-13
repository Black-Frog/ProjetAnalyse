#ifndef CONTROLEURACTIONS_H
#define CONTROLEURACTIONS_H

#include <QObject>

#include "Vues/vuefragment.h"
#include "Vues/vueprincipale.h"

#include <QSqlQuery>
#include <QSplitter>

class ControleurActions : public QObject
{
    Q_OBJECT

    // Contrôle l'exécution de l'onglet Actions de la vue principale

public:

    /**
     * @brief ControleurActions
     * @param vuePrincipale La vue à laquelle se rattache le contrôleur
     * @param parent
     */
    explicit ControleurActions(VuePrincipale* vuePrincipale, QObject* parent = 0);

private:

    // Le séparateur redimensionnable contenant les fragments
    QSplitter* splitter;

    // Le fragment des actions
    VueFragment* fragmentActions;

    // Le fragment des ensembles
    VueFragment* fragmentEnsembles;

    /**
     * @brief configurerFragmentActions
     * Configure fragmentActions
     */
    void configurerFragmentActions();

    /**
     * @brief configurerFragmentEnsembles
     * Configure fragmentEnsembles
     */
    void configurerFragmentEnsembles();

    const QString* requeteActions;

    const QString* requeteActionsFiltre;

    // La requête utilisée pour sélectionner les actions actives et inactives
    const QString* requeteToutesActions;

    // La requête utilisée pour sélectionner les actions actives uniquement
    const QString* requeteActionsActives;

    // La requête utilisée pour sélectionner les actions actives et inactives qui correspondent à une sous-chaîne
    const QString* requeteToutesActionsFiltre;

    // La requête utilisée pour sélectionner les actions actives uniquement qui correspondent à une sous-chaîne
    const QString* requeteActionsActivesFiltre;

    // La requête utilisée pour sélectionner les ensembles
    const QString* requeteEnsembles;

public slots:

    /**
     * @brief peuplerActions
     * Peuple la table du fragmentActions avec toutes les actions
     */
    void peuplerActions();

    /**
     * @brief peuplerEnsembles
     * Peuple la table de fragmentEnsembles avec tous les ensembles
     */
    void peuplerEnsembles();

    void activerCritereActions();

    void desactiverCritereActions();

    void filtrerActions(QString filtre);

    void voirAction();

};

#endif // CONTROLEURACTIONS_H
