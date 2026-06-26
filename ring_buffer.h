#ifndef RING_BUFFER_H
#define RING_BUFFER_H

typedef struct {
    int request_id;
    double request_count;
} TrafficRecord;

typedef struct {
    TrafficRecord* buffer_pool;
    int tail_idx;
    int items_tracked;
    int capacity_bound;
} LogRingBuffer;

LogRingBuffer* init_log_buffer(int capacity);
void write_log_record(LogRingBuffer* lrb, int id, double count);
double evaluate_average_frequency(LogRingBuffer* lrb);
void free_log_buffer(LogRingBuffer* lrb);

#endif
