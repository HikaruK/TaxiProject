/*DrawTaxi module*/

#include "GuberClient.h"

/*#define debug*/


#ifdef refrence

typedef struct Taxi
{
 int passenger;
 int rideLength;
 double fare;
 double expense;
 int type;
 int taxiID;
 int location;
 int pickup;
 int destination;
}Taxi;

/*context for image surfae*/
struct {
  cairo_surface_t *image;  
} glob;

#endif

/*drawtaxi function*/
void DrawTaxi(GtkWidget *Widget) 
{
	
	assert(DrawArea);
	
	GtkWidget *DrawAreaT;
	DrawAreaT = DrawArea;	
	
	#ifdef debug
        printf("\n\ntesting drawtaxi\n\n");
        #endif
	

	/*	
	DrawArea = gtk_drawing_area_new();
        gtk_container_add(GTK_CONTAINER(frameL), DrawArea);
	*/	
	assert(cairo.cr);		
			/* link cairo struct to local cr variable */

	g_signal_connect(DrawAreaT, "expose_event",G_CALLBACK(DrawTaxiExposed), NULL);
	/*
  	g_signal_connect(DrawArea, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	*/

	#ifdef jdjd
	int Width = DrawArea->allocation.width;
	int Height = DrawArea->allocation.height;
	printf("\nDrawing area width=%d, height=%d.\n", Width, Height);
	 
	glob.image = cairo_image_surface_create_from_png("compResized.png");
        cairo_set_source_surface(cr, glob.image, 100,100);
        cairo_paint(cr);

	cairo_surface_destroy(glob.image);
	cairo_destroy(cr);
	#endif

}


/*drawing image cairo*/
gboolean DrawTaxiExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data)
{
	GtkWidget *DrawArea = Widget;
	
	cairo_t *cr;

	assert(cairo.cr);
	cr = gdk_cairo_create(DrawArea->window);
	/*
	cr = gdk_cairo_create(DrawAreaT->window); 
	*/
	glob.image = cairo_image_surface_create_from_png("taxi_clipart.png");
        cairo_set_source_surface(cr, glob.image, 50,50);
	cairo.cr = gdk_cairo_create(DrawArea->window);		
	cr = cairo.cr;		/* link cairo struct to local cr variable */
	assert(cr);
	
	int Width = DrawArea->allocation.width;
	int Height = DrawArea->allocation.height;
	printf("\nDrawing area width=%d, height=%d.\n", Width, Height);
	 
	glob.image = cairo_image_surface_create_from_png("compResized.png");
        cairo_set_source_surface(cr, glob.image, 100,100);
       cairo_paint(cr);

	cairo_surface_destroy(glob.image);
	cairo_destroy(cr);
	
        return TRUE;

}

