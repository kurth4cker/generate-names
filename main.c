// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#define _POSIX_C_SOURCE 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

typedef struct {
	size_t name_count;
	size_t name_min, name_max;
} Config;

static void *
xcalloc(size_t count, size_t size)
{
	void *ptr = calloc(count, size);
	if (ptr == NULL) {
		fprintf(stderr, "could not allocate memory: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ptr;
}

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

static void
print_names(Config cfg)
{
	const char VOWS[] = "aeiou";
	const char CONS[] = "bcdfghjklmnpqrstvwxyz";

	srand(time(NULL));

	char *const name = xcalloc(12, sizeof(char));
	for (size_t i = 0; i < cfg.name_count; i++) {
		// TODO: needs review, there is segfaults sometimes
		const size_t name_len = rand() % (cfg.name_max - cfg.name_min) + cfg.name_min;
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

int
main(int argc, char **argv)
{
	Config cfg = {
		.name_count = 8,
		.name_min = 3,
		.name_max = 8,
	};

	int opt;
	while ((opt = getopt(argc, argv, "n:m:M:")) != -1) {
		switch (opt) {
		case 'n':
			sscanf(optarg, "%zu", &cfg.name_count);
			break;
		case 'm':
			sscanf(optarg, "%zu", &cfg.name_max);
			break;
		case 'M':
			sscanf(optarg, "%zu", &cfg.name_min);
			break;
		}
	}

	print_names(cfg);
}
