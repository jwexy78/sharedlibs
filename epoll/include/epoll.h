#ifndef EPOLL_H
#define EPOLL_H

#define HAS_EPOLL __has_include(<sys/epoll>)

#include <unistd.h>

namespace epolllib
{
    class Epoller
    {
    public:
        Epoller( int startingSize = 0 );
        ~Epoller();

        Epoller( const Epoller& ) = delete;
        Epoller& operator=( const Epoller& ) = delete;

        /**
         * Add a new file descriptor to monitor
         */
        void add( int fd );

        /**
         * Stop watching a file descriptor
         */
        void remove( int fd );

        /**
         * Return the next file descriptor ready
         */
        int poll();

    private:
    #if HAS_EPOLL
        int epollfd_;
    #else
        fd_set readSet_;
        fd_set readySet_;
        int maxfd_;
    #endif
    };
}

#include "epollINLINES.h"

#endif