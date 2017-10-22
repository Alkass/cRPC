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
  byte op;
  byte params[2];
} Request;

typedef struct {
  byte ack;
  byte id;
  byte status;
  byte data;
} Response;

#endif
