#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_signal(int sig);

int main() {
    int pid, status;
    float f1, f2, fdiv, fmul;
    int i1, i2, idiv, imul;

    // fork to child process
    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // child process

        // prompt for two floating point values
        printf("Enter two floating point values:\n");
        scanf("%f %f", &f1, &f2);

        // perform floating point division
        if (f2 == 0) {
            raise(SIGFPE); // division by zero
        } else {
            fdiv = f1 / f2;
            printf("Result of floating point division: %f\n", fdiv);
        }

        // perform floating point multiplication and check for overflow
        fmul = f1 * f2;
        if (isinf(fmul)) {
            raise(SIGFPE); // floating point overflow
        }

        // prompt for two integer values
        printf("Enter two integer values:\n");
        scanf("%d %d", &i1, &i2);

        // perform integer division
        if (i2 == 0) {
            raise(SIGFPE); // division by zero
        } else {
            idiv = i1 / i2;
            printf("Result of integer division: %d\n", idiv);
        }

        // perform integer multiplication and check for overflow
        imul = i1 * i2;
        if (imul > INT_MAX / 1000000000) {
            raise(SIGSEGV); // integer overflow
        }

        exit(0);
    } else {
        // parent process
        signal(SIGFPE, handle_signal);
        signal(SIGSEGV, handle_signal);

        wait(&status);

        if (WIFSIGNALED(status)) {
            printf("Signal %d received from child process\n", WTERMSIG(status));
        }
    }

    return 0;
}

void handle_signal(int sig) {
    switch (sig) {
        case SIGFPE:
            printf("Floating point exception: division by zero or overflow\n");
            break;
        case SIGSEGV:
            printf("Integer overflow\n");
            break;
        default:
            printf("Unknown signal received\n");
            break;
    }
    exit(1);
}

