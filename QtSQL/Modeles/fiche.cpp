#include "fiche.h"


int Fiche::getId() const
{
    return id;
}

void Fiche::setId(int value)
{
    id = value;
}

int Fiche::getPriorite() const
{
    return priorite;
}

void Fiche::setPriorite(int value)
{
    priorite = value;
}

QString Fiche::getCommentaire() const
{
    return commentaire;
}

void Fiche::setCommentaire(const QString &value)
{
    commentaire = value;
}

Statut *Fiche::getStatut() const
{
    return statut;
}

void Fiche::setStatut(Statut *value)
{
    statut = value;
}

QString Fiche::out()
{
    return QString::number(id) + " " + QString::number(priorite) + " " + commentaire + " " + statut->getNom();
}
Fiche::Fiche(QObject *parent) :
    QObject(parent)
{
}
