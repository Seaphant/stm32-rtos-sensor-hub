/**
 * @file cli.c
 */
#include "cli.h"

#include <ctype.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "app.h"
#include "app_config.h"
#include "fault_mgr.h"
#include "log.h"

#include "stm32g4xx_hal.h"

extern UART_HandleTypeDef hlpuart1;

static char s_line[CLI_LINE_MAX];
static size_t s_len;

static void line_reset(void)
{
    s_len = 0U;
    s_line[0] = '\0';
}

static void print_help(void)
{
    LOG_LINE("OK commands: help | status | start | stop | fault | rate <imu_hz> <slow_hz>");
}

static void print_status(void)
{
    app_status_t st;
    app_get_status(&st);
    const char *mode_str = "IDLE";
    if (st.mode == APP_STATE_RUN) {
        mode_str = "RUN";
    } else if (st.mode == APP_STATE_CAL) {
        mode_str = "CAL";
    }

    LOG_LINE("OK uptime_ms=%lu mode=%s imu_hz=%u slow_hz=%u last_sample_ms=%lu fault_warn_events=%lu cal=%u",
             (unsigned long)st.uptime_ms, mode_str, (unsigned)st.imu_hz, (unsigned)st.slow_hz,
             (unsigned long)st.last_sample_ms, (unsigned long)fault_active_count(),
             st.cal_valid ? 1U : 0U);
}

static void handle_line(const char *line)
{
    if (!line) {
        return;
    }

    while (*line == ' ' || *line == '\t') {
        line++;
    }

    char buf[CLI_LINE_MAX];
    (void)strncpy(buf, line, sizeof(buf) - 1U);
    buf[sizeof(buf) - 1U] = '\0';

    for (char *p = buf; *p != '\0'; p++) {
        *p = (char)tolower((unsigned char)*p);
    }

    if (buf[0] == '\0') {
        return;
    }

    if (strcmp(buf, "help") == 0) {
        print_help();
        return;
    }
    if (strcmp(buf, "status") == 0) {
        print_status();
        return;
    }
    if (strcmp(buf, "start") == 0) {
        app_set_mode(APP_STATE_RUN);
        LOG_LINE("OK mode=RUN");
        return;
    }
    if (strcmp(buf, "stop") == 0) {
        app_set_mode(APP_STATE_IDLE);
        LOG_LINE("OK mode=IDLE");
        return;
    }
    if (strcmp(buf, "fault") == 0) {
        fault_record_t records[8];
        uint32_t n = fault_snapshot(records, 8U);
        if (n == 0U) {
            LOG_LINE("OK faults=0");
            return;
        }
        LOG_LINE("OK faults=%lu", (unsigned long)n);
        for (uint32_t i = 0U; i < n; i++) {
            LOG_LINE("  FLT t_ms=%lu code=%d sev=%d detail=%s",
                     (unsigned long)records[i].t_ms,
                     (int)records[i].code,
                     (int)records[i].severity,
                     records[i].detail);
        }
        return;
    }
    if (strncmp(buf, "rate ", 5) == 0) {
        unsigned int imu = 0U, slow = 0U;
        const char *args = buf + 5;
        while (*args == ' ') args++;
        while (*args >= '0' && *args <= '9') { imu = imu * 10U + (unsigned)(*args - '0'); args++; }
        while (*args == ' ') args++;
        while (*args >= '0' && *args <= '9') { slow = slow * 10U + (unsigned)(*args - '0'); args++; }
        if (imu == 0U || slow == 0U || imu > 1000U || slow > 1000U) {
            LOG_LINE("ERR rate: usage 'rate <imu_hz 1-1000> <slow_hz 1-1000>'");
            return;
        }
        app_set_rates((uint16_t)imu, (uint16_t)slow);
        LOG_LINE("OK imu_hz=%u slow_hz=%u", imu, slow);
        return;
    }

    LOG_LINE("ERR unknown_cmd");
}

void cli_init(void)
{
    line_reset();
}

void cli_task_entry(void *argument)
{
    (void)argument;
    cli_init();

    uint8_t ch;
    for (;;) {
        HAL_StatusTypeDef st = HAL_UART_Receive(&hlpuart1, &ch, 1U, 25U);
        if (st != HAL_OK) {
            vTaskDelay(pdMS_TO_TICKS(10));
            continue;
        }

        if (ch == '\r' || ch == '\n') {
            if (s_len > 0U) {
                s_line[s_len] = '\0';
                handle_line(s_line);
                line_reset();
            }
            continue;
        }

        if (s_len < (sizeof(s_line) - 1U)) {
            s_line[s_len++] = (char)ch;
        } else {
            fault_raise(FAULT_UART_OVERRUN, FAULT_SEV_WARN, "cli_line");
            line_reset();
        }
    }
}
