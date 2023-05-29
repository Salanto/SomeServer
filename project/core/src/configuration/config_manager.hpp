#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <QObject>
#include <memory>

class QJsonDocument;

namespace AkashiCore
{
namespace Private
{
struct ConfigManagerPrivate;
} // namespace Private

class ConfigManager : private QObject
{
  Q_OBJECT

private:
  ConfigManager();
  ~ConfigManager();

  std::unique_ptr<Private::ConfigManagerPrivate> d_ptr;

public:
  Q_DISABLE_COPY_MOVE(ConfigManager);

  static ConfigManager &getInstance()
  {
    static ConfigManager instance;
    return instance;
  }

  static bool checkConfiguration();

  // Generic
  QString readTextFile(QString f_file_name);
  QJsonDocument readJsonFile(QString f_file_name);

  // Config
  int serverPort();
  int wsServerPort();
  QString serverName();
  QString serverDescription();
  int maxPlayers();

  // Advertiser
  bool enableAdvertiser();
  bool showDebug();
  QString masterServerAddress();
  QString hostname();
};

} // namespace AkashiCore

#endif // CONFIG_MANAGER_HPP
