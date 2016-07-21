#include "concreteprotocol.h"

#include <QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>

ConcreteProtocol::ConcreteProtocol(QWebSocket *socket)
    : QWebChannelAbstractTransport(socket), m_socket(socket)
{
    connect(m_socket, SIGNAL(textMessageReceived(QString)),
            this, SLOT(textMessageReceived(QString)));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

ConcreteProtocol::~ConcreteProtocol()
{
    m_socket->deleteLater();
}

void ConcreteProtocol::sendMessage(const QJsonObject &message)
{
    QJsonDocument document(message);
    QString serializedJson = QString::fromUtf8(document.toJson(QJsonDocument::Compact));
    m_socket->sendTextMessage(serializedJson);
}

void ConcreteProtocol::textMessageReceived(const QString &message)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8(), &error);
    if (!error.error && document.isObject()) {
        emit messageReceived(document.object(), this);
    }
}
