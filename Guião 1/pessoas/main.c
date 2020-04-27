#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#include "pessoas.h"

int main(int argc, char const *argv[]) {
    if(argc < 4) {
        puts("ERROR - Wrong number of arguments.");
        return 1;
    }

    int no_output = 0;

    if(argc == 5) {
        if(strcmp(argv[4],"--no-output") == 0) {
            no_output = 1;
        }
    }

    int fd;
    Person person;

    switch(*(argv[1] + 1)) {
        case 'i':
            if(!no_output) puts("Insert mode");
            fd = open("registo", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            if(fd == -1) {
                puts("ERROR - Couldn't open or create registry file.");
                return 1;
            }

            strcpy(person.name, argv[2]);
            person.age = atoi(argv[3]);

            if(write(fd, &person, sizeof(struct person)) < 1) {
                puts("ERROR - Couldn't write to registry file.");
                close(fd);
                return 1;
            }

            //This little section gets the file size, and then divides it by the struct size, to get the number of people in the registry, aka, the index of the most recent entry.
            struct stat st;
            fstat(fd, &st);
            off_t filesize = st.st_size;
            int pos = (int)filesize / sizeof(struct person);

            if(!no_output) printf("Insertion succccessful - registo %d\n", pos);

            close(fd);
            break;
        case 'u':
            if(!no_output) puts("Update mode");
            int fd = open("registo", O_RDWR);
            if(fd == -1) {
                puts("ERROR - Couldn't open registry file.");
                return 1;
            }

            int registry = -1;
            int i = 1;

            if(isdigit(*argv[2]))
                registry = atoi(argv[2]);

            while(read(fd, &person, sizeof(struct person)) > 0) {
                if((registry == -1 && strcmp(person.name,argv[2]) == 0) || registry == i) {
                    person.age = atoi(argv[3]);
                    lseek(fd, - sizeof(struct person), SEEK_CUR);
                    if(write(fd, &person, sizeof(struct person)) < 1) {
                        puts("ERROR - Couldn't write to registry file.");
                        close(fd);
                        return 1;
                    }
                    if(!no_output) puts("Update successful");
                    goto UPDATE_SUCCESS;
                }
                i++;
            }
            puts("ERROR - Registry entry not found");
            UPDATE_SUCCESS:
            close(fd);
            break;
        default:
            puts("ERROR - Invalid mode.");
            break;
    }
    
    if(!no_output) {
        fd = open("registo", O_RDONLY);
        while(read(fd, &person, sizeof(struct person)) > 0) {
            printf("%s - %d\n", person.name, person.age);
        }
        close(fd);
    }
    return 0;
}
