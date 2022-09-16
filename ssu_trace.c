#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int p_id , w_pid;

  if(argc < 3){
    printf(1,"$ ssu_trace [mask] [command] [file]\n");
    exit();
    
  }

  int mask = atoi(argv[1]);

  p_id = fork(); // child give parent mask for fork 

  if(p_id == 0)
  {
    trace(mask);
    exec(argv[2], argv+2);
    exit();
  }

  if(p_id < 0)
  {
    printf(2,"fork error \n");
    exit();
  }

  while((w_pid=wait()) >= 0 && w_pid != p_id)
      printf(1, "zombie!\n");

exit(); //pid 3 ssu_trace: trap 14 err 5 on cpu 1 eip 0xffffffff addr 0xffffffff--kill proc

return 0;
}
