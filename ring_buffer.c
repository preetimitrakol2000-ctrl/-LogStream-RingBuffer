#include <stdlib.h>
#include "ring_buffer.h"

LogRingBuffer* init_log_buffer(int capacity) {
    LogRingBuffer* lrb = (LogRingBuffer*)malloc(sizeof(LogRingBuffer));
    lrb->buffer_pool = (TrafficRecord*)malloc(capacity * sizeof(TrafficRecord));
    lrb->tail_idx = 0;
    lrb->items_tracked = 0;
    lrb->capacity_bound = capacity;
    return lrb;
}

void write_log_record(LogRingBuffer* lrb, int id, double count) {
    lrb->buffer_pool[lrb->tail_idx].request_id = id;
    lrb->buffer_pool[lrb->tail_idx].request_count = count;
    
    // Circular index shift wrap logic
    lrb->tail_idx = (lrb->tail_idx + 1) % lrb->capacity_bound;

    if (lrb->items_tracked < lrb->capacity_bound) {
        lrb->items_tracked++;
    }
}

double evaluate_average_frequency(LogRingBuffer* lrb) {
    if (lrb->items_tracked == 0) return 0.0;
    double total_sum = 0.0;
    for (int i = 0; i < lrb->items_tracked; i++) {
        total_sum += lrb->buffer_pool[i].request_count;
    }
    return total_sum / lrb->items_tracked;
}

void free_log_buffer(LogRingBuffer* lrb) {
    free(lrb->buffer_pool);
    free(lrb);
}
