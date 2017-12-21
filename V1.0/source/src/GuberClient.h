#ifndef GUBERCLIENT_H_INCLUDED_
#define GUBERCLIENT_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <assert.h>
#include "Reader.h"
#include "Taxi.h"
#include <cairo.h>
#include "Belle.h"
#include "Landmark.h"
#include <math.h>

GdkPixbuf *create_pixbuf(const gchar * filename);

void FatalError(const char *ErrorMsg);

char *Talk2Server(const char *Message,char *RecvBuf);

void GetResponseFromServer(GtkWidget *Widget, gpointer Data);

int main(int argc,char *argv[]);

double getServerClock();


void DrawMap(GtkWidget *FrameL);

int searchword(char *text, char *word);

void DrawTaxi(GtkWidget *Widget);

gboolean DrawAreaExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);

gboolean DrawAreaExposedLogo(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);

gboolean DrawTaxiExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);

typedef struct Entry {
    GtkWidget *entryPick;
    GtkWidget *entryDrop;
    GtkWidget *LabelToUpdate;
    GtkWidget *Label1;
    GtkWidget *Label2;
    int count;
}entry;

/*for taxi image */
struct {
  cairo_surface_t *image;
} glob;

/*context for cairo */
struct {
  cairo_t *cr;
}cairo;

/*Context for logo*/
struct {
  cairo_surface_t *image;  
}logo;

/*Context for compass image*/
struct {
  cairo_surface_t *image;  
} compass;

GdkPixbuf *icon;
GtkWidget *window;
GtkWidget *frameMain;	
GtkWidget *hboxMain;
GtkWidget *frameL;	
GtkWidget *frameR;	
GtkWidget *vboxL;	
GtkWidget *vboxR;	
GtkWidget *halignL;
GtkWidget *halignR;		
GtkWidget *frameStatus;		
GtkWidget *frameInput;
GtkWidget *valignStatus;
GtkWidget *hboxBtn;
GtkWidget *halignButtons;	
GtkWidget *halignBtn;
GtkWidget *halignCnl;
GtkWidget *valignBtn;
GtkWidget *reqBtn;	
GtkWidget *cnlBtn;	
GtkWidget *valignEntry;	
GtkWidget *vboxEntry;
GtkWidget *frameEntry;
GtkWidget *vboxPickup;		
GtkWidget *vboxDropoff;		
GtkWidget *valignDrop;
GtkWidget *valignPick;	
/*GtkWidget *entryPick;*/
/*GtkWidget *entryDrop;*/
gint tempPos;
GtkWidget *labelFare;
GtkWidget *valignNewLabel;
GtkWidget *valignLabel1;
GtkWidget *valignLabel2;
GtkWidget *vboxStatus;

/* cairo */
GtkWidget *DrawArea;
GtkWidget *dareaLogo;
GtkWidget *valignLogo;
GtkWidget *vboxLogo;

GtkWidget *DrawAreaT;
cairo_t *crLogo;
cairo_t *cr;

char* Belle(char* string);


#endif
