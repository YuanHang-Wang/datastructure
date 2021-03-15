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
#define QMAXSIZE 5 //队列大小 
typedef int status;  //数据元素类型定义
typedef char TElemType;//定义字符型常量 
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
}NODEkind;//节点种类

typedef enum Expressiontype
{
    Void,
    Int,
	Char,
	Float 
}expressiontype;//表达式种类

typedef struct TREENODE//树节点结构体孩子表示法 
{
    TREENODE * child;//左子节点
    TREENODE * rchilde;//右子节点
    int linenumber;//所在行
    Nodekind NODEkind;//节点类型
    char NODEstring[1100];//节点类型所代表的字符串，用于语法树打印
}TREENODE,*tokenTREE;

typedef struct token_text//token结构体
{
    Token_texttype token_texttype;//token类型
    char token_textstring[1100];//token串
    int linenumber;//token行号
}Token;
Token_texttype gettoken_texttype(char c[]);
void scan(); //扫描，词法识别 
char s[1005][1005];//文本
char p[1005][1005];//临时替换数组 
char t[1005];//当前token_text串
char tk[1005];  
char linshi[1100];//临时数组
int line; //文本行数 
int zs; //注释标记 
int tttt;  //标记，结构数组个数 
Token tokenlist[1000];    //token表声明 
Token ctoken;//当前token
Token ltoken;//上一个token
int xb=0;//token下标
int blank=0;//先行空格	
void gettoken_text();//得到token
void programerror();//输出错误
void match(Token_texttype toke);//匹配
TREENODE * compound_stmt();//函数声明
void printspace(int n);//打印空格
void printTREE(TREENODE * t);//打印语法分析树
TREENODE * NEWNODE(Nodekind kind);//创建新节点
TREENODE * function_listformat();//函数参数列表格式 
TREENODE * call(TREENODE * k);//函数调用
TREENODE * factor(TREENODE * k); //带括号的表达式 
TREENODE * term(TREENODE * k);  //乘除表达式 
TREENODE * additive_expression(TREENODE * k);//加成的表达式
TREENODE * simple_expression(TREENODE * k);//简单表达式
TREENODE * variabler(); //变量声明 
TREENODE * expression();  //表达式声明 
TREENODE * expression_stmt();//表达式声明
TREENODE * return_stmt();//返回式声明
TREENODE * continue_stmt();//continue声明 
TREENODE * break_stmt();//break声明 
TREENODE * while_stmt();//while声明
TREENODE * if_stmt();//if声明
TREENODE * else_stmt();//else声明 
TREENODE * statement();//复合语句后者种类
TREENODE * statement_list();//复合语句体后者
TREENODE * local_declaration();//复合语句体前者
TREENODE * function_def(TREENODE * k);//函参
TREENODE * function_def_list(TREENODE * k);//函参列表
TREENODE * compound_stmt();//函数内容，复合语句
TREENODE * function_defs();//函数参数
TREENODE * declaration();//函数声明
TREENODE * declaration_list();//多个函数列表
TREENODE * program();//语法分析
void savefile(TREENODE * T);//,FILE *FP);//保存文件 
void save(FILE * FP);
int main()
{
	/*FILE *FP; 
	int i = 0,j = 0;
	char w,c;
	 printf("请输入将要读取的文件名，以.txt结尾：\n");
	char file[30];
	scanf("%s",file);
	if ((FP=fopen(file,"rb")) == NULL)
	    printf("File open error\n ");
	else
	    printf("文件读取成功\n");
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
    printf("请输入一段代码，回车之后ctrl+z结束：\n");
	int i=0;
	int change; 
	line=0;
    while(gets(s[line++]))
    {}
    printf("单词识别 :\n");
    scan();
   // zhushi();
    printf("\n语法分析 :\n");
    TREENODE *t = program(); //生成ast树头结点 
    TREENODE *p;
	p = t; 
	printf("输入数值：");
	scanf("%d",&change);
	getchar();
	if(change == 1)
    printTREE(t);          //打印ast语法树 
    else if(change == 2)
    {
	FILE *FP;
    printf("请输入文件名称：\n");
    char file[30];
	scanf("%s",file);
	if ((FP=fopen(file,"w")) == NULL)
	printf("文件打开失败\n ");
	else
	printf("文件打开成功\n"); 
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
	int tt = 0;//tokenlist的下标 
    int i,j,m,l,n,b,d;//下标
    int f,flag;//标记
    int len;//当前行长度
    char keywords[50][20]={ "char", "continue","break",
                                "else","for", "float","if","while",
                                "int","long","double","case",
                                "return","void","continue", "struct",
                                "switch","default"};//关键字
    char headfile[50][30]={ "#include<stdio.h>","#include<stdlib.h>","#include<string.h>","#includ<file.h>","#include<math.h>"};
    char compare2[10][1005]={"<=",">=","==","!=","--","++","&&","||"};//双目比较符
    char compare1[1005]={'+','-','*','/','>','<','=',';',':',',','(','%',')','[',']','{','}','!'};//单目符号
    //zs=0;注释判断标志 
    for(i=0;i<line-1;i++)
    {
        len = strlen(s[i]);
        printf("%d: ",i+1);
        printf("%s\n",s[i]);
        if(len==0)//空行
        {
            continue;
        }
        for(j=0;j<len;j++)
        {
         
            if(s[i][j]==' ')//空格
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
					printf("  %d: 宏定义: %s\n",i+1,tk);
                        tokenlist[tt].token_texttype = gettoken_texttype(tk);
                        strcpy(tokenlist[tt].token_textstring,tk);
                        tokenlist[tt].linenumber=i+1;
                        tt++;
                        j = l-1;
                        break;}
				}
			} 
			 else if(s[i][j]<='9'&&s[i][j]>='0')//数字
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
                	printf("  %d:  长整型数字 = %s\n",i+1,t);
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
                printf("  %d:  整型数字 = %s\n",i+1,t);
                strcpy(linshi,"INT_CONST1");
                tokenlist[tt].token_texttype = gettoken_texttype(linshi);
                strcpy(tokenlist[tt].token_textstring,t);
                tokenlist[tt].linenumber=i+1;
                tt++;
                j=l-1;
                }
            }
            else if((s[i][j]<='z'&&s[i][j]>='a')||(s[i][j]<='Z'&&s[i][j]>='A'))//字母
            {
                l=j;
                m=0;
                while((s[i][l]<='z'&&s[i][l]>='a')||(s[i][l]<='Z'&&s[i][l]>='A'))
                {
                    t[m++]=s[i][l++];
                }
                t[m]='\0';
                f=1;//标记
                for(n = 0;n < 20;n++)
                {
                	
                    if(!strcmp(t,keywords[n]))
                    {
                        f=0;
                        printf("  %d: 关键字: %s\n",i+1,t);
                        tokenlist[tt].token_texttype = gettoken_texttype(t);
                        strcpy(tokenlist[tt].token_textstring,t);
                        tokenlist[tt].linenumber=i+1;
                        tt++;
                        break;
                    }
                }
                if(f)
                {
                    printf("  %d: ID 名称= %s\n",i+1,t);
                    strcpy(linshi,"ID");
                    tokenlist[tt].token_texttype = gettoken_texttype(linshi);
                    strcpy(tokenlist[tt].token_textstring,t);
                    tokenlist[tt].linenumber=i+1;
                    tt++;
                }
                j=l-1;
            }
            else//符号
            {
                l=j;
                n=0;
                while(1)
                {
                    flag=0;//标记
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
                if(!strcmp(t,"/*"))//注释开始
                {
                    zs=1;
                    uu[0]='/';
                    uu[1]='*';
                    uu[2]='\0';
                    printf("  %d: 注释 : %s",i+1,uu);
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
					printf("  %d: 注释 : %s",i+1,uu);
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
                    for(m=0;m<=5;m++)//双目比较符
                    {
                        if(!strcmp(t,compare2[m]))
                        {
                            tokenlist[tt].token_texttype=gettoken_texttype(t);
                            strcpy(tokenlist[tt].token_textstring,t);
                            tokenlist[tt].linenumber=i+1;
                            printf("  %d: 特殊字符 : %s\n",i+1,t);
                            flag=0;
                            tt++;
                            break;
                        }
                    }
                    if(flag)//单目符号
                    {
                        for(m=0;m<n;m++)
                        {
                            linshi[0]=t[m];
                            linshi[1]='\0';
                            tokenlist[tt].token_texttype=gettoken_texttype(linshi);
                            strcpy(tokenlist[tt].token_textstring,linshi);
                            tokenlist[tt].linenumber=i+1;
                            printf("  %d: 特殊字符: %c\n",i+1,t[m]);//一个一个输出
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

TREENODE * program()//语法分析，递归 下降 program的开始 
{
    TREENODE * t; //生成结点 
    gettoken_text();  //得到token结点的数据 
    t = declaration_list();  //分析 函数列表 
    if(ctoken.token_texttype != END)//一段函数的分析完成  end 
    {
        printf("分析错误！\n");
        programerror();
    }
    return t;
}

void gettoken_text()//得到token_text
{
    ltoken = ctoken;
    ctoken=tokenlist[xb++];
}

void match(Token_texttype toke)//匹配
{
    if(ctoken.token_texttype == toke)
    { 
        gettoken_text();
    }
    else
    {  
        printf("匹配错误\n");
        programerror();
    }
}

void programerror()//语法程序分析错误
{
	printf("第%d行语法分析错误\n",ctoken.linenumber);
}

TREENODE * NEWNODE(Nodekind kind)//创建新节点
{
    TREENODE * p = (TREENODE *)malloc(sizeof(TREENODE)); //创建结点过程分配结点的存储空间  
    if(p == NULL)                                     
	{
		printf("创建新结点失败!\n");                //创建失败 
	}
	else
	{
	    p->child = NULL;                      //孩子初始为空 
        p->rchilde = NULL;                     //右孩子初始为空 
        p->linenumber = ctoken.linenumber;        //行数右结点的行数 
        p->NODEkind = kind;                     //结点类型 
        strcpy(p->NODEstring,ctoken.token_textstring);      //结点串 
        //printf("结点字符串：%s\n",p->NODEstring);
	}
    return p;
}

TREENODE * declaration_list()//多个函数列表
{
	//TREEBODE * T; 
	TREENODE * t;
    t = declaration();  
    TREENODE * p;
    p = t;     //后面有用
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
    while(ctoken.token_texttype!=INT&&ctoken.token_texttype!=VOID&&ctoken.token_texttype!=END&&ctoken.token_texttype != CHAR&&ctoken.token_texttype != FLOAT&&ctoken.token_texttype != LONG&&ctoken.token_texttype != ID) //end为结束标志符 
    {
        printf("函数列表分析错误\n");
        programerror();
        gettoken_text();
        if(ctoken.token_texttype==END) //end为结束符 
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

TREENODE * declaration()//函数声明
{
    TREENODE * t;
    TREENODE * p;
    TREENODE * q;
    TREENODE * s;
    Nodekind c;
    if(ctoken.token_texttype==INT)//类型匹配
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
        printf("函数声明错误\n");
        programerror();
    }
    if(p!=NULL&&ctoken.token_texttype == ID)
    {
        q=NEWNODE(ids);
        match(ID);
        if(ctoken.token_texttype==LP)//函数声明
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
        else if(ctoken.token_texttype==LMP)//数组声明
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
        else if(ctoken.token_texttype==SEMI) //变量定义声明 
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
        printf("函数定义错误\n");
        programerror();
    }
    return t;
}

TREENODE * function_defs()//函数参数
{
    TREENODE * t;
    t=NEWNODE(hancanlist);
    TREENODE * p;
    p=NULL;//初始为空
    if(ctoken.token_texttype==VOID)//函参是void或void id{[]}
    {
        p = NEWNODE(voids);
        match(VOID);
        if(ctoken.token_texttype==RP)//(void)类型
        {
            t->child = p;  //如果是右括号，那么void就是括号内部的参数 
        }
        else
        {
            t->child = function_def_list(p);//(void id{[]})类型  函数参数列表 
        }
    }
    else if(ctoken.token_texttype==INT)//(int id{[]})类型
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

TREENODE * compound_stmt()//函数内容，复合语句
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
       (t->child)->rchilde=statement_list();  //语句列表 
    else
        t->child=statement_list();
    while(ctoken.token_texttype == RBP)
    match(RBP);
    return t;
}
    end1: 
    return t;
}

TREENODE * function_def_list(TREENODE * k)//函参列表
{
    TREENODE * t=function_def(k);//只有一个函参的情况
    TREENODE * p=t;
    k=NULL;
    while(ctoken.token_texttype==COMMA)//多个函参
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

TREENODE * function_def(TREENODE * k)//函参
{
    TREENODE * t=NEWNODE(hancan);  //生成函数参数结点 
    TREENODE * p=NULL;//t的child
    TREENODE * q=NULL;//p的rchilde
    if(k == NULL&&ctoken.token_texttype==INT)//解决viod ID的问题
    {
        p = NEWNODE(ints); //生成以int为根结点的树结点 
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
            printf("函数参数分析错误\n");
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
        printf("函数参数分析错误\n");
        programerror();
    }
    return t;
} 

TREENODE * local_declaration()//复合语句体前者
{
    TREENODE * t=NULL;
    TREENODE * p=NULL;
    TREENODE * q=NULL;
    TREENODE * q1=NULL;
    TREENODE * q2=NULL;
    TREENODE * q3=NULL;
    TREENODE * q4 =NULL;
    while(ctoken.token_texttype==INT||ctoken.token_texttype==VOID||ctoken.token_texttype==LONG||ctoken.token_texttype==FLOAT||ctoken.token_texttype==CHAR)//有变量声明
    {
        q=NEWNODE(variable);//变量声明
        if(ctoken.token_texttype==INT)//int声明
        {
            q1=NEWNODE(ints);
            q->child=q1;
            match(INT);
        }
        else if(ctoken.token_texttype==LONG)//long声明
        {
            q1=NEWNODE(longs);
            q->child=q1;
            match(LONG);
        }
        else if(ctoken.token_texttype==CHAR)//char声明
        {
            q1=NEWNODE(chars);
            q->child=q1;
            match(CHAR);
        }
        else if(ctoken.token_texttype==FLOAT)//float声明
        {
            q1=NEWNODE(floats);
            q->child=q1;
            match(FLOAT);
        }
        else if(ctoken.token_texttype==VOID)//void声明
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

TREENODE * statement_list()//复合语句体后者
{
    TREENODE * t=NULL;
    t=statement();
    TREENODE * p=t;
    while(ctoken.token_texttype==IF||ctoken.token_texttype==LP||
          ctoken.token_texttype==ID||ctoken.token_texttype==WHILE||
          ctoken.token_texttype==RETURN||ctoken.token_texttype==SEMI||
          ctoken.token_texttype==BREAK||ctoken.token_texttype==CONTINUE||
          ctoken.token_texttype==LBP||ctoken.token_texttype==ELSE||ctoken.token_texttype==INT_CONST||ctoken.token_texttype==LONG_CONST||ctoken.token_texttype == FOR)  // 判断是否为复合语句和条件语句 
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

TREENODE * statement()//复合语句后者种类
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

TREENODE * if_stmt()//if声明
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
TREENODE * while_stmt()//while声明
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

TREENODE * return_stmt()//返回式声明
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
TREENODE * expression_stmt()//表达式声明
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

TREENODE * expression()//表达式
{
    TREENODE * t=variabler();  //定义结点t是一个变量声明的结点 
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
            match(ASSIGN); //判断条件语句里的赋值语句 
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

TREENODE * variabler()//变量声明
{
    TREENODE * t=NULL;
    TREENODE * p=NULL;
    TREENODE * q=NULL;
    if(ctoken.token_texttype==ID)
    {
        p=NEWNODE(ids); //新建一个id结点 
        match(ID);
        if(ctoken.token_texttype==LMP) //数组的定义 
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
            q = expression(); //表达式函数调用   赋给一个实际的值 
            t=NEWNODE(shuzuyuansu);  //生成一个数组元素结点 
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

TREENODE * simple_expression(TREENODE * k)//简单表达式  
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

TREENODE * additive_expression(TREENODE * k)//加成的表达式
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
    if(k!=NULL) //k为传递而来的variable;id  k的NODEstring是变量 
    {
        if(ctoken.token_texttype==LP)//call  
        {
            t=call(k);   //如果当前的ctoken里面的string是括号，那么判定为函数调用 
        }
        else//variable，等于本身
        {
            t=k;        //不是函数调用 
        }
    }
    else
    {
        if(ctoken.token_texttype==LP)
        {
            match(LP);
            t=expression();  //得到一个变量id 
            match(RP);  //匹配到右括号 
        } 
        else if(ctoken.token_texttype==ID)//还是有可能是variable或call
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
            gettoken_text();   //得到下一个节点数组tokenlist里面的结点 
        }
    }
    return t;
}

TREENODE * call(TREENODE * k)//函数调用
{
    TREENODE * t=NEWNODE(hanshudiaoyong); //函数调用元素k，从上面下降递归得到的 
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

TREENODE * function_listformat() //函数参数列表格式 
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
void printspace(int n)//打印空格
{
    int i;
    for(i=0;i<n;i++)
    {
        printf(" ");
    }
}

void printTREE(TREENODE * t)//打印语法分析树 
{
    while(t !=  NULL)
    {
        printspace(blank);  //打印行前空格 
        if(t->NODEkind == hong)
        {
            printf("宏定义\n");
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
            printf("整型常数:%s\n",t->NODEstring);
        }
         else if(t->NODEkind==LONG_CONSTS)
        {
            printf("长整型常数:%s\n",t->NODEstring);
        }
        else if(t->NODEkind==variable)
        {
            printf("赋值\n");
        }
        else if(t->NODEkind==shuzu)
        {
            printf("数组声明\n");
        }
        else if(t->NODEkind==hanshu)
        {
            printf("函数声明\n");
        }
        else if(t->NODEkind==hancanlist)
        {
            printf("函数参数列表\n");
        }
        else if(t->NODEkind==hancan)
        {
            printf("函数参数\n");
        }
        else if(t->NODEkind==fuheyuju)
        {
            printf("复合语句\n");
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
            printf("赋值\n");
        }
        else if(t->NODEkind==yunsuan)
        {
            printf("运算:%s\n",t->NODEstring);
        }
        else if(t->NODEkind==shuzuyuansu)
        {
            printf("数组元素\n");
        }
        else if(t->NODEkind==hanshudiaoyong)
        {
            printf("函数调用\n");
        }
        else if(t->NODEkind==hanshudiaoyongcanlist)
        {
            printf("函数调用参数列表\n");
        }
        else
        {
            printf("未知\n");
        }
        blank++;//子树空格多一个
        if(t->child!=NULL)
        {
            printTREE(t->child);
        }
        blank--;//右孩子 
        t=t->rchilde;
    }
}
int fff = 0;
int flag1 = 0;
int flag2;
int fbp = 0;
char snc[1000][1000];
void savefile(TREENODE * T)//保存文件辅助函数 
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
void save(FILE * FP)//保存文件 
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
