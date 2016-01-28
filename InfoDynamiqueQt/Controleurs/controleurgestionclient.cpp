#include "Controleurs/controleurgestionclient.h"

#include "Controleurs/application.h"
#include "Controleurs/controleurbd.h"

#include "Vues/vuegestionclient.h"
#include <QSqlQueryModel>
#include <QDebug>

ControleurGestionClient::ControleurGestionClient(QObject* parent)
    : QObject(parent)
{
}

void ControleurGestionClient::ajouterClient()
{
    VueGestionClient* vue = new VueGestionClient(Application::getVuePrincipale());
    if (vue->exec() == vue->Accepted) {
        Client* client = new Client();
        client->setNom(vue->getNom());
        client->setPrenom(vue->getPrenom());
        client->setTelephone(vue->getTelephone());
        client->setAdresse(vue->getAdresse());
        if (Application::clients->inserer(client)) {
            emit donneesModifiees();
        } else {
            qDebug() << "Pas marché: " << client->out();
        }
        vue->deleteLater();
        client->deleteLater();
    }
}

void ControleurGestionClient::modifierClient(const int idClient)
{
    VueGestionClient* vue = new VueGestionClient(Application::getVuePrincipale());
    Client* client = Application::clients->getClient(idClient);
    assignerClient(vue, client);
    vue->exec();
    vue->deleteLater();
}

void ControleurGestionClient::voirClient(const int idClient)
{
    VueGestionClient* vue = new VueGestionClient(Application::getVuePrincipale());
    Client* client = Application::clients->getClient(idClient);
    assignerClient(vue, client);
    vue->setLectureSeule();
    QObject::connect(vue, SIGNAL(finished(int)), vue, SLOT(deleteLater()));
    vue->show();
}

void ControleurGestionClient::assignerClient(VueGestionClient* vue, const Client* client)
{
    vue->setPrenom(client->getPrenom());
    vue->setNom(client->getNom());
    vue->setAdresse(client->getAdresse());
    vue->setTelephone(client->getTelephone());
}

