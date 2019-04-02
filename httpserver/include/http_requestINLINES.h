#ifndef HTTP_REQUEST_INLINES_H
#define HTTP_REQUEST_INLINES_H

#include <sstream>

namespace httpserverlib
{
    HTTPRequest HTTPRequest::createFromHeader( std::string header )
    {
        std::istringstream ss( header );
        std::string type;
        std::string resource;
        std::string version;
        if( !( ss >> type >> resource >> version ) ) {
            throw std::runtime_error( "Invalid first line in header" );
        }
        HTTPRequestType httpType;
        HTTPVersionType httpVersion;
        if( type == "GET" ) {
            httpType = HTTPRequestType::GET;
        } else {
            throw std::runtime_error( "Unknown request type: " + type );
        }

        if( version == "HTTP/1.0" ) {
            httpVersion = V1_0;
        } else if( version == "HTTP/1.1" ) {
            httpVersion = V1_1;
        } else {
            throw std::runtime_error( "Unknown HTTP Version: " + version );
        }

        HTTPRequest request( httpType, resource, httpVersion );

        std::string token;
        std::string key;
        std::string value;
        while( ss >> token ) {
            if( token[token.size() - 1] == ':' ) {
                if( key.size() ) {
                    request.addParameter( key, value );
                }
                key = token.substr( 0, token.size() - 1 );
                value = "";
            } else {
                if( value.size() ) {
                    value += " ";
                }
                value += token;
            }
        }
        if( key.size() ) {
            request.addParameter( key, value );
        }

        return request;
    }

    HTTPRequest::HTTPRequest( HTTPRequestType type, std::string file, HTTPVersionType version )
    : requestType_( type )
    , file_( file )
    , httpVersion_( version )
    {
    }

    void HTTPRequest::addParameter( std::string key, std::string value )
    {
        parameters_[key] = value;
    }

    std::string HTTPRequest::getParameter( std::string key )
    {
        return parameters_[key];
    }

    std::string HTTPRequest::toString()
    {
        std::string output;

        output += ::httpserverlib::toString( requestType_ )
                + " " + file_ + " "
                + ::httpserverlib::toString( httpVersion_ ) + "\r\n";

        for( const auto& pair : parameters_ ) {
            output += pair.first + ": " + pair.second + "\r\n";
        }
        output += "\r\n";

        return output;
    }
}

#endif