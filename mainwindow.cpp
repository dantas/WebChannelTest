#include "mainwindow.h"

#include "exportedobject.h"
#include "concreteprotocol.h"

#include <QResizeEvent>
#include <QUrl>
#include <QFile>
#include <QStringList>

#define INITIAL_WIDTH 1024
#define INITIAL_HEIGHT 768
#define INTERFACE_NAME QStringLiteral("interface")

MainWindow::MainWindow()
    : QMainWindow(nullptr), m_webView(this),
      m_server(QStringLiteral("Websocket server"), QWebSocketServer::NonSecureMode),
      m_interface(new ExportedObject(this, 22, QStringLiteral("Johnson")))
{
    if (!m_server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to start socket server");
    }

    QObject::connect(&m_server, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));

    resize(INITIAL_WIDTH, INITIAL_HEIGHT);

    m_channel.registerObject(INTERFACE_NAME, m_interface);

    loadUrlWithInjectedJavascript();

    m_interface->age(45);
    m_interface->name("Silent Bob");
}

MainWindow::~MainWindow()
{
    if (m_protocol) m_protocol->deleteLater();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_webView.resize(event->size());
}

void MainWindow::handleNewConnection()
{
    m_protocol = new ConcreteProtocol(m_server.nextPendingConnection());
    m_channel.connectTo(m_protocol);
}

void MainWindow::loadUrlWithInjectedJavascript()
{
    QStringList list = loadHtml().split("<head>");
    list.insert(1, loadJs().arg(INTERFACE_NAME, m_interface->javascriptObject(), "ws://localhost:12345"));
    m_webView.setHtml(list.join(""), QUrl::fromLocalFile(BUILD_DIR "/"));
}

QString MainWindow::loadHtml()
{
    QFile htmlFile(BUILD_DIR "/index.html");

    if (!htmlFile.open(QIODevice::ReadOnly)) qFatal("Unable to load html file");

    QString htmlContent(htmlFile.readAll());

    htmlFile.close();

    return htmlContent;
}

QString MainWindow::loadJs()
{
    QFile jsFile(BUILD_DIR "/inject.js");

    if (!jsFile.open(QIODevice::ReadOnly)) qFatal("Unable to load js file");

    QString jsContent(jsFile.readAll());

    jsFile.close();

    return jsContent;
}
