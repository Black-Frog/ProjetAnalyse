#include "Modeles/fabricant.h"

Fabricant::Fabricant(QObject* parent) : ModeleBD(parent) {}

Fabricant::Fabricant(const int &a_id, const QString &a_nom, QObject* parent): ModeleBD(parent)
{
    m_id = a_id;
    m_nom = a_nom;
}

QString Fabricant::nom() const
{
    return m_nom;
}

void Fabricant::setNom(const QString &value)
{
    m_nom = value;
}

QString Fabricant::out() const
{
    return QString::number(m_id) + " " + m_nom;
}

