#ifndef EPOLL_INLINES_H
#define EPOLL_INLINES_H

#if HAS_EPOLL
#include <sys/epoll.h>
#endif

#include <stdexcept>

namespace epolllib
{
    inline Epoller::Epoller( int startingSize )
    {
    #if HAS_EPOLL
        epollfd_ = epoll_create1( startingSize );
        if( epollfd_ < 0 ) {
            throw std::runtime_error( "epoll failed" );
        }
    #else
        FD_ZERO( &readSet_ );
        FD_ZERO( &readySet_ );
        maxfd_ = 0;
    #endif
    }

    inline Epoller::~Epoller()
    {
    #if HAS_EPOLL
        close( epollfd_ );
    #else
    #endif
    }

    inline void Epoller::add( int fd )
    {
    #if HAS_EPOLL
        // !!! TODO !!!
    #else
        if( fd >= FD_SETSIZE ) {
            throw std::runtime_error( "fd is too large" );
        }
        if( fd > maxfd_ ) {
            maxfd_ = fd;
        }
        FD_SET( fd, &readSet_ );
    #endif
    }

    inline void Epoller::remove( int fd )
    {
    #if HAS_EPOLL
        // !!! Todo !!!
    #else
        FD_CLR( fd, &readSet_ );
    #endif
    }

    inline int Epoller::poll()
    {
    #if HAS_EPOLL
        // !!! Todo !!!
    #else
        while( true ) {
            for( int i = 0; i < maxfd_ + 1; ++i ) {
                if( FD_ISSET( i, &readySet_ ) ) {
                    FD_CLR( i, &readySet_ );
                    return i;
                }
            }
            readySet_ = readSet_;
            int ret = select( maxfd_ + 1, &readySet_, nullptr, nullptr, nullptr );
            if( ret < 0 ) {
                throw std::runtime_error( "select() failed" );
            }
        }
    #endif
    }
}

#endif