#include "Vues/vueeditionfiche.h"
#include "ui_vueeditionfiche.h"

#include "Controleurs/application.h"

#include <QComboBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>

VueEditionFiche::VueEditionFiche(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::VueEditionFiche)
{
    ui->setupUi(this);
    configurerFragmentTaches();
    configurerFragmentPieces();
}

VueEditionFiche::~VueEditionFiche()
{
    delete ui;
}

void VueEditionFiche::setIdFiche(const int &id)
{
    if (id != idFiche) {
        idFiche = id;
        emit nouvelId();
    }
}

void VueEditionFiche::configurerFragmentTaches()
{
    fragmentTaches = new Fragment(this);
    fragmentTaches->setEtiquette(tr("Tâches"));
    delete fragmentTaches->caseCocher();
    delete fragmentTaches->champ();
    ui->cadreFragmentTaches->addWidget(fragmentTaches);
    QObject::connect(this, SIGNAL(nouvelId()), this, SLOT(peuplerTaches()));
//    QComboBox* combo = fragmentTaches->ajouterCombobox(4);
}

void VueEditionFiche::configurerFragmentPieces()
{
    fragmentPieces = new Fragment(this);
    delete fragmentPieces->caseCocher();
    delete fragmentPieces->champ();
    fragmentPieces->setEtiquette(tr("Pièces"));
    ui->cadreFragmentPieces->addWidget(fragmentPieces);
    QObject::connect(this, SIGNAL(nouvelId()), this, SLOT(peuplerPieces()));
}

void VueEditionFiche::peuplerTaches()
{
    QSqlQueryModel* modele = new QSqlQueryModel(this);
    modele->setQuery(QSqlQuery("SELECT * FROM taches", *Application::bd));
    fragmentTaches->peuplerTableau(modele);
}

void VueEditionFiche::peuplerPieces()
{

}
