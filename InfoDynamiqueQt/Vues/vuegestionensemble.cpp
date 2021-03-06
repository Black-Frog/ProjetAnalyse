#include "Vues/vuegestionensemble.h"
#include "ui_vuegestionensemble.h"

#include "Controleurs/controleuractions.h"
#include "Mappeurs/mappeuractions.h"
#include "Modeles/action.h"
#include "Modeles/ensembleactions.h"
#include "Vues/champformulaire.h"

#include <QStandardItemModel>

VueGestionEnsemble::VueGestionEnsemble(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::VueGestionEnsemble)
{
    ui->setupUi(this);
    nom = new ChampFormulaire(tr("Ce champ est requis."), this);
    nom->setFocus();
    ui->formLayout->setWidget(0,QFormLayout::FieldRole, nom);
    configurerBoutonOk();
    setTabOrder(nom->getChamp(), ui->champDescription);
    connect(nom, SIGNAL(valeurChangee()), this, SLOT(verifierNom()));
    ui->boutonAjouter->setEnabled(false);
    ui->boutonRetirer->setEnabled(false);
    connect(ui->listeExistantes, SIGNAL(activated(QModelIndex)), this, SLOT(horsEnsembleSelectionnee()));
    connect(ui->listeExistantes, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ajouter()));
    connect(ui->boutonAjouter, SIGNAL(clicked()), this, SLOT(ajouter()));
    connect(ui->listeSelectionnees, SIGNAL(clicked(QModelIndex)), this, SLOT(dansEnsembleSelectionnee()));
    connect(ui->listeSelectionnees, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(retirer()));
    connect(ui->boutonRetirer, SIGNAL(clicked()), this, SLOT(retirer()));
    connect(ui->boutonNouvelle, SIGNAL(clicked()), this, SLOT(creerAction()));
}

VueGestionEnsemble::~VueGestionEnsemble()
{
    delete ui;
}

void VueGestionEnsemble::setActions(const QList<Action*>* horsEnsemble, const QList<Action*>* dansEnsemble)
{
    delete ui->listeExistantes->model();
    modeleHorsEnsemble = listeEnModele(horsEnsemble);
    modeleHorsEnsemble->sort(0);
    ui->listeExistantes->setModel(modeleHorsEnsemble);
    delete ui->listeSelectionnees->model();
    if (dansEnsemble == 0) {
        modeleDansEnsemble = new QStandardItemModel(this);
    } else {
        modeleDansEnsemble = listeEnModele(dansEnsemble);
    }
    modeleDansEnsemble->sort(0);
    ui->listeSelectionnees->setModel(modeleDansEnsemble);
}

QStandardItemModel* VueGestionEnsemble::listeEnModele(const QList<Action*>* actions)
{
    QStandardItemModel* modele = new QStandardItemModel(this);
    for (QList<Action*>::const_iterator i = actions->constBegin(); i != actions->constEnd(); ++i) {
        modele->appendRow(actionEnItem((*i)));
    }
    return modele;
}

QStandardItem* VueGestionEnsemble::actionEnItem(const Action* action) {
    QStandardItem* element = new QStandardItem(action->nom());
    element->setToolTip(action->description());
    element->setData(action->id());
    return element;
}

void VueGestionEnsemble::configurerBoutonOk()
{
    QPushButton* boutonOk = ui->buttonBox->button(QDialogButtonBox::Save);
    boutonOk->setEnabled(false);
    connect(nom, SIGNAL(validiteChangee()), this, SLOT(verifierOk()));
    boutonOk->setEnabled(false);
    connect(this, SIGNAL(champsRequisModifies(bool)), boutonOk, SLOT(setEnabled(bool)));
}

void VueGestionEnsemble::setNom(const QString &valeur)
{
    nom->setTexte(valeur);
}

QString VueGestionEnsemble::getNom() const
{
    return nom->getTexte();
}

void VueGestionEnsemble::setDescription(const QString &valeur)
{
    ui->champDescription->setText(valeur);
}

QString VueGestionEnsemble::getDescription() const
{
    return ui->champDescription->text();
}

QList<int>* VueGestionEnsemble::getActionsSelectionnees() const
{
    QList<int>* liste = new QList<int>;
    for (int i = 0; i < modeleDansEnsemble->rowCount(); ++i) {
        liste->append(modeleDansEnsemble->item(i, 0)->data().toInt());
    }
    return liste;
}

void VueGestionEnsemble::horsEnsembleSelectionnee()
{
    ui->boutonAjouter->setEnabled(true);
}

void VueGestionEnsemble::dansEnsembleSelectionnee()
{
    ui->boutonRetirer->setEnabled(true);
}

void VueGestionEnsemble::ajouter()
{
    modeleDansEnsemble->appendRow(modeleHorsEnsemble->takeRow(ui->listeExistantes->currentIndex().row()));
    modeleDansEnsemble->sort(0);
    if (modeleHorsEnsemble->rowCount() == 0) {
        ui->boutonAjouter->setEnabled(false);
    }
}

void VueGestionEnsemble::retirer()
{
    modeleHorsEnsemble->appendRow(modeleDansEnsemble->takeRow(ui->listeSelectionnees->currentIndex().row()));
    modeleHorsEnsemble->sort(0);
    if (modeleDansEnsemble->rowCount() == 0) {
        ui->boutonRetirer->setEnabled(false);
    }
}

void VueGestionEnsemble::verifierNom()
{
    nom->setValide(!nom->getTexte().isEmpty());
}

void VueGestionEnsemble::verifierOk()
{
    emit champsRequisModifies(nom->estValide());
}

void VueGestionEnsemble::creerAction()
{
    Action* nouvelle = MappeurActions::get(ControleurActions::creerAction());
    if (nouvelle != NULL) {
        modeleDansEnsemble->appendRow(actionEnItem(nouvelle));
    }
    nouvelle->deleteLater();

}
