#ifndef AREA_MANAGER_HPP
#define AREA_MANAGER_HPP

#include <QObject>
#include <memory>

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
} // namespace AkashiArea

#endif // AREA_MANAGER_HPP
