#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

extern char **environ;
struct cpLink{
    const char *cp;
    struct cpLink *next;
};

static void printEnvs();
static void updateEnv(const char *envStr);
static void execCmd(int n, char **argv);

int main(int argc, char **argv){
    int i = 0, clearEnvs = 0, ncmd = 0, nenv = 0;
    struct cpLink *cmdLink = NULL, *envLink = NULL, *item = NULL, *plink = NULL;

#ifdef DEBUG
    printf("argc: %d\n", argc);
    printf("argv: ");
    for(i=0; i<argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
#endif

    // no arguments
    // print out the environs
    if(argc == 1){
        printEnvs();
        return 0;
    } 

    // process the arguments
    for(i=1; i<argc; i++){
        if(strcmp(argv[1], "-i") == 0){
            clearEnvs = 1; 
            continue;
        }

        if(strchr(argv[i], '=') != NULL)
        {
            plink = envLink;
            nenv++;
        }
        else
        {
            plink = cmdLink; 
            ncmd++;
        }
        item = (struct cpLink*)malloc(sizeof(struct cpLink)); 
        item->cp = argv[i];
        item->next = NULL;
        if(plink == NULL){
            plink = item;
        }
        else
        {
            plink->next = item;
        }
    }
#ifdef DEBUG
    printf("amount of user defined environs: %d\n", nenv);
    printf("amount of command string: %d\n", ncmd);
#endif
    
    if(clearEnvs){
        
    }
    else{
    
    }
    /*
#ifdef DEBUG
printEnvs();
#endif
*/

    return 0;
}

void printEnvs(){
    int i;

    for(i=0; environ[i] != NULL; i++){
        printf("%s\n", environ[i]);
    }
}

void updateEnv(const char *envStr){
    int n;
    char *pos, *p, *key, *value;

    if(envStr == NULL){
        fprintf(stderr, "char pointer is NULL\n");
        return;
    }


    p = (char *)malloc(strlen(envStr)+1);
    if(p == NULL){
        perror("failed in allocating memory in updateEnv()");
        return;
    }
    strcpy(p, envStr);
    pos = strchr(p, '=');
    if(pos == NULL){
        fprintf(stderr, "invalid environ string: %s\n", p);
        return;
    }
    *pos = '\0';
    key = p;
    value = pos+1;
#ifdef DEBUG
    printf("set environ: %s, %s\n", key, value);
#endif
    setenv(key, value, 1);
}

void execCmd(int n, char **argv){
    int i, len, inc;
    char *cmd, *p;

    // count the total string length
    // including cmomand and arguments
    len = 0;
    for(i=0; i<n; i++){
        len = len + strlen(argv[i]) + 1; 
    }
    p = cmd = (char *)malloc(len);
    if(cmd == NULL){
        perror("fail in allocate memory for command");
        return;
    }

    // append the command and arguments
    p[0] = '\0';
    for(i=0; i<n; i++){
        inc = strlen(argv[i]);
        strncat(p, argv[i], inc); 
        p += inc + 1;
        *(p-1) = ' ';
        *p = '\0';
    }
#ifdef DEBUG
    printf("command string: %s\n", cmd);
#endif
    system(cmd);
}
