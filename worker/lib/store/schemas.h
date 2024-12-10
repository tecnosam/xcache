/*
* Here we have code to help us store items in a key value fashion with ideally
* O(1) retrieval time and O(n) space
*/

#ifndef MAX_KEY_LENGTH
  #define MAX_KEY_LENGTH 256
#endif // !MAX_KEY_LENGTH

#ifndef MAX_HASHMAP_SIZE
  // We can have up to 500 elements in one single hash map.
  // TODO: move this to the config/constants.h
  #define MAX_HASHMAP_SIZE 500
#endif // !MAX_HASHMAP_SIZE


typedef struct KeyHash {

  char * key;
  int primary_index;
} KeyHash;


typedef struct Value {
  KeyHash * key_hash;
  unsigned char *value;

  // Next element with hash collisions
  // NOTE: not to be mistaken with chain next element
  struct Value * next;

} Value;

