#include "area.hpp"

#include <QDebug>
#include <QJsonObject>
#include <QObject>

using namespace AkashiArea;

Area::Area(QObject *parent, const QJsonObject &f_area_entry)
    : QObject(parent)
    , name(f_area_entry.value("area_name").toString())
{
  qDebug() << "[AREA]::CTOR"
           << "Creating area" << name;
}

Area::~Area()
{}

void Area::setAreaName(const QString &f_area_name)
{
  name = f_area_name;
}

QString Area::getAreaName() const
{
  return name;
}

void Area::addClient(const int &f_player_id)
{
  clients.append(f_player_id);
}

void Area::removeClient(const int &f_player_id)
{
  clients.removeAll(f_player_id);
}

QVector<int> Area::getClients() const
{
  return clients;
}
