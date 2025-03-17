#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <iostream>

using boost::asio::ip::tcp;

class EchoSession : public std::enable_shared_from_this<EchoSession> {
public:
    EchoSession(tcp::socket socket);
    void start();

private:
    void do_read();
    void do_write(std::size_t length);

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class EchoServer {
public:
    EchoServer(boost::asio::io_context& io_context, short port);

private:
    void do_accept();

    tcp::acceptor acceptor_;
};

#endif
