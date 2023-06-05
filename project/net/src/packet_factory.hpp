#include "packet.hpp"

#include <map>

namespace AkashiNetwork {
    class PacketFactory
    {
      public:
        static bool canCreatePacket(QString header);
        static AOJsonPacket *createPacket(QString type, QJsonObject content);

        void registerPacket(AOJsonPacket *(*builder)(QJsonObject content));

      private:
        static std::map<QString, AOJsonPacket *(*)(QJsonObject)> m_builder_map;
    };
} // namespace AkashiNetwork
