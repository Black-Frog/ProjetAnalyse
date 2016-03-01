#ifndef VUERAPPORT_H
#define VUERAPPORT_H

class Client;
class Appareil;
class Tache;
class Piece;

#include <QDialog>

namespace Ui {
class vueRapport;
}

class VueRapport : public QDialog
{
    Q_OBJECT

public:
    explicit VueRapport(QWidget *parent = 0);
    ~VueRapport();

    /**
     * @brief setInformations
     * Assigne la valeur du champ informations
     * @param client Le client dont les informations doivent être affichées
     * @param appareil L'appareil dont les informations doivent être affichées
     */
    void setInformations(const Client *client, const Appareil *appareil);

    /**
     * @brief setDescription
     * Assigne la valeur du champ description
     * @param description La description qui doit être affichée
     */
    void setDescription(const QString &description);

    /**
     * @brief setTaches
     * Assigne la valeur du champ taches
     * @param taches La liste de toutes les tâches qui doivent être affichées
     */
    void setTaches(const QList<Tache*>* taches);

    /**
     * @brief setPieces
     * Assigne la valeur du champ pieces
     * @param pieces La liste de toutes les pièces qui doivent être affichées
     */
    void setPieces(const QList<Piece*>* pieces);

private:
    Ui::vueRapport *ui;
};

#endif // VUERAPPORT_H
