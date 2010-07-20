/* Generates a number of random blotto teams

   http://www.amsta.leeds.ac.uk/~pmt6jrp/personal/blotto.html

   James Stanley 2009 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
	int	teams = 1;
	int	battlefields, soldiers;
	int	i, j;
	int	*numsoldiers;

	if(argc != 3 && argc != 4) {
		fprintf(stderr, "Usage: %s battlefields soldiers [teams]\n\n"
		"Specify the number of battlefields and the number of soldiers, "
		"and optionally the number of teams to output information for.\n",
		argv[0]);
		return 1;
	}

	srand(time(NULL));

	battlefields	= atoi(argv[1]);
	soldiers	= atoi(argv[2]);

	if(argc == 4) teams = atoi(argv[3]);

	if(battlefields < 1 || soldiers < 1) {
		fprintf(stderr, "Need at least 1 battlefield and at least 1 soldier.\n");
		return 1;
	}

	numsoldiers = malloc(battlefields * sizeof(int));

	for(i = 0; i < teams; i++) {
		memset(numsoldiers, 0, battlefields * sizeof(int));
		/* add a soldier to a random battlefield until all have been done */
		for(j = 0; j < soldiers; j++) {
			numsoldiers[rand() % battlefields]++;
		}
		printf("team%d", i + 1);
		for(j = 0; j < battlefields; j++) {
			printf(" %d", numsoldiers[j]);
		}
		putchar('\n');
	}

	free(numsoldiers);

	return 0;
}
