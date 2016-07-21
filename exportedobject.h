#ifndef EXPORTEDOBJECT_H
#define EXPORTEDOBJECT_H

#include <QObject>
#include <QString>

class ExportedObject : public QObject
{
    Q_OBJECT

    // Use properties because they are cached by the javascript's
    // client automatically
    Q_PROPERTY(int age READ age WRITE age NOTIFY ageNotifySignal)
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameNotifySignal)

public:
    ExportedObject(QObject *parent, int age, QString name);

    int age() const;
    QString name() const;
    void age(int value);
    void name(QString value);
    QString javascriptObject() const;

public slots:
    void dialog(QString message);

signals:
    void ageNotifySignal(int newValue);
    void nameNotifySignal(QString newValue);

private:
    int m_age;
    QString m_name;
};

#endif // EXPORTEDOBJECT_H
