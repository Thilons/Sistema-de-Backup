#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <linux/if.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include"commonFunc.h"
#include"cliFunc.h"
#include"serFunc.h"




int main(){

    int s = create_socket("lo");//eno1
    char current_path[MAXPATH]=CLIPATH;
    DIR *dirstream = openDir(current_path);
    if(!dirstream){
        perror("Erro na abertura do diretorio");
        exit(1);

    }
     
    mensagem_t m;   
    char entry[MAXLINE];
    char* value;
    int ended=0;
    unsigned char seq=0;

    menu();
    do{    
        printf("%s%s>%s ",ANSI_COLOR_CYAN,current_path,ANSI_COLOR_RESET);
        fgets(entry, MAXLINE+1, stdin);     //recebe entrada
        replaceFirst(entry,'\n','\0');
        firstWord(&value,entry);
        if(strcmp(value,"ls")==0){
            custom_ls(dirstream);

        }else if(strcmp(value,"cd")==0){
            custom_cd(entry,current_path,CLIPATH);
            dirstream = openDir(current_path);

        }else if(strcmp(value,"backup")==0){
            while(strcmp(entry,"\0")!=0){
                firstWord(&value,entry);
                backup(s,value,current_path,&seq);
            }

        }else if(strcmp(value,"recover")==0){
            while(strcmp(entry,"\0")!=0){
                firstWord(&value,entry);
                requestBackup(s,value,&seq);
                strcpy((char*)m.dados,value);
                receiveBackup(s,&m,&seq,current_path);
                do{

                    sendEmpty(s,getSeqAdding(&seq,-1),ACK);

                }while(recvMensagem(s,END,&seq)<0);
                
            }
        }else if(strcmp(value,"defdir")==0){
            setSerDir(s,entry,&seq);
        }else if(strcmp(value,"verify")==0){
            if(strcmp(entry,"\0")!=0){
                firstWord(&value,entry);
                verifyFile(s,value,&seq,current_path);
            }
        }else if(strcmp(value,"exit")==0||strcmp(value,"q")==0){
            ended=1;

        }


    }while(!ended);


    closedir(dirstream);
    close(s);

    return 0;

}
