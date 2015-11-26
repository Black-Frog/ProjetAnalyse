#include "fabriquepiece.h"

FabriquePiece::FabriquePiece(GestionnaireConnexion *a_gc, QObject *parent) :
    QObject(parent)
{
    gc = a_gc;
}

Piece *FabriquePiece::getPiece(int id)
{
    Piece *piece = NULL;
    QString requete = "SELECT * FROM pieces WHERE id="+QString::number(id);
    QSqlQuery commande = gc->requete(requete);
    if (commande.next()) {
        piece = new Piece(commande.value(0).toInt(), commande.value(1).toString(), commande.value(2).toString(), commande.value(3).toInt(), this);
    }
    return piece;
}

QList<Piece*> FabriquePiece::getPieces(void) {
    QList<Piece*> liste;
    QString requete = "SELECT * FROM pieces";
    QSqlQuery commande = gc->requete(requete);
    while (commande.next()) {
        Piece *piece = new Piece(commande.value(0).toInt(), commande.value(1).toString(), commande.value(2).toString(), commande.value(3).toInt(), this);
        liste.append(piece);
    }
    return liste;
}
