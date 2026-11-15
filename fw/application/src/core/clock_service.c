#include "clock_service.h"
#include "app_timer.h"

APP_TIMER_DEF(m_clock_timer);

static uint8_t s_hours = 12;
static uint8_t s_minutes = 0;
static uint8_t s_seconds = 0;

static void clock_timer_handler(void *p_context) {
    if (++s_seconds >= 60) {
        s_seconds = 0;
        if (++s_minutes >= 60) {
            s_minutes = 0;
            if (++s_hours >= 24) {
                s_hours = 0;
            }
        }
    }
}

void clock_service_init(void) {
    app_timer_create(&m_clock_timer, APP_TIMER_MODE_REPEATED, clock_timer_handler);
    app_timer_start(m_clock_timer, APP_TIMER_TICKS(1000), NULL);
}

void clock_service_get_time(uint8_t *h, uint8_t *m, uint8_t *s) {
    if (h) *h = s_hours;
    if (m) *m = s_minutes;
    if (s) *s = s_seconds;
}

void clock_service_set_time(uint8_t h, uint8_t m) {
    s_hours = h % 24;
    s_minutes = m % 60;
    s_seconds = 0;
}
