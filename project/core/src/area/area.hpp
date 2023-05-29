#ifndef AREA_HPP
#define AREA_HPP

class QJsonObject;

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QVector>

namespace AkashiArea
{
class Area : public QObject
{
  Q_OBJECT

public:
  Area(QObject *parent, const QJsonObject &f_area_config);
  ~Area();

  void setAreaName(const QString &f_area_name);
  QString getAreaName() const;

  void addClient(const int &f_player_id);
  void removeClient(const int &f_player_id);
  QVector<int> getClients() const;

private:
  QString name;
  QVector<int> clients;
};
} // namespace AkashiArea

#endif // AREA_HPP
