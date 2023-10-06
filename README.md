## HTTPServer by Brian Lawler

The program **httpserver** takes in a port number as a command line argument. It will create an httpserver that runs until the user closes the terminal or uses the command ctrl+c to finish execution. This program is incomplete and will not send any response to the client.

## Usage
The first step in using this program is to make it. Go into the bash terminal, navigate to the directory containing the file "**httpserver.c**" and type the command "**make**". This will create an executable file called **httpserver** in the same directory. Now you can use the executable as you see fit. Below will be the format for how to use it.

The format for using this program is as follows.

**./httpserver {port number} **

Example use case for port number "1234" 

**./httpserver 1234**

Errors will be produced upon improper entry of command line arguments. See the following section on Errors for more.

## Files

* Makefile
* README.md
* httpserver.c
* bind.c
* bind.h

## Errors

This program will produce error messages upon execution under the following circumstances
* Too few arguments -> the program must be given the arguments of at least one file and a single delimiting character. Program exits.
* Non-integer port number -> the program exits. The user must supply only an integer as a port number.
* Reserved port number as input (port number <= 1024) -> the program exits. The user must supply a port number argument greater than 1024.

## Design Decisions

My program flow goes as follows.
* Retrieve Port Number and validate
* Create listening socket
* While 1 loop everything following
* accept a connection
* Read loop until connection is closed or the request line and header fields are present in the buffer
* Parse request line and header fields for validity, throw errors on  malformed request and unsupported method
* Perform method
* Close connection

For my implementation I have not completed the parsing and method performing. As of right now there is no functionality except for extracting the request line and header fields. I still have to work on the parsing and then to implement the methods. I will implement the methods as function calls to make it nice and neat and separate concerns. In the case of a Put request, the function will have access to the original buffer to make sure it reads the entirety of the message body.

I chose the input buffer length to be 2048 since that coincides with the maximum length for the request line and header fields of any request we will receive. That way its easy to check if either the buffer is full to know a full request should be present or if there is the presence of the sequence of characters "\r\n\r\n"

## Credits

Anything to do with sockets - Man page for **socket, accept**


