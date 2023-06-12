#include "Server.h"

std::ostream& operator<<(std::ostream& out, const Socket& socket) {
    out << inet_ntoa(socket.addr.sin_addr) << ":" << socket.addr.sin_port;
    return out;
}