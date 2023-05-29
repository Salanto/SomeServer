#include "aotcpsocket.hpp"

#include <QDebug>
#include <QTcpSocket>

namespace AkashiNetwork
{
AOTCPSocket::AOTCPSocket(QObject *parent, QTcpSocket *f_socket)
    : NetworkSocket(parent)
    , m_socket(f_socket)
{
  connect(m_socket, &QTcpSocket::readyRead, this, &AOTCPSocket::receiveData);
  connect(m_socket, &QTcpSocket::disconnected, this, &AOTCPSocket::disconnected);
  ip = m_socket->peerAddress();
}

AOTCPSocket::~AOTCPSocket()
{
  qDebug() << "[AOTCPSOCKET]DTOR Destroying client connection.";
}

QHostAddress AOTCPSocket::remoteIP()
{
  return ip;
}

QString AOTCPSocket::pendingData()
{
  QString current_data = m_buffer;
  m_buffer.clear();
  return current_data;
}

void AOTCPSocket::writeData(const QByteArray f_data)
{
  m_socket->write(f_data);
}

void AOTCPSocket::receiveData()
{
  m_buffer += QString::fromUtf8(m_socket->readAll());
  emit dataReceived();
};
} // namespace AkashiNetwork
