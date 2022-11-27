#include "tcp_server.h"

#include "boost/asio/ip/tcp.hpp"

#include "boost/system/detail/error_code.hpp"
#include "tcp_connection.h"

using namespace boost::asio::ip;

TcpServer::TcpServer(boost::asio::io_context& ioc)
        : ioc_(ioc), acceptor_(ioc_, tcp::endpoint(tcp::v4(), 8899)) {
    Accept();
}

void TcpServer::Accept() {
    auto connection = TcpConnection::Create(ioc_);

    acceptor_.async_accept(connection->Socket(),
                           [this, connection](const boost::system::error_code& err) {
                               connection->Start();
                               Accept();
                           });
}