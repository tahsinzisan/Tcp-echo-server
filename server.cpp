#include "server.h"
using namespace boost::asio;

EchoSession::EchoSession(tcp::socket socket) 
    : socket_(std::move(socket)) {}

void EchoSession::start() {
    do_read();
}

void EchoSession::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                do_write(length);
            }
        });
}

void EchoSession::do_write(std::size_t length) {
    auto self(shared_from_this());
    async_write(socket_, buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                do_read();
            }
        });
}

EchoServer::EchoServer(io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
}

void EchoServer::do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<EchoSession>(std::move(socket))->start();
            }
            do_accept();
        });
}
