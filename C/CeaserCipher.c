#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*

This program shifts the given text within the ascii alphabet and outputs shifted text.
Should take 4 command line arguments: 1- a source file, 2- a destination file, 3- shift-amount, 4- direction
Direction specifies encryption or decryption
0 to decrypt
1 to encrypt

usage: a.out src-filename dest-filename integral-shiftAmount De/Encrypt

Next project, have program get the shell to do these things:

  1 Give a text doc to edit in vim
  2 Run CeaserCipher on the document with specified inputs (first line of vim document)
  3 Show a text document containing the encrypted text.

  // Do it yourself and then show Dr. Tan.

*/

FILE *in, *out;
int current_char, shift;


int main(int argc, char** argv) {
  if(argc != 5) {
    fprintf(stderr, "Wrong number of arguments\n");
    exit(1);
  }
  if((in = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Problem opening: %s\n", argv[1]);
    exit(1);
  }
  if((out = fopen(argv[2], "w")) == NULL) {
    fprintf(stderr, "Problem opening: %s\n", argv[2]);
    exit(1);
  }
  shift = (atoi(argv[3]) % 26);
  if(atoi(argv[4])) {  // if decrypt
    shift *= (-1);
  }

  while(1) {
    if((current_char = fgetc(in)) == EOF) {
      fprintf(stdout, "Success! Done Encoding.\n");
      return 0;
    }

    // If you wish to modify the text before it goes to the outfile,
    // here is where to do it.
    
    current_char = (current_char + shift);
    if(fputc(current_char, out) == EOF) {
      fprintf(stderr, "There was an error writing\n");
      exit(1);
    }
  }
  return 0;
}



