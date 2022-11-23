#include <chrono>
#include <exception>
#include <sstream>
#include <string>
#include <ctime>

#include "boost/asio/buffer.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/write.hpp"
#include "boost/system/detail/error_code.hpp"
#include "spdlog/spdlog.h"

#include "catch2/catch.hpp"

#include "boost/asio.hpp"

using namespace boost::asio::ip;

namespace {

std::string DayTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t today_time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream stream;
    stream << std::ctime(&today_time);
    return stream.str();
}

}  // namespace

TEST_CASE("init session", "[init]") {
    spdlog::info("start to run : {}", DayTimeString());

    try {
        boost::asio::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8899));
        while (true) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);

            spdlog::info("a client coming");

            std::string time_message = DayTimeString();

            boost::system::error_code err;
            auto response_size = boost::asio::write(socket, boost::asio::buffer(time_message), err);
            spdlog::info("write bytes: {}", response_size);
        }
    } catch (const std::exception& exc) {
        spdlog::error(exc.what());
    }
}