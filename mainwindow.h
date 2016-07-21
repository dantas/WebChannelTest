#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebSocketServer>
#include <QWebChannel>
#include <QPointer>

class QResizeEvent;
class ExportedObject;
class ConcreteProtocol;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
    void handleNewConnection();

private:
    QWebEngineView m_webView;
    QWebSocketServer m_server;
    QWebChannel m_channel;

    ExportedObject *m_interface;
    QPointer<ConcreteProtocol> m_protocol;

    void loadUrlWithInjectedJavascript();
    static QString loadHtml();
    static QString loadJs();
};

#endif // MAINWINDOW_H
