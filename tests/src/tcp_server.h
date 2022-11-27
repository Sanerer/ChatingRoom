#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"

class TcpServer {
public:
    TcpServer(boost::asio::io_context& ioc);

    void Accept();

private:
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
};