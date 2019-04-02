#ifndef SOCKET_INLINES_H
#define SOCKET_INLINES_H

#include <unistd.h>
#include <errno.h>

#include "socket.h"

namespace socketlib
{
    inline Socket::Socket( int fd )
    : fd_( fd )
    {
    }

    inline void Socket::close()
    {
        if( fd_ > 0 ) {
            ::close( fd_ );
            fd_ = -1;
        }
    }

    inline std::string Socket::read()
    {
        if( buffer_.size() ) {
            std::string out = buffer_;
            buffer_ = "";
            return out;
        }
        readIntoBuffer();
        std::string output = buffer_;
        buffer_ = "";
        return output;
    }

    inline std::string Socket::readUntil( std::string delim )
    {
        while( true ) {
            int idx = buffer_.find( delim );
            if( idx > 0 ) {
                std::string output = buffer_.substr( 0, idx + delim.size() );
                buffer_ = buffer_.substr( idx + delim.size() );
                return output;
            }
            readIntoBuffer();
        }
    }

    inline std::string Socket::readUntilError()
    {
        std::string output;
        while( true ) {
            try {
                output += read();
            } catch( std::runtime_error& error ) {
                return output;
            }
        }
    }

    inline std::string Socket::readBytes( int length )
    {
        while( true ) {
            if( buffer_.size() >= length ) {
                std::string output = buffer_.substr( 0, length );
                buffer_ = buffer_.substr( length );
                return output;
            }
            readIntoBuffer();
        }
    }

    inline void Socket::write( const std::string& data )
    {
        int length = data.length();
        int written = 0;
        while( written < length )
        {
            int ret = ::write( fd_, data.c_str() + written, length - written );
            if( ret > 0 ) {
                written += ret;
                continue;
            }
            if( ret < 0 && errno == EAGAIN ) {
                continue;
            }
            throw std::runtime_error( "Error writing to socket" );
        }
    }

    inline void Socket::readIntoBuffer()
    {
        while( true ) {
            char buffer[216];
            errno = 0;
            int readed = ::read( fd_, buffer, 215 );
            if( readed == 0 ) {
                break;
            }
            if( readed < 0 ) {
                if( errno == EAGAIN ) {
                    break;
                }
                throw std::runtime_error( "Error reading from socket" );
            }
            buffer_ += std::string( buffer, readed );
            if( readed < 215 ) {
                break;
            }
        }
    }
}

#endif