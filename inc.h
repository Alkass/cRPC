#ifndef INC_H
#define INC_H

#define ACK 0xA

typedef char byte;

typedef enum {
  ADD = 0,
  SUB,
  MUL,
  DIV
} OpType;

typedef struct {
  byte ack;
  byte id;
  OpType op;
  byte params[2];
} Request;

typedef struct {
  byte ack;
  byte id;
  byte status;
  byte data;
} Response;

void printRequest(Request req) {
  printf("Request: ACK: %d, ID: %d, OP: %d, PARAMS: [%d, %d]\n",
    req.ack,
    req.id,
    req.op,
    req.params[0],
    req.params[1]
  );
}

void printResponse(Response res) {
  printf("Response: ACK: %d, ID: %d, STATUS: %d, DATA: %d\n",
    res.ack,
    res.id,
    res.status,
    res.data
  );
}

#endif
