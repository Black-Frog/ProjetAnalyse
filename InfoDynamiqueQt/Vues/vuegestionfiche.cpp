#include "Vues/vuegestionfiche.h"
#include "ui_vuegestionfiche.h"

#include "Mappeurs/mappeurensembles.h"
#include "Modeles/action.h"
#include "Modeles/ensembleactions.h"
#include "Modeles/tache.h"

#include <QStandardItemModel>

VueGestionFiche::VueGestionFiche(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::VueGestionFiche)
{
    ui->setupUi(this);
    connect(ui->comboEnsemble, SIGNAL(currentIndexChanged(int)), this, SLOT(peuplerTaches()));
}

VueGestionFiche::~VueGestionFiche()
{
    delete ui;
}

QList<int>* VueGestionFiche::getTaches() const
{
    QList<int>* taches = new QList<int>;
    if (ui->listeTaches->model() != NULL) {
        for (int i = 0; i < ui->listeTaches->model()->rowCount(); ++i) {
            int id = ui->listeTaches->model()->data(ui->listeTaches->model()->index(i, 0), Qt::UserRole).toInt();
            taches->append(id);
        }
    }
    return taches;
}

int VueGestionFiche::getIdEnsemble() const
{
    return ui->comboEnsemble->currentData().toInt();
}

void VueGestionFiche::peuplerTaches()
{
    if (ui->listeTaches->model() != NULL) {
        ui->listeTaches->model()->deleteLater();
    }
    EnsembleActions* ensemble = MappeurEnsembles::get(getIdEnsemble());
    if (ensemble != NULL) {
        ui->listeTaches->setModel(listeEnModele(ensemble->actions()));
        getTaches();
    }
}

QStandardItemModel* VueGestionFiche::listeEnModele(const QList<Action*>* actions)
{
    QStandardItemModel* modele = new QStandardItemModel(this);
    for (QList<Action*>::const_iterator i = actions->constBegin(); i != actions->constEnd(); ++i) {
        modele->appendRow(actionEnItem((*i)));
    }
    return modele;
}

QStandardItem* VueGestionFiche::actionEnItem(const Action* action) {
    QStandardItem* element = new QStandardItem(action->nom());
    element->setToolTip(action->description());
    element->setData(action->id(), Qt::UserRole);
    return element;
}

void VueGestionFiche::setPriorite(const int &priorite)
{
    ui->champPriorite->setValue(priorite);
}

int VueGestionFiche::getPriorite() const
{
    return ui->champPriorite->value();
}

void VueGestionFiche::setEnsembles(const QList<EnsembleActions*>* ensembles)
{
    ui->comboEnsemble->addItem(tr("Sélectionner un ensemble"), -1);
    for (QList<EnsembleActions*>::const_iterator i = ensembles->constBegin(); i != ensembles->constEnd(); ++i) {
        ui->comboEnsemble->addItem((*i)->nom(), (*i)->id());
    }
}

void VueGestionFiche::setDescription(const QString &description)
{
    ui->champDescription->setPlainText(description);
}

QString VueGestionFiche::getDescription() const
{
    return ui->champDescription->toPlainText();
}

