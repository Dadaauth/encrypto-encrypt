#ifndef METADATA_TOOLS_H
#define METADATA_TOOLS_H

#include <stdio.h>

long unsigned read_enc_file(char *filename, char **file_contents);
bool metadata_end(char *file_contents, unsigned long char_count);
bool check_metadata_begin(char *file_contents, size_t *cursor);
bool check_metadata_end(char *file_contents, size_t fc_length, size_t *cursor);

void extract_md_string(char *file_contents, size_t cursor, char **md_contents);

#endif 