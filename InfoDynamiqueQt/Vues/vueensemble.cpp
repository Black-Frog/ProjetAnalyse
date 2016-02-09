#include "vueensemble.h"
#include "ui_vueensemble.h"

VueEnsemble::VueEnsemble(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VueEnsemble)
{
    ui->setupUi(this);
}

VueEnsemble::~VueEnsemble()
{
    delete ui;
}

void VueEnsemble::setNom(const QString &nom)
{
    ui->champNom->setText(nom);
}

void VueEnsemble::setDescription(const QString &description)
{
    ui->champDescription->setPlainText(description);
    ui->champDescription->adjustSize();
}

void VueEnsemble::setActions(const QList<Action *> *actions)
{
    delete ui->listeActions->model();
    ui->listeActions->setModel(listeVersModele(actions));
    adjustSize();
}

QStandardItemModel *VueEnsemble::listeVersModele(const QList<Action*>* liste)
{
    QStandardItemModel* modele = new QStandardItemModel(this);
    for (QList<Action*>::const_iterator i = liste->constBegin(); i != liste->constEnd(); ++i) {
        QStandardItem* element = new QStandardItem((*i)->nom());
        element->setToolTip((*i)->description());
        modele->appendRow(element);
    }
    return modele;
}
