#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mysql/mysql.h>
#include <stdio_ext.h>

#define STR_SIZE 255
#define BUF_SIZE 1024
#define OPSZ 255
void error_handling(char *message);
int database(int opnum, int opnds[], char oprator);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	char opinfo[BUF_SIZE];
	int result, opnd_cnt, i;
	int recv_cnt, recv_len;	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(serv_sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");	
	clnt_adr_sz=sizeof(clnt_adr);

		opnd_cnt = 1;	
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);	
		read(clnt_sock, &opnd_cnt, 1);
		
		recv_len=0;
		while((opnd_cnt*OPSZ+1)>recv_len)
		{
			recv_cnt=read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1);
			recv_len+=recv_cnt;
		}

		result=database(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
		write(clnt_sock, (char*)&result, sizeof(result));
		close(clnt_sock);

	close(serv_sock);
	return 0;
}

int database(int opnum, int opnds[], char op)
{
	int result=opnds[0], i;
	
	switch(op)
	{
	case '1':
      
	int res;
        char bookName[STR_SIZE];
        char bookAuthor[STR_SIZE];
        char bookLocation[STR_SIZE];
        char InsertValue[STR_SIZE];

        printf("Insert book_name: ");
        fgets(bookName,sizeof(bookName),stdin);
        bookName[strlen(bookName)-1]='\0';

        printf("Insert book_author: ");
        fgets(bookAuthor,sizeof(bookAuthor),stdin);
        bookAuthor[strlen(bookAuthor)-1]='\0';

        printf("Insert book_location: ");
        fgets(bookLocation,sizeof(bookLocation),stdin);
        bookLocation[strlen(bookLocation)-1]='\0';

        mysql_init(&my_connection);
        if(mysql_real_connect(&my_connection, "localhost","root","","bookManagementSystem",0,NULL,0))
        {
                printf("Connection success\n");
                sprintf(InsertValue,"INSERT INTO booklist(book_name,book_author,book_location) values('%s','%s','%s')",bookName,bookAuthor,bookLocation);

                res = mysql_query(&my_connection, InsertValue);

                if(!res){
                        printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(&my_connection));
                }
                else{
                        fprintf(stderr, "Insert error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
                }

                mysql_close(&my_connection);
                }
                else{
                        fprintf(stderr, "Connection failed\n");
                        if(mysql_errno(&my_connection)){
                        fprintf(stderr, "Connection error %d: %s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
                }
        }
        return EXIT_SUCCESS;
	
	case '2':
		for(i=1; i<opnum; i++) result-=opnds[i];
		break;
	case '3':
		for(i=1; i<opnum; i++) result*=opnds[i];
		break;
	}
	return result;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
