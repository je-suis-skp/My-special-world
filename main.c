#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Function for testing purpose: It accepts character and print Binary representation */
/*void printBinary(char ch)
{
    for(int i=7;i>=0;i--)
        printf("%d",(ch>>i)&1);
}*/

void encryption();
void decryption();
void menu();

int main(int argc, char **argv) //main start
{  
    menu();
    return 0;
} //main end

/* "Menu" Function to get choice input */
void menu()
{
    int choice;
    do
    {
        system("cls");
        printf("***********************\n");
        printf("*********MENU**********\n");
        printf("***********************\n");
        printf("\nEnter 1 For Encryption");
        printf("\nEnter 2 For Decryption");
        printf("\nEnter 3 For exit\n");
        printf("Please Enter Your Choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
          case 1:   
                    encryption();
                    break;
          case 2:   
                    decryption();
                    break;
          case 3:   
                    exit(0);
          default : 
                    printf("You Entered Wrong Choice.Try Again\n");
        }
    }while(choice != 3);
}

/* "Encryption" Function for encrypting the bmp image with required message" */
void encryption()
{
    FILE *img,*eimg;
    char *message;
    int i,messageLength;
    printf("Enter message to be encrypted:-");
    fseek(stdin,0,SEEK_END);//To flush stdin
    gets(message);
    for(i=0;message[i]!='\0';i++);//To get the length of message to be encrypted
    messageLength = i;
    img=fopen("abcd.bmp","rb+");//Opening the image to be encrypted
    if(img==NULL)
        printf("cannot open file");
    eimg=fopen("eabcd.bmp","wb");//Encrypted image
    i=0;
    while(i++<255) //To copy the header of bmp image
    {
        fputc(fgetc(img),eimg);
    }
    for(i=31;i>=0;i--)
    {
        char ch=fgetc(img);
        ch=(ch&0xFFFE)|((messageLength>>i)&1);
        fputc(ch,eimg);
    }
    i=0;
    while(!feof(img) && i<messageLength)//Logic for Encryption
    {
        for(int j=7;j>=0;j--)
            {    
                char ch=fgetc(img);
                ch=(ch&0xFFFE)|((message[i]>>j)&1);
                fputc(ch,eimg);
            }
        i++;
    }

    while(!feof(img))
    {
        fputc(fgetc(img),eimg);
    }
    fclose(img);
    fclose(eimg);
    printf("\n\nYour Message is successfully Encrypted...\n\nPress any key to continue");
    getch();
}
void decryption()
{
    FILE *img,*eimg;
    int i;
    eimg=fopen("eabcd.bmp","r");
    i=0;
    while(i++<255) //Skiping header info
        fgetc(eimg);
    i=0;
    int messageLength=0;
    for(int j=31;j>=0;j--)
    {    
        char ch=fgetc(eimg);
        messageLength=(messageLength<<1)|(ch&1);
    }
    printf("Message in encrypted image is : "); 
    while(!feof(eimg) && i<messageLength)//Logic for Decryption
    {
        char c=0;
        for(int j=7;j>=0;j--)
        {    
            char ch=fgetc(eimg);
            c=(c<<1)|(ch&1);
        }
        i++;
        printf("%c",c);
    }
    printf("\n");
    fclose(eimg);
    printf("Press any key to continue...");
    getch();
}
