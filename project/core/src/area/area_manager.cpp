#include "area_manager.hpp"
#include "area.hpp"
#include "area_manager_p.hpp"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace AkashiArea;

AreaManager::AreaManager(QObject *parent, const QString &f_hub_name, const QJsonArray &f_area_array)
    : QObject(parent)
    , d_ptr(std::make_unique<Private::AreaManagerPrivate>())
{
  d_ptr.get()->hub_name = f_hub_name;
  qDebug() << "[AreaManager]::CTOR"
           << "Building Hub" << f_hub_name << "with" << f_area_array.size() << "areas";

  for (int area_index = 0; area_index < f_area_array.size(); area_index++)
  {
    d_ptr.get()->areas.append(new Area(this, f_area_array.at(area_index).toObject()));
  }
}

AreaManager::~AreaManager()
{}
