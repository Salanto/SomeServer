#include "packet.hpp"
#include "packet_factory.hpp"

AkashiNetwork::AOPacket::AOPacket(QStringList &contents)
    : m_content(contents)
    , escaped(false)
{}

AkashiNetwork::AOPacket::~AOPacket()
{}

const QStringList AkashiNetwork::AOPacket::getContent()
{
  return m_content;
}

QString AkashiNetwork::AOPacket::toString()
{
  this->escapeContent();
  return QString("%1#%2#%3").arg(getPacketInfo().header, m_content.join("#"), packetFinished);
}

QByteArray AkashiNetwork::AOPacket::toUtf8()
{
  QString l_packet = this->toString();
  return l_packet.toUtf8();
}

void AkashiNetwork::AOPacket::setContentField(int f_content_index, QString f_content_data)
{
  m_content[f_content_index] = f_content_data;
}

void AkashiNetwork::AOPacket::escapeContent()
{
  if (isPacketEscaped())
  {
    return;
  }
  m_content.replaceInStrings("#", "<num>").replaceInStrings("%", "<percent>").replaceInStrings("$", "<dollar>").replaceInStrings("&", "<and>");
  this->setPacketEscaped(true);
}

void AkashiNetwork::AOPacket::unescapeContent()
{
  if (!isPacketEscaped())
  {
    return;
  }
  m_content.replaceInStrings("<num>", "#").replaceInStrings("<percent>", "%").replaceInStrings("<dollar>", "$").replaceInStrings("<and>", "&");
  this->setPacketEscaped(false);
}

void AkashiNetwork::AOPacket::setPacketEscaped(bool f_packet_state)
{
  escaped = f_packet_state;
}

bool AkashiNetwork::AOPacket::isPacketEscaped()
{
  return escaped;
}
