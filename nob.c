#include <stdlib.h>
#include <unistd.h>

#define NOB_IMPLEMENTATION
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "vendor/nob.h"

typedef struct {
	bool run;
} Config;

static void
cc(Nob_Cmd *cmd)
{
	static const char *cc = NULL;
	if (cc == NULL) {
		cc = getenv("CC");
	}
	if (cc == NULL) {
		cc = "cc";
	}
	nob_cmd_append(cmd, cc);
}

static void
build(Nob_Cmd *cmd)
{
	cmd->count = 0;
	cc(cmd);
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
run(Nob_Cmd *cmd)
{
	cmd->count = 0;
	nob_cmd_append(cmd, "./generate-names");

	if (!nob_cmd_run_sync(*cmd)) {
		exit(EXIT_FAILURE);
	}
}

int
main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "vendor/nob.h");

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

	Nob_Cmd cmd = { 0 };
	build(&cmd);
	if (cfg.run) {
		run(&cmd);
	}

	nob_cmd_free(cmd);
}
