/*skippart.c -- 使用continue跳过部分循环*/
#include <stdio.h>
int main(void)
{
  const float MIN = 0.0F;
  const float MAX = 100.0f;

  int score;
  int total = 0.0f;
  int n = 0;
  float min = MAX;
  float max = MIN;

  printf("Enter the first score(q to quit):\n");
  while (scanf("%d", &score) == 1)
  {
      if (score < MIN || score > MAX)
      {
        printf("%.1f is an invaild value. Try again.\n", score);
        continue;
      }
      printf("Accepting %0.1f:\n", score);
      min = (score < min) ? score : min;
      max = (score > max) ? score : max;
      total += score;
      n++;
      printf("Enter another score.\n");
  }
  if (n > 0)
  {
    printf("Average of %d scores is %0.1f.\n", n, total / n);
    printf("Low = %0.1f, High = %0.1f", min, max);
  }
  else {
    printf("No valid scores were entered.\n");
  }

  return 0;
}