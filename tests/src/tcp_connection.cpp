#include "tcp_connection.h"
#include <vcruntime.h>

#include <functional>
#include <memory>

#include "boost/asio/buffer.hpp"
#include "boost/asio/write.hpp"
#include "boost/system/detail/error_code.hpp"
#include "common/day_time_string.h"
#include "spdlog/spdlog.h"

auto TcpConnection::Create(boost::asio::io_context& ioc) -> TcpConnectionPtr {
    return std::shared_ptr<TcpConnection>(new TcpConnection(ioc));
}

// TcpConnection::TcpConnection(boost::asio::io_context& ioc) : socket_(ioc) {}

tcp::socket& TcpConnection::Socket() {
    return socket_;
}

void TcpConnection::Start() {
    message_ = DayTimeString();

    boost::asio::async_write(socket_,
                             boost::asio::buffer(message_),
                             [self = shared_from_this()](const boost::system::error_code& err,
                                                         size_t bytes_transferred) {
                                 spdlog::info("write message : {}", bytes_transferred);
                             });
}
