/*
 Client.cpp
 An asynchronous TCP Client.
 Author: Rafid Siddiqui
 j.rafid.siddiqui@gmail.com

*/

#include <iostream>
#include <vector>
#include "Connection.hpp"
#include <boost/serialization/vector.hpp>
#include "Package.hpp"


using boost::asio::ip::tcp;


class Client
{
public:
    // Constructor establishes the asynchronous connect operation.
    Client(boost::asio::io_service& io_service,const std::string& host, const std::string& port) : conn(io_service)
    {

        // Hostname resolution.
        tcp::resolver res(io_service);
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = res.resolve(query);
        tcp::endpoint end_point = *endpoint_iterator;

        // Start an asynchronous connect operation.
        conn.socket().async_connect(end_point,
                                    boost::bind(&Client::handle_connect, this,
                                                boost::asio::placeholders::error, ++endpoint_iterator));

    }

    // Handle completion of a connect operation.
    void handle_connect(const boost::system::error_code& e, tcp::resolver::iterator endpoint_iterator)
    {
        if (!e)
        {
            // prepare the Query
            std::time_t now = std::time(0);
            pkg = Package("Hello!","What ya doin?",std::ctime(&now));

            // Send the package using asychronous write
            conn.async_write(pkg,
                             boost::bind(&Client::handle_write, this,
                                         boost::asio::placeholders::error));

            // Client Receives the Response from Server

            conn.async_read(pkg,
                            boost::bind(&Client::handle_read, this,
                                        boost::asio::placeholders::error));
        }
        else if (endpoint_iterator != tcp::resolver::iterator())
        {
            // Try the next endpoint.
            conn.socket().close();
            boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
            conn.socket().async_connect(endpoint,
                                        boost::bind(&Client::handle_connect, this,
                                                    boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {

            std::cerr << e.message() << std::endl;
        }
    }

    // Handle the async read.
    void handle_read(const boost::system::error_code& e)
    {
        if (!e)
        {

            std::cout << pkg.get_msg() << "\t";
            std::cout << pkg.get_status() << "\t";
            std::cout << pkg.get_time() << std::endl;


        }
        else
        {
            // An error occurred.
            std::cerr << e.message() << std::endl;
        }

    }

    void handle_write(const boost::system::error_code& e)
    {
        // Nothing to do.
    }

private:
    /// The connection to the server.
    Connection conn;

    /// The data received from the server.
    Package pkg;
};



int main(int argc, char* argv[])
{
    try
    {
        // Checking the command line arguments.
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_service io_service;
        Client client(io_service, argv[1], argv[2]);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


