#include <stdlib.h>
#include <unistd.h>

#define NOB_IMPLEMENTATION
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

typedef struct {
	bool run;
} Config;

static void
build(void)
{
	Nob_Cmd *cmd = &(Nob_Cmd){ 0 };
	nob_cmd_append(cmd, "cc");
	nob_cmd_append(cmd, "-std=c11");
	nob_cmd_append(cmd, "-g");
	nob_cmd_append(cmd, "-Wall", "-Wextra");
	nob_cmd_append(cmd, "-Werror");
	nob_cmd_append(cmd, "-o", "generate-names");
	nob_cmd_append(cmd, "main.c");

	if (!nob_cmd_run_sync(*cmd)) {
		exit(EXIT_FAILURE);
	}
}

static void
run(void)
{
	Nob_Cmd *cmd = &(Nob_Cmd){ 0 };
	nob_cmd_append(cmd, "./generate-names");

	if (!nob_cmd_run_sync(*cmd)) {
		exit(EXIT_FAILURE);
	}
}

int
main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "nob.h");

	Config cfg = {
		.run = false,
	};
	int opt;
	while ((opt = getopt(argc, argv, "r")) != -1) {
		switch (opt) {
		case 'r':
			cfg.run = true;
		}
	}

	build();
	if (cfg.run) {
		run();
	}
}
