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

static bool
is_vow(int ch)
{
	return strchr(VOWS, ch) != NULL;
}

static int
random_con(void)
{
	return CONS[rand() % strlen(CONS)];
}

static int
random_lower(void)
{
	return rand() % ('z'-'a') + 'a';
}

static int
random_vow(void)
{
	return VOWS[rand() % strlen(VOWS)];
}

int
main(void)
{
	srand(time(NULL));

	for (size_t name_count = 0; name_count < 16; name_count++) {
		const size_t name_len = rand() % 5 + 3;
		char *const name = calloc(WORD_NAME_MAX + 1, sizeof(char));
		name[0] = random_lower();
		for (size_t i = 1; i < name_len; i++) {
			if (is_vow(name[i-1])) {
				name[i] = random_con();
			}
			else {
				name[i] = random_vow();
			}
		}

		printf("%s\n", name);
		free(name);
	}
}
