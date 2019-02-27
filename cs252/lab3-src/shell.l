
/*
 *
 * CS-252 Fall 2017
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <cstring>
#include "y.tab.hh"

static  void yyunput (int c,char *buf_ptr  );

void myunputc(int c) {
  unput(c);
}

%}

%%

\n {
  return NEWLINE;
}

[ \t] {
  /* Discard spaces and tabs */
}

">" {
  return GREAT;
}

[ ]"<"[ ] {
  return LESS;
}

">>" {
  return GREATGREAT;
}

">&" {
  return GREATAMPERSAND;
}

">>&" {
  return GREATGREATAMPERSAND;
}

"|" {
  return PIPE;
}

[ ]"&" {
  return AMPERSAND;
}

"2>" {
  return ERR2;
}

\"([^"]*)\" {
  char * word = strdup(yytext);
  char * word1;
  char * word2;
  word1 = (char*)memmove(&word[0], &word[1], strlen(word));
  int len = strlen(word1);
  word2 = (char*)memmove(&word1[len-1], &word1[len], 1);
  char* tempword = word;
  while(strchr(tempword, '\\') != NULL) {
    tempword = strchr(tempword, '\\');
    tempword = (char*)memmove(&tempword[0], &tempword[1], strlen(tempword));
    tempword++;
  }
  yylval.string_val = strdup((const char*) word); 
  return WORD;
}


[^ \t\n>|][^ \t\n>|]*  {
  /* Assume that file names have only alpha chars */
  char* word = strdup(yytext); 
  if(word[0] != '\\') {
    char* tempword = word;
      while(strchr(tempword, '\\') != NULL) {
      tempword = strchr(tempword, '\\');
      tempword = (char*)memmove(&tempword[0], &tempword[1], strlen(tempword));
      tempword++;
    }
    yylval.string_val = strdup((const char*) word); 
  }
  yylval.string_val = strdup(word);
  return WORD;
}


