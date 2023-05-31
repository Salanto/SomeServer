#ifndef CLIENT_PACKET_HANDLER_HPP
#define CLIENT_PACKET_HANDLER_HPP

#include "interfaces/network_socket_i.hpp"

#include <QObject>

namespace AkashiArea {
    class HubManager;
} // namespace AkashiArea

namespace AkashiNetwork {
    class AOPacket;
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

        void handshake();
        void handle_HI(AkashiNetwork::AOPacket *f_packet);
        void handle_ID(AkashiNetwork::AOPacket *f_packet);

      signals:

      private:
        Client *client;
        AkashiNetwork::NetworkSocket *socket;
        AkashiArea::HubManager *hub_manager;
        AkashiNetwork::PacketHandler *handler;
        AkashiCore::ClientManager *client_manager;

        static void registerMappers();
        inline static std::map<QString, void (ClientPacketHandler::*)(AkashiNetwork::AOPacket *)> m_handler_map;

      private slots:
        void
        handlePacket(AkashiNetwork::AOPacket *packet);
    };
} // namespace AkashiCore
#endif // CLIENT_PACKET_HANDLER_HPP
