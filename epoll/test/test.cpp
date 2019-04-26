#include "epoll.h"

#include <iostream>
#include <unistd.h>

#define CATCH_CONFIG_MAIN

#include "catch.h"

TEST_CASE( "Basic EPoll Test" )
{
    epolllib::Epoller poller;

    constexpr int numPipes = 4;
    int fds[numPipes][2];
    for( int i = 0; i < numPipes; ++i ) {
        pipe( fds[i] );
    }

    SECTION( "One File" )
    {
        poller.add( fds[0][0] );
        write( fds[0][1], "whatsup", 7 );
        int ready = poller.poll();
        REQUIRE( ready == fds[0][0] );
    }

    SECTION( "Two Files, One Ready" )
    {
        poller.add( fds[0][0] );
        poller.add( fds[1][0] );
        write( fds[1][1], "whatsup", 7 );
        int ready = poller.poll();
        REQUIRE( ready == fds[1][0] );
    }

    SECTION( "Four Files, Two Ready" )
    {
        poller.add( fds[0][0] );
        poller.add( fds[1][0] );
        poller.add( fds[2][0] );
        poller.add( fds[3][0] );
        write( fds[1][1], "whatsup", 7 );
        write( fds[3][1], "whatsup", 7 );
        int r1 = poller.poll();
        REQUIRE( r1 == fds[1][0] );
        int r2 = poller.poll();
        REQUIRE( r2 == fds[3][0] );
    }

    SECTION( "Remove a File" )
    {
        poller.add( fds[0][0] );
        poller.add( fds[1][0] );
        poller.add( fds[2][0] );
        poller.add( fds[3][0] );
        poller.remove( fds[1][0] );
        write( fds[1][1], "whatsup", 7 );
        write( fds[3][1], "whatsup", 7 );
        int r1 = poller.poll();
        REQUIRE( r1 == fds[3][0] );
    }

    for( int i = 0; i < numPipes; ++i ) {
        close( fds[i][0] );
        close( fds[i][1] );
    }
}