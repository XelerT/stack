#ifndef SECURITY_H
#define SECURITY_H

#include <cstdint>
#include "stack.h"

#define FULL_SECURITY //Comment line to turn off canaries and hashes
#ifdef FULL_SECURITY
#define CANARY_ON
#define HASH_ON
#endif /*FULL_SECURITY*/

#ifndef FULL_SECURITY
// #define CANARY_ON //Uncomment line to turn on canaries
// #define HASH_ON   //Unomment line to turn on hashes
#endif /*!FULL_SECURITY*/

#ifdef CANARY_ON
void  get_canaries (stack *stk);
int check_canaries (stack *stk);
#endif /*CANARY_ON*/

#ifdef HASH_ON
const uint64_t SEED = 5381;

uint64_t gnu_hash_stack   (const void *ptr, uint64_t seed);
uint64_t gnu_hash_data    (const void *ptr, uint64_t seed);
uint64_t check_data_hash  (const void *ptr, uint64_t seed);
uint64_t check_stack_hash (const void *ptr, uint64_t seed);

#endif /*HASH_ON*/

#endif /*SECURITY_H*/
