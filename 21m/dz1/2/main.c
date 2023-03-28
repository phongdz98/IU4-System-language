#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "signal.h"

void signal_handler(int code) {
	switch (code) {
		case 1:
  		printf ("\nSignal SIGHUP processed\n");
		break;
		case 2:
  		printf ("\nSignal SIGINT processed\n");
		break;
		case 3:
  		printf ("\nSignal SIGQUIT processed\n");
		break;
		case 6:
  		printf ("\nSignal SIGABRT processed\n");
		break;
		// case 9:
  		// printf ("\nSignal SIGKILL processed\n"); //Cannot be processed
		// break;
		case 15:
  		printf ("\nSignal SIGTERM processed\n");
		break;
		// case 19:
  		// printf ("\nSignal SIGSTOP processed\n");//Cannot be processed
		// break;
		case 20:
  		printf ("\nSignal SIGTSTP processed\n");
		break;
	}
     exit(EXIT_SUCCESS);
}

int main() {
    const char *signals[] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGABRT","SIGTERM", "SIGTSTP"};
    int signal_nums[] = {SIGHUP, SIGINT, SIGQUIT, SIGABRT, SIGTERM, SIGTSTP};

    printf("Use \"kill 'signal' 'pid'\" to send me a signal\n");
    printf("Available signals:\n");

    for (int i = 0; i < sizeof(signals)/sizeof(signals[0]); i++) {
        printf("%d - %s\n", signal_nums[i], signals[i]);
    }

    struct sigaction signal;
    signal.sa_handler = signal_handler;
    for (int i = 0; i < sizeof(signal_nums)/sizeof(signal_nums[0]); i++) {
        sigaction(signal_nums[i], &signal, 0);
    }

    printf("My pid is %i\n", getpid());
    printf("Waiting for signal...\n");
    while(1);
    return 0;
}