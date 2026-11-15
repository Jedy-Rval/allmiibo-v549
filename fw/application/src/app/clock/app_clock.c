#include "app_clock.h"
#include "flower_art.h"
#include "clock_service.h"
#include "mini_app_registry.h"
#include "mini_app_launcher.h"
#include "mui_include.h"
#include <stdio.h>

typedef struct {
    mui_view_dispatcher_t *p_view_dispatcher;
    mui_view_t *p_clock_view;
} app_clock_t;

static void clock_view_draw_cb(mui_view_t *p_view, mui_canvas_t *p_canvas) {
    // 1. Draw floral background
    mui_canvas_draw_xbm(p_canvas, 0, 0, 128, 64, flower_art_bits);

    // 2. Fetch current time
    uint8_t h, m, s;
    clock_service_get_time(&h, &m, &s);

    // 3. Format time string
    char time_str[10];
    snprintf(time_str, sizeof(time_str), "%02d:%02d", h, m);

    // 4. Draw large clock centered
    mui_canvas_set_font(p_canvas, u8g2_font_helvB14_tr);
    uint16_t tw = mui_canvas_string_width(p_canvas, time_str);
    mui_canvas_draw_utf8(p_canvas, 64 - (tw / 2), 36, time_str);

    // 5. Draw AM/PM below
    char sub_str[8];
    snprintf(sub_str, sizeof(sub_str), "%s", (h >= 12 ? "PM" : "AM"));
    mui_canvas_set_font(p_canvas, u8g2_font_5x8_tr);
    uint16_t sw = mui_canvas_string_width(p_canvas, sub_str);
    mui_canvas_draw_utf8(p_canvas, 64 - (sw / 2), 48, sub_str);
}

static void clock_view_input_cb(mui_view_t *p_view, mui_input_event_t *p_event) {
    if (p_event->type == INPUT_TYPE_SHORT || p_event->type == INPUT_TYPE_LONG) {
        mini_app_launcher_kill(mini_app_launcher(), MINI_APP_ID_CLOCK);
    }
}

void app_clock_on_run(mini_app_inst_t *p_app_inst) {
    app_clock_t *p_app = mui_mem_malloc(sizeof(app_clock_t));
    p_app_inst->p_handle = p_app;

    p_app->p_view_dispatcher = mui_view_dispatcher_create();
    p_app->p_clock_view = mui_view_create();

    p_app->p_clock_view->draw_cb = clock_view_draw_cb;
    p_app->p_clock_view->input_cb = clock_view_input_cb;

    mui_view_dispatcher_add_view(p_app->p_view_dispatcher, 0, p_app->p_clock_view);
    mui_view_dispatcher_attach(p_app->p_view_dispatcher, MUI_LAYER_FULLSCREEN);
    mui_view_dispatcher_switch_to_view(p_app->p_view_dispatcher, 0);
}

void app_clock_on_kill(mini_app_inst_t *p_app_inst) {
    app_clock_t *p_app = p_app_inst->p_handle;
    mui_view_dispatcher_detach(p_app->p_view_dispatcher, MUI_LAYER_FULLSCREEN);
    mui_view_dispatcher_free(p_app->p_view_dispatcher);
    mui_view_free(p_app->p_clock_view);
    mui_mem_free(p_app);
    p_app_inst->p_handle = NULL;
}

mini_app_t app_clock_info = {
    .id = MINI_APP_ID_CLOCK,
    .name = "Reloj",
    .name_i18n_key = 0,
    .icon = 0xe016,
    .deamon = false,
    .sys = false,
    .hibernate_enabled = false,
    .run_cb = app_clock_on_run,
    .kill_cb = app_clock_on_kill,
    .on_event_cb = NULL
};
