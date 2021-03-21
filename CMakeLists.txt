cmake_minimum_required(VERSION 3.10)

project(Mongo_Test)

find_package (bson-1.0 1.7 REQUIRED)
find_package (mongoc-1.0 1.7 REQUIRED)

add_executable(Connect_Test connect_server.cpp)

target_link_libraries(Connect_Test PRIVATE mongo::mongoc_static mongo::bson_static)

add_executable(List_dbs list_dbs.cpp)

target_link_libraries(List_dbs PRIVATE mongo::mongoc_static mongo::bson_static)

add_executable(InsertTest insert_test.cpp)

target_link_libraries(InsertTest PRIVATE mongo::mongoc_static mongo::bson_static)

add_executable(QueryTest query_test.cpp)

target_link_libraries(QueryTest PRIVATE mongo::mongoc_static mongo::bson_static)

add_executable(CountTest collection_count.cpp)
target_link_libraries(CountTest PRIVATE mongo::mongoc_static mongo::bson_static)

add_executable(InsertBulk insert_batch.cpp)
target_link_libraries(InsertBulk PRIVATE mongo::mongoc_static mongo::bson_static)
# target_link_libraries(QueryTest)
# target_link_libraries(QueryTest PRIVATE mongo::mongoc_static mongo::bson_static)

add_executable(DeleteTest delete_test.cpp)
target_link_libraries(DeleteTest PRIVATE mongo::mongoc_static mongo::bson_static)

add_executable(UpdateTest update_test.cpp)
target_link_libraries(UpdateTest PRIVATE mongo::mongoc_static mongo::bson_static)
