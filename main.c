#include <stdio.h>
#include "ring_buffer.h"

extern int assess_ddos_risk(double average_rate, double safety_limit);

int main() {
    printf("📡 Activating LogStream-RingBuffer Dynamic Monitoring Ring...\n\n");

    int rolling_window_limit = 3;
    LogRingBuffer* live_traffic_log = init_log_buffer(rolling_window_limit);

    // Logging connection metrics [Log Event ID, Access Ingestion Rate (Req/Sec)]
    write_log_record(live_traffic_log, 1001, 45.0);
    write_log_record(live_traffic_log, 1002, 50.0);
    write_log_record(live_traffic_log, 1003, 55.0);

    double window_average = evaluate_average_frequency(live_traffic_log);
    printf("📊 Baseline Rolling Traffic Frequency Average: %.2f req/s\n", window_average);

    // Ingesting a massive volume burst overwrites the oldest normal trace
    printf("\n📥 Logging Incoming Trace Frame: 450.0 req/s (Triggers Slide Overwrite)\n");
    write_log_record(live_traffic_log, 1004, 450.0);

    window_average = evaluate_average_frequency(live_traffic_log);
    printf("🔮 Recalculated Window Traffic Frequency Average: %.2f req/s\n", window_average);

    if (assess_ddos_risk(window_average, 100.0)) {
        printf("🚨 FIREWALL ALARM VERDICT: High Probability Volumetric DDoS Cascade Active!\n");
    } else {
        printf("✅ Security status nominal.\n");
    }

    free_log_buffer(live_traffic_log);
    return 0;
}
