#include "bind.h"
#include "methodGET.h"
#include "macros.h"
#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

// NEED TO WRITE A FLAG TO CHECK IF DONE PARSING HEADERS FOR SECURITY AGAINST
// MESSAGE CONTENT

// ONLY FOR TESTING PURPOSES
#include <stdio.h>

// #define BLOCK 8192
// #define URI_LEN 80
extern int errno;

int MIN(int a, int b) { return a > b ? b : a; }

int main(int argc, char **argv) {
  // initialize port number
  int portnum = 8080;

  // initialize buffers and holder arrays
  char inbuf[BLOCK];
  int inbuflen = 0;

  char resource[URI_LEN + 1];
  int resourcelen = 0;
  char defaultresource[] = "index.html";

  /*
  char hostname[BLOCK];
  int hostnamelen = 0;

  int contentlength = -1;
  */

  char outbuf[BLOCK];
  // int outbuflen = 0;

  FILE *errtxt = fopen("err.txt", "w+");

  // STRING LITERALS FOR RESPONSE
  // char httpversion[] = "HTTP/1.1 ";
  // char twohundred[] = "200 OK\r\n\r\n";

  // one port number
  if (argc > 1) {
    int temparg = atoi(argv[1]);

    if (temparg > 1024) {
      portnum = temparg;
    } else {
      warnx("bind: Permission denied");
      return -1;
    }
    if (temparg == 0) {
      warnx("invalid port number: %s", argv[1]);
      return -1;
    }
  }

  if (argc == 1) {
    warnx("wrong arguments\nusage: ./httpserver port_num usage: ./httpserver "
          "<port>");
    return -1;
  }

  // port number too large
  if (portnum > 65535) {
    portnum = 8080;
  }

  int listening = create_listen_socket(portnum);

  // MAIN SERVER LOOP START
  while (1) {
    int client = accept(listening, NULL, NULL);

    // HTTP STUFF START

    // loop to get request line and header
    int getflag, headflag, postflag = 0;
    int rb = 0;
    char *endofheader;
    char *startline = &inbuf[0];
    char *endline = &inbuf[0];
    int reqvhed = 0;

    // clean buffers each request
    for (int i = 0; i < BLOCK + 1; i += 1) {
      inbuf[i] = 0;
    }
    for (int i = 0; i < BLOCK + 1; i += 1) {
      outbuf[i] = 0;
    }
    for (int i = 0; i < URI_LEN + 1; i += 1) {
      resource[i] = 0;
    }
    inbuflen = 0;
    // outbuflen = 0;
    resourcelen = 0;

    while ((rb = read(client, inbuf, BLOCK - inbuflen)) > 0) {
      inbuflen += rb;

      // if we have a complete line gather data
      if ((endline = strstr(startline, "\r\n")) != NULL) {
        // set
        // if havent gotten request line yet, get it
        if (reqvhed == 0) {
          if (strstr(startline, "GET ") != NULL) {
            getflag = 1;
          } else if (strstr(startline, "HEAD ") != NULL) {
            headflag = 1;
          } else if (strstr(startline, "POST ") != NULL) {
            postflag = 1;
          }
          // for any http methods not supported or mangled method
          else {
            warnx("request type: Invalid or unsupported request type");
            break;
          }

          // find first space and http type locations
          char *firstspace = strstr(startline, " ");
          char *httpspot = strstr(startline, " HTTP/");
          if (firstspace == NULL || httpspot == NULL) {
            warnx("request line: Mangled request line");
            break;
          }

          // copy URI to storage
          firstspace += 2;
          resourcelen = httpspot - firstspace;
          strncpy(resource, firstspace, MIN(URI_LEN, resourcelen));

          // default resource
          strncpy(resource, defaultresource, 10);

          if (httpspot - firstspace != 0) {
            for (int i = 0; i < URI_LEN; i += 1) {
              resource[i] = 0;
            }
            strncpy(resource, defaultresource, 10);
          }

          // check if valid http type
          if (strstr(startline, "HTTP/1.1") == NULL) {
            warnx("http version: Invalid http version");
            break;
          }

          // set request as parsed
          reqvhed = 1;
        }
        // else get headers
        else {
          break;
        }
      }
      // TESTING BEGIN
      fprintf(errtxt, "First and Last of Line BEGIN\n");
      fprintf(errtxt, "%c", startline[0]);
      fprintf(errtxt, "%c", endline[0]);
      fprintf(errtxt, "First and Last of Line END\n");
      // TESTING END
      // catch up startline to endline and skip the \r\n
      endline += 2 * sizeof(char);
      startline = endline;

      if ((endofheader = strstr(inbuf, "\r\n\r\n")) != NULL) {
        // TESTING BEGIN
        fprintf(errtxt, "length of top of header is %ld\n",
                endofheader - &inbuf[0]);
        // TESTING END
        break;
      }

      if (inbuflen == BLOCK) {
        // reset buffer index and zero buffer
        inbuflen = 0;
        for (int i = 0; i < BLOCK; i += 1) {
          inbuf[i] = 0;
        }
        // TESTING BEGIN
        fprintf(errtxt, "max request length %d, zeroing and resetting buffer\n",
                inbuflen);
        // TESTING END
        break;
      }
    }

    // TESTING BEGIN
    char bar[10];
    bar[0] = '|';
    write(1, bar, 1);
    write(1, inbuf, inbuflen);
    write(1, bar, 1);

    if (getflag) {
      fprintf(errtxt, "GET Requested\n");
    }
    if (headflag) {
      fprintf(errtxt, "HEAD Requested\n");
    }
    if (postflag) {
      fprintf(errtxt, "POST Requested\n");
    }

    fprintf(errtxt, "%s\n", resource);
    // TESTING END

    // GET REQUEST
    if (getflag) {
      method_GET(200, client, resource);
      /*
      printf("resource: %s\n", resource);
      int res = open(resource, O_RDONLY);
      if (res == -1){
          warnx("file: Error opening resource");
      }
      else {
          // write response line
          write(client, httpversion, 9);
          write(client, twohundred, 10);

          int written = 0;
          // write content
          while((rb = read(res, outbuf, BLOCK - outbuflen)) > 0){
              outbuflen += rb;

              // flush on full
              if (outbuflen == BLOCK) {
                  while (written += write(client, outbuf, BLOCK) != BLOCK){
                      continue;
                  }
                  for (int i = 0; i < BLOCK; i += 1){
                      outbuf[i] = 0;
                  }
                  outbuflen = 0;
              }
          }
          while (written += write(client, outbuf, outbuflen) != outbuflen){
                      continue;
              }
      }
      close(res);
      */
    }

    // HTTP STUFF END
    close(client);

    // TESTING BEGIN
    fprintf(errtxt, "closed client\n");
    // break;
    // TESTING END

    // END
  }

  close(listening);

  // TESTING BEGIN
  fprintf(errtxt, "closed socket\n");
  // TESTING END

  return 0;
}
