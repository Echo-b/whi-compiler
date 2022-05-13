#include "parse.c"
#include "scanner.c"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("parm is not enough!\n");
    exit(-1);
  }
  FILE* fp;
  char str[128];

  /* opening file for reading */
  fp = fopen(argv[1], "r");
  //ssam_out = fopen("./inst_out/ssam.out", "a");
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
  show_token();
  parse();
  show_systable();
  fclose(fp);
  //fclose(ssam_out);

  return (0);
}
