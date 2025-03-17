#include "server.h"
using namespace std;

int main() {
    try {
        boost::asio::io_context io_context;
        EchoServer server(io_context, 12345);
        io_context.run();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
