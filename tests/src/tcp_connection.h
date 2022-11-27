#include <vcruntime.h>
#include <memory>
#include <string>

#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/system/detail/error_code.hpp"

using namespace boost::asio::ip;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

    static TcpConnectionPtr Create(boost::asio::io_context& ioc);

    tcp::socket& Socket();

    void Start();

private:
    TcpConnection(boost::asio::io_context& ioc) : socket_(ioc){};

    tcp::socket socket_;
    std::string message_;
};