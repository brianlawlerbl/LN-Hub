#include "methodGET.h"
#include "macros.h"

// for testing
#include <stdio.h>

int method_GET(int response_code, int client, char *resource) {
  // printf("resource: %s\n", resource);
  int res = open(resource, O_RDONLY);
  if (res == -1) {
    warnx("file: Error opening resource");
  } else {
    // write response line
    if (response_code == 200) {
      responseline(200, client);
    }

    char out[BLOCK];
    for (int i = 0; i < BLOCK; i += 1) {
      out[i] = 0;
    }

    int outlen = 0;
    int written = 0;
    int rb = 0;
    // write content
    while ((rb = read(res, out, BLOCK - outlen)) > 0) {
      outlen += rb;

      // flush on full
      if (outlen == BLOCK) {
        while (written += write(client, out, BLOCK) != BLOCK) {
          continue;
        }
        for (int i = 0; i < BLOCK; i += 1) {
          out[i] = 0;
        }
        outlen = 0;
      }
    }
    while (written += write(client, out, outlen) != outlen) {
      continue;
    }
  }
  close(res);

  return 0;
}

/*
int main(void){

  char res[URI_LEN + 1];
  for (int i= 0; i < URI_LEN; i += 1){
    res[i] = 0;
  }
  strcpy(&res[0], "food.txt");
  printf("copied resource into resource string for testing\n");

  int ret = method_GET(200, 1, &res[0]);

  return ret;
}
*/
