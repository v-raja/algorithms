#ifndef _JOB_H_
#define _JOB_H_

#include <stdint.h>

typedef struct {
  int weight;
  int length;
} Job;

int job_compar_diff(const void* a, const void* b);
int job_compar_ratio(const void* a, const void* b);
int_fast64_t compute_weighted_completion_time(Job* jobs, int njobs);


#endif
