#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

/**
 * Class that holds the server side of a TCP connection
 */

#include "socket.h"

namespace socketlib
{
    class ServerSocket : public Socket
    {
    public:
        /**
         * Create a new ServerSocket
         * @param port the port to bind to
         */
        ServerSocket( const char* port );

        /**
         * Accept and return a new client connection to the server
         */
        Socket accept();
    };
}

#include "server_socketINLINES.h"

#endif