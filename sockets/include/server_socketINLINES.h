#ifndef SERVER_SOCKET_INLINES_H
#define SERVER_SOCKET_INLINES_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdexcept>

#include "socket.h"
#include "server_socket.h"

namespace socketlib
{
    inline ServerSocket::ServerSocket( const char* port )
    : Socket()
    {
        // Open a new socket
        fd_ = socket( AF_INET, SOCK_STREAM, 0 );
        
        int optval = 1;
        setsockopt( fd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof( optval ) );
        optval = 1;
        setsockopt( fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof( optval ) );

        // Get the address info of localhost port
        struct addrinfo hints, *result;
        memset(&hints, 0, sizeof( struct addrinfo ) );
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        if( getaddrinfo( NULL, port, &hints, &result ) ) {
            throw std::runtime_error( "getaddrinfo()" );
        }

        if( bind( fd_, result->ai_addr, result->ai_addrlen ) ) {
            throw std::runtime_error( "bind()" );
        }

        if( listen( fd_, 10 ) != 0 ) {
            throw std::runtime_error( "listen()" );
        }
    }

    inline Socket ServerSocket::accept()
    {
        int clientFd = ::accept( fd_, NULL, NULL );
        if( clientFd <= 0 ) {
            throw std::runtime_error( "accept()" );
        }
        return Socket( clientFd );
    }
};

#endif

