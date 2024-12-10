
/*
* Functionality of hashmap
* 1. set_entry(map, key, value) -> null
* 2. get_entry(map, key) -> value
* 3. evict_entry(map, key) -> flag 0 or 1
* 4. dump_entries(map, char *filename) -> null
* 5. load_entries(map, char *filename) -> address of map
*
* Helper functions
* 0. create_hashmap()
* 1. compute_hash(key) -> KeyHash
* 2. find_at_index(map, key_hash) -> Value
* 3. calculate_primary_index(key_hash) -> int
* 4. compare_key(value, key_hash) -> short [basically a boolean]
*/

#include "schemas.h"

#ifndef STDLIB_IMPORTED

  #define STDLIB_IMPORTED 1
  #include <stdlib.h>
  #include <string.h>

#endif // !STDLIB_IMPORTED


// ===== Helper Functions =====

char compare_key(Value * value, KeyHash * key_hash);
int calculate_primary_index(char * key);

Value * create_hashmap();
Value * find_at_index(Value * map, KeyHash * key_hash);

void reset_value_node(Value * node, Value * resetter);
void delete_from_value_list(Value * head, KeyHash * key_hash);

KeyHash * compute_hash(char *key);

Value * create_hashmap() {

  /*
   * Creates a hashmap using an array of `Value` items as
   * the ADT. Dynamically allocate space for this array
  */

  // dynamically allocate memory for top level array
  Value* map = (Value*) malloc(sizeof(Value) * MAX_HASHMAP_SIZE);

  if (map == NULL) {
    return NULL;
  }

  return map;
}


KeyHash * compute_hash(char *key) {

  /*
    * Compute the hash of the key in relation to the hashmap.
    * Returns a KeyHash with the primary hash being it's location
    * on the array ADT and the secondary hash being it's offset
    * along the secondary axis
  */

  KeyHash *key_hash = (KeyHash *) malloc(sizeof(KeyHash) * 1);

  if (key_hash == NULL) {
    // Insuffieint memory
    return NULL;
  }

  key_hash->primary_index = (int)calculate_primary_index(key);
  key_hash->key = key;

  return key_hash;
}


Value * find_at_index(Value* map, KeyHash * key_hash) {
  /*
  * Find the value at index in a map.
  * Return's a pointer to the element at that specific index
  */

  if (key_hash->primary_index >= MAX_HASHMAP_SIZE) {
    // going to cause segmentation fault
    return NULL;
  }

  Value * value_node = map + key_hash->primary_index;

  while (value_node->value != NULL) {

    if ((char)compare_key(value_node, key_hash) == 1) {
      break;
    }
    value_node = value_node->next;
  }

  if (value_node->value == NULL) {
    return NULL;
  }

  return value_node;
}


char compare_key(Value * value, KeyHash * key_hash) {
  /*
  * Confirm that the key associated with the value
  * is the same as the one in he key hasg
  */

  return strcmp(value->key_hash->key, key_hash->key) == 0 ? 1 : 0;
}


int calculate_primary_index(char * key) {
  /*
    * simple algorithm that calculates the primary index of a given key;
    * by summing it's characters and finding the modulo of the hashmap size
  */

  int sum = 0;

  for (int i = 0; i < MAX_KEY_LENGTH; i++) {
    sum += (int)(*(key + i));
  }

  return sum % MAX_HASHMAP_SIZE;
}


void reset_value_node(Value * node, Value * resetter) {

  if (resetter == NULL) {
    node->key_hash = NULL;
    node->value = NULL;
    node->next = NULL;
  }
  else {
    *node = *resetter;
  }
}


void delete_from_value_list(Value * head, KeyHash * key_hash) {

  /*
  * Takes in a value node, and returns the Value LinkedList
  * without the element who's key is key hash
  */

  if (head == NULL) {
    return;
  }
  // We've hit the node we want to evict
  if ((int)compare_key(head, key_hash) == 1) {
    // so we skip it
    reset_value_node(head, head->next);
  }
  else {
    delete_from_value_list(head->next, key_hash);
  }
}

