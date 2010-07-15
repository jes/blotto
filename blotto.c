/* Runs a round-robin blotto tournament

   http://www.geocities.com/j_r_partington/blotto.html
   http://www.amsta.leeds.ac.uk/~pmt6jrp/personal/blotto.html

   James Stanley 2009 */

#define _XOPEN_SOURCE 600
#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

typedef struct {
  char *name;
  int *soldiers;
  int points;
  int win, draw, lose;
} Player;

int battlefields, soldiers;

/* returns the rounded-down integer log10 of n
   intlog10(0) returns -1 */
int intlog10(int n) {
  int k, log;

  for(k = 1, log = -1; n > k; k *= 10) log++;

  return log;
}

int player_sort(const void *a, const void *b) {
  const Player *one = a, *two = b;

  return two->points - one->points;
}

/* parses the input given in input in to the proper Player structure */
int parse_name(Player *p, char *input) {
  char *ptr;
  char *ptr2;
  int i;
  int total = 0;

  p->name = NULL;

  /* skip whitespace */
  for(ptr = input; isblank(*ptr); ptr++);
  if(*ptr == '\0') return -1;

  /* find end of player name */
  for(ptr2 = ptr; !isblank(*ptr2) && *ptr2 != '\0'; ptr2++);
  if(*ptr2 == '\0') return -1;

  /* copy the name */
  p->name = strndup(ptr, ptr2 - ptr);

  /* now get the soldiers for all the battlefields */
  for(i = 0; i < battlefields; i++) {
    /* skip whitespace */
    for(ptr = ptr2; isblank(*ptr); ptr++);
    if(*ptr == '\0') return -1;

    /* find end of number */
    for(ptr2 = ptr; !isblank(*ptr2) && *ptr2 != '\0'; ptr2++);
    if(*ptr2 == '\0' && i != (battlefields - 1)) return -1;

    /* get the value */
    p->soldiers[i] = strtol(ptr, NULL, 0);

    /* check for cheating */
    total += p->soldiers[i];
    if(total > soldiers)
      fprintf(stderr, "Using more than %d soldiers in '%s'!\n", soldiers,
              input);
  }

  /* check for foolishness */
  if(total < soldiers)
    fprintf(stderr, "Using less than %d soldiers in '%s'!\n", soldiers, input);

  /* skip whitespace */
  for(ptr = ptr2; isblank(*ptr); ptr++);
  if(*ptr != '\0') {
    fprintf(stderr, "Using more than %d battlefields in '%s'!\n", battlefields,
            input);
  }

  return 0;
}

int main(int argc, char **argv) {
  int i, j;
  Player *player = NULL;
  int players = 0;
  char *input = NULL;
  char *p;
  size_t len = 0;
  int p1, p2;
  int score;
  int widthpos, widthname = 0, widthw, widthd, widthl, widthpts, widthsol;
  int maxwin = 0, maxdraw = 0, maxlose = 0, maxsol = 0;

  if(argc != 3) {
    fprintf(stderr, "Usage: %s battlefields soldiers\n\n"
            "Specify the number of battlefields the game is to be played on, "
            "and the number of soldiers each team has. No attempt is made to "
            "prevent two teams using the same name.\n"
            "See http://www.amsta.leeds.ac.uk/~pmt6jrp/personal/blotto.html for more "
            "information.\n"
            "If stdin is a terminal, brief instructions will be "
            "given to the operator.\n", argv[0]);
    return 1;
  }

  battlefields = atoi(argv[1]);
  soldiers = atoi(argv[2]);

  if(battlefields < 1 || soldiers < 1) {
    fprintf(stderr, "Need at least 1 battlefield and at least 1 soldier.\n");
    return 1;
  }

  /* if stdin is a terminal, give the user instructions and an example */
  if(isatty(fileno(stdin))) {
      fprintf(stderr, "Enter the army arrangements, ending with EOF, in the "
              "form 'player_name %d", soldiers);
      for(i = 1; i < battlefields; i++) {
        fputs(" 0", stderr);
      }
      fputs("'\n\n", stderr);
  }

  /* read the team configurations */
  while(1) {
    player = realloc(player, sizeof(Player) * (players + 1));

    /* read a line, stopping on eof */
    if(getline(&input, &len, stdin) == -1) break;

    /* skip blank lines */
    if(*input == '\n') continue;

    /* remove the endline if present */
    p = strchr(input, '\n');
    if(p) *p = '\0';

    /* fill in the player structure */
    memset(&player[players], 0, sizeof(Player));
    player[players].soldiers = malloc(sizeof(int) * battlefields);
    if(parse_name(&player[players], input) == -1) {
      fprintf(stderr, "Parse error in '%s'. Continuing anyway...\n", input);
    }

    /* find longest player name */
    if(strlen(player[players].name) > widthname)
      widthname = strlen(player[players].name);

    /* find most soldiers on any battlefield */
    for(i = 0; i < battlefields; i++) {
      if(player[players].soldiers[i] > maxsol)
        maxsol = player[players].soldiers[i];
    }

    players++;
  }

  /* run the tournament! */
  for(p1 = 0; (p1 + 1) < players; p1++) {
    for(p2 = p1 + 1; p2 < players; p2++) {
      score = 0;

      /* fight! */
      for(i = 0; i < battlefields; i++) {
        if(player[p1].soldiers[i] > player[p2].soldiers[i]) score++;
        else if(player[p1].soldiers[i] < player[p2].soldiers[i]) score--;
      }

      /* administer points */
      if(score > 0) {
        player[p1].points += 2;
        player[p1].win++;
        player[p2].lose++;
      } else if(score < 0) {
        player[p2].points += 2;
        player[p2].win++;
        player[p1].lose++;
      } else {
        player[p1].points++;
        player[p1].draw++;
        player[p2].points++;
        player[p2].draw++;
      }
    }
  }

  /* find highest wins, draws, and losses */
  for(i = 0; i < players; i++) {
    if(player[i].win > maxwin) maxwin = player[i].win;
    if(player[i].draw > maxdraw) maxdraw = player[i].draw;
    if(player[i].lose > maxlose) maxlose = player[i].lose;
  }

  /* sort by points */
  qsort(player, players, sizeof(Player), player_sort);

  /* width of number fields */
  widthpos = intlog10(players) + 1;
  widthw = intlog10(maxwin) + 1;
  widthd = intlog10(maxdraw) + 1;
  widthl = intlog10(maxlose) + 1;
  widthpts = intlog10(player[0].points) + 1;
  widthsol = intlog10(maxsol) + 1;

  /* these must be wide enough for their headings */
  if(widthpos < 3) widthpos = 3;
  if(widthname < 4) widthname = 4;
  if(widthpts < 3) widthpts = 3;

  /* print out table heading */
  printf("%*s  %-*s  %*s  %*s  %*s  %*s  Soldiers\n",
         widthpos, "Pos",
         widthname, "Name",
         widthw, "W",
         widthd, "D",
         widthl, "L",
         widthpts, "Pts");

  /* print out results table */
  for(i = 0; i < players; i++) {
    printf("%*d  %-*s  %*d  %*d  %*d  %*d ",
           widthpos, i+1,
           widthname, player[i].name,
           widthw, player[i].win,
           widthd, player[i].draw,
           widthl, player[i].lose,
           widthpts, player[i].points);

    for(j = 0; j < battlefields; j++) {
      printf(" %*d", widthsol, player[i].soldiers[j]);
    }
    putchar('\n');
    free(player[i].name);
  }
  free(player);

  return 0;
}
