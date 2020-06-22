#include "job.h"
#include "qsort.h"
#include <stdio.h>
#include <stdlib.h> // For exit() function


void print_jobs(Job* jobs, int nelem);
Job* populate_jobs_from_file(Job* jobs, int* njobs, char* file);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Error! Usage: ./greedy <in txt file>\n");
    return -1;
  }

  int* njobs = malloc(sizeof(int));
  Job* jobs;

  jobs = populate_jobs_from_file(jobs, njobs, argv[1]);
  q_sort(jobs, *njobs, sizeof(Job), &job_compar_diff);
  int_fast64_t res = compute_weighted_completion_time(jobs, *njobs);
  printf("The total weighted completion time using difference as greedy algo is: %lld\n", res);

  q_sort(jobs, *njobs, sizeof(Job), &job_compar_ratio);
  res = compute_weighted_completion_time(jobs, *njobs);
  printf("The total weighted completion time using ratio as greedy algo is: %lld\n", res);

  return 0;
}

Job* populate_jobs_from_file(Job* jobs, int* njobs, char* file)
{
  FILE *fptr;
  if ((fptr = fopen(file, "r")) == NULL) {
      printf("Couldn't open file.");
      exit(1);
  }

  fscanf(fptr, "%d\n", njobs);
  jobs = malloc(sizeof(Job) * *njobs);

  int weight;
  int length;
  int i = 0;
  while(fscanf(fptr, "%d<space>", &weight) == 1 &&
          fscanf(fptr, "%d\n", &length) == 1)
  {
    Job job = {.weight = weight, .length = length};
    jobs[i] = job;
    i++;
  }

  fclose(fptr);
  return jobs;
}

void print_jobs(Job* jobs, int nelem)
{
  for (int i = 0; i < nelem; i++)
  {
    int diff = jobs[i].weight - jobs[i].length;
    printf("w: %d, l: %d, diff: %d\n", jobs[i].weight, jobs[i].length, diff);
  }
  printf("\n");
}
