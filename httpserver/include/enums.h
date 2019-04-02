#ifndef HTTP_ENUMS_H
#define HTTP_ENUMS_H

#include <string>
#include <stdexcept>

namespace httpserverlib
{
    enum HTTPRequestType {
        GET
    };
    enum HTTPVersionType {
        V1_0,
        V1_1
    };
    enum HTTPStatusCode {
        Code200,
        Code404,
        Code500
    };

    static std::string toString( HTTPRequestType rt )
    {
        switch( rt ) {
            case HTTPRequestType::GET:
                return "GET";
            default:
                throw std::runtime_error( "Bad HTTPRequestType" );
        }
    }

    static std::string toString( HTTPVersionType vt )
    {
        switch( vt ) {
            case HTTPVersionType::V1_0:
                return "HTTP/1.0";
            case HTTPVersionType::V1_1:
                return "HTTP/1.1";
            default:
                throw std::runtime_error( "Bad HTTPVersionType" );
        }
    }

    static std::string toString( HTTPStatusCode sc )
    {
        switch( sc ) {
            case HTTPStatusCode::Code200:
                return "200 OK";
            case HTTPStatusCode::Code404:
                return "404 Not Found";
            default:
                throw std::runtime_error( "Bad HTTPStatusCode" );
        }
    }
}

#endif