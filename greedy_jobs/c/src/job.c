#include "job.h"

int job_compar_diff(const void* a, const void* b)
{
  Job * pa = a, * pb = b;
  int diff_a = pa->weight - pa->length;
  int diff_b = pb->weight - pb->length;
  // prioritise the job with the more positive difference
  if (diff_a < diff_b)
  {
    return 1;
  }
  else if (diff_a > diff_b)
  {
    return -1;
  }
  else
  {
    // if same diff, prioritise job with greater weight
    if (pa->weight > pb->weight)
    {
      return -1;
    }
    else if (pb->weight > pa->weight)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

int_fast64_t compute_weighted_completion_time(Job* jobs, int njobs)
{
  int_fast64_t total_time = 0;
  int_fast64_t weighted_time = 0;
  for (int i = 0; i < njobs; i++)
  {
    total_time += jobs[i].length;
    weighted_time += jobs[i].weight * total_time;
  }
  return weighted_time;
}

int job_compar_ratio(const void* a, const void* b)
{
  Job * pa = a, * pb = b;
  double ratio_a = (double)pa->weight/(double)pa->length;
  double ratio_b = (double)pb->weight/(double)pb->length;
  if (ratio_a < ratio_b)
  {
    return 1;
  }
  else if (ratio_a > ratio_b)
  {
    return -1;
  }
  else
  {
    return 0;
  }

}
