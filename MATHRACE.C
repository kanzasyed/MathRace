#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<ctype.h>
char playboard[12][12],s[100],*ques[20];
int size=50,p1Score=0,p2Score=0;
int p1stack[50],p2stack[50],answers[2];
int p1moves=0,p2moves=0,top=-1;
int gd=DETECT,gm;
int p1isFull();
int p1isEmpty();
void p1pushit(int value);
int p1popit();
int p2isFull();
int p2isEmpty();
void p2pushit(int value);
int p2popit();
void board();
void scoreBoard();
void game();
void Menu();
void instructions();
void p1Car(int pos);
void p2Car(int pos);
void placeCars();
void readFileEASY();
void push(int elem);
int pop();
int infixToPostfixEvaluation(char *infx);
int isCorrect(int ans,char *ques);
void p1move(int ans,char *ques);
void p2move(int ans,char *ques);
void main(){
	clrscr();
	readFileEASY();
	Menu();
	getch();
}
void board(){
	int i,j;
	printf("\n\t\t\t----------------------------------------\n\t\t\t  ");
	for(i=1;i<10;i++)
		printf(" %d ",i);
	printf("| WIN |\n\t\t\t");
	for(i=1;i<=2;i++){
	     printf("%d|",i);
	     for(j=1;j<=11;j++)
		printf(" %c ",playboard[i][j]);
	     printf("   %c  \n\t\t\t",playboard[i][j]);
	}
	printf("----------------------------------------\n\t\t\t");
}
void game(){
	int i=0,j;
	while(p1Score!=55 && p2Score!=55){
	clrscr();
	printf("\t\t\t----------------------------------------\n\t\t\t  ");
	printf("QUESTION: %s",ques[i]);
	board();
	scoreBoard();
	for(j=1;j<=2;j++) {
		printf("Player%d answer:",j);
		scanf("%d",&answers[j]);
		printf("\n\t\t\t  ");
	}
	p1move(answers[1],ques[i]);
	p2move(answers[2],ques[i]);
	i++;
	}
	if(p1Score==55 && p2Score!=55){
		clrscr();
		board();
		scoreBoard();
		printf("Player 1 Wins\n\t\t\t");
	}
	else if(p2Score==55 && p1Score !=55){
		clrscr();
		board();
		scoreBoard();
		printf("Player 2 Wins\n\t\t\t");
	}
	else if(p1Score==55 && p2Score==55){
		clrscr();
		board();
		scoreBoard();
		printf("TIE");
	}
}
void scoreBoard(){
	printf("Player1 Score:%d         Player2 Score:%d ",p1Score,p2Score);
	printf("\n\t\t\t----------------------------------------\n\t\t\t  ");
}
void Menu(){
	int choice;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	clrscr();
	printf("\n\n\n\t\t\t\t1-NEW GAME\n\t\t\t\t2-INSTRUCTIONS\n\t\t\t\t3-QUIT\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			clrscr();
			setbkcolor(LIGHTBLUE);
			placeCars();
			break;
		case 2:
			setbkcolor(BLUE);
			instructions();
			break;
		case 3:
			break;
	}
}
void instructions(){
	printf("\n\t\t\tEach player is provided with a question and player have \n\t\t\tto give right answer in order to win the race");
}
void p1Car(int pos){
	if(playboard[1][pos-1]==NULL){
		playboard[1][pos+1]=NULL;
		playboard[1][pos]='=';
	}
	else{
	    playboard[1][pos-1]=NULL;
	    playboard[1][pos]='=';
	}
}
void p2Car(int pos){
	if(playboard[2][pos-1]==NULL){
		playboard[2][pos+1]=NULL;
		playboard[2][pos]='=';
	}
	else{
	    playboard[2][pos-1]=NULL;
	    playboard[2][pos]='=';
	}
}
void placeCars(){
	playboard[1][1]='=';
	playboard[2][1]='=';
	game();
}
void readFileEASY(){
	FILE *fp;
       char singleLine[150];
       int i=0;
       fp = fopen("easy.txt","r");
	while(fgets(singleLine,sizeof(singleLine),fp)!=NULL){
		ques[i]=strdup(singleLine);
		i++;
	}
	fclose(fp);
}
////////////////player 1 moves stack//////////////////
int p1isEmpty(){
	if(p1moves==0)
		return 1;
	else
		return 0;
}
int p1isFull(){
	if(p1moves==size)
		return 1;
	else
		return 0;
}
void p1pushit(int value){
	if(p1isFull())
		printf("stack is Full\n");
	else{
	       p1moves++;
	       p1stack[p1moves]=value;
	}
}
int p1popit(){
	if(p1isEmpty())
		printf("Player 1 game Over");
	else{
	      return p1stack[p1moves--];
	}
}
/////////////player 2 moves stack////////////////
int p2isEmpty(){
	if(p2moves==0)
		return 1;
	else
		return 0;
}
int p2isFull(){
	if(p2moves==size)
		return 1;
	else
		return 0;
}
void p2pushit(int value){
	if(p2isFull())
		printf("stack is Full\n");
	else{
	       p2moves++;
	       p2stack[p2moves]=value;
	}
}
int p2popit(){
	if(p2isEmpty())
		printf("Player 2 game Over");
	else{
	       return p2stack[p2moves--];
	}
}
int infixToPostfixEvaluation(char *infx){
	char pofx[50],ch,elem;
	int i=0,k=0,op1,op2,ele;
	push('#');
	while((ch = infx[i++]) !='\0')
	{
		if(ch== '(')
		push(ch);
		else if (isalnum(ch))
		pofx[k++]=ch;
		else if(ch == ')')
		{
			while(s[top] != '(')
			pofx[k++] = pop();
			elem=pop();
		}

		else
		{
			while(pr(s[top]) >= pr(ch))
			pofx[k++] = pop();
			push(ch);
		}
	}
	while(s[top] != '#')
	pofx[k++] = pop();
	pofx[k]='\0';
	i=0;
	while (( ch =pofx[i++]) != '\0')
	{

		if(isdigit(ch))
		push(ch-'0');
		else
		{
			op2=pop();
			op1=pop();
			switch(ch)
			{
				case '+':
				push(op1+op2);
				break;
				case '-':
				push(op1-op2);
				break;
				case '*':
				push(op1*op2);
				break;
				case '/':
				push(op1/op2);
				break;
			}
		}
	}
	return s[top];
}
void push(int elem)
{
	s[++top] = elem;
}
int pop()
{
	return(s[top--]);
}
int pr(char elem)
{
	switch(elem)
	{
		case '#':
		return 0;
		case '(':
		return 1;
		case '+':
		return 2;
		case '-':
		return 2;
		case '*':
		return 3;
		case '/':
		return 3;
	}
}
int isCorrect(int ans,char *ques){
	int answer=0,i=0;
	char copy[20]="";
	 while(ques[i]!='\n'){
		copy[i]=ques[i];
		i++;
	  }
//	printf("%s,%s\n",arr,ques[0]);
	answer=infixToPostfixEvaluation(copy);
	if(ans==answer)
		return 1;
	 return 0;
}
void p1move(int ans,char *ques){
	if(isCorrect(ans,ques)){
		p1pushit(p1moves+1);
		p1Score=p1Score+p1stack[p1moves];
		p1Car(p1moves);
	}
	else{
		if(p1moves==0)
			p1Score=p1Score-1;
		 else{
			p1Score=p1Score-p1popit();
			p1Car(p1moves);
			}
	}
}
void p2move(int ans,char *ques){
	if(isCorrect(ans,ques)){
		p2pushit(p2moves+1);
		p2Score=p2Score+p2stack[p2moves];
		p2Car(p2moves);
	}
	else{
		if(p2moves==0)
			p2Score=p2Score-1;
		 else{
			p2Score=p2Score-p2popit();
			p2Car(p2moves);
			}
	}
}


