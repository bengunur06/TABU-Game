#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define true 1
#define false 0
pthread_t scanf_thread_tid, wait_time_tid;

int wait = true, b = 0;

void *myScanf(void *vargp) {
  scanf("%d", &b);
  wait = false;
  return NULL;
}
void *waitTime(void *vargp) {
  unsigned int ttime = 0,
               delay = 10000, // 10ms
      total_delay = 20;        // sn

  while (wait) {
    if (ttime >= delay * 100 * total_delay) {
      wait = false;
      printf("User entered nothing!!\nUser will get negative points\n");
      b=-1;
      sleep(1);
      pthread_cancel(scanf_thread_tid);
    }
    ttime += delay;
    usleep(delay); // 10 ms
  }
  wait = true;
  return NULL;
}
void word(int a) {

  switch (a) {
  case 0:
    printf("**Cat**\n\nforbidden words :\nMiyaw\npurr\ndog\ngrumpy\nmrr\n");
    break;

  case 1:
    printf(
        "**Bird**\n\nforbidden words :\nBirb\nseed\nu want sum\ntweet\nfly\n");
    break;

  case 2:
    printf("**Korra**\n\nforbidden words :\nAvatar\nWater "
           "Tribe\nBolin\nAsami\nAang\n");
    break;

  case 3:
    printf("**Illuminati**\n\nforbidden words :\nTriangle\nConspracy "
           "Theories\nPyramids\nWorld Domination\nMoney\n");
    break;

  case 4:
    printf("**Kermit**\n\nforbidden words :\nFrog\nFrug\nPuppet\nGreen\nDa "
           "vinci\n");
    break;

  case 5:
    printf("**Diggat et bebeim**\n\nforbidden words :\nLink\nAz kalsın "
           "merdivenden düşüyordum ha\n");
    break;

  case 6:
    printf("**Bed sheets**\n\nforbidden words :\n1 aydır değiştirilmeyen "
           "şey\nFatma ablanın deiştirmediği şey\nGri oldular\nPis\n");
    break;

  case 7:
    printf("**Eşrefpaşa Tatlısı**\n\nforbidden words :\nTatlı\n");
    break;

  case 8:
    printf("**Nohutgiller**\n\nforbidden words :\nDefne'nin sevmediği "
           "yemek\nBurger king\n");
    break;

  case 9:
    printf("------------sus------------");
    break;

  case 10:
    printf("**Yoo sıcak**\n\nforbidden words :\nPencere\nSoğuk\nYoo\n");
    break;
  }
}
int main() {
  int a;
  static int  hold;
  int i = 1; // counter
  char d;
  int c;

  printf("*********RULES*********\n\nDo not use forbidden words\nif player "
         "gives true answer press 1 \nif player gives false answer press 0 \n");

  printf("%s", "To start please press enter");
  puts("");
  while (i > 0) {
    scanf("%c", &d);
    if (d == '\n') {
      break;
    }
    ++i;
  }

  for (c = 1; c > 0; ++c) {
    for (a = 0; a < 11; ++a) {
      puts("");
      puts("");
      puts("");
      word(a);
      pthread_create(&scanf_thread_tid, NULL, myScanf, NULL);
      pthread_create(&wait_time_tid, NULL, waitTime, NULL);
      pthread_join(scanf_thread_tid, NULL);
      pthread_join(wait_time_tid, NULL);
      // pthread_exit(NULL);
      // scanf("%d", &b);

      if (b == 0 || b == 1 || b == -1) {
        hold += b;
      } else
        printf("\n-----Invalid score question passed-----\n");
    }

    puts("");

    printf("The score is %d\n", hold);
    puts("*********************");
    printf("Enter 1 if you want to play again ,enter 0 for exit \n");
    scanf("%d", &c);

    if (c == 1)
      continue;

    else
      break;
  }
}
