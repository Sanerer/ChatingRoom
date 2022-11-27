

#include "catch2/catch.hpp"
#include "spdlog/spdlog.h"

#include "boost/asio/io_context.hpp"

#include "tcp_server.h"

TEST_CASE("async tcp server", "[asynctcp]") {
    spdlog::info("start to run async tcp server");

    boost::asio::io_context ioc;

    TcpServer server(ioc);
    ioc.run();
}