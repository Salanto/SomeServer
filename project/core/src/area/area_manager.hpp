#ifndef AREA_MANAGER_HPP
#define AREA_MANAGER_HPP

#include "area.hpp"

#include <QObject>

namespace AkashiArea
{
namespace Private
{
struct AreaManagerPrivate;
} // namespace Private

class AreaManager : public QObject
{
  Q_OBJECT

public:
  AreaManager(QObject *parent, const QString &f_hub_name, const QJsonArray &f_area_array);
  ~AreaManager();

private:
  std::unique_ptr<Private::AreaManagerPrivate> d_ptr;
};

class AreaGroup
{
public:
  QString getName();

  QList<Area *> getAreaList();

  void load(QString file);
};

} // namespace AkashiArea

#endif // AREA_MANAGER_HPP
