#ifndef CLIENT_SOCKET_INLINES_H
#define CLIENT_SOCKET_INLINES_H

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

#include "client_socket.h"

namespace socketlib
{
    inline ClientSocket::ClientSocket( const char* hostname, const char* port )
    : Socket()
    {
        struct addrinfo* serverinfo;
        struct addrinfo hints;
        memset( &hints, 0, sizeof( hints ) );
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if( getaddrinfo( hostname, port, &hints, &serverinfo ) < 0 ) {
            throw std::runtime_error( "getaddrinfo()" );
            return;
        }

        struct addrinfo* address;
        for( address = serverinfo; address; address = address->ai_next ) {
            fd_ = socket(
                address->ai_family,
                address->ai_socktype,
                address->ai_protocol );
            if( fd_ < 0 ) {
                continue;
            }
            if( connect( fd_, address->ai_addr, address->ai_addrlen ) < 0 ) {
                ::close( fd_ );
                fd_ = -1;
                continue;
            }
            break;
        }
        if( !address ) {
            throw std::runtime_error( "Failed to connect" );
        }

        void* in_addr = 
            ( address->ai_addr->sa_family == AF_INET ) ?
            (void*) &(((struct sockaddr_in*)address->ai_addr)->sin_addr ) :
            (void*) &(((struct sockaddr_in6*)address->ai_addr)->sin6_addr );

        char s[INET6_ADDRSTRLEN];
        inet_ntop(
            address->ai_family,
            in_addr,
            s,
            sizeof( s ) );
        freeaddrinfo(serverinfo);
    }

    inline unsigned short ClientSocket::getLocalPort()
    {
        struct sockaddr_in my_addr;
        unsigned int len = sizeof( my_addr );
        char myIP[6];
        getsockname( fd_, (struct sockaddr *) &my_addr, &len );
	    inet_ntop(  AF_INET, &my_addr.sin_addr, myIP, sizeof( myIP ) );
	    return ntohs(my_addr.sin_port);
    }
}

#endif