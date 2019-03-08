/*
 server.cpp
 An asynchronous TCP Server.
 Author: Rafid Siddiqui
 j.rafid.siddiqui@gmail.com

*/

#include <iostream>
#include <string>
#include "Connection.hpp"
#include <boost/serialization/vector.hpp>
#include "Package.hpp"

using boost::asio::ip::tcp;


class Server
{

private:

    Package pkg;
    tcp::acceptor acceptor_;

    void handle_accept(const boost::system::error_code& error,Connection::ptr conn)
    {
        if (!error)
        {

            // Server reads the request msg

            conn->async_read(pkg,
                             boost::bind(&Server::handle_read, this,
                                         boost::asio::placeholders::error,conn));



        }

        start_accept();
    }


// Handle the async read.
    void handle_read(const boost::system::error_code& e,Connection::ptr conn)
    {
        if (!e)
        {

            // Server prints the msg
            std::cout << pkg.get_msg() << "\t";
            std::cout << pkg.get_status() << "\t";
            std::cout << pkg.get_time() << std::endl;

            // Server Responds the request
            std::time_t now = std::time(0);
            pkg = Package("Hi!","I'm Working",std::ctime(&now));
            conn->async_write(pkg,
                              boost::bind(&Server::handle_write, this,
                                          boost::asio::placeholders::error, conn));

        }
        else
        {
            // An error occurred.
            std::cerr << e.message() << std::endl;
        }

    }

    void handle_write(const boost::system::error_code& e, Connection::ptr conn)
    {
        // Nothing to do.
    }

public:
    Server(boost::asio::io_context& io_context,int port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

    void start_accept()
    {
        Connection::ptr conn(new Connection(acceptor_.get_io_service()));

        acceptor_.async_accept(conn->socket(),boost::bind(&Server::handle_accept, this, boost::asio::placeholders::error,conn));

    }

};

int main(int argc,char* argv[])
{
    try
    {

        // Check command line arguments.
        if (argc != 2)
        {
            std::cerr << "Usage: Server <port>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        Server server(io_context,stoi(argv[1]));
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
