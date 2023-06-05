#pragma once

#include "interfaces/network_socket_i.hpp"
#include "packet.hpp"

#include <QObject>

namespace AkashiNetwork {
    class PacketHandler : public QObject
    {
        Q_OBJECT

      public:
        explicit PacketHandler(NetworkSocket *socket, QObject *parent = nullptr);

        void sendPacket(AOJsonPacket *packet);

      signals:
        void packetReceived(AOJsonPacket *packet);

      private:
        NetworkSocket *m_socket;

      private slots:
        void handleSocketData();
    };
} // namespace AkashiNetwork
