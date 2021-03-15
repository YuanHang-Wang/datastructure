#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXLENG 10
#define MAXSIZE 2
#define INFEASTABLE -1
#define OVERFLOW -2
#define QMAXSIZE 5 //���д�С 
typedef int status;  //����Ԫ�����Ͷ���
typedef char TElemType;//�����ַ��ͳ��� 
#define LINE 1024

static char keywords[50][20]={ "char", "continue","break",
                                "else","for", "float","if","while",
                                "int","double","case",
                                "return","void","continue", "struct",
                                "switch","default"};
static char headfile[50][30]={ "#include<stdio.h>","#include<stdlib.h>","#include<string.h>","#includ<file.h>","#include<math.h>"};
typedef enum
{
    ELSE=1,IF,INT,RETURN,VOID,WHILE,FOR,CHAR,FLOAT,LONG,LEQ,REQ,EQ,BREAK,CONTINUE,UNEQ,//16
    PLUS,MINUS,TIMES,DIVISION,BIG,LITTLE,ASSIGN,SEMI,COMMA,LP,RP,LMP,//12
    RMP,LBP,RBP,ERROR_TOKEN,IDENT,INT_CONST,LONG_CONST,CHAR_CONST,FLOAT_CONST,ID,END, //11
    HONG1,HONG2,HONG3,HONG4,HONG5//5 
}Token_texttype;

typedef enum Nodekind
{
    ints,ids,voids,chars,floats,longs,INT_CONSTS,LONG_CONSTS,variable,shuzu,hanshu,hancanlist,hancan,fuheyuju,ifs,elses,whiles,returns,breaks,continues,
    fuzhi,yunsuan,hong,hong1,hong2,hong3,hong4,hong5,shuzuyuansu,hanshudiaoyong,hanshudiaoyongcanlist,unknown
}NODEkind;//�ڵ�����

typedef enum Expressiontype
{
    Void,
    Int,
	Char,
	Float 
}expressiontype;//���ʽ����

typedef struct TREENODE//���ڵ�ṹ�庢�ӱ�ʾ�� 
{
    TREENODE * child;//���ӽڵ�
    TREENODE * rchilde;//���ӽڵ�
    int linenumber;//������
    Nodekind NODEkind;//�ڵ�����
    char NODEstring[1100];//�ڵ�������������ַ����������﷨����ӡ
}TREENODE,*tokenTREE;

typedef struct token_text//token�ṹ��
{
    Token_texttype token_texttype;//token����
    char token_textstring[1100];//token��
    int linenumber;//token�к�
}Token;
Token_texttype gettoken_texttype(char c[]);
void scan(); //ɨ�裬�ʷ�ʶ�� 
char s[1005][1005];//�ı�
char p[1005][1005];//��ʱ�滻���� 
char t[1005];//��ǰtoken_text��
char tk[1005];  
char linshi[1100];//��ʱ����
int line; //�ı����� 
int zs; //ע�ͱ�� 
int tttt;  //��ǣ��ṹ������� 
Token tokenlist[1000];    //token������ 
Token ctoken;//��ǰtoken
Token ltoken;//��һ��token
int xb=0;//token�±�
int blank=0;//���пո�	
void gettoken_text();//�õ�token
void programerror();//�������
void match(Token_texttype toke);//ƥ��
TREENODE * compound_stmt();//��������
void printspace(int n);//��ӡ�ո�
void printTREE(TREENODE * t);//��ӡ�﷨������
TREENODE * NEWNODE(Nodekind kind);//�����½ڵ�
TREENODE * function_listformat();//���������б��ʽ 
TREENODE * call(TREENODE * k);//��������
TREENODE * factor(TREENODE * k); //�����ŵı��ʽ 
TREENODE * term(TREENODE * k);  //�˳����ʽ 
TREENODE * additive_expression(TREENODE * k);//�ӳɵı��ʽ
TREENODE * simple_expression(TREENODE * k);//�򵥱��ʽ
TREENODE * variabler(); //�������� 
TREENODE * expression();  //���ʽ���� 
TREENODE * expression_stmt();//���ʽ����
TREENODE * return_stmt();//����ʽ����
TREENODE * continue_stmt();//continue���� 
TREENODE * break_stmt();//break���� 
TREENODE * while_stmt();//while����
TREENODE * if_stmt();//if����
TREENODE * else_stmt();//else���� 
TREENODE * statement();//��������������
TREENODE * statement_list();//������������
TREENODE * local_declaration();//���������ǰ��
TREENODE * function_def(TREENODE * k);//����
TREENODE * function_def_list(TREENODE * k);//�����б�
TREENODE * compound_stmt();//�������ݣ��������
TREENODE * function_defs();//��������
TREENODE * declaration();//��������
TREENODE * declaration_list();//��������б�
TREENODE * program();//�﷨����
void savefile(TREENODE * T);//,FILE *FP);//�����ļ� 
void save(FILE * FP);
int main()
{
	/*FILE *FP; 
	int i = 0,j = 0;
	char w,c;
	 printf("�����뽫Ҫ��ȡ���ļ�������.txt��β��\n");
	char file[30];
	scanf("%s",file);
	if ((FP=fopen(file,"rb")) == NULL)
	    printf("File open error\n ");
	else
	    printf("�ļ���ȡ�ɹ�\n");
	while((c = fgetc(FP)) == 1)
	{
		if(c == '\n')
		{
			j = 0;
			i++;
		}
		else
		s[i][j++] = c; 
		line = i;
		if(c == '#')
		 break;
	}
    fclose(FP); */
    printf("������һ�δ��룬�س�֮��ctrl+z������\n");
	int i=0;
	int change; 
	line=0;
    while(gets(s[line++]))
    {}
    printf("����ʶ�� :\n");
    scan();
   // zhushi();
    printf("\n�﷨���� :\n");
    TREENODE *t = program(); //����ast��ͷ��� 
    TREENODE *p;
	p = t; 
	printf("������ֵ��");
	scanf("%d",&change);
	getchar();
	if(change == 1)
    printTREE(t);          //��ӡast�﷨�� 
    else if(change == 2)
    {
	FILE *FP;
    printf("�������ļ����ƣ�\n");
    char file[30];
	scanf("%s",file);
	if ((FP=fopen(file,"w")) == NULL)
	printf("�ļ���ʧ��\n ");
	else
	printf("�ļ��򿪳ɹ�\n"); 
	savefile(p);
	save(FP);
	fclose(FP);
    } 
    else
    {
	getchar();
    return 0;
	}
	getchar();
    return 0;
}
Token_texttype gettoken_texttype(char c[])
{
    Token_texttype to;
    if(!strcmp(c,"else"))
    {
        to=ELSE;
    }
    if(!strcmp(c,"break"))
    {
        to=BREAK;
    }
    if(!strcmp(c,"continue"))
    {
        to=CONTINUE;
    }
    else if(!strcmp(c,"if"))
    {
        to=IF;
    }
    else if(!strcmp(c,"return"))
    {
        to=RETURN;
    }
    else if(!strcmp(c,"int"))
    {
        to=INT;
    }
    else if(!strcmp(c,"char"))
    {
        to=CHAR;
    }
    else if(!strcmp(c,"float"))
    {
        to=FLOAT;
    }
    else if(!strcmp(c,"long"))
    {
        to=LONG;
    }
    else if(!strcmp(c,"void"))
    {
        to=VOID;
    }
    else if(!strcmp(c,"while"))
    {
        to=WHILE;
    }
    else if(!strcmp(c,"+"))
    {
        to=PLUS;
    }
    else if(!strcmp(c,"-"))
    {
        to=MINUS;
    }
    else if(!strcmp(c,"*"))
    {
        to=TIMES;
    }
    else if(!strcmp(c,"/"))
    {
        to=DIVISION;
    }
    else if(!strcmp(c,"<"))
    {
        to=LITTLE;
    }
    else if(!strcmp(c,"<="))
    {
        to=LEQ;
    }
    else if(!strcmp(c,"#include<stdio.h>"))
    {
    	to = HONG1;
	}
	 else if(!strcmp(c,"#include<stdlib.h>"))
    {
    	to = HONG1;
	}
	 else if(!strcmp(c,"#include<string.h>"))
    {
    	to = HONG1;
	}
	 else if(!strcmp(c,"#include<file.h>"))
    {
    	to = HONG1;
	}
	 else if(!strcmp(c,"#include<math.h>"))
    {
    	to = HONG1;
	}
    else if(!strcmp(c,">"))
    {
        to=BIG;
    }
    else if(!strcmp(c,">="))
    {
        to=REQ;
    }
    else if(!strcmp(c,"=="))
    {
        to=EQ;
    }
    else if(!strcmp(c,"!="))
    {
        to=UNEQ;
    }
    else if(!strcmp(c,"="))
    {
        to=ASSIGN;
    }
    else if(!strcmp(c,";"))
    {
        to=SEMI;
    }
    else if(!strcmp(c,","))
    {
        to=COMMA;
    }
    else if(!strcmp(c,"("))
    {
        to=LP;
    }
    else if(!strcmp(c,")"))
    {
        to=RP;
    }
    else if(!strcmp(c,"["))
    {
        to = LMP;
    }
    else if(!strcmp(c,"]"))
    {
        to=RMP;
    }
    else if(!strcmp(c,"{"))
    {
        to=LBP;
    }
    else if(!strcmp(c,"}"))
    {
        to=RBP;
    }
    else if(!strcmp(c,"INT_CONST1"))
    {
        to=INT_CONST;
    }
    else if(!strcmp(c,"LONG_CONST1"))
    {
        to=LONG_CONST;
    }
    else if(!strcmp(c,"ID"))
    {
        to=ID;
    }
    else if(!strcmp(c,"end"))
    {
        to=END;
    }
    return to;
}

void scan()
{
	zs = 0;
	char uu[3];
	int tt = 0;//tokenlist���±� 
    int i,j,m,l,n,b,d;//�±�
    int f,flag;//���
    int len;//��ǰ�г���
    char keywords[50][20]={ "char", "continue","break",
                                "else","for", "float","if","while",
                                "int","long","double","case",
                                "return","void","continue", "struct",
                                "switch","default"};//�ؼ���
    char headfile[50][30]={ "#include<stdio.h>","#include<stdlib.h>","#include<string.h>","#includ<file.h>","#include<math.h>"};
    char compare2[10][1005]={"<=",">=","==","!=","--","++","&&","||"};//˫Ŀ�ȽϷ�
    char compare1[1005]={'+','-','*','/','>','<','=',';',':',',','(','%',')','[',']','{','}','!'};//��Ŀ����
    //zs=0;ע���жϱ�־ 
    for(i=0;i<line-1;i++)
    {
        len = strlen(s[i]);
        printf("%d: ",i+1);
        printf("%s\n",s[i]);
        if(len==0)//����
        {
            continue;
        }
        for(j=0;j<len;j++)
        {
         
            if(s[i][j]==' ')//�ո�
            {
                continue;
            }
            if(s[i][j] == '#')
            {
            	l = j;
            	d = 0;
            	for(;l<len;l++)
            	{
            		tk[d++] = s[i][l];
				}
				tk[d] = '\0';
				for(b=0;b<5;b++)
				{
					if(!strcmp(tk,headfile[b]));
					{
					printf("  %d: �궨��: %s\n",i+1,tk);
                        tokenlist[tt].token_texttype = gettoken_texttype(tk);
                        strcpy(tokenlist[tt].token_textstring,tk);
                        tokenlist[tt].linenumber=i+1;
                        tt++;
                        j = l-1;
                        break;}
				}
			} 
			 else if(s[i][j]<='9'&&s[i][j]>='0')//����
            {
            	l = j;
            	m = 0;
            	if(s[i][l] == '0')
            	{
				    t[m++]=s[i][l++];
            		if(s[i][l] == 'x')
            		{
            			t[m++] = s[i][l++];
					}
				}
                while(s[i][l]<='9'&&s[i][l]>='0')
                {
                    t[m++] = s[i][l++];
                }
                if(s[i][l] == 'L')
                {
                	t[m++] = s[i][l++];
                	t[m]='\0';
                	printf("  %d:  ���������� = %s\n",i+1,t);
                strcpy(linshi,"LONG_CONST1");
                tokenlist[tt].token_texttype = gettoken_texttype(linshi);
                strcpy(tokenlist[tt].token_textstring,t);
                tokenlist[tt].linenumber=i+1;
                tt++;
                j=l-1;
				}
				else
				{ 
                t[m]='\0';
                printf("  %d:  �������� = %s\n",i+1,t);
                strcpy(linshi,"INT_CONST1");
                tokenlist[tt].token_texttype = gettoken_texttype(linshi);
                strcpy(tokenlist[tt].token_textstring,t);
                tokenlist[tt].linenumber=i+1;
                tt++;
                j=l-1;
                }
            }
            else if((s[i][j]<='z'&&s[i][j]>='a')||(s[i][j]<='Z'&&s[i][j]>='A'))//��ĸ
            {
                l=j;
                m=0;
                while((s[i][l]<='z'&&s[i][l]>='a')||(s[i][l]<='Z'&&s[i][l]>='A'))
                {
                    t[m++]=s[i][l++];
                }
                t[m]='\0';
                f=1;//���
                for(n = 0;n < 20;n++)
                {
                	
                    if(!strcmp(t,keywords[n]))
                    {
                        f=0;
                        printf("  %d: �ؼ���: %s\n",i+1,t);
                        tokenlist[tt].token_texttype = gettoken_texttype(t);
                        strcpy(tokenlist[tt].token_textstring,t);
                        tokenlist[tt].linenumber=i+1;
                        tt++;
                        break;
                    }
                }
                if(f)
                {
                    printf("  %d: ID ����= %s\n",i+1,t);
                    strcpy(linshi,"ID");
                    tokenlist[tt].token_texttype = gettoken_texttype(linshi);
                    strcpy(tokenlist[tt].token_textstring,t);
                    tokenlist[tt].linenumber=i+1;
                    tt++;
                }
                j=l-1;
            }
            else//����
            {
                l=j;
                n=0;
                while(1)
                {
                    flag=0;//���
                    for(m=0;m<18;m++)
                    {
                        if(s[i][l]==compare1[m])
                        {
                            flag=1;
                            t[n++]=compare1[m];
                            l++;
                            break;
                        }
                        else if(s[i][l] == '&')
                        {
                        	flag = 1;
                        	t[n++]='&';
                        	l++;
                        	break;
						}
						else if(s[i][l]=='|')
						{
							flag = 1;
							t[n++]='|';
							l++;
							break;
						}
                    }
                    if(!flag)
                    {
                        break;
                    }
                }
                t[n]='\0';
                b=l;
                if(!strcmp(t,"/*"))//ע�Ϳ�ʼ
                {
                    zs=1;
                    uu[0]='/';
                    uu[1]='*';
                    uu[2]='\0';
                    printf("  %d: ע�� : %s",i+1,uu);
                    while(zs)
                    {
                    	
                    	if(s[i][b]=='*'&&s[i][b+1]=='/')
                    	{
                    		uu[0]='*';
                            uu[1]='/';
                            uu[2]='\0';
                    		zs = 0;
                    		printf("%s\n",uu);
						}
						else
						{
						printf("%c",s[i][b++]);	
						}
					}
                    j=b+1; 
                }
                else if(!strcmp(t,"//"))
                {
                	zs=1;
					uu[0] = '/';
					uu[1] = '/';
					uu[2] = '\0';
					printf("  %d: ע�� : %s",i+1,uu);
					for(b=l;b<len;b++)
					{
						printf("%c",s[i][b]);
					 } 
					 printf("\n");
					 j = 0;
					 break;
				}
                else
                {
                    flag=1;
                    for(m=0;m<=5;m++)//˫Ŀ�ȽϷ�
                    {
                        if(!strcmp(t,compare2[m]))
                        {
                            tokenlist[tt].token_texttype=gettoken_texttype(t);
                            strcpy(tokenlist[tt].token_textstring,t);
                            tokenlist[tt].linenumber=i+1;
                            printf("  %d: �����ַ� : %s\n",i+1,t);
                            flag=0;
                            tt++;
                            break;
                        }
                    }
                    if(flag)//��Ŀ����
                    {
                        for(m=0;m<n;m++)
                        {
                            linshi[0]=t[m];
                            linshi[1]='\0';
                            tokenlist[tt].token_texttype=gettoken_texttype(linshi);
                            strcpy(tokenlist[tt].token_textstring,linshi);
                            tokenlist[tt].linenumber=i+1;
                            printf("  %d: �����ַ�: %c\n",i+1,t[m]);//һ��һ�����
                            tt++;
                        }
                    }
                    j=l-1;
                }
            }
        }
    }
    tokenlist[tt].linenumber = i;
    tokenlist[tt].token_texttype = END; //////////
    strcpy(tokenlist[tt].token_textstring,"endfile");  /////////////////////
    tt++;
    tttt = tt - 1;
}

TREENODE * program()//�﷨�������ݹ� �½� program�Ŀ�ʼ 
{
    TREENODE * t; //���ɽ�� 
    gettoken_text();  //�õ�token�������� 
    t = declaration_list();  //���� �����б� 
    if(ctoken.token_texttype != END)//һ�κ����ķ������  end 
    {
        printf("��������\n");
        programerror();
    }
    return t;
}

void gettoken_text()//�õ�token_text
{
    ltoken = ctoken;
    ctoken=tokenlist[xb++];
}

void match(Token_texttype toke)//ƥ��
{
    if(ctoken.token_texttype == toke)
    { 
        gettoken_text();
    }
    else
    {  
        printf("ƥ�����\n");
        programerror();
    }
}

void programerror()//�﷨�����������
{
	printf("��%d���﷨��������\n",ctoken.linenumber);
}

TREENODE * NEWNODE(Nodekind kind)//�����½ڵ�
{
    TREENODE * p = (TREENODE *)malloc(sizeof(TREENODE)); //���������̷�����Ĵ洢�ռ�  
    if(p == NULL)                                     
	{
		printf("�����½��ʧ��!\n");                //����ʧ�� 
	}
	else
	{
	    p->child = NULL;                      //���ӳ�ʼΪ�� 
        p->rchilde = NULL;                     //�Һ��ӳ�ʼΪ�� 
        p->linenumber = ctoken.linenumber;        //�����ҽ������� 
        p->NODEkind = kind;                     //������� 
        strcpy(p->NODEstring,ctoken.token_textstring);      //��㴮 
        //printf("����ַ�����%s\n",p->NODEstring);
	}
    return p;
}

TREENODE * declaration_list()//��������б�
{
	//TREEBODE * T; 
	TREENODE * t;
    t = declaration();  
    TREENODE * p;
    p = t;     //��������
	while(ctoken.token_texttype == HONG1||ctoken.token_texttype == HONG2||ctoken.token_texttype == HONG3||ctoken.token_texttype == HONG4||ctoken.token_texttype == HONG5)
	{
		TREENODE * q;
        q = declaration();
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t = q;
                p = q;
            }
            else
            {
                p->rchilde=q;
                p=q;
            }
	}
    } 
    while(ctoken.token_texttype!=INT&&ctoken.token_texttype!=VOID&&ctoken.token_texttype!=END&&ctoken.token_texttype != CHAR&&ctoken.token_texttype != FLOAT&&ctoken.token_texttype != LONG&&ctoken.token_texttype != ID) //endΪ������־�� 
    {
        printf("�����б��������\n");
        programerror();
        gettoken_text();
        if(ctoken.token_texttype==END) //endΪ������ 
        {
            break;
        }
    }
    while(ctoken.token_texttype==INT||ctoken.token_texttype==VOID||ctoken.token_texttype==CHAR||ctoken.token_texttype==FLOAT||ctoken.token_texttype==LONG)
    {
        TREENODE * q;
        q = declaration();
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t = q;
                p = q;
            }
            else
            {
                p->rchilde=q;
                p=q;
            }
        }
    }
    return t;
}

TREENODE * declaration()//��������
{
    TREENODE * t;
    TREENODE * p;
    TREENODE * q;
    TREENODE * s;
    Nodekind c;
    if(ctoken.token_texttype==INT)//����ƥ��
    {
        p = NEWNODE(ints);
        match(INT);
        c = ints;
    }
    else if(ctoken.token_texttype==VOID)
    {
        p=NEWNODE(voids);
        match(VOID);
        c = voids;
    }
     else if(ctoken.token_texttype==LONG)
    {
        p=NEWNODE(longs);
        match(LONG);
        c = longs;
    }
    else if(ctoken.token_texttype == CHAR)
	{
		p = NEWNODE(chars);
		match(CHAR);
		c = chars;
	 } 
	else if(ctoken.token_texttype == FLOAT)
	{
		p =NEWNODE(floats);
		match(FLOAT);
		c = floats;
	}
	else if(ctoken.token_texttype == HONG1||ctoken.token_texttype == HONG2||ctoken.token_texttype == HONG3||ctoken.token_texttype == HONG4||ctoken.token_texttype == HONG5)
	{
		if(ctoken.token_texttype == HONG1)
	    {
		     //printf("#include<stdio.h>\n");
		     p =NEWNODE(hong1);
		     match(HONG1);
		     c = ints;
       	}
	    else if(ctoken.token_texttype == HONG2)
	    {
		     //printf("#include<stdlib.h>\n");
		     p =NEWNODE(hong2);
		     match(HONG2);
		     c = hong2;
	    }
	    else if(ctoken.token_texttype == HONG3)
	    {
		    //printf("#include<string.h>\n");
		    p =NEWNODE(hong3);
		     match(HONG3);
		     c = hong3;
	    }
	    else if(ctoken.token_texttype == HONG4)
    	{
		     //printf("#include<file.h>\n");
		     p =NEWNODE(hong4);
		     match(HONG4);
		     c = hong4;
	    }
	    else if(ctoken.token_texttype == HONG5)
	    {
		     //printf("#include<math.h>\n");
		     p =NEWNODE(hong5);
		     match(HONG5);
		     c = hong5;
	    }
	    t = NEWNODE(hong);
	    t->child = p;
	    return t;
	}
    else
    {
        printf("������������\n");
        programerror();
    }
    if(p!=NULL&&ctoken.token_texttype == ID)
    {
        q=NEWNODE(ids);
        match(ID);
        if(ctoken.token_texttype==LP)//��������
        {
            t=NEWNODE(hanshu);
            t->child = p;
            p->rchilde = q;
            match(LP);
            q->rchilde=function_defs();
            match(RP);
            if(q->rchilde!=NULL)
                (q->rchilde)->rchilde=compound_stmt();
            else
                q->child=compound_stmt();
        }
        else if(ctoken.token_texttype==LMP)//��������
        {
            t=NEWNODE(variable);
            match(LMP);
            TREENODE * m;
            m=NEWNODE(shuzu);
            s=NEWNODE(INT_CONSTS);
            match(INT_CONST);
            t->child=p;
            if(p!=NULL)
                p->rchilde=m;
            m->child=q;
            if(q!=NULL)
                q->rchilde=s;
            match(RMP);
            match(SEMI);
            if(ctoken.token_texttype==RBP)
            match(RBP);
        }
        else if(ctoken.token_texttype==SEMI) //������������ 
        {
            t = NEWNODE(variable);
            t->child=p;
            if(p!=NULL)
                p->rchilde=q;
            match(SEMI);
            if(ctoken.token_texttype==RBP)
            match(RBP);
        }
        else
        {
            printf("declaration error\n");
            programerror();
        }
    }
    else
    {
        printf("�����������\n");
        programerror();
    }
    return t;
}

TREENODE * function_defs()//��������
{
    TREENODE * t;
    t=NEWNODE(hancanlist);
    TREENODE * p;
    p=NULL;//��ʼΪ��
    if(ctoken.token_texttype==VOID)//������void��void id{[]}
    {
        p = NEWNODE(voids);
        match(VOID);
        if(ctoken.token_texttype==RP)//(void)����
        {
            t->child = p;  //����������ţ���ôvoid���������ڲ��Ĳ��� 
        }
        else
        {
            t->child = function_def_list(p);//(void id{[]})����  ���������б� 
        }
    }
    else if(ctoken.token_texttype==INT)//(int id{[]})����
    {
        p = NEWNODE(ints);
        match(INT);
        t->child=function_def_list(p);
    }
    else if(ctoken.token_texttype==CHAR)
    {
        p = NEWNODE(chars);
        match(CHAR);
        t->child=function_def_list(p);
    }
    else if(ctoken.token_texttype==FLOAT)
    {
        p = NEWNODE(floats);
        match(FLOAT);
        t->child = function_def_list(p);
    }
    else if(ctoken.token_texttype==LONG)
    {
        p = NEWNODE(longs);
        match(LONG);
        t->child = function_def_list(p);
    }
    return t;
}

TREENODE * compound_stmt()//�������ݣ��������
{
	TREENODE * t;
	if(ctoken.token_texttype == ELSE)
	{
		 t = statement_list();
		goto end1;
	}
	else if(ctoken.token_texttype==WHILE)
    {
         t = statement_list();
        goto end1;
    }
    else if(ctoken.token_texttype==RETURN)
    {
        t = statement_list();
        goto end1;
    }
    else if(ctoken.token_texttype==BREAK)
    {
    	t = statement_list();
    	goto end1;
	}
    else if(ctoken.token_texttype==CONTINUE)
    {
    	t = statement_list();
    	goto end1;
	}
	else
	{
    t = NEWNODE(fuheyuju);
    if(ctoken.token_texttype == LBP)
    match(LBP);
    t->child=local_declaration();
    if(t->child!=NULL)
       (t->child)->rchilde=statement_list();  //����б� 
    else
        t->child=statement_list();
    while(ctoken.token_texttype == RBP)
    match(RBP);
    return t;
}
    end1: 
    return t;
}

TREENODE * function_def_list(TREENODE * k)//�����б�
{
    TREENODE * t=function_def(k);//ֻ��һ�����ε����
    TREENODE * p=t;
    k=NULL;
    while(ctoken.token_texttype==COMMA)//�������
    {
        TREENODE * q;
        match(COMMA);
        q = function_def(k);
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t = q;
                p = q;
            }
            else
            {
                p->rchilde = q;
                p = q;
            }
        }
    }
    return t;
}

TREENODE * function_def(TREENODE * k)//����
{
    TREENODE * t=NEWNODE(hancan);  //���ɺ���������� 
    TREENODE * p=NULL;//t��child
    TREENODE * q=NULL;//p��rchilde
    if(k == NULL&&ctoken.token_texttype==INT)//���viod ID������
    {
        p = NEWNODE(ints); //������intΪ����������� 
        match(INT);
    }
    else if(k == NULL&&ctoken.token_texttype==CHAR)
    {
    	p = NEWNODE(chars);  
        match(CHAR);
	}
	else if(k == NULL&&ctoken.token_texttype==LONG)
    {
    	p = NEWNODE(longs); 
        match(LONG);
	}
	else if(k == NULL&&ctoken.token_texttype == FLOAT)
	{
     	p = NEWNODE(floats); 
        match(FLOAT);
    }
    else if(k!=NULL)  
    {
        p = k;
    }
    if(p!=NULL)
    {
        t->child=p;
        if(ctoken.token_texttype==ID)
        {
            q=NEWNODE(ids);
            p->rchilde=q;
            match(ID);
        }
        else
        {
            printf("����������������\n");
            programerror();
        }
        if(ctoken.token_texttype==LMP&&q!=NULL)
        {
            match(LMP);
            q->rchilde=NEWNODE(INT_CONSTS);
            match(INT_CONST);
            match(RMP);
        }
        else
        {
            return t;
        }
    }
    else
    {
        printf("����������������\n");
        programerror();
    }
    return t;
} 

TREENODE * local_declaration()//���������ǰ��
{
    TREENODE * t=NULL;
    TREENODE * p=NULL;
    TREENODE * q=NULL;
    TREENODE * q1=NULL;
    TREENODE * q2=NULL;
    TREENODE * q3=NULL;
    TREENODE * q4 =NULL;
    while(ctoken.token_texttype==INT||ctoken.token_texttype==VOID||ctoken.token_texttype==LONG||ctoken.token_texttype==FLOAT||ctoken.token_texttype==CHAR)//�б�������
    {
        q=NEWNODE(variable);//��������
        if(ctoken.token_texttype==INT)//int����
        {
            q1=NEWNODE(ints);
            q->child=q1;
            match(INT);
        }
        else if(ctoken.token_texttype==LONG)//long����
        {
            q1=NEWNODE(longs);
            q->child=q1;
            match(LONG);
        }
        else if(ctoken.token_texttype==CHAR)//char����
        {
            q1=NEWNODE(chars);
            q->child=q1;
            match(CHAR);
        }
        else if(ctoken.token_texttype==FLOAT)//float����
        {
            q1=NEWNODE(floats);
            q->child=q1;
            match(FLOAT);
        }
        else if(ctoken.token_texttype==VOID)//void����
        {
            q1=NEWNODE(voids);
            q->child=q1;
            match(VOID);
        }
        if(q!=NULL&&ctoken.token_texttype==ID)
        {
            q2=NEWNODE(ids);
            q1->rchilde=q2;
           // q1->child=q2;
            match(ID);
            if(ctoken.token_texttype==LMP)
            {
                q3=NEWNODE(shuzu);
                q3->rchilde = q2;
                match(LMP);
                q4 = NEWNODE(INT_CONSTS);
                match(INT_CONST);
                match(RMP);
                q1->rchilde = q3;
                q2->rchilde = q4;
            }
            match(SEMI);
            if(ctoken.token_texttype==RBP)
            match(RBP);
        }
        else
        {
            printf("local_declaration error\n");
            programerror();
        }
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t=q;
				t=q;
            }
            else
            {
                p->rchilde=q;
                p=q;
            }
        }
    }
    return t;
}

TREENODE * statement_list()//������������
{
    TREENODE * t=NULL;
    t=statement();
    TREENODE * p=t;
    while(ctoken.token_texttype==IF||ctoken.token_texttype==LP||
          ctoken.token_texttype==ID||ctoken.token_texttype==WHILE||
          ctoken.token_texttype==RETURN||ctoken.token_texttype==SEMI||
          ctoken.token_texttype==BREAK||ctoken.token_texttype==CONTINUE||
          ctoken.token_texttype==LBP||ctoken.token_texttype==ELSE||ctoken.token_texttype==INT_CONST||ctoken.token_texttype==LONG_CONST||ctoken.token_texttype == FOR)  // �ж��Ƿ�Ϊ��������������� 
    {
        TREENODE * q;
        q = statement();
        if(q!=NULL)
        {
            if(t==NULL)
            {
                t = q;
                p = q; 
            }
            else
            {
                p->rchilde=q;
                p=q;
            }
        }
    }
    return t;
}

TREENODE * statement()//��������������
{
    TREENODE * t=NULL;
     if(ctoken.token_texttype==IF)
    {
        t = if_stmt();
    }
    else if(ctoken.token_texttype==ELSE)
    {
    	t = else_stmt(); 
	}
    else if(ctoken.token_texttype==WHILE)
    {
        t = while_stmt();
    }
    else if(ctoken.token_texttype==RETURN)
    {
        t = return_stmt();
    }
    else if(ctoken.token_texttype==BREAK)
    {
    	t = break_stmt();
	}
    else if(ctoken.token_texttype==CONTINUE)
    {
    	t = continue_stmt();
	}
    else if(ctoken.token_texttype==RBP)
    {
        t = compound_stmt();
    }
    else if(ctoken.token_texttype==ID)
    {
        t = expression_stmt();
    }
    /*else if(ctoken.token_texttype == FOR)
    {
    	t = for_stmt();
	}*/
    else
    {
        printf("statement error\n");
        programerror();
        gettoken_text();
    }
    return t;
}

TREENODE * if_stmt()//if����
{
    TREENODE * t=NEWNODE(ifs);
    match(IF);
    match(LP);
    if(t!=NULL)
    {
        t->child=expression();
    }
    match(RP);
    if(ctoken.token_texttype == LBP)
    {
    	match(LBP);
	}
    if(t->child!=NULL)
        (t->child)->rchilde=statement();
    return t;
}

TREENODE * else_stmt()
{
	   match(ELSE);
        if(ctoken.token_texttype == LBP)
    {
    	match(LBP);
	}
	TREENODE * t = NEWNODE(elses);
	if(t!=NULL)
	{
		t->child=statement();
	}
	return t;
}
TREENODE * while_stmt()//while����
{
    TREENODE * t=NEWNODE(whiles);
    match(WHILE);
    match(LP);
    if(t!=NULL)
    {
        t->child=expression();
    }
    match(RP);
    match(LBP);
    if(t!=NULL)
    {
        (t->child)->rchilde=statement();
    }
    return t;
}

TREENODE * return_stmt()//����ʽ����
{
    TREENODE * t=NEWNODE(returns);
    match(RETURN);
    if(ctoken.token_texttype==SEMI)
    {
        match(SEMI);
        if(ctoken.token_texttype==RBP)
        match(RBP);
        return t;
    }
    else
    {
        if(t!=NULL)
        {
            t->child=expression();
        }
    }
    match(SEMI);
    if(ctoken.token_texttype==RBP)
    match(RBP);
    return t;
}
TREENODE * break_stmt()
{
	TREENODE * t = NEWNODE(breaks);
	match(BREAK);
	if(ctoken.token_texttype==SEMI)
    {
        match(SEMI);
       if(ctoken.token_texttype==RBP)
        match(RBP); 
        return t;
    }
}
TREENODE * continue_stmt()
{
	TREENODE * t = NEWNODE(continues);
	match(CONTINUE);
	if(ctoken.token_texttype==SEMI)
    {
        match(SEMI);
       if(ctoken.token_texttype==RBP)
        match(RBP);
        return t;
    }
}
TREENODE * expression_stmt()//���ʽ����
{
    TREENODE * t=NULL;
    if(ctoken.token_texttype==SEMI)
    {
        match(SEMI);
        if(ctoken.token_texttype==RBP)
        match(RBP);
    }
    else
    {
        t=expression();
        match(SEMI);
        if(ctoken.token_texttype==RBP)
        match(RBP);
    }
    return t;
}

TREENODE * expression()//���ʽ
{
    TREENODE * t=variabler();  //������t��һ�����������Ľ�� 
    if(t == NULL)
    {
        t=simple_expression(t);
    }
    else
    {
        TREENODE * p=NULL;
        if(ctoken.token_texttype == ASSIGN) 
        {
            p=NEWNODE(fuzhi);
            match(ASSIGN); //�ж����������ĸ�ֵ��� 
            p->child=t;
            (p->child)->rchilde=expression();
            return p;
        }
        else
        {
            t=simple_expression(t);
        }
    }
    return t;
}

TREENODE * variabler()//��������
{
    TREENODE * t=NULL;
    TREENODE * p=NULL;
    TREENODE * q=NULL;
    if(ctoken.token_texttype==ID)
    {
        p=NEWNODE(ids); //�½�һ��id��� 
        match(ID);
        if(ctoken.token_texttype==LMP) //����Ķ��� 
        {
            match(LMP);
            if(ctoken.token_texttype==INT_CONST)
			{
				q = NEWNODE(INT_CONSTS);
				match(INT_CONST);
				match(RMP);
				match(SEMI);
			 } 
			else
            q = expression(); //���ʽ��������   ����һ��ʵ�ʵ�ֵ 
            t=NEWNODE(shuzuyuansu);  //����һ������Ԫ�ؽ�� 
            t->child=p; 
            p->rchilde=q;
        }
        else
        {
            t=p;
        }
    }
    return t;
}

TREENODE * simple_expression(TREENODE * k)//�򵥱��ʽ  
{
    TREENODE * t=additive_expression(k);
    k=NULL;
    if(ctoken.token_texttype==LEQ||ctoken.token_texttype==LITTLE||
       ctoken.token_texttype==BIG||ctoken.token_texttype==REQ||
       ctoken.token_texttype==EQ||ctoken.token_texttype==UNEQ)
    {
        TREENODE * q=NEWNODE(yunsuan);
        match(ctoken.token_texttype);
        q->child=t;
        (q->child)->rchilde=additive_expression(k);
        return q;
    }
    return t;
} 

TREENODE * additive_expression(TREENODE * k)//�ӳɵı��ʽ
{
    TREENODE * t=term(k);
    k=NULL;
    while(ctoken.token_texttype==PLUS||ctoken.token_texttype==MINUS)
    {
        TREENODE * q=NEWNODE(yunsuan);
        match(ctoken.token_texttype);
        q->child=t;
        (q->child)->rchilde=term(k);
        t=q;
    }
    return t;
}

TREENODE * term(TREENODE * k)
{
    TREENODE * t=factor(k);
    k=NULL;
    while(ctoken.token_texttype==TIMES||ctoken.token_texttype==DIVISION)
    {
        TREENODE * q=NEWNODE(yunsuan);
        match(ctoken.token_texttype);
        q->child=t;
        (q->child)->rchilde=factor(k);
        t=q;
    }
    return t;
}

TREENODE * factor(TREENODE * k)
{
    TREENODE * t=NULL;
    if(k!=NULL) //kΪ���ݶ�����variable;id  k��NODEstring�Ǳ��� 
    {
        if(ctoken.token_texttype==LP)//call  
        {
            t=call(k);   //�����ǰ��ctoken�����string�����ţ���ô�ж�Ϊ�������� 
        }
        else//variable�����ڱ���
        {
            t=k;        //���Ǻ������� 
        }
    }
    else
    {
        if(ctoken.token_texttype==LP)
        {
            match(LP);
            t=expression();  //�õ�һ������id 
            match(RP);  //ƥ�䵽������ 
        } 
        else if(ctoken.token_texttype==ID)//�����п�����variable��call
        {
            t=variabler();//variable
            if(ctoken.token_texttype==LP)
            {
                t=call(k);
            }
        }
        else if(ctoken.token_texttype == INT_CONST)
        {
            t=NEWNODE(INT_CONSTS);
            match(INT_CONST);
        }
        else if(ctoken.token_texttype == LONG_CONST)
        {
            t=NEWNODE(LONG_CONSTS);
            match(LONG_CONST);
        }
        else
        {
            printf("factor error\n");
            programerror();
            gettoken_text();   //�õ���һ���ڵ�����tokenlist����Ľ�� 
        }
    }
    return t;
}

TREENODE * call(TREENODE * k)//��������
{
    TREENODE * t=NEWNODE(hanshudiaoyong); //��������Ԫ��k���������½��ݹ�õ��� 
    if(k!=NULL)
    {
        t->child=k;  
    }
    match(LP);
    if(ctoken.token_texttype==RP)
    {
        match(RP);
        return t;
    }
    else if(k!=NULL)
    {
        (t->child)->rchilde=function_listformat();
        match(RP);
    }
    return t;
}

TREENODE * function_listformat() //���������б��ʽ 
{
    TREENODE * t=NEWNODE(hanshudiaoyongcanlist);
    TREENODE * p=NULL;
    TREENODE * q=NULL;
    if(ctoken.token_texttype!=RP)
    {
        p=expression();
        q=p;
        while(ctoken.token_texttype==COMMA)
        {
            TREENODE * s;
            match(COMMA);
            s=expression();
            if(q!=NULL)
            {
                if(p==NULL)
                {
                    p=s;
                    q=s;
                }
                else
                {
                    q->rchilde=s;
                    q=s;
                }
            }
        }
    }
    if(p!=NULL)
    {
        t->child=p;
    }
    return t;
}
void printspace(int n)//��ӡ�ո�
{
    int i;
    for(i=0;i<n;i++)
    {
        printf(" ");
    }
}

void printTREE(TREENODE * t)//��ӡ�﷨������ 
{
    while(t !=  NULL)
    {
        printspace(blank);  //��ӡ��ǰ�ո� 
        if(t->NODEkind == hong)
        {
            printf("�궨��\n");
        }
       else if(t->NODEkind == hong1)
        {
            printf("#include<stdio.h>\n");
        }
        else if(t->NODEkind == hong2)
        {
            printf("#include<stdlib.h\n");
        }
        else if(t->NODEkind == hong3)
        {
            printf("#include<string.h>\n");
        }
        else if(t->NODEkind == hong4)
        {
            printf("#include<file.h>\n");
        }
        else if(t->NODEkind == hong5)
        {
            printf("#include<math.h>\n");
        }
        else if(t->NODEkind == ints)
        {
            printf("int\n");
        }
        else if(t->NODEkind == longs)
        {
            printf("long\n");
        }
        else if(t->NODEkind == chars)
		{
			printf("char\n"); 
		} 
		else if(t->NODEkind == floats)
		{
			printf("float\n");
		}
        else if(t->NODEkind==voids)
        {
            printf("void\n");
        }
        else if(t->NODEkind==ids)
        {
            printf("ID:%s\n",t->NODEstring);
        }
        else if(t->NODEkind==INT_CONSTS)
        {
            printf("���ͳ���:%s\n",t->NODEstring);
        }
         else if(t->NODEkind==LONG_CONSTS)
        {
            printf("�����ͳ���:%s\n",t->NODEstring);
        }
        else if(t->NODEkind==variable)
        {
            printf("��ֵ\n");
        }
        else if(t->NODEkind==shuzu)
        {
            printf("��������\n");
        }
        else if(t->NODEkind==hanshu)
        {
            printf("��������\n");
        }
        else if(t->NODEkind==hancanlist)
        {
            printf("���������б�\n");
        }
        else if(t->NODEkind==hancan)
        {
            printf("��������\n");
        }
        else if(t->NODEkind==fuheyuju)
        {
            printf("�������\n");
        }
        else if(t->NODEkind==ifs)
        {
            printf("if\n");
        }
        else if(t->NODEkind==elses)
        {
            printf("else\n");
        }
        else if(t->NODEkind==whiles)
        {
            printf("while\n");
        }
        else if(t->NODEkind==returns)
        {
            printf("return\n");
        }
        else if(t->NODEkind==breaks)
        {
            printf("break\n");
        }
        else if(t->NODEkind==continues)
        {
            printf("continue\n");
        }
        else if(t->NODEkind==fuzhi)
        {
            printf("��ֵ\n");
        }
        else if(t->NODEkind==yunsuan)
        {
            printf("����:%s\n",t->NODEstring);
        }
        else if(t->NODEkind==shuzuyuansu)
        {
            printf("����Ԫ��\n");
        }
        else if(t->NODEkind==hanshudiaoyong)
        {
            printf("��������\n");
        }
        else if(t->NODEkind==hanshudiaoyongcanlist)
        {
            printf("�������ò����б�\n");
        }
        else
        {
            printf("δ֪\n");
        }
        blank++;//�����ո��һ��
        if(t->child!=NULL)
        {
            printTREE(t->child);
        }
        blank--;//�Һ��� 
        t=t->rchilde;
    }
}
int fff = 0;
int flag1 = 0;
int flag2;
int fbp = 0;
char snc[1000][1000];
void savefile(TREENODE * T)//�����ļ��������� 
{
	TREENODE * t;
	 t = T;
	int ll;
	int i;
    while(t !=  NULL)
    {
         
        if(t->NODEkind == hong)
        {
        	goto end;
        }
        else if(t->NODEkind == hong1)
        {
            strcpy(snc[flag1++],"#include<stdio.h>");
            strcpy(snc[flag1++],"#");
            fff++;
        }
        else if(t->NODEkind == hong2)
        {
            strcpy(snc[flag1++],"#include<stdlib.h>");
            strcpy(snc[flag1++],"#");
            fff++;
        }
        else if(t->NODEkind == hong3)
        {
            strcpy(snc[flag1++],"#include<string.h>");
            strcpy(snc[flag1++],"#");
            fff++;
        }
        else if(t->NODEkind == hong4)
        {
            strcpy(snc[flag1++],"#include<file.h>");
            strcpy(snc[flag1++],"#");
            fff++;
        }
        else if(t->NODEkind == hong5)
        {
            strcpy(snc[flag1++],"#include<math.h>");
            strcpy(snc[flag1++],"#");
            fff++;
        }
		else if(t->NODEkind == ints)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
                 strcpy(snc[flag1++],"int ");
                 fff++; 
           
        }
        else if(t->NODEkind == longs)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
                 strcpy(snc[flag1++],"long ");
                 fff++;
            
        }
        else if(t->NODEkind == chars)
		{
			  for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
                 strcpy(snc[flag1++],"char ");
                 fff++;
		} 
		else if(t->NODEkind == floats)
	    {
		  for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
                 strcpy(snc[flag1++],"float ");
                 fff++;
		}
		else if(t->NODEkind==variable)
        {
            goto end; 
        }
        else if(t->NODEkind==shuzu)
        {
            goto end;
        }
        else if(t->NODEkind==hanshu)
        {
            goto end;
        }
        else if(t->NODEkind==hancanlist)
        {
            goto end;
        }
        else if(t->NODEkind==hancan)
        {
           goto end;
        }
        else if(t->NODEkind==fuheyuju)
        {
        	fbp++;
            goto end;
        }    
        else if(t->NODEkind==voids)
        {
            strcpy(snc[flag1++],"void ");
            ll = fff+1;
            for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
            if(!strcmp(tokenlist[ll].token_textstring ,")"))
            {
            	strcpy(snc[flag1++],")");
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	ll++;
            	ll++;
            	fff = ll;
			}
			else
			goto end;
        }
        else if(t->NODEkind==ids)
        {
            if(!strcmp(tokenlist[fff-1].token_textstring ,";"))
            {
            	 for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
			}
			if(!strcmp(tokenlist[fff-1].token_textstring ,"{"))
            {
            	 for(i=0;i<fbp;i++)
        	{;
        		strcpy(snc[flag1++],"   ");
			}
			}
				if(!strcmp(tokenlist[fff-1].token_textstring ,")"))
            {
            	 for(i=0;i<fbp;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
			}
				if(!strcmp(tokenlist[fff-1].token_textstring ,"else"))
            {
            	 for(i=0;i<fbp+1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
			}
            strcpy(snc[flag1++],t->NODEstring);
            fff++;
            if(!strcmp(tokenlist[fff].token_textstring ,";"))
            {
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	fff++;
            	while(!strcmp(tokenlist[fff].token_textstring ,"}"))
            	{
            		for(i=0;i<fbp-1;i++);
            		strcpy(snc[flag1++],"   ");;
            		strcpy(snc[flag1++],"}");
            		strcpy(snc[flag1++],"#");
            		fff++;
            		fbp--;
				}
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,","))
			{
				strcpy(snc[flag1++],",");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"["))
			{
				strcpy(snc[flag1++],"[");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"("))
			{
				strcpy(snc[flag1++],"(");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"="))
			{
				strcpy(snc[flag1++],"=");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"=="))
			{
				strcpy(snc[flag1++],"==");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"+"))
			{
				strcpy(snc[flag1++],"+");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"-"))
			{
				strcpy(snc[flag1++],"-");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"*"))
			{
				strcpy(snc[flag1++],"*");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"/"))
			{
				strcpy(snc[flag1++],"/");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,">"))
			{
				strcpy(snc[flag1++],">");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"<"))
			{
				strcpy(snc[flag1++],"<");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,">="))
			{
				strcpy(snc[flag1++],">=");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"<="))
			{
			strcpy(snc[flag1++],"<=");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,")"))
			{
				strcpy(snc[flag1++],")");
            	fff++;
            	if(!strcmp(tokenlist[fff].token_textstring ,";"))
            	{
            		strcpy(snc[flag1++],";");
            		strcpy(snc[flag1++],"#");
            		fff++;
				}
				else if(!strcmp(tokenlist[fff].token_textstring ,"{"))
				{
					fbp++;
					strcpy(snc[flag1++],"#");
					for(i=0;i<fbp-1;i++)
					strcpy(snc[flag1++],"   ");
					strcpy(snc[flag1++],"{");
					strcpy(snc[flag1++],"#");
            		fff++;
				}
			}
        }
        else if(t->NODEkind==INT_CONSTS)
        {
            strcpy(snc[flag1++],t->NODEstring);
            fff++;
            
            if(!strcmp(tokenlist[fff].token_textstring ,"+"))
            {
            	strcpy(snc[flag1++],"+");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,"-"))
            {
            		strcpy(snc[flag1++],"-");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,"*"))
            {
            	strcpy(snc[flag1++],"*");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,"/"))
            {
            	strcpy(snc[flag1++],"/");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,";"))
            {
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	fff++;
			}
			else if(!strcmp(tokenlist[fff].token_textstring ,"]"))
			{
				strcpy(snc[flag1++],"]");
            	fff++;
            	if(!strcmp(tokenlist[fff].token_textstring ,";"))
            {
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	fff++;
            	while(!strcmp(tokenlist[fff].token_textstring ,"}"))
            	{
            		strcpy(snc[flag1++],"}");
            		strcpy(snc[flag1++],"#");
            		fff++;
            		fbp--;
				}
			}
			}
        }
         else if(t->NODEkind==LONG_CONSTS)
        {
            strcpy(snc[flag1++],t->NODEstring);
            fff++;
            if(!strcmp(tokenlist[fff].token_textstring ,"+"))
            {
            	strcpy(snc[flag1++],"+");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,"-"))
            {
            	strcpy(snc[flag1++],"-");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,"*"))
            {
            	strcpy(snc[flag1++],"*");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,"/"))
            {
            	strcpy(snc[flag1++],"/");
            	fff++;
			}
            else if(!strcmp(tokenlist[fff].token_textstring ,";"))
            {
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	fff++;
			}
        }
        else if(t->NODEkind==ifs)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
            strcpy(snc[flag1++],"if(");
            fff++;
            fff++;
        }
        else if(t->NODEkind==elses)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
             strcpy(snc[flag1++],"else");
             strcpy(snc[flag1++],"#");
            fff++;
            if(!strcmp(tokenlist[fff].token_textstring ,"{"))
            {
            	strcpy(snc[flag1++],"{");
            	strcpy(snc[flag1++],"#");
            	fff++;
            	fbp++;
			}
        }
        else if(t->NODEkind==whiles)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
            strcpy(snc[flag1++],"while");
            strcpy(snc[flag1++],"#");
            fff++;
            if(!strcmp(tokenlist[fff].token_textstring ,"("))
            {
            	strcpy(snc[flag1++],"(");
            	fff++;
			}
        }
        else if(t->NODEkind==returns)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
            strcpy(snc[flag1++],"return ");
            fff++;
            if(!strcmp(tokenlist[fff].token_textstring ,";"))
            {
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	fff++;
            	while(!strcmp(tokenlist[fff].token_textstring ,"}"))
            	{
            		fff++;
            		fbp--;
            		strcpy(snc[flag1++],"}");
            		strcpy(snc[flag1++],"#");
				}
			}
        }
        else if(t->NODEkind==breaks)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
            strcpy(snc[flag1++],"break");
            fff++;
            if(!strcmp(tokenlist[fff].token_textstring ,";"))
            {
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	fff++;
            	while(!strcmp(tokenlist[fff].token_textstring ,"}"))
            	{
            		strcpy(snc[flag1++],"}");
            		strcpy(snc[flag1++],"#");
            		fff++;
            		fbp--;
				}
			}
        }
        else if(t->NODEkind==continues)
        {
        	for(i=0;i<fbp-1;i++)
        	{
        		strcpy(snc[flag1++],"   ");
			}
            strcpy(snc[flag1++],"continue");
            fff++;
            if(!strcmp(tokenlist[fff].token_textstring ,";"))
            {
            	strcpy(snc[flag1++],";");
            	strcpy(snc[flag1++],"#");
            	fff++;
            	while(!strcmp(tokenlist[fff].token_textstring ,"}"))
            	{
            		strcpy(snc[flag1++],"}");
            		strcpy(snc[flag1++],"#");
            		fff++;
            		fbp--;
				}
			}
        }
        else if(t->NODEkind==fuzhi)
        {
            goto end;
        }
        else if(t->NODEkind==yunsuan)
        {
           goto end;
        }
        else if(t->NODEkind==shuzuyuansu)
        {
           goto end;
        }
        else if(t->NODEkind==hanshudiaoyong)
        {
             goto end;
        }
        else if(t->NODEkind==hanshudiaoyongcanlist)
        {
           goto end;
        }
        else
        {
        	goto end;
        }
    end:
        if(t->child!=NULL)
       {
            savefile(t->child);
        }
        t=t->rchilde;
    }
}
void save(FILE * FP)//�����ļ� 
{
	int flag3;
	flag3 = flag1-1;
	int i;
	for(i=0;i<flag3;i++)
	{
	if(!strcmp(snc[i],"#"))
	fputc('\n',FP);
	else
	fprintf(FP,"%s",snc[i]);
}
}
