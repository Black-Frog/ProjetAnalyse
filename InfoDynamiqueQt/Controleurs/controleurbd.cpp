#include "Controleurs/controleurbd.h"

#include "ui_vueconnexion.h"

#include "Controleurs/requetessql.h"

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>

ControleurBD::ControleurBD(QObject* parent) :
    QObject(parent)
{
}

QSqlDatabase* ControleurBD::getBd()
{
    return &bd;
}

void ControleurBD::connecterDossiers()
{
//    vue = new VueConnexion(Application::vuePrincipale());
//    configurerBoutonConnecter();
//    if (vue->exec() == vue->Accepted) {
//        bd.setDatabaseName(vue->getNomBD());
//        if (!bd.open()) {
//            qDebug() << "Erreur d'ouverture de la base de données";
//        }
//    }
    bd = QSqlDatabase::addDatabase(QString("QMYSQL"), nomBd());
    bd.setHostName("localhost");
    bd.setPort(3307);
    bd.setUserName("root");
    bd.setPassword("");
    bd.setDatabaseName("InfoDynamiqueDossiers");
    if (!bd.open()) {
        qDebug() << "Erreur d'ouverture de la base de données";
    }
}

const QString ControleurBD::nomBd()
{
    return QString("dossiers");
}

void ControleurBD::clicConnecter()
{
    bd = QSqlDatabase::addDatabase(QString("QMYSQL"), nomBd());
    bd.setHostName(vue->getHote());
    bd.setPort(vue->getPort());
    bd.setUserName(vue->getUsager());
    bd.setPassword(vue->getMotDePasse());
    if (!bd.open()) {
        qDebug() << "Erreur de connexion à la base de données";
    }
    peuplerBd();
}

void ControleurBD::configurerBoutonConnecter()
{
    QObject::connect(vue->getButtonBox(), SIGNAL(accepted()), this, SLOT(clicConnecter()));
}

void ControleurBD::peuplerBd()
{
    QSqlQueryModel* baseDeDonnees = new QSqlQueryModel(this);
    baseDeDonnees->setQuery(*RequetesSQL::listerBD, bd);
    vue->peuplerTableau(baseDeDonnees);
}

const QString* ControleurBD::meta = new QString("%");
