// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const size_t WORD_NAME_MAX = 16;

const char VOWS[] = "aeiou";
const char CONS[] = "bcdfghjklmnpqrstvwxyz";

#define IS_VOW(ch) (strchr(VOWS, ch) != NULL)
#define RANDOM_CON() (CONS[rand() % strlen(CONS)])
#define RANDOM_VOW() (VOWS[rand() % strlen(VOWS)])
#define RANDOM_LOWER() (rand() % ('z'-'a') + 'a')

int
main(void)
{
	srand(time(NULL));

	char *const name = calloc(WORD_NAME_MAX + 1, sizeof(char));
	for (size_t name_count = 0; name_count < 16; name_count++) {
		const size_t name_len = rand() % 5 + 3;
		name[name_len] = '\0';
		name[0] = RANDOM_LOWER();
		for (size_t i = 1; i < name_len; i++) {
			if (IS_VOW(name[i-1])) {
				name[i] = RANDOM_CON();
			}
			else {
				name[i] = RANDOM_VOW();
			}
		}

		printf("%s\n", name);
	}
	free(name);
}
