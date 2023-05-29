#include "configuration/config_manager.hpp"
#include "configuration/config_manager_p.hpp"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QSettings>

using namespace AkashiCore;

ConfigManager::ConfigManager()
    : d_ptr(std::make_unique<Private::ConfigManagerPrivate>())
{
  d_ptr.get()->config = new QSettings("config/config.ini", QSettings::IniFormat);
  d_ptr.get()->config->setIniCodec("UTF-8");
}

ConfigManager::~ConfigManager()
{}

bool ConfigManager::checkConfiguration()
{
  QStringList l_files = {"config/config.ini", "config/areas.json"};

  if (!QDir().exists("config"))
  {
    qDebug() << "[ConfigManager]::CHECK"
             << "Configuration folder not found. Make sure to rename config_sample to config!";
    return false;
  }

  bool config_folder_complete = true;
  for (const QString &l_file : l_files)
  {
    if (!QFile::exists(l_file))
    {
      qDebug() << "[ConfigManager]::CHECK" << l_file << "not found.";
      config_folder_complete = false;
    }
  }
  return config_folder_complete;
}

QString ConfigManager::readTextFile(QString f_file_name)
{
  QFile l_file(f_file_name);
  if (!l_file.open(QIODevice::ReadOnly))
  {
    qDebug() << "[ConfigManager]::ReadFile"
             << "Unable to open file" << f_file_name;
    return "";
  }
  QString l_content = l_file.readAll();
  if (l_content.isEmpty())
  {
    qDebug() << "[ConfigManager]::ReadFile" << QStringLiteral("No data read. This might indicate an error... or your file is just empty. Idk man. ¯\\_(ツ)_/¯");
  }
  return l_content;
}

QJsonDocument ConfigManager::readJsonFile(QString f_file_name)
{
  QJsonParseError error;
  QJsonDocument document = QJsonDocument::fromJson(readTextFile(f_file_name).toUtf8(), &error);
  if (error.error)
  {
    qWarning() << "[ConfigManager]::ReadJsonFile" << error.errorString();
  }
  return document;
}

int ConfigManager::serverPort()
{
  return d_ptr.get()->config->value("config/server_port", 0).toInt();
}

int ConfigManager::wsServerPort()
{
  return d_ptr.get()->config->value("config/ws_server_port", 0).toInt();
}

QString ConfigManager::serverName()
{
  return d_ptr.get()->config->value("config/server_name", "My First Server").toString();
}

QString ConfigManager::serverDescription()
{
  return d_ptr.get()->config->value("config/server_description", "Sample Text").toString();
}

int ConfigManager::maxPlayers()
{
  return d_ptr.get()->config->value("config/max_players", 200).toInt();
}

bool ConfigManager::enableAdvertiser()
{
  return d_ptr.get()->config->value("advertiser/advertise", false).toBool();
}

bool ConfigManager::showDebug()
{
  return d_ptr.get()->config->value("advertiser/debug", false).toBool();
}

QString ConfigManager::masterServerAddress()
{
  return d_ptr.get()->config->value("advertiser/ms_ip", "").toString();
}

QString ConfigManager::hostname()
{
  return d_ptr.get()->config->value("advertiser/hostname", "").toString();
}
