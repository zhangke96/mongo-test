
#include <bson/bson.h>
#include <mongoc/mongoc.h>

#include <sys/types.h>
#include <unistd.h>


#include <iostream>

int main(int argc, char *argv[]) {
  mongoc_init();
  mongoc_client_t *client =  mongoc_client_new("mongodb://127.0.0.1:27017/?appname=insert-example");
  mongoc_collection_t *collection = mongoc_client_get_collection(client, "test", "people");

  bson_t *doc = bson_new ();
  BSON_APPEND_UTF8 (doc, "name", "test");

  bson_error_t error;

  if (!mongoc_collection_delete (
          collection, MONGOC_DELETE_NONE, doc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
  }

  bson_destroy (doc);
  mongoc_collection_destroy (collection);
  mongoc_client_destroy (client);
  mongoc_cleanup ();
  
  // std::cout << "pid:" << get
  return 0;

}
