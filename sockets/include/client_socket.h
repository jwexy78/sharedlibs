#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

/**
 * Class that represents a TCP client-side connection
 */

#include "socket.h"
#include "client_socket.h"

namespace socketlib
{
    class ClientSocket : public Socket
    {
    public:
        /**
        * Create a new socket that connects to <hostname>:<port>
        */
        ClientSocket( const char* hostname, const char* port );

        /**
        * Get the port this socket is on locally
        */
        unsigned short getLocalPort();
    };
}

#include "client_socketINLINES.h"

#endif