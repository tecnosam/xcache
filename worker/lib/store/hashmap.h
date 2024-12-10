#include "utils.h"


unsigned short set_entry(Value * map, char * key, unsigned char *raw_value) {

  Value * value = (Value *) malloc(sizeof(Value));

  if (value == NULL) {
    // TODO: log memory error
    // code of 999 means memory error here
    return 999;
  }

  value->value = raw_value;
  value->key_hash = compute_hash(key);

  if (value->key_hash == NULL) {
    // TODO: log memory error
    return 999;
  }

  *(map + value->key_hash->primary_index) = *value;

  return 0;
}


Value * get_entry(Value * map, char * key) {

  KeyHash * key_hash = compute_hash(key);

  if (key_hash == NULL) {
    // TODO: log memory error
    return NULL;
  }

  return find_at_index(map, key_hash);
}


unsigned short evict_entry(Value * map, char * key) {
  KeyHash * key_hash = compute_hash(key);

  if (key_hash == NULL) {
    // TODO: log memory error
    return 999;
  }

  // TODO: algorithm to remove an element from a linked list
  delete_from_value_list(map + key_hash->primary_index, key_hash);

  return 0;
}

