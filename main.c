// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

#define NAME_LENGTH_MAX 16

typedef struct {
	size_t name_count;
	size_t name_min, name_max;
} Config;

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

static int
random_range(size_t min, size_t max)
{
	assert(min < max);
	return rand() % (max - min) + min;
}

static const char *
random_name(Config cfg)
{
	const char VOWS[] = "aeiou";
	const char CONS[] = "bcdfghjklmnpqrstvwxyz";

	static char name[NAME_LENGTH_MAX] = { 0 };

	const size_t name_len = random_range(cfg.name_min, cfg.name_max);
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
	return name;
}

static void
print_names(Config cfg)
{
	srand(time(NULL));

	for (size_t count = 0; count < cfg.name_count; count++) {
		const char *name = random_name(cfg);

		printf("%s\n", name);
	}
}

static void
help(void)
{
	fprintf(stderr, "usage: generate-names [options]\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "options:\n");
	fprintf(stderr, "    -n <name-count>        count of names to generate (default: 8)\n");
	fprintf(stderr, "    -m <max-name-length>   max length of generated names, exclusive (default: 8)\n");
	fprintf(stderr, "    -h                     display this help and exit\n");
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
	while ((opt = getopt(argc, argv, "hn:m:")) != -1) {
		switch (opt) {
		case 'n':
			sscanf(optarg, "%zu", &cfg.name_count);
			break;
		case 'm':
			sscanf(optarg, "%zu", &cfg.name_max);
			break;
		case 'h':
			help();
			exit(EXIT_SUCCESS);
		}
	}

	print_names(cfg);
}
