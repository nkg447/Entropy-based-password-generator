/*
* The Main executing file which creates the
  password using the parameters
*/

#include "regexValidator.c"
#include "linkedList.c"
#include <stdlib.h>
#include <time.h>
#include <string.h>

static struct Node* head;
static char password[100];
static int idx=0;
/*
* A function to generate a password character which is in the range of set
* Requires Parameter - character array of set
*/
void getPasswordChar(char * set){
    int length=strlen(set);
    //get the password character from the range defined in the set
    if(length==1){
        password[idx++]=set[0];
        //printf("%c",set[0]);
    }
    else{
        int charASCII=set[0]+(getElementAt(head,(clock()+idx)%5)%(set[2]-set[0]));
        password[idx++]=charASCII;
        //printf("%c",charASCII);
    }
}

/*
* A function to create sets from the groups
* Requires Parameter - A character array of group, it's size and it's occurence
*/
void getPasswordFromGroup(char * group,int size,int occurence){
    if(occurence==0)    return;
    char sets[100][3];
    int i=0,setidx=0,idx=0;

    //get sets "[]" from  the groups
    while(i<size){
        if(group[i]=='['){
            i++;
            idx=0;
            while(group[i]!=']'){
                sets[setidx][idx++]=group[i++];
            }
            sets[setidx][idx++]='\0';
            setidx++;
            
        }
        else if(group[i]!='|'){
            sets[setidx][0]=group[i++];
            sets[setidx][1]='\0';
            setidx++;   
        }
        i++;
    }
    //printf("setidx - %d\n",setidx);
    getPasswordChar(sets[clock()%setidx]);
    getPasswordFromGroup(group,size,occurence-1);
}

/*
* A function to create a password from the parameters by
  dividing the regex into groups and their occurence
* Requires Parameter - A validated character string
*/
void createPassword(char * regex){
    srand(time(NULL));
    int i=0;
	char temp,popch;
	
    char group[1000];
    int occurence,idx=0;
    //get groups "()" from the regex along with their occurence 
	while(regex[i]!='\0'){
        idx=0;
        occurence=1;
		if(regex[i]=='('){
			i++;
			while(regex[i]!=')'){
                group[idx++]=regex[i++];
            }
            
            i++;
            
            if(regex[i]=='{')
            {
                occurence=regex[++i]-48;
                i+=2;
            }
            
            //printf("%s and occ - %d\n",group,occurence);
            getPasswordFromGroup(group,idx,occurence);
        }
	}
    
        
}

void inputOptions(){
    printf("Password Generator - \n");
    printf("Select one of the following password template - \n\n");
    printf("\t1 - Complex Password\n");
    printf("\t2 - PIN Password\n");
    printf("\t3 - Number Password\n");
    printf("\t4 - Simple Password\n");
    printf("\t5 - Customized Password\n");
}

int main(){
    char *regex;
    int i=1;
    FILE *fp;
    fp = fopen("pass.txt", "a+");

    do{
        idx=0;
        inputOptions();
        scanf("%d",&i);
        //complex password
        if(i==1){
            regex="([a-z])([A-Z])([A-Z]|[a-z]|[0-9]){5}(!|@|#|$|%|^|&|_)([0-9])";
        }
        //pin password
        else if(i==2){
            regex="([0-9]){4}";
        }
        //number password
        else if(i==3){
            regex="([0-9]){8}";
        }
        //simple password
        else if(i==4){
            regex="([a-z]|[A-Z])([A-Z]|[a-z]){7}";
        }
        //customized passoword
        else{
            printf("Enter the regex:- \n");
            regex = malloc(200);
            scanf("%200s",regex);
        }

        i=isValidRegex(regex);
        

        if(i==1){
            head = getParameters();
            createPassword(regex);
        }
            
        else{
            printf("Invalid Regex please enter again\n");
            continue;
        }
        
        password[idx]='\0';
        printf("\n\nPassword - %s\n\n",password);
        fputs(password,fp);
        fputs("\n",fp);
        printf("Enter 1 to calculate password again - \n");
        printf("      2 to get previous password - ");
        scanf("%d",&i);
        if(i==2){
            fclose(fp);
            fp = fopen("pass.txt", "a+");
            printf("Enter password index - ");
            scanf("%d",i);
            int itr=0;
            char pass[10];
            while(fgets (pass, sizeof(pass), fp)!=NULL ){
                printf("%s",pass);
            }
            
        }
    }while(i==1);

    fclose(fp);
    return 0;

}