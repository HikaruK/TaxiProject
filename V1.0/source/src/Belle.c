#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "Route.h"

#define DDEBUG;

int searchword(char *text, char *word);

int searchindex(char *word);

char* FullStreetName(char* a);
int source,des;


char* Belle(char* string)
{

printf("\nreceived message in belle is %s\n", string);

char *comp=NULL;
char *word=NULL;
char *word2=NULL;
char *a=NULL;
char *b=NULL;
char *c=NULL;
char *d=NULL;
/* Word Bank*/
char str2[]=" do what how when who where why wen ";
char negative[]=" no don't cancel not nevermind bu ";
char confirm[]=" CONFIRM yes yea okay sure good confirm perfect hoa ";
char greetings[]=" hey hi hello morning greetings ";
char demand[]=" want get xiang ";
char taxi[]=" Taxi1 Taxi2 Taxi3 Taxi3 Taxi4 Taxi5 Taxi6 Taxi7 Taxi8 Taxi9 Taxi10 ";

Map map;
TaxiStandList *list = MakeTaxiStandList();
map = Reader(map, list);

/* make taxi */
int totalTaxis = list->totalTaxis; 
Taxi *taxis = malloc(totalTaxis*sizeof(Taxi));
Taxi *fleet = MakeTaxiFleet(map.list, taxis);

/* make landmark */
/*	LandmarkList *landmarklist = MakeLandmarkList();*/
	

#ifdef jdjd
printf("%s", map.x_names);
printf("\n");
printf("%s", map.y_names);
#endif
printf("%d",map.l_index);

int cnt,leng,count,question, index_a,index_b,index_c,index_d;

index_a=0;
index_b=0;
index_c=0;
index_d=0;
cnt=0;
count=0;
question =0;

char str[100]={0};

/*printf("\nEnter Command : ");*/
/*scanf("%[^\n]s", str);*/
leng=strlen(str);

char reply[256]="Belle: ";
char *send = malloc(sizeof(char)*256);

printf("\nbreakpoint\n");

comp = strtok(string," ");
while (comp != NULL) {
	
	if (searchword(str2, comp)) {
        /* Match found */
	#ifdef DDEBUG
        printf("Question word found: %s\n", comp);
	#endif
	
	sleep(2);	
	char re[29]="That's a very good question, ";
	strcat(reply,re);
        count =1;
	}	
	if(searchword(map.l_names,comp))
	{
		if(*(comp-3)=='t'||*(comp-4)=='d'||*(comp-3)=='T')
        	{
        	c=comp;
		d=comp;
        	strcat(reply," So you want to go to ");
        	strcat(reply,comp);

        	count =1;
        	}
		if(*(comp-5)=='f'||*(comp-5)=='c'||*(comp-13)=='R')
        	{
        	a=comp;
		b=comp;
        	strcat(reply," I assume you are at ");
        	strcat(reply,comp);

        	count =1;
		}

	
		
	}
	if (searchword(map.x_names, comp)||searchword(map.y_names, comp))
	{
	if(*(comp-4)=='a')
	{
		if((a!=NULL&&c==NULL)||(a!=NULL&&c!=NULL&&d!=NULL&&b==NULL))
		{
			b=comp;
			
			strcat(reply," and ");
			strcat(reply,comp);
			
		}
		if((c!=NULL&&a==NULL)||(a!=NULL&&c!=NULL&&b!=NULL&&d==NULL))
		{
			d=comp;
		
                        strcat(reply," and ");
			strcat(reply,comp);
                        
		}	
	
	}	
	if((*(comp-3)=='t'||*(comp-4)=='d'||*(comp-3)=='T')&&c==NULL)
	{
	c=comp;
	
	strcat(reply," So you want to go to "); 
	strcat(reply,comp);
	
	count =1;
	}
	if((*(comp-7)=='C'||*(comp-5)=='f'||*(comp-5)=='c'||*(comp-13)=='R')&&a==NULL)
	{
	a=comp;

	strcat(reply," I assume you are at ");
        strcat(reply,a);

	count =1;

	}
	if(a==NULL&&c==NULL&&b==NULL&&d==NULL)
	{
	strcat(reply," Sorry to be clear can you say from where to where? Thanks. ");
	count=1;
	}
	if(a!=NULL&&c!=NULL&&b!=NULL&&d!=NULL)
	{
	char a2,b2,c2,d2;
a2=a;
b2=b;
c2=c;
d2=d;
	/*FIND FULL STREET NAME*/
	char * pch;
	pch = strtok (map.x_names,",.-");
	while (pch != NULL)
  {
if(strstr(pch,a))
{
        printf ("%s\n",pch);
	a=pch;
}
    pch = strtok (NULL, ",.-");
  }
pch = strtok (map.y_names,",.-");
        while (pch != NULL)
  {
if(strstr(pch,a))
{
        printf ("%s\n",pch);
        a=pch;
}
    pch = strtok (NULL, ",.-");
  }  
b=FullStreetName(b);
c=FullStreetName(c);
d=FullStreetName(d);
	/*END FIND FULL STREET NAME*/
	char client_input[100]="REQUEST_TAXI";
	if(a2!=b2){
	strcat(client_input, " CORNER");
	strcat(client_input, a);
	strcat(client_input," AND");
	strcat(client_input, b);
	}else{
	strcat(client_input, a);
	}
	strcat(client_input, " TO");
	if(c2!=d2){
	strcat(client_input, c);
	strcat(client_input," AND");
	strcat(client_input, d);
	}else{
	strcat(client_input, c);
	}
	printf("\n %s \n",client_input);	
	
	/*INDEX SEARCHING*/
 	char t;
        t=searchindex(client_input);
	/*END INDEX SEARCHING*/
	
	int eta=9999;
	int price=9999;
	char e[10],p[10];
	snprintf(e, 10, "%d", eta);
	snprintf(p, 10, "%d", price);
	
	/*Calculate Price and Calculate ETA functions will be called here*/
	printf("\nIndex for source is : %d \n", source);
	printf("\nIndex for destination is : %d \n", des);
		
	strcat(reply," the ETA would be "); 
	strcat(reply,p);	
	strcat(reply," minutes and the price would be ");
	strcat(reply,e);
	strcat(reply," dollars. Would you like me to confirm the order for you? ");
	
	count=1;
	}
	}
	if (searchword(confirm, comp)) {
	strcat(reply,"Perfect! Hope you will enjoy our service ");
	/* Confirm order function will be called here*/
	
	count=1;
	}
	if (searchword(" REQUEST_POSITION ", comp)) {
        strcat(reply," Your Taxi is at ");

        count=1;
        }
	if (searchword(taxi, comp)) {
	/* Taxi POSITION function will be called here*/

        

        count=1;
        }


	if (searchword(negative, comp)) {
        strcat(reply," I am sorry to hear that. ");

        count=1;
        }
	if (searchword(demand, comp)) {
        strcat(reply," Let me look into that for you, ");

        count=1;
        }
	if (searchword(" professor doemer ", comp)) {
        strcat(reply," How are you doing Professor Doemer? ");

        count=1;
        }

	if (searchword(greetings, comp)) {
        /* Match found */
	#ifdef DDEBUG
        printf("Greetings word found : %s\n", comp);
        #endif
	strcat(reply," Hello! Hope you are having a great day:) ");
	count=1;
	}

comp = strtok(NULL," ");
}
if((word==NULL&&word2!=NULL)||(word!=NULL&&word2==NULL))
{
strcat(reply," Sorry you mind telling me from where to where you would like to go instead? "); 
}
if(count==0)
{
strcat(reply," Sorry I dont understand what you are saying! ");

count =0;
}

#ifdef DDEBUG
printf(" %s ", reply);
printf(" %s %s %s %s ", a,b,c,d);
#endif
printf("\n");

send = reply;
return send;


#ifdef jdkd
char *SendBuf = malloc(sizeof(char)*256);
strcpy(SendBuf, "testing Belle.c");
return SendBuf;
#endif
}

int searchword(char *text, char *word) {
    int i;

    while (*text != '\0') {
        while (isspace((unsigned char) *text))
            text++;
        for (i = 0; *text == word[i] && *text != '\0'; text++, i++);
        if ((isspace((unsigned char) *text) || *text == '\0') && word[i] == '\0')
            return 1;
        while (!isspace((unsigned char) *text) && *text != '\0')
            text++;
    }

    return 0;
}

int searchindex(char *client_input)
{
	Map map;
	TaxiStandList *list = MakeTaxiStandList();
	map = Reader(map, list);
	int i, j, src_index, dest_index;;
	char *finder = NULL, *line = NULL, *line2 = NULL, *dest = NULL;
	
	char client_temp[100];
	char src[100];
	char *x_temp = (char *)malloc(sizeof(char)*map.x*80);
	char *x_temp2 = (char *)malloc(sizeof(char)*map.x*80);
	char *y_temp = (char *)malloc(sizeof(char)*map.y*80);
	char *y_temp2 = (char *)malloc(sizeof(char)*map.y*80);
	
	memcpy(x_temp, map.x_names, strlen(map.x_names)+1);
	memcpy(x_temp2, map.x_names, strlen(map.x_names)+1);
	memcpy(y_temp, map.y_names, strlen(map.y_names)+1);
	memcpy(y_temp2, map.y_names, strlen(map.y_names)+1);
	
/*	printf("\nEnter Command : ");
	fgets(client_input, 100, stdin);	
*/	memcpy(client_temp, client_input, 100);
	line = strtok(client_temp, " ");
	printf("line: %s\n", line);
	int max = 0;
	while (strcmp(line, "TO")) {
		max += strlen(line) + 1;
		line = strtok(NULL, " ");
	}
	
	memcpy(src, client_input, max);
	finder = strstr(client_input, "REQUEST_TAXI");
	if(finder){
		finder = strstr(client_input, "CORNER");
		if(finder){
			line = strtok(x_temp, ",");
			for(i = 0; i < map.x; i++){
				line2 = strstr(src, line);
				if(line2) {
					line = strtok(y_temp, ",");
					for(j = 0; j < map.y; j++){
						line2 = strstr(src, line);
						if(line2) {
							printf("\nfirst set found\n");
							src_index = map.x*j + i;
							i = map.x;
							break;
						}
						line = strtok(NULL, ",");
					}
				}
				if (i < map.x) {
					line = strtok(NULL, ",");
				}
			}
			dest = strstr(client_input, "TO");
			line = strtok(x_temp2, ",");
			for(i = 0; i < map.x; i++){
				line2 = strstr(dest, line);
				if(line2) {
					line = strtok(y_temp2, ",");
					for(j = 0; j < map.y; j++){
						line2 = strstr(dest, line);
						if(line2) {
							printf("\n2nd set found\n");
							dest_index = map.x*j + i;
							i = map.x;
							break;
						}
						line = strtok(NULL, ",");
					}
				}
				if (i < map.x) {
					line = strtok(NULL, ",");
				}
			}
		}
	}
	source=src_index;
	des=dest_index;
	printf("src index: %d dest index: %d\n", src_index, dest_index);
	return 0;

}

char* FullStreetName( char* a){
char *pch;

Map map;
TaxiStandList *list = MakeTaxiStandList();
map = Reader(map, list);

        pch = strtok (map.x_names,",.-");
        while (pch != NULL)
  {
if(strstr(pch,a))
{
        printf ("%s\n",pch);
        return pch;
}
    pch = strtok (NULL, ",.-");
  }
pch = strtok (map.y_names,",.-");
        while (pch != NULL)
  {
if(strstr(pch,a))
{
        printf ("%s\n",pch);
        return pch;
}
    pch = strtok (NULL, ",.-");
  }
pch = strtok (map.l_names,",.-");
        while (pch != NULL)
  {
if(strstr(pch,a))
{
        printf ("%s\n",pch);
        return pch;
}
    pch = strtok (NULL, ",.-");
  }
}
