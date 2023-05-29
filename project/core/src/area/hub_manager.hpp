#ifndef HUB_MANAGER_HPP
#define HUB_MANAGER_HPP

#include <QObject>
#include <memory>

namespace AkashiArea
{
namespace Private
{
struct HubManagerPrivate;
} // namespace Private

class HubManager : public QObject
{
  Q_OBJECT

public:
  HubManager(QObject *parent);
  ~HubManager();

  void loadAreaList(const QString &f_area_list);

private:
  static std::unique_ptr<Private::HubManagerPrivate> d_ptr;
};
} // namespace AkashiArea

#endif // HUB_MANAGER_HPP
