#ifndef CONTROLEURACTIONS_H
#define CONTROLEURACTIONS_H

#include <QObject>

#include "Modeles/action.h"

#include "Vues/vuegestionaction.h"
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
    explicit ControleurActions(QWidget* conteneur, QObject* parent = 0);
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

    void assignerAction(VueGestionAction* vue, Action* action) const;

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

    void modifierAction();

    void voirAction();

    void changerEtat();

    void recharger();

signals:

    void donneesModifiees();

};

#endif // CONTROLEURACTIONS_H
