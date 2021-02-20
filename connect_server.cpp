
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

  mongoc_client_set_appname(client, "connect-example");

  // mongoc_database_t *default_database = mongoc_client_get_default_database(client);
  // if (!default_database) {
  //   std::cerr << "get default database fail" << std::endl;
  //   return 0;
  // }
  // std::cout << "get default database:" << default_database->name << std::endl;

  bson_t *command;
  bson_t reply;

  command = BCON_NEW("ping", BCON_INT32 (1));
  std::cout << sizeof(reply) << std::endl;
  bool ret = mongoc_client_command_simple(client, "test", command, NULL, &reply, &error);
  if (!ret) {
    std::cerr << "ping database fail" << std::endl;
    return 0;
  }
  // char *str = bson_as_json(&reply, nullptr);
  // std::cout << str << std::endl;
  return 0;
}