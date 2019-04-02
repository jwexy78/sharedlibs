#ifndef HTTP_RESPONSE_INLINES_H
#define HTTP_RESPONSE_INLINES_H

#include "http_response.h"

namespace httpserverlib
{
    HTTPResponse::HTTPResponse( HTTPStatusCode code, HTTPVersionType version, std::string body )
    : statusCode_( code )
    , httpVersion_( version )
    {
        setBody( body );
    }

    void HTTPResponse::setBody( std::string body )
    {
        body_ = body;
        setHeader( "Content-Length", std::to_string( body.size() ) );
    }

    void HTTPResponse::setHeader( std::string key, std::string value )
    {
        headers_[key] = value;
    }

    std::string HTTPResponse::toString()
    {
        std::string output = ::httpserverlib::toString( httpVersion_ ) + " "
            + ::httpserverlib::toString( statusCode_ ) + "\r\n";
        for( const auto& pair : headers_ ) {
            output += pair.first + ": " + pair.second + "\r\n";
        }
        output += "\r\n";
        output += body_;
        return output;
    };


}

#endif