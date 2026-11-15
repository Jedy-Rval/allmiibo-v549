#ifndef CLOCK_SERVICE_H
#define CLOCK_SERVICE_H

#include <stdint.h>
#include <stdbool.h>

void clock_service_init(void);
void clock_service_get_time(uint8_t *h, uint8_t *m, uint8_t *s);
void clock_service_set_time(uint8_t h, uint8_t m);

#endif
