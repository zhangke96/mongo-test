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
  bson_oid_t oid;
  bson_oid_init(&oid, nullptr);
  BSON_APPEND_UTF8 (doc, "name", "test1");
  BSON_APPEND_UTF8(doc, "comment", "insert1");
  BSON_APPEND_OID(doc, "_id", &oid);


  bson_error_t error;
  bson_t* insert_array[3];
  insert_array[0] = doc;
  
  doc = bson_new();
  BSON_APPEND_UTF8(doc, "name", "test2");
  BSON_APPEND_UTF8(doc, "comment", "insert2");
  BSON_APPEND_OID(doc, "_id", &oid);
  insert_array[1] = doc;
  doc = bson_new();
  BSON_APPEND_UTF8(doc, "name", "test3");
  BSON_APPEND_UTF8(doc, "comment", "insert3");
  BSON_APPEND_OID(doc, "_id", &oid);
  insert_array[2] = doc;

  if (!mongoc_collection_insert_bulk (
          collection, MONGOC_INSERT_CONTINUE_ON_ERROR, (const bson_t**)&(insert_array[0]), 3, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
  }

  bson_destroy (doc);
  mongoc_collection_destroy (collection);
  mongoc_client_destroy (client);
  mongoc_cleanup ();
  
  // std::cout << "pid:" << get
  return 0;

}
