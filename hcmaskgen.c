#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "libhcmask.h"

#define usage(str) fprintf(stderr, \
	"Usage: %s [-h] [-c] [-1 <custom_charset_1>, ...] <mask>\n" \
	" -h                  Show this help menu\n" \
	" -c                  Show total combinations (don't generate)\n" \
	" -1..9 <charset>     Use a custom characterset (identified by 1..9)\n" \
	, str)

int main(int argc, char **argv) {

	int c;
	char option;
	char *custom_charsets[9];
	mask_t *maskctx;

	c = 0;
	option = 0;
	memset(custom_charsets, '\0', sizeof(char *) * 9);

	while((option = getopt(argc, argv, "1:2:3:4:5:6:7:8:9:hc")) != -1) {
		if(option >= '1' && option <= '9') {
			if(optarg == NULL)
				return 1;
			custom_charsets[ctoi(option)-1] = optarg;
		} else if(option == 'h') {
			usage(argv[0]);
			return 0;
		} else if(option == 'c') {
			c = 1;
		} else if(option == '?') {
			fprintf(stderr, "ERROR: Unkown option '%c'\n", optopt);
			usage(argv[0]);
			return 1;
		}
	}

	if(optind >= argc) {
		fprintf(stderr, "ERROR: No mask specified\n");
		usage(argv[0]);
		return 1;
	}

	maskctx = init_mask(
		argv[optind],
		custom_charsets[0],
		custom_charsets[1],
		custom_charsets[2],
		custom_charsets[3],
		custom_charsets[4],
		custom_charsets[5],
		custom_charsets[6],
		custom_charsets[7],
		custom_charsets[8]
	);

	if(!maskctx) {
		fprintf(stderr, "ERROR: Failed to initialize mask\n");
		return 1;
	}

	if(c == 1) {
		printf("%lu\n", maskctx->keyspace_len);
		return 0;
	}

	do {
		puts(maskctx->current_string);
	} while(next_mask(maskctx));

	free_mask(maskctx);

	return 0;

}
