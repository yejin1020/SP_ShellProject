# SP_ShellProject

간단한 쉘 프로그램을 만들고 다음과 같이 동작하도록 수정하시오.

1. "exit"를 치면 프로그램을 끝내도록 프로그램을 수정하시오.
2. csh, bash 등에서처럼 쉘 명령의 마지막에 ‘&’을 입력하면 백그라운드로 실행되도록 프로그램을 수정하시오.
3. csh, bash 등에서처럼 인터럽트키 (SIGINT: Ctrl-C, SIGQUIT: Ctrl-Z) 가 동작하도록 프로그램을 수정하시오.
4. 파일 재지향 (>, <) 및 파이프(|) 기능이 가능하도록 프로그램을 수정하시오.
5. ls, pwd, cd, mkdir, rmdir, ln, cp, rm, mv, cat 명령을 팀원이 공평하게 나누어 구현하시오. 


[num11 파일 쉘 실핼방법]
 make clean  -  make -  ./minish 

[다른 쉘 실행 방법]
 gcc -o simplesh file_chdir.c handlesignal.c simplesh.c  -  ./simplesh 
