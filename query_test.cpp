
#include <bson/bson.h>
#include <mongoc/mongoc.h>


#include <iostream>

int main(int argc, char *argv[]) {
  mongoc_init();

  mongoc_client_t *client =  mongoc_client_new("mongodb://127.0.0.1:27017/?appname=insert-example");
  mongoc_collection_t *collection = mongoc_client_get_collection(client, "test", "test");

  bson_error_t error;

  bson_t *command;
  bson_t reply;

  bson_t *query = bson_new();
  mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);

  const bson_t *doc = nullptr;
  char *str = nullptr;

  while (mongoc_cursor_next(cursor, &doc)) {
    str = bson_as_canonical_extended_json(doc, nullptr);
    std::cout << str << std::endl;
    bson_free(str);
  }

  return 0;
}