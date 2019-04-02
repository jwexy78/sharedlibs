#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <unordered_map>
#include "enums.h"

namespace httpserverlib
{
    class HTTPResponse
    {
    public:
        HTTPResponse( HTTPStatusCode code, HTTPVersionType version, std::string body = "" );
        void setBody( std::string body );
        void setHeader( std::string key, std::string value );
        std::string toString();

    private:
        HTTPStatusCode statusCode_;
        HTTPVersionType httpVersion_;
        std::string body_;

        std::unordered_map<std::string,std::string> headers_;
    };
};

#include "http_responseINLINES.h"

#endif