#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[])
{
  int p_id , w_pid;

  if(argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9')){
    printf(1,"$ ssu_trace [mask] [command] [file]\n");
    exit();
    
  } /*for command error handle*/

  int mask = atoi(argv[1]);

 while(1){ 
  p_id = fork(); // child give parent mask for fork 

  if(p_id == 0) // process for trace and exec S
  {
    trace(mask);
    exec(argv[2], argv+2); // command + 2 == file 
    exit();
  }

  // if(trace(atoi(argv[1])) < 0) {
	// 	printf(1,trace failed\n");
	// 	exit();
	// }

  if(p_id < 0)
  {
    printf(2,"fork error\n");
    exit();
  }

  while((w_pid=wait()) >= 0 && w_pid != p_id)
      printf(1, "zombie!\n");

exit(); //pid 3 ssu_trace: trap 14 err 5 on cpu 1 eip 0xffffffff addr 0xffffffff--kill proc

return 0;
 }
}
