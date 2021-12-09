#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define READ 0
#define WRITE 1
#define LEN 1024

int main(){
    int pToC[2];

    pipe( pToC );
    // printf("pToC[0]: %d pToC[1]: %d\n", pToC[0], pToC[1]);

    int cToP[2];

    pipe( cToP );
    // printf("cToP[0]: %d fsd1[1]: %d\n", cToP[0], cToP[1]);

    int f;
    f = fork();

    if (f){
        // parent

        close(pToC[READ]);
        close(cToP[WRITE]);

        while(1){
            char line[LEN];
            fgets(line, LEN, stdin);


            // printf("A\n");
            write(pToC[WRITE], line, LEN);

            // printf("%s\n", line);

            // printf("B\n");

            // sleep(0.001);

            char line2[LEN];
            read(cToP[READ], line2, LEN);
            printf("The child says: \n%s\n", line2);
        }
    }
    else{
        // child
        close(pToC[WRITE]);
        close(cToP[READ]);

        while (1){
            char line[LEN];

            read(pToC[READ], line, LEN);

            // printf("%s\n", line);

            char* tmp = line;
            int i = 0;
            while (i < strlen(line)){
                *tmp = toupper(*tmp);
                tmp++;
                i++;
            }

            // printf("%s\n", line);

            write(cToP[WRITE], line, LEN);
        }
    }

    return 0;
}