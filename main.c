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

static int
random_char(const char *chars)
{
	return chars[rand() % strlen(chars)];
}

static int
random_lower(void)
{
	return rand() % ('z'-'a') + 'a';
}

int
main(void)
{
	srand(time(NULL));

	char *const name = calloc(WORD_NAME_MAX + 1, sizeof(char));
	for (size_t name_count = 0; name_count < 16; name_count++) {
		const size_t name_len = rand() % 5 + 3;
		name[name_len] = '\0';
		name[0] = random_lower();
		for (size_t i = 1; i < name_len; i++) {
			if (strchr(VOWS, name[i-1])) {
				name[i] = random_char(CONS);
			}
			else {
				name[i] = random_char(VOWS);
			}
		}

		printf("%s\n", name);
	}
	free(name);
}
