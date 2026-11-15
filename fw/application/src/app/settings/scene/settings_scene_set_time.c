#include "app_settings.h"
#include "settings_scene.h"
#include "clock_service.h"
#include "mui_progress_bar.h"
#include "mui_view_dispatcher.h"
#include "mui_scene_dispatcher.h"

static void settings_scene_time_hour_event_cb(mui_progress_bar_event_t event, mui_progress_bar_t *p_progress_bar) {
    app_settings_t *app = p_progress_bar->user_data;
    uint8_t h = mui_progress_bar_get_current_value(p_progress_bar);
    uint8_t cur_h, cur_m, cur_s;
    clock_service_get_time(&cur_h, &cur_m, &cur_s);
    clock_service_set_time(h, cur_m);
    if (event != MUI_PROGRESS_BAR_EVENT_DECREMENT && event != MUI_PROGRESS_BAR_EVENT_INCREMENT) {
        mui_scene_dispatcher_previous_scene(app->p_scene_dispatcher);
    }
}

void settings_scene_set_time_hour_on_enter(void *user_data) {
    app_settings_t *app = user_data;
    uint8_t cur_h, cur_m, cur_s;
    clock_service_get_time(&cur_h, &cur_m, &cur_s);
    mui_progress_bar_set_header(app->p_progress_bar, "Ajustar Hora (0-23)");
    mui_progress_bar_set_min_value(app->p_progress_bar, 0);
    mui_progress_bar_set_max_value(app->p_progress_bar, 23);
    mui_progress_bar_set_current_value(app->p_progress_bar, cur_h);
    mui_progress_bar_set_event_cb(app->p_progress_bar, settings_scene_time_hour_event_cb);
    mui_view_dispatcher_switch_to_view(app->p_view_dispatcher, SETTINGS_VIEW_ID_PROGRESS_BAR);
}

void settings_scene_set_time_hour_on_exit(void *user_data) {
    app_settings_t *app = user_data;
    mui_progress_bar_reset(app->p_progress_bar);
}

static void settings_scene_time_min_event_cb(mui_progress_bar_event_t event, mui_progress_bar_t *p_progress_bar) {
    app_settings_t *app = p_progress_bar->user_data;
    uint8_t m = mui_progress_bar_get_current_value(p_progress_bar);
    uint8_t cur_h, cur_m, cur_s;
    clock_service_get_time(&cur_h, &cur_m, &cur_s);
    clock_service_set_time(cur_h, m);
    if (event != MUI_PROGRESS_BAR_EVENT_DECREMENT && event != MUI_PROGRESS_BAR_EVENT_INCREMENT) {
        mui_scene_dispatcher_previous_scene(app->p_scene_dispatcher);
    }
}

void settings_scene_set_time_min_on_enter(void *user_data) {
    app_settings_t *app = user_data;
    uint8_t cur_h, cur_m, cur_s;
    clock_service_get_time(&cur_h, &cur_m, &cur_s);
    mui_progress_bar_set_header(app->p_progress_bar, "Ajustar Minutos (0-59)");
    mui_progress_bar_set_min_value(app->p_progress_bar, 0);
    mui_progress_bar_set_max_value(app->p_progress_bar, 59);
    mui_progress_bar_set_current_value(app->p_progress_bar, cur_m);
    mui_progress_bar_set_event_cb(app->p_progress_bar, settings_scene_time_min_event_cb);
    mui_view_dispatcher_switch_to_view(app->p_view_dispatcher, SETTINGS_VIEW_ID_PROGRESS_BAR);
}

void settings_scene_set_time_min_on_exit(void *user_data) {
    app_settings_t *app = user_data;
    mui_progress_bar_reset(app->p_progress_bar);
}
