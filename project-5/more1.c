#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define PAGELEN 23
#define LINELEN 512 

void do_more(FILE *, int);
int see_more(FILE *);

int main(int argc, char *argv[])
{

  void tcontrol(int);
  signal( SIGINT, tcontrol);
  tty_mode(0);
  set_cr_noecho_mode();

  FILE *fp;
  
  if (argc == 1)
  {
    printf("\033[7m bytes \033[m");
    do_more(stdin, 0);
  }
  else
  {
    int fsze = detersize(argv[1]);
    while (--argc)
      if((fp = fopen( *++argv, "r")) != NULL)
      {
        do_more(fp, fsze);
        fclose(fp);
      }
      else
        exit(1);
  }
  tty_mode(1);
  return 0;
}

void do_more(FILE *fp, int nline)
{
  char line[LINELEN];
  int num_of_lines = 0;
  int see_more(FILE *), reply;
  FILE *fp_tty;

  fp_tty = fopen("/dev/tty", "r");
  if (fp_tty == NULL)
    exit(1);
  
  while(fgets(line, LINELEN, fp))
  {
    int totalLines = 0;
    if (num_of_lines ==  PAGELEN)
    {
      totalLines += PAGELEN;
      int perc = (totalLines*100)/nline;
      printf("here2: %i, %i, %i\n", totalLines, nline, perc);
      printf("\033[7m %i%%\n \033[m", perc);
      reply = see_more(fp_tty);
      if(reply == 0)
        break;
      num_of_lines -= reply;
    }
    if(fputs(line, stdout) == EOF)
      exit(1);
    num_of_lines++;
  }
}

int see_more(FILE *cmd)
{
  int c;
  while((c=getc(cmd)) != EOF)
  {
    if (c == 'q')
      return 0;
    if (c == ' ')
      return PAGELEN;
    if (c == '\n')
      return 1;
  }
  return 0;
}
 
set_cr_noecho_mode()
{
  struct termios ttystate;

  tcgetattr(0,&ttystate);
  ttystate.c_lflag &= ~ICANON;
  ttystate.c_lflag &= ~ECHO;
  ttystate.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &ttystate);
}

tty_mode(int how)
{
  static struct termios original_mode;
  if (how == 0)
    tcgetattr(0, &original_mode);
  else
    return tcsetattr(0, TCSANOW, &original_mode);
}

void tcontrol(int signum)
{
  tty_mode(1);
  exit(1);
}

int detersize(char *fpt)
{
  char c;  
  int nuL = 0;
  FILE *fp;
  fp = fopen(fpt, "r");
  if(fp == NULL)
    return 0;
  else
    while((c=fgetc(fp)) != EOF)
    {
      if (c=='\n')
        nuL++;
    }
  return nuL;
}
