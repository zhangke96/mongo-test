#include <bson/bson.h>
#include <mongoc/mongoc.h>

#include <iostream>

int main(int argc, char *argv[]) {
  mongoc_init();
  mongoc_client_t *client =  mongoc_client_new("mongodb://127.0.0.1:27017/?appname=insert-example");
  mongoc_collection_t *collection = mongoc_client_get_collection(client, "test", "people");

  int64_t count = mongoc_collection_count(collection, MONGOC_QUERY_NONE, NULL, 1000, 50, NULL, NULL);
  std::cout << "collection count:" << count;
}