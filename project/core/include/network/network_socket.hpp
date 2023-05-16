#ifndef NETWORK_SOCKET_HPP
#define NETWORK_SOCKET_HPP

class QTcpSocket;
class QWebSocket;

#include "include/interfaces/network_socket_i.hpp"

namespace AkashiCore {
    class AOTCPSocket : public NetworkSocket
    {
        Q_OBJECT

      public:
        AOTCPSocket(QObject *parent, QTcpSocket *f_socket, int f_client_id);
        ~AOTCPSocket() {}

      private:
        QTcpSocket *m_socket;

      private slots:
        void receiveData();
    };

    class AOWebSocket : public NetworkSocket
    {
        Q_OBJECT

      public:
        AOWebSocket(QObject *parent, QWebSocket *f_socket, int f_client_id);
        ~AOWebSocket() {}

      private:
        QWebSocket *m_socket;

      private slots:
        void receiveData(QString f_data = "");
    };
}

#endif // NETWORK_SOCKET_HPP
