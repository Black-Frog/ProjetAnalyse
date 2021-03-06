#include "Vues/vuegestionpiece.h"
#include "ui_vuegestionpiece.h"

#include "Vues/champformulaire.h"

#include <QPushButton>

VueGestionPiece::VueGestionPiece(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::VueGestionPiece)
{
    ui->setupUi(this);
    nom = new ChampFormulaire(tr("Ce champ est requis."), this);
    ui->formLayout->setWidget(0, QFormLayout::FieldRole, nom);
    connect(nom, SIGNAL(valeurChangee()), this, SLOT(verifierNom()));
    connect(nom, SIGNAL(validiteChangee()), this, SLOT(verifierOk()));
    verifierOk();
}

VueGestionPiece::~VueGestionPiece()
{
    delete ui;
}

QString VueGestionPiece::getNom() const
{
    return nom->getTexte();
}

void VueGestionPiece::setNom(const QString &valeur)
{
    nom->setTexte(valeur);
}

QString VueGestionPiece::getDescription() const
{
    return ui->champDescription->toPlainText();
}

void VueGestionPiece::setDescription(const QString &description)
{
    ui->champDescription->setPlainText(description);
}

double VueGestionPiece::getPrix() const
{
    return ui->champPrix->value();
}

int VueGestionPiece::getPrixInt() const
{
    return getPrix()*100;
}

void VueGestionPiece::setPrix(const double &prix)
{
    ui->champPrix->setValue(prix);
}

void VueGestionPiece::verifierNom()
{
    nom->setValide(!nom->getTexte().isEmpty());
}

void VueGestionPiece::verifierOk()
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(nom->estValide());
}
