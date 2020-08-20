#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
void mul(int *m1,int *m2){
    int res[]={0,0,0,0};
    int temp=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp=m1[i]*m2[j];
            if(i==j && i!=3)
                res[3]-=temp;
            else if(i==3)
                res[j]+=temp;
            else if(j==3)
                res[i]+=temp;   
            else{
                switch(i){
                case 0:
                    switch(j){
                        case 1:
                            res[2]+=temp;
                            break;
                        case 2:
                            res[1]-=temp;
                            break;  
                    }
                    break;
                case 1:
                    switch(j){
                        case 0:
                            res[2]-=temp;
                            break;
                        case 2:
                            res[0]+=temp;
                            break;  
                    }
                    break;
                case 2:
                    switch(j){
                        case 0:
                            res[1]+=temp;
                            break;
                        case 1:
                            res[0]-=temp;
                            break;  
                    }
                    break;  
                }   
            }
        }   
    } 
    for(int i=0;i<4;i++)
        m1[i]=res[i];
}
int getint(int s, int f, char *str){
    char num[11];
    int ct=0;   
    for(int n=s;n<f+1;n++){
        num[ct]=str[n]; 
        ct++;   
    }
    num[ct]='\0';
    return atoi(num);
}
void eval(int b, int e, int *br, char *c){
    int val=0;
    int p0=b+1;
    int p1=b+1;
    int l=0;
    int type=0;
    for(int n=b;n<e+1;n++){
        if(c[n]=='i' || c[n]=='j' || c[n]=='k'){
            switch(c[n]){
                case 'i':
                    type=0;
                    break;
                case 'j':
                    type=1;
                    break;
                case 'k':
                    type=2;
                    break;
            }
            p1=n-1;
            if(p1-p0>0 || (p1-p0>-1 && c[p0]!='-' && c[p0]!='+'))
                val=getint(p0,p1,c);
            else if(p1-p0==-1)
                val=1;
            else if(p1-p0==0 && c[p0]=='-')
                val=-1; 
            else if(p1-p0==0 && c[p0]=='+')
                val=1;  
            p0=n+1;
            p1=p0;
            br[type]=val;
        }
    }
    if (c[e-1]!='i' && c[e-1]!='j' && c[e-1]!='k'){
        l=e-1;
        while(c[l]!='+' && c[l]!='-' && c[l]!='(') 
            l--;
        p0=l+1;
        p1=e-1;
        val=getint(p0,p1,c);
        br[3]=val;
        if (c[l]=='-')
            br[3]*=-1;  
    }
}
int main()
{
    char expr[256];
    fgets(expr, 256, stdin);
    
    int brac[10][4]={0};
    int count=0;
    int begin=0;
    int end=0;
    int pass=0;
    for(int i=0;i<strlen(expr);i++){
        if(expr[i]=='(')
            begin=i;
        if(expr[i]==')')
            end=i;
        if (begin!=end && end!=0){
            eval(begin,end,brac[count],expr);
            begin=0;
            end=0;
            count++;
        }
    }
    for(int i=1;i<count;i++)
        mul(brac[0],brac[i]);
    for(int n=0;n<4;n++)
        if(brac[0][n]==0)
            pass++;
        else
            break;  
    for(int n=pass;n<4;n++){
        if(n==pass && brac[0][n]>0){
            if(brac[0][n]>1){
                switch(n){
                    case 0:
                        printf("%di",brac[0][n]);
                        break;
                    case 1:
                        printf("%dj",brac[0][n]);
                        break;
                    case 2:
                        printf("%dk",brac[0][n]);
                        break;
                    case 3:
                        printf("%d",brac[0][n]);
                        break;
                }       
            }
            if(brac[0][n]==1){
                switch(n){
                    case 0:
                        printf("i");
                        break;
                    case 1:
                        printf("j");
                        break;
                    case 2:
                        printf("k");
                        break;
                    case 3:
                        printf("1");
                        break;
                }   
            }
        }
        else {
            if(brac[0][n]==-1){
                switch(n){
                    case 0:
                        printf("-i");
                        break;
                    case 1:
                        printf("-j");
                        break;
                    case 2:
                        printf("-k");
                        break;
                    case 3:
                        printf("-1");
                        break;
                }
            }
            else if(brac[0][n]==1){
                switch(n){
                    case 0:
                        printf("+i");
                        break;
                    case 1:
                        printf("+j");
                        break;
                    case 2:
                        printf("+k");
                        break;
                    case 3:
                        printf("+1");
                        break;
                }   
            }
            else if(brac[0][n]>1){
                switch(n){
                    case 0:
                        printf("+%di",brac[0][n]);
                        break;
                    case 1:
                        printf("+%dj",brac[0][n]);
                        break;
                    case 2:
                        printf("+%dk",brac[0][n]);
                        break;
                    case 3:
                        printf("+%d",brac[0][n]);
                        break;
                }   
            }
            else if(brac[0][n]<-1){
                switch(n){
                    case 0:
                        printf("%di",brac[0][n]);
                        break;
                    case 1:
                        printf("%dj",brac[0][n]);
                        break;
                    case 2:
                        printf("%dk",brac[0][n]);
                        break;
                    case 3:
                        printf("%d",brac[0][n]);
                        break;
                }   
            }
        }
    }
    printf("\n");       
    return 0;
}
