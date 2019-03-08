ASIO_COMM
~~~~~~~~~~

Description:
~~~~~~~~~~~~

A Simple TCP Server and Client using ASIO library. The Program uses Serialization for the transport of custom data between the Client and the Server.

Dependencies:
~~~~~~~~~~~~~

Boost > 1.66


Files:
~~~~~~

Server.cpp	Implementation of Server side 
Client.cpp	Implementation of Client Side
Connection.hpp	TCP Socket Read and Write Operations
Package.hpp	Communication Interface


Usage:
~~~~~~

Server <port>
Client <host> <port>

Example Output:
~~~~~~~~~~~~~~~~

Client Says:  Hello!	What ya doin?	Tue Mar  5 08:05:54 2019
Server Responds: Hi!	I'm Working	Tue Mar  5 08:05:54 2019


