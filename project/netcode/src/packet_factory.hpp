#include "packet.hpp"

#include <map>

namespace AkashiNetwork
{
class PacketFactory
{
public:
  static bool canCreatePacket(QString header);
  static AOPacket *createPacket(QString header, QStringList content);

  void registerPacket(AOPacket *(*builder)(QStringList content));

  template <typename T>
  void registerPacket()
  {
    registerPacket(&PacketFactory::newPacket<T>);
  }

private:
  static std::map<QString, AOPacket *(*)(QStringList)> m_builder_map;

  template <typename T>
  AOPacket *newPacket(QStringList content)
  {
    AOPacket *packet = new T;
    packet->setContent(content);
    return packet;
  }
};
} // namespace AkashiNetwork
