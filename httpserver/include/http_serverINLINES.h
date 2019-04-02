#ifndef HTTP_SERVER_INLINES_H
#define HTTP_SERVER_INLINES_H

namespace httpserverlib
{
    HTTPServer::HTTPServer( short port )
    : serverSocket_( std::to_string( port ).c_str() )
    {
    }

    void HTTPServer::run()
    {
        while( true ) {
            socketlib::Socket client = serverSocket_.accept();
            std::string header = client.readUntil("\r\n\r\n");
            HTTPRequest request = HTTPRequest::createFromHeader( header );

            HTTPResponse response( HTTPStatusCode::Code200, HTTPVersionType::V1_1, "Here's the body!" );
            std::cout << response.toString() << "\n";
            client.write( response.toString() );
            client.close();
        }
    }
}

#endif