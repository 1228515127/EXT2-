#include <stdio.h>
#include <string.h>
#include "./main.c"

int getcmd(char* buf, int nbuf){
    printf("$ ");
    memset(buf, 0, nbuf);
    fgets(buf, nbuf, stdin);
    if (buf[0] == 0)
        return -1;
    return 0;
}

int parse_cmd(char* buf){
    char cmd[20],path[121];
    memset(cmd,0,sizeof(cmd));
    memset(path,0,sizeof(path));
    int len = strlen(buf);
    int i=0;
    for(i=0;i<len;i++){
        if(buf[i]==' ' || buf[i]=='\n'){
            strncpy(cmd,buf,i);
            break;
        }
    }
    if(strcmp("ls",cmd)==0){
        strcpy(path,buf+i+1);
        path[strlen(path)-1]=0;
        ls(path);
    }else if(strcmp("mkdir",cmd)==0){
        strcpy(path,buf+i+1);
        path[strlen(path)-1]=0;
        mkdir(path);
    }else if(strcmp("touch",cmd)==0){
        strcpy(path,buf+i+1);
        path[strlen(path)-1]=0;
        touch(path);
    }else if(strcmp("cp",cmd)==0){
        strcpy(path,buf+i+1);
        //printf("剩下的path为：%s",path);
        char src[121],des[121];
        memset(src,0,sizeof(src));
        memset(des,0,sizeof(des));
        len = strlen(path);
        for(i=0;i<len;i++){
            if(path[i]==' ' || path[i]=='\n'){
            strncpy(src,path,i);
            break;
            }
        }
        strcpy(des,path+i+1);
        des[strlen(des)-1]=0;
        cp(src,des);
    }else{
        shutdown();
        return 0;
    }
    return 1;
}

int main(void){
    char buf[200];
    ext2Init();
    while (getcmd(buf, sizeof(buf)) >= 0)
    {
        if (!parse_cmd(buf))
            return 0;
        memset(buf,0,sizeof(buf));
    }
    return -1;
}