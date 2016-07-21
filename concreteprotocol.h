#ifndef CONCRETEPROTOCOL_H
#define CONCRETEPROTOCOL_H

#include <QWebChannelAbstractTransport>

class QWebSocket;

// More information at:
//      https://github.com/qt/qtwebchannel/tree/dev/src/webchannel
class ConcreteProtocol : public QWebChannelAbstractTransport
{
    Q_OBJECT

public:
    explicit ConcreteProtocol(QWebSocket *socket);
    virtual ~ConcreteProtocol();

    void sendMessage(const QJsonObject &message);

private slots:
    void textMessageReceived(const QString &message);

private:
    QWebSocket* const m_socket;
};

#endif // CONCRETEPROTOCOL_H
