#include <iostream>

#include "socket.h"

#define CATCH_CONFIG_MAIN

#include "catch.h"

TEST_CASE( "TCP Client/Server Test" )
{
    socketlib::ServerSocket server( "1234" );
    socketlib::ClientSocket client( "localhost", "1234" );
    socketlib::Socket clientOnServer = server.accept();

    SECTION( "ReadAll()" ) {
        std::string content = "Hey! Here's a String!";

        clientOnServer.write( content );

        std::string received = client.read();
        REQUIRE( content == received );
    }

    SECTION( "ReadUntil()" ) {
        std::string content = "Here's a line\nHere's another!";

        clientOnServer.write( content );
        std::string received = client.readUntil( "\n" );

        REQUIRE( received == "Here's a line\n" );
        received = client.read();
        REQUIRE( received == "Here's another!" );
    }

    SECTION( "ReadBytes()" ) {
        std::string content = "Here is my random string";

        clientOnServer.write( content );
        std::string received = client.readBytes( 4 );

        REQUIRE( received == "Here" );
        received = client.read();
        REQUIRE( received == " is my random string" );
    }

    server.close();
    clientOnServer.close();
    client.close();
}