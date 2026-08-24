#define DT_DRV_COMPAT pixart_behavior_pmw3360_config

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zmk/behavior.h>

#include "pmw3360.h"

#if IS_ENABLED(CONFIG_PMW3360)
extern int pmw3360_control_default(enum pmw3360_control_command command);
#else
int pmw3360_control_default(enum pmw3360_control_command command) {
    return -ENODEV;
}
#endif

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_pmw3360_config_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    return pmw3360_control_default(binding->param1);
}

static int on_pmw3360_config_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    return 0;
}

static const struct behavior_driver_api behavior_pmw3360_config_driver_api = {
    .binding_pressed = on_pmw3360_config_pressed,
    .binding_released = on_pmw3360_config_released,
};

BEHAVIOR_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, POST_KERNEL,
                        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                        &behavior_pmw3360_config_driver_api);

#endif
