#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int is_valid(char choice[9]) {
  if (strcmp(choice, "rock") == 0)
    return 0;
  else if (strcmp(choice, "paper") == 0)
    return 1;
  else if (strcmp(choice, "scissors") == 0)
    return 2;
  else
    return -1;
}

int main() {
  srand(time(0));
  int rounds, r_num, h_num, hscore, mscore;
  char h_choice[9];
  char m_choice[9];

  printf("Welcome to Rock, Paper, Scissors!\nHow many rounds do you want to play? ");
  scanf("%d", &rounds);
  hscore = mscore = 0;

  for (int i = 0; i < rounds; ++i) {
    printf("\nWhich do you choose? rock, paper, or scissors? ");
    scanf("%s", h_choice);
    r_num = rand() % 3;

    if (r_num == 0)
      printf("AI chose rock\n");
    else if (r_num == 1)
      printf("AI chose paper\n");
    else if (r_num == 2)
      printf("AI chose scissors\n");
    else
      printf("ERROR. AI choice bug.");

    h_num = is_valid(h_choice);
    if (h_num == -1)
      printf("You entered an invalid choice: %s\n", h_choice);
    else if (h_num == r_num) {
      ;
    } else if (h_num == 0 && r_num == 1) {
      printf("Paper covers rock\n");
      mscore++;
    } else if (h_num == 0 && r_num == 2) {
      printf("Rock bashes scissors\n");
      hscore++;
    } else if (h_num == 1 && r_num == 0) {
      printf("Paper covers rock\n");
      hscore++;
    } else if (h_num == 1 && r_num == 2) {
      printf("Scissors cuts paper\n");
      mscore++;
    } else if (h_num == 2 && r_num == 0) {
      printf("Rock bashes scissors\n");
      mscore++;
    } else if (h_num == 2 && r_num == 1) {
      printf("Scissors cuts paper\n");
      hscore++;
    }
    printf("AI score: %d, Player score: %d\n", mscore, hscore);
  }

  if (hscore == mscore)
    printf("It's a tie!\n");
  else if (hscore > mscore)
    printf("Player wins!\n");
  else
    printf("AI wins!\n");

  return 0;
}

