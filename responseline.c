#include "macros.h"
#include "responseline.h"

#include <stdio.h>

int responseline(int response_code, int client){
  // httpversion and \r\n\r\n
  char httpversion[] = "HTTP/1.1 ";
  char rnrn[] = "\r\n\r\n";

  // lookup table for codes
  char *codes[600];

  // response buffer
  char out[URI_LEN + 1];
  for (int i = 0; i < URI_LEN + 1; i += 1) {
    out[i] = 0;
  }

  // 200 code
  char ok[] = "200 OK";
  char created[] = "201 Created";
  char accepted[] = "202 Accepted";
  char non_authoritative_information[] = "203 Non-Authoritative Information";
  char no_content[] = "204 No Content";
  char reset_content[] = "205 Reset Content";
  char partial_content[] = "206 Partial Content";
  char multi_status[] = "207 Multi-Status";
  char already_reported[] = "208 Already Reported";
  char IM_used[] = "226 IM Used";

  // 300 code
  char multiple_choices[] = "300 Multiple Choices";
  char moved_permanently[] = "301 Moved Permanently";
  char found[] = "302 Found";
  char see_other[] = "303 See Other";
  char not_modified[] = "304 Not Modified";
  char use_proxy[] = "305 Use Proxy";
  char switch_proxy[] = "306 Switch Proxy";
  char temporary_redirect[] = "307 Temporary Redirect";
  char permanent_redirect[] = "308 Permanent Redirect";

  // 400 code
  char bad_request[] = "400 Bad Request";
  char unauthorized[] = "401 Unauthorized";
  char payment_required[] = "402 Payment Required";
  char forbidden[] = "403 Forbidden";
  char not_found[] = "404 Not Found";
  char method_not_allowed[] = "405 Method Not Allowed";
  char not_acceptable[] = "406 Not Acceptable";
  char proxy_authentication_required[] = "407 Proxy Authentication Required";
  char request_timeout[] = "408 Request Timeout";
  char conflict[] = "409 Conflict";
  char gone[] = "410 Gone";
  char length_required[] = "411 Length Required";
  char precondition_failed[] = "412 Precondition Failed";
  char payload_too_large[] = "413 Payload Too Large";
  char URI_too_long[] = "414 URI Too Long";
  char unsupported_media_type[] = "415 Unsupported Media Type";
  char range_not_satisfiable[] = "416 Range Not Satisfiable";
  char expectation_failed[] = "417 Expectation Failed";
  char im_a_teapot[] = "418 I'm a teapot";
  char misdirected_request[] = "421 Misdirected Request";
  char unprocessable_entity[] = "422 Unprocessable Entity";
  char locked[] = "423 Locked";
  char failed_dependency[] = "424 Failed Dependency";
  char too_early[] = "425 Too Early";
  char upgrade_required[] = "426 Upgrade Required";
  char precondition_required[] = "428 Precondition Required";
  char too_many_requests[] = "429 Too Many Requests";
  char request_header_fields_too_large[] = "431 Request Header Fields Too Large";
  char unavailable_for_legal_reasons[] = "451 Unavailable For Legal Reasons";

  // 500 code
  char internal_server_error[] = "500 Internal Server Error";
  char not_implemented[] = "501 Not Implemented";
  char bad_gateway[] = "502 Bad Gateway";
  char service_unavailable[] = "503 Service Unavailable";
  char gateway_timeout[] = "504 Gateway Timeout";
  char http_version_not_supported[] = "505 HTTP Version Not Supported";
  char variant_also_negotiates[] = "506 Variant Also Negotiates";
  char insufficient_storage[] = "507 Insufficient Storage";
  char loop_detected[] = "508 Loop Detected";
  char not_extended[] = "510 Not Extended";
  char network_authentication_required[] = "511 Network Authentication Required";

  // populate lookup table
  for (int i = 0; i < 600; i += 1){
    codes[i] = NULL;
  }
  codes[200] = &ok[0];
  codes[201] = &created[0];
  codes[202] = &accepted[0];
  codes[203] = &non_authoritative_information[0];
  codes[204] = &no_content[0];
  codes[205] = &reset_content[0];
  codes[206] = &partial_content[0];
  codes[207] = &multi_status[0];
  codes[208] = &already_reported[0];
  codes[226] = &IM_used[0];

  codes[300] = &multiple_choices[0];
  codes[301] = &moved_permanently[0];
  codes[302] = &found[0];
  codes[303] = &see_other[0];
  codes[304] = &not_modified[0];
  codes[305] = &use_proxy[0];
  codes[306] = &switch_proxy[0];
  codes[307] = &temporary_redirect[0];
  codes[308] = &permanent_redirect[0];

  codes[400] = &bad_request[0];
  codes[401] = &unauthorized[0];
  codes[402] = &payment_required[0];
  codes[403] = &forbidden[0];
  codes[404] = &not_found[0];
  codes[405] = &method_not_allowed[0];
  codes[406] = &not_acceptable[0];
  codes[407] = &proxy_authentication_required[0];
  codes[408] = &request_timeout[0];
  codes[409] = &conflict[0];
  codes[410] = &gone[0];
  codes[411] = &length_required[0];
  codes[412] = &precondition_failed[0];
  codes[413] = &payload_too_large[0];
  codes[414] = &URI_too_long[0];
  codes[415] = &unsupported_media_type[0];
  codes[416] = &range_not_satisfiable[0];
  codes[417] = &expectation_failed[0];
  codes[418] = &im_a_teapot[0];
  codes[421] = &misdirected_request[0];
  codes[422] = &unprocessable_entity[0];
  codes[423] = &locked[0];
  codes[424] = &failed_dependency[0];
  codes[425] = &too_early[0];
  codes[426] = &upgrade_required[0];
  codes[428] = &precondition_required[0];
  codes[429] = &too_many_requests[0];
  codes[431] = &request_header_fields_too_large[0];
  codes[451] = &unavailable_for_legal_reasons[0];

  codes[500] = &internal_server_error[0];
  codes[501] = &not_implemented[0];
  codes[502] = &bad_gateway[0];
  codes[503] = &service_unavailable[0];
  codes[504] = &gateway_timeout[0];
  codes[505] = &http_version_not_supported[0];
  codes[506] = &variant_also_negotiates[0];
  codes[507] = &insufficient_storage[0];
  codes[508] = &loop_detected[0];
  codes[510] = &not_extended[0];
  codes[511] = &network_authentication_required[0];

  // write full status line to client
  char *code = codes[response_code];
  if (code == NULL){
    printf("error: no such status code\r\n\r\n");
    return -1;
  }
  int codelen = strlen(code);
  int totallen = 9 + codelen + 4;
  int written = 0;
  strncpy(&out[0], httpversion, 9);
  strncpy(&out[9], code, codelen);
  strncpy(&out[9 + codelen], rnrn, 4);
  // write(client, httpversion, 9);
  // write (client, code, codelen);
  // write(client, rnrn, 4);
  while (written += write(client, out, totallen - written) < totallen){
    continue;
  }

  // rezero the out buffer
  for (int i = 0; i < URI_LEN + 1; i += 1) {
    out[i] = 0;
  }

  // return 0 on success
  return 0;

}

/*
int main(void){

  for (int i = 200; i < 512; i += 1){
    // printf("response code %d: ", i);
    responseline(i, 1);
  }

  return 0;
}
*/
