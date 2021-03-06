#include "typeappareil.h"

QString TypeAppareil::getNom() const
{
    return nom;
}

void TypeAppareil::setNom(const QString &value)
{
    nom = value;
}

QString TypeAppareil::out()
{
    return QString::number(id) + " " + nom;
}

int TypeAppareil::getId() const
{
    return id;
}

void TypeAppareil::setId(int value)
{
    id = value;
}

TypeAppareil::TypeAppareil(int a_id, QString a_nom, QObject *parent) :
    QObject(parent)
{
    setId(a_id);
    setNom(a_nom);
}

