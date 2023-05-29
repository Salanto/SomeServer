#ifndef PACKET_HPP
#define PACKET_HPP

#include "packet_info.hpp"
#include <QStringList>

namespace AkashiNetwork
{
class AOPacket
{
public:
  AOPacket(QStringList &contents);
  virtual ~AOPacket();

  const QStringList getContent();

  QString toString();
  QByteArray toUtf8();
  void setContentField(int f_content_index, QString f_content_data);
  void escapeContent();
  void unescapeContent();
  void setPacketEscaped(bool f_packet_state);
  bool isPacketEscaped();

  virtual PacketInfo getPacketInfo() const = 0;
  virtual bool validatePacket() const = 0;

protected:
  QStringList m_content;
  bool escaped;
  const QString packetFinished = "%";
};
} // namespace AkashiNetwork

#endif // PACKET_HPP
