#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <unordered_map>
#include "enums.h"

namespace httpserverlib
{
    class HTTPRequest
    {
    public:
        /**
         * Create an HTTPRequest object from a received
         * request's header
         */
        static HTTPRequest createFromHeader( std::string header );

        /**
         * Create a new HTTP Request
         */
        HTTPRequest( HTTPRequestType type, std::string file, HTTPVersionType version = V1_1 );

        /**
         * Add a parameter to the header
         */
        void addParameter( std::string key, std::string value );

        /**
         * Get the value for a given parameter key
         */
        std::string getParameter( std::string key );

        /**
         * Convert the request into a string that can be sent
         */
        std::string toString();

    private:
        HTTPRequestType requestType_;
        std::string file_;
        HTTPVersionType httpVersion_;

        std::unordered_map<std::string,std::string> parameters_;
    };
}

#include "http_requestINLINES.h"

#endif