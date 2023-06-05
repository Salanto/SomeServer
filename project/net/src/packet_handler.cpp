#include "packet_handler.hpp"
#include "packet_factory.hpp"

#include <QJsonDocument>

namespace AkashiNetwork {
    PacketHandler::PacketHandler(NetworkSocket *socket, QObject *parent) :
        QObject(parent),
        m_socket(socket)
    {
        connect(socket, &NetworkSocket::dataReceived, this, &PacketHandler::handleSocketData);
    }

    void PacketHandler::sendPacket(AOJsonPacket *packet)
    {
        m_socket->writeData(packet->serialize());
    }

    void PacketHandler::handleSocketData()
    {
        QJsonParseError l_error;
        QJsonDocument l_data = QJsonDocument::fromJson(m_socket->pendingData().toUtf8(), &l_error);
        QString type = l_data.object().value("type").toString();
        QJsonObject content = l_data.object().value("content").toObject();

        AOJsonPacket *packet = PacketFactory::createPacket(type, content);
        emit packetReceived(packet);
    }
} // namespace AkashiNetwork
