/*Desmond Chan 82883276*/
#ifndef GUBERCLIENT_H_INCLUDED_
#define GUBERCLIENT_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <math.h>
#include "Taxi.h"
#include <sys/time.h>
#include <signal.h>
#include "Reader.h" 

#define BUFFSIZE 256
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

typedef void (*ClientHandler)(int DataSocketFD);
typedef void (*TimeoutHandler)(void);

gboolean DrawAreaExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);
GtkWidget *CreateWindow(int *argc, char **argv[]);

void DrawTaxi(GtkWidget *FrameL, GtkWidget *vboxLogo);
gboolean DrawTaxiExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);
double GetElapsedTime(struct timeval t1, struct timeval t2); 
	

double GetServerClock();
void ShutdownClicked(		/* shutdown button was clicked */
	GtkWidget *Widget,
	gpointer Data);
/*gui*/
GdkPixbuf *icon;

char *Belle(char *string);

#endif
