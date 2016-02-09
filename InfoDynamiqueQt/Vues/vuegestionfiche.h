#ifndef GESTIONFICHE_H
#define GESTIONFICHE_H

#include <QDialog>

namespace Ui {
class VueGestionFiche;
}

class VueGestionFiche : public QDialog
{
    Q_OBJECT

    // Vue servant à modifier les informations générales d'une fiche

public:
    explicit VueGestionFiche(QWidget* parent = 0);
    ~VueGestionFiche();

    void setDescription(const QString &commentaire);

    QString getDescription() const;



private:
    Ui::VueGestionFiche* ui;

public slots:

    void setLectureSeule();
};

#endif // GESTIONFICHE_H
