// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>

#include "flag.h"

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
usage(FILE *out)
{
	fprintf(out, "usage: generate-names [options]\n");
	fprintf(out, "\n");
	fprintf(out, "options:\n");
	flag_print_options(out);
}

int
main(int argc, char **argv)
{
	const bool *help = flag_bool("h", false, "print this help to stdout and exit");
	const size_t *name_count = flag_size("c", 8, "count of names to generate");
	const size_t *name_max = flag_size("m", 7, "max length of names, exclusive");
	if (!flag_parse(argc, argv)) {
		usage(stderr);
		flag_print_error(stderr);
		exit(EXIT_FAILURE);
	}

	if (*help) {
		usage(stdout);
		exit(EXIT_SUCCESS);
	}

	Config cfg = {
		.name_count = *name_count,
		.name_min = 3,
		.name_max = *name_max,
	};

	print_names(cfg);
}
