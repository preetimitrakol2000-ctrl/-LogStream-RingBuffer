#include "ring_buffer.h"
int assess_ddos_risk(double average_rate, double safety_limit) {
    return (average_rate > safety_limit);
}
