#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "inc.h"

int handleAdd(const Request* req, Response* res) {
  printf("res->data = %d + %d\n", req->params[0], req->params[1]);
  res->data = req->params[0] + req->params[1];
  return true;
}

int handleSub(const Request* req, Response* res) {
  printf("res->data = %d - %d\n", req->params[0], req->params[1]);
  res->data = req->params[0] - req->params[1];
  return true;
}

int handleMul(const Request* req, Response* res) {
  printf("res->data = %d * %d\n", req->params[0], req->params[1]);
  res->data = req->params[0] * req->params[1];
  return true;
}

int handleDiv(const Request* req, Response* res) {
  printf("res->data = %d / %d\n", req->params[0], req->params[1]);
  res->data = req->params[0] / req->params[1];
  return true;
}

int handleRequest(const Request* req, Response* res) {
  switch (req->op) {
    case ADD:
      return handleAdd(req, res);
    case SUB:
      return handleSub(req, res);
    case MUL:
      return handleMul(req, res);
    case DIV:
      return handleDiv(req, res);
    default:
      return false;
  }
}

int main() {
  struct sockaddr_in servaddr;
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

  // Clear servaddr
  bzero(&servaddr, sizeof(servaddr));

  // Set Addressing scheme
  servaddr.sin_family      = AF_INET;

  // Allow any IP to connect
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);

  // Listen on port 22000 – htons(22000)
  servaddr.sin_port        = htons(22000);

  // Prepare to listen for connections from address/port
  // specified in sockaddr ( Any IP on port 22000 )
  bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  // Start Listening for connections.
  // Keep at the most 1 connection requests waiting.
  // If there are more than 10 computers wanting to connect
  // at a time, the 11th one fails to.
  listen(listen_fd, 1);

  // Accept a connection from any device who is willing to connect.
  // If there is no one who wants to connect , wait. A file descriptor
  // is returned. This can finally be used to communicate, whatever
  // is sent by the device accepted can be read from comm_fd, whatever
  // is written to comm_fd is sent to the other device.
  int comm_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);

  Request req  = {0};
  Response res = {0};

  // Read a stream of bytes in the form of a Request structure
  // from end-user.
  // NOTE: The 'if' expression is used to silence the compiler about
  // complaining about an unused result (warn_unused_result).
  if (read(comm_fd, (byte*)&req, sizeof(Request)));

  // Verify that ACK is set properly
  if (req.ack == ACK) {

    printRequest(req);

    res.ack = req.ack;
    res.id = req.id;

    // Handle request.
    // This will set the value of req.data if applicable.
    if (handleRequest(&req, &res)) {
      res.status = true;
    }
    else {
      res.status = false;
    }

    printResponse(res);

    // Send a stream of bytes back in the form of a Response structure.
    // NOTE: The 'if' expression is used to silence the compiler about
    // complaining about an unused result (warn_unused_result).
    if (write(comm_fd, (byte*)&res, sizeof(Response)));
  }
  else {
    printf("Unrecognized ACK (%d). Failing here\n", req.ack);
  }
  
  close(comm_fd);

  return 0;
}
