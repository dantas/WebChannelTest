#include "exportedobject.h"

#include <QStringBuilder>
#include <QMessageBox>

ExportedObject::ExportedObject(QObject *parent, int age, QString name)
    : QObject(parent), m_age(age), m_name(name)
{

}

int ExportedObject::age() const
{
    return m_age;
}

QString ExportedObject::name() const
{
    return m_name;
}

void ExportedObject::age(int value)
{
    emit ageNotifySignal(m_age = value);
}

void ExportedObject::name(QString value)
{
    emit nameNotifySignal(m_name = value);
}

void ExportedObject::dialog(QString message)
{
    QMessageBox::information(nullptr, "Dialog from javascript", message);
}

QString ExportedObject::javascriptObject() const
{
    return QString("{")
            % "age: " % QString::number(age()) % ","
            % "name: \"" % name() % "\","
            % "}";
}
