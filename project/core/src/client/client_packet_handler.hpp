#ifndef CLIENT_PACKET_HANDLER_HPP
#define CLIENT_PACKET_HANDLER_HPP

#include "interfaces/network_socket_i.hpp"

#include <QObject>

namespace AkashiArea {
    class HubManager;
} // namespace AkashiArea

namespace AkashiNetwork {
    class AOJsonPacket;
    class PacketHandler;
} // namespace AkashiNetwork

namespace AkashiCore {
    class Client;
    class ClientManager;

    class ClientPacketHandler : public QObject
    {
        Q_OBJECT

      public:
        ClientPacketHandler(Client *client, AkashiNetwork::NetworkSocket *socket, AkashiArea::HubManager *hub_manager, QObject *parent = nullptr);
        void handle_join(AkashiNetwork::AOJsonPacket *f_packet);

      signals:

      private:
        Client *client;
        AkashiNetwork::NetworkSocket *socket;
        AkashiArea::HubManager *hub_manager;
        AkashiNetwork::PacketHandler *handler;
        AkashiCore::ClientManager *client_manager;

        static void registerMappers();
        inline static std::map<QString, void (ClientPacketHandler::*)(AkashiNetwork::AOJsonPacket *)> m_handler_map;

      private slots:
        void
        handlePacket(AkashiNetwork::AOJsonPacket *packet);
    };
} // namespace AkashiCore
#endif // CLIENT_PACKET_HANDLER_HPP
