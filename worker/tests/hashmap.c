#include <stdio.h>
#include "../lib/store/hashmap.h"


void test_basic_usecase();
void test_multiple_keys();
void test_overriding_key_values();


int main() {

  printf("===== BASIC TEST CASE ===== \n\n");
  test_basic_usecase();

  printf("===== MULTIPLE KEYS TEST CASE ===== \n\n");
  test_multiple_keys();

  printf("===== OVERRIDING KEYS TEST CASE ===== \n\n");
  test_overriding_key_values();

  return 0;
}


void test_basic_usecase() {

  unsigned short errorCode = 0;
  Value *map, *valueResponse;
  char *correctKey, *incorrectKey;
  unsigned char *value;

  map = create_hashmap();
  correctKey = "foo";
  incorrectKey = "bar";
  value = "The quick brown fox!";

  printf("Test ability to set an entry to a hashmap...\n");
  errorCode = set_entry(map, correctKey, value);
  if (errorCode != 0) {
    printf("ERROR: Setting entry in map failed with code: %d!!!\n", errorCode);
    return;
  }

  printf("Test ability to get already stored entry...\n");
  valueResponse = get_entry(map, correctKey);
  if (valueResponse == NULL) {
    printf("ERROR: Could not find key %s in map!!!\n", correctKey);
    return;
  }
  printf("Value Response: %s\n\n", valueResponse->value);

  printf("Test ability to return NULL when an incorrect Key is parsed to get_entry...\n");
  valueResponse = get_entry(map, incorrectKey);
  if (valueResponse != NULL) {
    printf("ERROR: unset key %s returning an address!!!\n", incorrectKey);
    return;
  }

  printf("Test ability to correctly evict an entry...\n");
  errorCode = evict_entry(map, correctKey);
  if (errorCode != 0) {
    printf("ERROR: Failed to evict entry from map with code: %d!!!\n", errorCode);
    return;
  }

  printf("Test that evicted entry is truly evicted...\n");
  valueResponse = get_entry(map, correctKey);
  if (valueResponse != NULL) {
    printf("Value Response: %s\n\n", valueResponse->value);
    printf("ERROR: evicted key %s is still returning an address!!!\n", correctKey);
    return;
  }

}

void test_multiple_keys() {

  unsigned short errorCode = 0;
  Value *map, *valueResponse1, *valueResponse2;
  char *key1, *key2;
  unsigned char *value1, *value2;

  key1 = "foo";
  value1 = "The quick brown fox!";
  key2 = "bar";
  value2 = "Jump over the lazy dog.";

  map = create_hashmap(); // Create an empty hashmap.
  
  printf("Test ability to set multiple entries in a hashmap...\n");
  errorCode = set_entry(map, key1, value1);
  if (errorCode != 0) {
    printf("ERROR: Setting entry in map failed with code: %d!!!\n", errorCode);
    return;
  }

  errorCode = set_entry(map, key2, value2);
  if (errorCode != 0) {
    printf("ERROR: Setting entry in map failed with code: %d!!!\n", errorCode);
    return;
  }

  printf("Test ability to get previously stored entries...\n");
  
  valueResponse1 = get_entry(map, key1);
  if (valueResponse1 == NULL) {
    printf("ERROR: Could not find key %s in map!!!\n", key1);
    return;
  }
  printf("Value Response for Key 1: %s\n", valueResponse1->value);
  
  valueResponse2 = get_entry(map, key2);
  if (valueResponse2 == NULL) {
    printf("ERROR: Could not find key %s in map!!!\n", key2);
    return;
  }
  printf("Value Response for Key 2: %s\n\n", valueResponse2->value);
  
  printf("Test collision handling in a hashmap...\n");
  
  // Create new key-value pairs with the same characters as key1 and key2.
  char *collisionKey1 = "foo";
  unsigned char *collisionValue1 = "Milk!";
  
  char *collisionKey2 = "oof";
  unsigned char *collisionValue2 = "Cookies!";
  
  errorCode = set_entry(map, collisionKey1, collisionValue1);
  if (errorCode != 0) {
    printf("ERROR: Setting entry in map failed with code: %d!!!\n", errorCode);
    return;
  }

  errorCode = set_entry(map, collisionKey2, collisionValue2);
  if (errorCode != 0) {
    printf("ERROR: Setting entry in map failed with code: %d!!!\n", errorCode);
    return;
  }
  
  valueResponse1 = get_entry(map, collisionKey1);
  if (valueResponse1 == NULL) {
    printf("ERROR: Could not find key %s in map!!!\n", collisionKey1);
    return;
  }
  printf("Value Response for Collided Key 1: %s\n", valueResponse1->value);
  
  valueResponse2 = get_entry(map, collisionKey2);
  if (valueResponse2 == NULL) {
    printf("ERROR: Could not find key %s in map!!!\n", collisionKey2);
    return;
  }
  printf("Value Response for Collided Key 2: %s\n\n", valueResponse2->value);
  
  printf("Test ability to remove entries from a hashmap...\n");
  
  errorCode = evict_entry(map, collisionKey1);
  if (errorCode != 0) {
    printf("ERROR: Deleting entry in map failed with code: %d!!!\n", errorCode);
    return;
  }

  valueResponse1 = get_entry(map, collisionKey1);
  if (valueResponse1 != NULL) {
    printf("ERROR: Key %s still present in the map after deletion!\n", collisionKey1);
    return;
  }

  errorCode = evict_entry(map, collisionKey2);
  if (errorCode != 0) {
    printf("ERROR: Deleting entry in map failed with code: %d!!!\n", errorCode);
    return;
  }

  valueResponse2 = get_entry(map, collisionKey2);
  if (valueResponse2 != NULL) {
    printf("ERROR: Key %s still present in the map after deletion!\n", collisionKey2);
    return;
  }
}


void test_overriding_key_values() {}
