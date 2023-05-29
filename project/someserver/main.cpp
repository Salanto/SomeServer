#include "configuration/config_manager.hpp"
#include "server.hpp"

int main(int argc, char *argv[])
{
  if (!AkashiCore::ConfigManager::checkConfiguration())
  {
    return EXIT_FAILURE;
  }

  AkashiCore::Server ServerCore(argc, argv);
  ServerCore.setApplicationName("SomeServer");
  ServerCore.setApplicationVersion("0.0.1");

  return ServerCore.exec();
}
