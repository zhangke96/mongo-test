
#include <bson/bson.h>
#include <mongoc/mongoc.h>


#include <iostream>

int main(int argc, char *argv[]) {
  const char *uri_string = "mongodb://127.0.0.1:27017";
  mongoc_init();

  bson_error_t error;

  mongoc_uri_t *uri = mongoc_uri_new_with_error(uri_string, &error);
  if (!uri) {
    std::cerr << "fail to parse:" << uri_string << std::endl;
    return 0;
  }
  mongoc_client_t *client = mongoc_client_new_from_uri(uri);
  if (!client) {
    return 0;
  }
  std::cout << "open server:" << uri_string << " succ" << std::endl;

  mongoc_client_set_appname(client, "zhangke-test-client");

  bson_t *command;
  bson_t reply;

  // char **dbs = mongoc_client_get_database_names(client, &error);
  char **dbs = mongoc_client_get_database_names_with_opts(client, nullptr, &error);

  if (error.code) {
    std::cerr << "get database error" << std::endl;
    return 0;
  }
  char **p = dbs;
  while (*p) {
    std::cout << *p << std::endl;
    ++p;
  }


  return 0;
}