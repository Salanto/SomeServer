#include "hub_manager.hpp"
#include "area_manager.hpp"
#include "hub_manager_p.hpp"

using namespace AkashiArea;

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

std::unique_ptr<Private::HubManagerPrivate> AkashiArea::HubManager::d_ptr = std::make_unique<Private::HubManagerPrivate>();

// Passing the arealist as a QString to handle invalid QJsonDocument by the hub manager.
HubManager::HubManager(QObject *parent)
    : QObject(parent)
{
  qDebug() << "[HUBMANAGER]::CTOR"
           << "Starting Hub Manager";
}

HubManager::~HubManager()
{
  qDebug() << "[HUBMANAGER]::DTOR"
           << "Destroying Hub Manager";
}

void HubManager::loadAreaList(const QString &f_area_list)
{
  qDebug() << "[HUBMANAGER]::LOAD"
           << "Loading Arealist";

  QJsonParseError error;
  QJsonDocument l_area_list = QJsonDocument::fromJson(f_area_list.toUtf8(), &error);

  if (error.error != QJsonParseError::NoError)
  {
    qDebug() << "[HUBMANAGER]::LOAD Invalid JSON file, encountered error" << error.errorString() << "at offset" << error.offset;
    return;
  }

  QJsonArray l_hub_array = l_area_list.array();
  for (int index = 0; index < l_hub_array.size(); index++)
  {
    QJsonObject l_hub_info = l_hub_array.at(index).toObject();
    QString name = l_hub_info.value("hub_name").toString();
    QJsonArray areas = l_hub_info.value("areas").toArray();
    d_ptr.get()->l_hubs.append(new AreaManager(this, name, areas));
  }
}
