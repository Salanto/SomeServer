#ifndef SERVER_HPP
#define SERVER_HPP

#include <QCoreApplication>
#include <memory>

namespace AkashiCore
{
namespace Private
{
struct ServerPrivate;
} // namespace Private

class Server : public QCoreApplication
{
public:
  Server(int argc, char *argv[]);
  ~Server();

private:
  std::unique_ptr<Private::ServerPrivate> d_ptr;
};
} // namespace AkashiCore

#endif // SERVER_HPP
