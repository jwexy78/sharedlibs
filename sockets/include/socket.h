#ifndef SOCKET_H
#define SOCKET_H

/**
 * Base class for a Socket
 *
 * Holds the general interface for dealing with Sockets
 */

#include <string>

namespace socketlib
{
    class Socket
    {
    public:
        /**
         * Create a new Socket, optionally giving it a pre-made file descriptor
         */
        Socket( int fd = -1 );

        /**
         * Close the socket, closing the inderlying file descriptor
         */
        void close();

        /**
         * Make one call to read() on the socket and return whatever was read
         */
        std::string read();

        /**
         * Read until a delimiter is read
         * Note the delimiter is included in the returned string
         */
        std::string readUntil( std::string delimeter );

        /**
         * Read until an error occurs when trying to read more
         */
        std::string readUntilError();

        /**
         * Read up to a certain number of bytes
         */
        std::string readBytes( int length );

        /**
         * Write some data to the socket
         */
        void write( const std::string& data );

    protected:
        int fd_;
    
    private:
        /**
         * Append to `buffer_` whatever is returned by one call to read
         */
        void readIntoBuffer();

        std::string buffer_;
    };
}

#include "socketINLINES.h"

#include "client_socket.h"
#include "server_socket.h"

#endif