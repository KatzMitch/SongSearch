
#include <stdint.h> 
#include <string>

uint32_t hashlittle( const void *key, size_t length, uint32_t initval);
uint32_t hash_string(const std::string & str);
