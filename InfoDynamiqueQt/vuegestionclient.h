#ifndef GESTIONCLIENT_H
#define GESTIONCLIENT_H

#include <QDialog>

namespace Ui {
class VueGestionClient;
}

class VueGestionClient : public QDialog
{
    Q_OBJECT

public:
    explicit VueGestionClient(QWidget *parent = 0);
    ~VueGestionClient();

private:
    Ui::VueGestionClient *ui;
};

#endif // GESTIONCLIENT_H
