#include <iostream>

#include "http_server.h"

#define CATCH_CONFIG_MAIN

#include "catch.h"

TEST_CASE( "Test Case" )
{
    httpserverlib::HTTPServer server( 4000 );
    server.run();
}