/* Simple C program that connects to MySQL Database server*/
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int login( char *xinput, char * yinput , char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row, int userid )
{
	
	printf("Login(user id): ");

	scanf("%d", &userid); // input user id 
	//fgets(xinput, 200, stdin);
	
	printf("Password: "); 
	
	scanf("%s",yinput); // input password 
	//fgets(yinput, 200, stdin);
	sprintf(Query,"%s%d%s%s%s", "SELECT * FROM account WHERE uid=",userid," AND password='",yinput,"'"); // input query
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s\n", row[0], row[1]); 

	printf("login successfully!\nUser %d welcome back!\n", userid);
	return userid;

}

void adduser(char *xinput, char * yinput , char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row, int userid)
{

	char addinput[200];
	
	printf("Your user id will be auto assign\n please enter password\n");
	scanf("%s",xinput);
	//fgets(xinput, 200, stdin);
	sprintf(Query, "%s%s%s", "INSERT INTO account(password) values ('",xinput,"')");
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	int id = mysql_insert_id(conn);
	printf("%d\n",id);

	/*sprintf(Query,"%s%s%s", "SELECT * FROM account WHERE password='",xinput,"' ORDER BY uid DESC");
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s\n", row[0], row[1]); 
	*/ // for checking if account is create in account table 
	printf("Enter first name:\n");
	scanf("%s",xinput);
	//fgets(xinput,200,stdin);
	printf("Enter last name:\n");
	scanf("%s",yinput);
	//fgets(yinput,200,stdin);
	printf("Enter location: example: lexington, ky please have space after comma\n"); // there will be error if have space after comma should be some type of buffer overflow 
	scanf("%s",addinput);
	//fgets(addinput,200,stdin);

	sprintf(Query,"%s%d%s%s%s%s%s%s%s", "INSERT INTO flitters(uid,fname,lname,location) values (",id,",'", xinput,"','",yinput,"','" ,addinput,"')");
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	sprintf(Query,"%s%d%s", "SELECT * FROM flitters WHERE uid='",id,"'");
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s %s %s\n", row[0], row[1], row[2], row[3]); 
	int ch;
		
	while ((ch = getchar()) != '\n' && ch != EOF);
	userid=id;
	printf("now, please login using your user id and password\n");


}
void fleet(char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row, int userid)
{

	//printf("please enter your fleet!\n");
	//scanf("%*[\n]",zinput);
	
	char zinput[200];
	
  
  	printf ("Please enter your fleet: ");
  
  		if (fgets(zinput, sizeof(zinput), stdin))
  		{
    		printf ("You entered: %s", zinput);
  		}
  	int i;
	for (i = 0; zinput[i] != '\0'; i++); /* getting the string size */
	
	zinput[i-1] = '\0'; /* removing the newline */
		
	sprintf(Query,"%s%s%s%d%s", "INSERT INTO fleets(post,uid) values ('",zinput,"',", userid,")");
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	sprintf(Query,"%s%d%s", "SELECT * FROM fleets WHERE uid='",userid,"'");
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s %s\n", row[0], row[1], row[2]);

}
void search(char *option, char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row )
{	
	char zinput [200];
	printf("please input the search %s:", option);
	scanf("%s", zinput);
	sprintf(Query,"%s%s%s%s%s", "select * from flitters where ", option, "= '", zinput, "'" ); // input query
	printf("you have follow below people:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s %s\n", row[0], row[1], row[2]); 

}
void follow(char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row, int userid)
{
	int lopinput;
	char *qfname= "fname";
	char *qlname= "lname";
	char *qloca= "location";
	sprintf(Query,"%s", "SELECT * FROM flitters "); // input query
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s\n", row[0], row[1]);
	
	do{
		printf("choose your search option: \n1.first name\n2.last name\n3.location\n0.exit search\n"); // first screen option
		scanf("%d", &lopinput);
		switch(lopinput)
		{
			case 1:
				search(qfname, Query, conn, res, row);// firstname
				break;
			case 2:
				search(qlname, Query, conn, res, row);// lastname
				break;
			case 3:
				search(qloca, Query, conn, res, row);//location
				default: printf("Search finish\n");
					break;
		}
	}while (lopinput !=0);



	int id;
	printf("please type in who you want to follow:\n");
	scanf("%d",&id );
	sprintf(Query,"%s%d%s%d%s", "INSERT INTO follows(head,follower) values (",id,",",userid,")"); // input query
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	sprintf(Query,"%s%d%s", "select uid, fname, lname from flitters natural join follows where follows.head = flitters.uid and follows.follower =",userid, " group by head "); // input query
	printf("you have follow below people:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s %s\n", row[0], row[1], row[2]); 

}

void showfleets(char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row, int userid)
{
	printf("please type in the last X number of fleets you want to see\n");
	printf("Format like: X Y Z where Last X number of fleets and Y is the offect as starting point\nX default is 25 and Y is 0\nAddiontally, if you want to see every user you follow Z has to be 1\n");
	int k; // x 
	int l; // y
	int j; // z 
	scanf("%d %d %d", &k,&l,&j);
	if (k==0){k=25;}

	if (j==0)


	sprintf(Query,"%s%d%s%d%s%d%s", "select uid, post from fleets natural join follows where fleets.uid=follows.head and follows.follower =" ,userid, " Order by pid desc limit ", l," ,", k, ""); // input query
	//printf("you have follow below people:\n");
	//printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("The fleet you request:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s\n", row[0], row[1]); 
}

void unfollow(char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row, int userid)
{
	int id;
	printf("Please enter the user id you want to unfollow\n" );
	scanf("%d",&id );
	sprintf(Query,"%s%d%s%d%s", "DELETE FROM follows where follower=",userid," and head =" , id,""); // input query
	printf("Check this out:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	sprintf(Query,"%s%d%s", "select uid, fname, lname from flitters natural join follows where follows.head = flitters.uid and follows.follower =",userid, " group by head "); // input query
	printf("you have follow below people:\n");
	printf("[%s]\n",Query); // print out the query that has input
	if (mysql_query(conn, Query)) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Results:\n"); // print out the result
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s %s\n", row[0], row[1], row[2]); 
}

void refleet(char * Query, MYSQL *conn, MYSQL_RES *res, MYSQL_ROW row, int userid)
{
	showfleets(Query, conn, res, row, userid);

}

// has to set the server name, username, password and database first

int main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = ""; // server name
	char *user = ""; // username
	char *password = ""; /* password*/
	char *database = ""; // database
	char Query[400];
	char xinput[200];
	char yinput[200];
	int opinput;
	int userid;
	
	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn,server,user,password,database,0,NULL,0)) {
		fprintf(stderr, "%s\n",
		mysql_error(conn));
		exit(1);
	}

	/* send SQL query */
	if (mysql_query(conn, "show tables")) { 
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	/* output
	 * table
	 * name
	 * */
	printf("MySQL Tables in mysql database:\n");
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s \n", row[0]); 
	/* close
	 * connection
	 * */


	do{
		printf("choose your option: \n1.Login\n2.Create user\n"); // first screen option
		scanf("%d", &opinput);
		int ch;
		
		while ((ch = getchar()) != '\n' && ch != EOF);
		switch(opinput)
		{
			case 1:userid=login(xinput, yinput, Query, conn, res, row, userid);
				if (userid>0)opinput=0;
				break;
			case 2:adduser(xinput, yinput, Query, conn, res, row, userid);
				break;
			case 3: exit(1);
				default: printf("wrong input. Enter again\n");
					break;
		}
	}while (opinput !=0);

	do{
		printf("User %d You have login successfully! choose your option:\n1.fleet\n2.follow\n3.show fleets\n4.unfollow\n6.exit\n", userid);
		scanf("%d",&opinput);
		int ch;
		
		while ((ch = getchar()) != '\n' && ch != EOF);
		
		switch(opinput)
		{
			case 1:fleet(Query, conn, res, row, userid);
				break;
			case 2:follow(Query, conn, res, row, userid);
				break;
			case 3:showfleets(Query, conn, res, row, userid);
				break;
			case 4:unfollow(Query, conn, res, row, userid);
				break;
			case 5:refleet(Query, conn, res, row, userid);
				break;
			case 6:return(0);
				break;
				default: printf("wrong input. Enter again\n");
					break;
		}

	}while (opinput !=5);



	

	mysql_free_result(res);
	mysql_close(conn);
}
