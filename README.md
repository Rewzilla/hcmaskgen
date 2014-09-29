#hcmaskgen

A command-line wordlist generator using libhcmask


#Author

Andrew Kramer


#Compiling

	gcc -Wall -O3 -o hcmaskgen hcmaskgen.c libhcmask.c


#Usage

	Usage: hcmaskgen [-h] [-c] [-1 <custom_charset_1>, ...] <mask>
	 -h                  Show this help menu
	 -c                  Show total combinations (don't generate)
	 -1..9 <charset>     Use a custom characterset (identified by 1..9)


#Example

	hcmaskgen -1 "?dabcdef" -2 "?l?u" "?2?1?1?d?a"