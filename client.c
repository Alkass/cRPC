#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "inc.h"

int main()
{
    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(22000);

    // Set IP address in servaddr to “127.0.0.1” (computers way of saying myself)
    // since our server is also on the same machine . The address in servaddr
    // needs to be in integer format , hence the function inet_pton.
    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

    // Connect to the device whose address and port number is specified in servaddr.
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    Request req = {
      .ack = ACK,
      .id = 0,
      .op = ADD,       // other options are SUB, DIV, MUL
      .params = {8, 2} // You may change these two values to any 8-bit integer values
    };

    Response res = {0};

    printRequest(req);

    // Send a stream of bytes in the form of a Request structure.
    // NOTE: The 'if' expression is used to silence the compiler about
    // complaining about an unused result (warn_unused_result).
    if (write(sockfd, (byte*)&req, sizeof(Request)));

    // Read a stream of bytes in the form of a Response structure.
    // NOTE: The 'if' expression is used to silence the compiler about
    // complaining about an unused result (warn_unused_result).
    if (read(sockfd, (byte*)&res, sizeof(Response)));

    printResponse(res);
    
    close(sockfd);
    
    return 0;
}
