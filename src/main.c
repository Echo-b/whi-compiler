#include "parse.c"
#include "scanner.c"

int main(int argc, char* argv[]) {              
  if (argc < 3) {
    printf("lexicial [src] [dst]!\n");
    exit(-1);
  }
  FILE* fp;
  FILE* out;
  char str[128];
  /* opening file for reading */
  fp = fopen(argv[1], "r");
  out = fopen(argv[2], "a");
  if (fp == NULL) {
    perror("Error opening file");
    return (-1);
  }
  bool successful = false;
  init_regex();
  while (fgets(str, 128, fp) != NULL) {
    // printf("%s",str);
    init_token(str, &successful);
  }
  tokens[nr_token++].type = TK_EOF;
  // show_token();
  parse(out);
  // show_systable();
  fclose(fp);
  fclose(out);
  return (0);

}
