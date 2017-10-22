#ifndef DEBUG_H
#define DEBUG_H

#define dprint(...) \
          fprintf(stderr, __VA_ARGS__); \
          printf("\n"); \
          fflush(stderr);

void printRequest(Request req) {
  dprint("Request: ACK: %d, ID: %d, OP: %d, PARAMS: [%d, %d]",
    req.ack,
    req.id,
    req.op,
    req.params[0],
    req.params[1]
  );
}

void printResponse(Response res) {
  dprint("Response: ACK: %d, ID: %d, STATUS: %d, DATA: %d",
    res.ack,
    res.id,
    res.status,
    res.data
  );
}

#endif
