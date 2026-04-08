#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdbool.h>

typedef bool bool_t;

/* Prototipos públicos */
void debounceFSM_init(void);
void debounceFSM_update(void);
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
