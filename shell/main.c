#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
char* command[1000];
char str[100];
char str2[100];
char str5[100];
bool flag = false;
bool flag3=false;
int fileexist;
char* exp[10];
char exp2;
char* exp9;
char exp8[100];
char help[1000];
char help2[100];
char str3[20];
char* str4[50];
char* exp3;
char* exp4[50];
char* exp5;
char* exp6;
char  exp7[20];
char str6[1000];
int e=0;
int r=0;
int i3=0;
char temp21[1000];
char temp77[1000];
char helping[1000];
char tem[100];
char* abc[100];
char variables[1000];
char values[1000];
/// in this function we use it to parse the input into two parts the first part is the command itself and the second part is the parameter of the command
void parse_input()
{
    int j;
    int z=0;
    int leng=0;
    flag=false;
    int f=0;
    int i=0;
    while(str[f]!='\0')
    {
        str2[f]=str[f];
        f++;
    }
    str2[f]='\0';
    char *token2 = strtok(str2," ");
    if(strcmp(token2,"ls")==0)
    {
        while(str[z]!=' ' )
        {
            z++;
            j=z;
            if(leng==strlen(str))
            {
                flag=true;
                break;
            }
            leng++;
        }
        if(flag==true)
        {
            command[0]=token2;
            command[1]=NULL;
            return;
        }
        j=j+1;
        int k=0;
        while(str[j]!='\0')
        {
            help2[k]=str[j];
            j++;
            k++;
        }
        help2[k]='\0';
        if(strchr(help2, '$') != NULL)
        {
            int s=0;
            int n=1;
            while(help2[s]!='\0')
            {
                help2[s]=help2[n++];
                s++;
            }
            help2[s]='\0';
            if(strlen(exp)!=0)
            {
                if(strcmp(help2,exp[0])==0)
                {
                    char *token = strtok(exp7," ");
                    while (token != NULL)
                    {
                        command[i]=token;
                        token = strtok(NULL, " ");
                        i++;
                    }
                    command[i]=token;
                    return;
                }
                else
                {
                    int i=0;
                    char *token = strtok(str," ");
                    while (token != NULL)
                    {
                        command[i]=token;
                        token = strtok(NULL, " ");
                        i++;
                    }
                    command[i]=token;
                    command[1]=NULL;
                    return;
                }
            }
            else
            {
                command[0]="ls";
                command[1]=NULL;
            }
        }
        char *token = strtok(str," ");
        while (token != NULL)
        {
            command[i]=token;
            token = strtok(NULL, " ");
            i++;
        }
        command[i]=token;
        return;
    }
    command[0]=token2;
    while(str[z]!=' ' )
    {
        z++;
        j=z;
        if(leng==strlen(str))
        {
            flag=true;
            break;
        }
        leng++;
     }
    if(flag==true)
    {
        command[1]=NULL;
        return;
    }
    int k=0;
    j=j+1;
    while(str[j]!='\0')
    {
        help2[k]=str[j];
        j++;
        k++;
    }
    help2[k]='\0';
    command[1]=help2;
}
/// in this function we exceute shell built in command like :cd, export ,echo
void execute_shell_bultin()
{
    if(strcmp(command[0],"cd")==0)
    {

        if(strcmp(command[1],"~")==0 || command[1]==NULL)
        {
            setup_environment();
        }
        else
        {
            chdir(command[1]);
        }
    }
    else if(strcmp(command[0],"echo")==0)
    {
        if(strchr(command[1], '$') != NULL)
        {
            char* temp2=strtok(command[1],"\"");
            temp2=strtok(temp2,"$");
            char* temp4;
            int check =0;
            temp4=temp2;
            char* temp3[10];
            while(temp2!=NULL)
            {
                temp2=strtok(NULL,"$");
                if(temp2!=NULL)
                {
                    check=1;
                    temp3[0]=temp2;
                }
            }
            if(check==0)
            {
                temp3[0]=temp4;
            }
            else
            {
                printf("%s",temp4);
            }
            int u;
            bool flag4=false;
            char* temp5;

            temp5 =strtok(variables,"*");
            int y=0;


            while(temp5!=NULL)
            {
                if(strcmp(temp5,temp3[0])==0)
                {
                    flag4=true;
                    break;
                }
                temp5 =strtok(NULL,"*");
                y++;
            }
            if(flag4==false)
            {
                printf("\n");
            }
            else
            {

                char* temp6;
                temp6=strtok(values,"*");
                int s=0;


                while(temp6!=NULL)
                {
                    if(s==y)
                    {

                        printf("%s",temp6);
                        break;
                    }
                    temp6=strtok(NULL,"*");

                    s++;
                }
                printf("\n");
            }
        }
        else
        {
            if(strchr(command[1], '"') != NULL)
            {
               char* temp9= strtok(command[1],"\"");
                printf("%s",temp9);
                printf("\n");
            }
            else
            {
                printf(" \n");
            }
        }
    }
    else
    {
        int f=0;
        int i=0;
        char str66[100];
        bool flag55=false;
        int y7=0;

        char str77[100];
        int y8=0;
        while(str[f]!='\0')
        {
            if(str[f]=='=')
            {

                flag55=true;
            }
            if(flag55==true)
            {
                str66[y7]=str[f];
                y7++;
            }
            else
            {
                str77[y8]=str[f];

                y8++;
            }

            str3[f]=str[f];
            f++;
        }
         str66[y7]='\0';
        char* temp8=strtok(str77," ");
        temp8=strtok(NULL," ");
        char* temp7;
        temp7= strtok(str66,"=");
        char* temp10;
        char* temp24[1000];
        char temp20[1000];
        int i2=0;
        while(temp24[i2]!='\0')
        {
            temp20[i2]=temp24[i2];

            i2++;
        }

        temp10=temp8;
        char* lol;
        lol=temp7;
        bool flag6=false;
        int y=0;
        char* temp55;
        char temp66[1000];
        temp55 =strtok(temp66,"*");
        while(temp55!=NULL)
        {

            if(strcmp(temp55,temp10)==0)
            {
                flag6=true;
                break;
            }
            temp55 =strtok(NULL,"*");
            y++;
        }
        int s=0;
        if(flag6==false)
        {

            while(temp10[s]!='\0')
            {
                temp21[i3]=temp10[s];
                i3++;
                s++;
            }
             temp21[i3]='*';
             i3++;
            int i5=0;
            while(temp21[i5]!='\0')
            {
                variables[i5]=temp21[i5];

                i5++;
            }
        }
        int i4=0;
        while(temp21[i4]!='\0')
        {
            temp66[i4]=temp21[i4];
            i4++;
        }
        char* temp11;
        temp11=strtok(lol,"=");

        char* temp12;
        temp12=strtok(temp11,"\"");
        int t2=0;
        if(flag6==false)
        {
            while(temp12[t2]!='\0')
            {
                temp77[r]=temp12[t2];
                r++;
                t2++;
            }
            temp77[r]='*';
            r++;
            int i55=0;
             while(temp77[i55]!='\0')
            {
                values[i55]=temp77[i55];

                i55++;
            }
        }
        char* temp;
        temp=strtok(command[1],"=");
        exp2=*temp;
        while(temp != NULL)
        {
            exp[i]=temp;
            temp = strtok(NULL, "=");
            i++;
        }
        exp[i]=temp;
        temp=strtok(exp[1],"\"");
        exp[1] =temp;
        exp9=exp[1];
        int p=0;
        while(exp9[p]!='\0')
        {
            exp8[p]=exp9[p];
            p++;
        }
        str4[0]=temp;
        exp5=str4[0];
        int l=3;
        int m=0;
        while(exp5[m]!='\0')
        {
            exp4[l]=exp5[m];
            l++;
            m++;
        }
        exp6="ls ";
        int t=strlen(exp6);
        int g=strlen(exp5);
        int b=0;
        int a=0;
        int q=0;
        while(exp6[a]!='\0')
        {
            exp7[a]=exp6[a];
            a++;
        }
        while(exp5[b]!='\0')
        {
            exp7[a]=exp5[b];
            a++;
            b++;
        }
    }
}
/// in this function we execute any other neither (cd,echo,export)
void execute_command()
{
    pid_t child_id=fork();
    if (child_id == -1)
    {
        printf("Failed forking child..\n");
        return;
    }
    else if (child_id == 0)
    {
        if (execvp(command[0],command) < 0)
        {
            printf("Could not execute command..\n");
        }
        exit(0);
    }
    else
    {
        if(flag3==true)
        {
            flag3=false;
            return;
        }
        wait(NULL);
        return;
    }
}
///in this function we write into the log file that child have been terminated
void on_child_exit()
{
    char msg[]="Child terminated\n";
    if(fileexist != 1)
    {
        write(fileexist,msg,strlen(msg));
    }
}
void reap_child_zombie()
{
    int wstat;
    pid_t pid;
    pid = wait3 (&wstat, WNOHANG, (struct rusage *)NULL );
    if (pid == 0)
        return;
    else if (pid == -1)
        return;
}
///in this function we setup the home directory
 void setup_environment()
 {
    char *homedir = getenv("HOME");
    chdir(homedir);
 }
int main ()
{
    reap_child_zombie();
    signal (SIGCHLD, on_child_exit);
    fileexist = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    setup_environment();
    while(1)
    {
        gets(str);
        if(strchr(str, '&') != NULL)
        {
            flag3=true;
            int i=0;
            while(i<strlen(str)-2)
            {
                str5[i]=str[i];
                i++;
            }
            str5[i]='\0';
            int j=0;
            while(str5[j]!='\0')
            {
                str[j]=str5[j];
                j++;
            }
            str[j]='\0';
            parse_input();
            if(strcmp(command[0],"cd")==0 || strcmp(command[0],"echo")==0 || strcmp(command[0],"export")==0)
            {
                execute_shell_bultin();
            }
            else
            {
                execute_command();
            }
        }
        else
        {
            if(!strcmp(str,"exit"))
            {
                exit(0);
            }
            parse_input(str);
            if(strcmp(command[0],"cd")==0 || strcmp(command[0],"echo")==0 || strcmp(command[0],"export")==0)
            {
                execute_shell_bultin();
            }
            else
            {
                execute_command();
            }
        }
    }
    return 0;
}
