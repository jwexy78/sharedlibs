#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "socket.h"

#include "http_request.h"
#include "http_response.h"

namespace httpserverlib
{
    class HTTPServer
    {
    public:
        /**
         * Open an HTTP Server on a given port
         */
        HTTPServer( short port );

        /**
         * Start the HTTP Server.
         * A blocking call.
         */
        void run();

    private:
        socketlib::ServerSocket serverSocket_;
    };
};

#include "http_serverINLINES.h"

#endif