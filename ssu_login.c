#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define LEN 16

char userID[16][32];
char pwdID[16][32];

int login_count = 0;
int stp_flag = 0;

void parsing_word(int fd, char *dest){
    for (int i=0; i<LEN; i++)
    {
        if (read(fd, &dest[i], 1) <= 0){
            stp_flag = 1;
            break;
        }
        if (dest[i] == ' ' || dest[i] == '\n') {
            dest[i] = '\0';
            break;
        }
    }
}

void get_user_list()
{
  int fd;

  fd = open("list.txt", O_RDONLY);

  for (int i = 0; i < LEN; i++)
  {
    if(stp_flag) break;
    login_count++;
    parsing_word(fd, userID[i]);
    parsing_word(fd, pwdID[i]);
  }
}
    int check_idpw(){

        char id[LEN] = {0,};
        char pw[LEN] = {0,};

        printf(1, "Username: ");
        parsing_word(0, id);
        printf(1, "Password: ");
        parsing_word(0, pw);

        for (int i=0; i< login_count; i++){
            if(!strcmp(id, userID[i]) && !strcmp(pw, pwdID[i]))
            {
                return 1;
            }
            else return 0;
        }
        return 0;
    }
int 
main(int argc, char *argv[])
{
  //int p_id, w_pid;
  get_user_list();

  for (;;)
  {
    if (check_idpw())
      for (;;)
      {
        exec("sh", argv);
      }
  }
  return 0;
}