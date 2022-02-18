#include <stdio.h>

void input(FILE *f,int k);
void output(FILE *f, int k);
int mult(FILE *f, int size, int num);
void cycleSh(FILE *f,int size);
int main() {
    setbuf(stdout, 0);
    FILE *f;
    do {
        printf("chose filename\n");
        char name[100];
        scanf_s("%s",name);
        f= fopen(name,"w+b");
    } while (f==NULL);
    int count=0;
    do {
        printf("input number of digits\n");
        scanf_s("%d",&count);
    } while ((count<=0)||(count>1000));
    printf("enter data sequentially\n");
    input(f,count);

    for (;;) {
        int ch;
        printf("Menu:\n1)count the number\n2)cyclic shift\n3)show data\n4)exit\n");
        scanf_s("%d",&ch);

        switch (ch) {
            case 1:
                printf("input number\t");
                int num;
                scanf_s("%d",&num);
                printf("number:\t%d\n", mult(f,count,num));
                break;
            case 2:
                printf("enter shift size ");
                int buf;
                scanf_s("%d",&buf);
                for (int i = 0; i < buf; ++i) {
                    cycleSh(f,count);
                }
                break;
            case 3:
                output(f,count);
                break;
            case 4:
                return 0;
            default:
                printf("incorrect input\n");
        }
    }
}
void input(FILE *f, int k) {
    for (int i = 0; i < k; ++i) {
        int num;
        scanf_s("%d",&num);
        fwrite(&num,sizeof(int),1,f);
    }
}

void output(FILE *f, int k) {
    fseek(f,0,0);
    printf("Data:\n");
    for (int i = 0; i < k; ++i) {
        int buf;
        fread(&buf, sizeof(int),1,f);
        printf("%d\n",buf);
    }
}

int mult(FILE *f, int size, int num) {
    int counter=0,buf;

    fseek(f,0,0);
    for (int i = 0; i < size; ++i) {

        fread(&buf, sizeof(int),1,f);
        if(buf%num==0) counter++;
    }
    return counter;
}

void cycleSh(FILE *f, int size) {
    fseek(f, 0,0);
    int buf,buf2;
    fread(&buf, sizeof(int),1,f);
    fread(&buf2, sizeof(int),1,f);
    fseek(f, sizeof(int),0);
    for (int i = 2; i <= size; ++i) {
        fwrite(&buf,sizeof(int),1,f);
        buf=buf2;
        fseek(f, i*sizeof(int),0);
        fread(&buf2, sizeof(int),1,f);
        fseek(f, i*sizeof(int),0);
    }
    fseek(f, 0,0);
    fwrite(&buf,sizeof(int),1,f);
}
