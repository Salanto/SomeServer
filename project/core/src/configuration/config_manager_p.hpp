#ifndef CONFIG_MANAGER_PRIVATE_HPP
#define CONFIG_MANAGER_PRIVATE_HPP

class QSettings;

namespace AkashiCore::Private
{
struct ConfigManagerPrivate
{
  QSettings *config;
};
} // namespace AkashiCore::Private

#endif // CONFIG_MANAGER_PRIVATE_HPP
