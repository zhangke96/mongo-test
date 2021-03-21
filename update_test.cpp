#include <bson/bson.h>
#include <mongoc/mongoc.h>

#include <sys/types.h>
#include <unistd.h>


#include <iostream>

int main(int argc, char *argv[]) {
  mongoc_init();
  mongoc_client_t *client =  mongoc_client_new("mongodb://127.0.0.1:27017/?appname=insert-example");
  mongoc_collection_t *collection = mongoc_client_get_collection(client, "test", "people");

  bson_t *filter_doc = bson_new ();
  BSON_APPEND_UTF8 (filter_doc, "name", "test1");

  // $set:{"time": time(nullptr)}
  bson_t *update_doc = bson_new();
  bson_t *time_doc = bson_new();
  BSON_APPEND_INT32(time_doc, "time", time(nullptr));
  BSON_APPEND_DOCUMENT(update_doc, "$set", time_doc);
  bson_error_t error;

  if (!mongoc_collection_update_one(collection, filter_doc, update_doc, nullptr, nullptr, &error)) {
    fprintf (stderr, "%s\n", error.message);
  }

  if (!mongoc_collection_update(collection, MONGOC_UPDATE_NONE, filter_doc, update_doc, nullptr, &error)) {
    fprintf(stderr, "%s\n", error.message);
  }

  // upsert
  bson_t *selector_doc = bson_new();
  BSON_APPEND_UTF8(selector_doc, "name", "jj");

  if (!mongoc_collection_update(collection, MONGOC_UPDATE_UPSERT, selector_doc, update_doc, nullptr, &error)) {
    fprintf(stderr, "%s\n", error.message);
  }

  bson_destroy (filter_doc);
  bson_destroy(update_doc);
  mongoc_collection_destroy (collection);
  mongoc_client_destroy (client);
  mongoc_cleanup ();
  
  // std::cout << "pid:" << get
  return 0;

}
