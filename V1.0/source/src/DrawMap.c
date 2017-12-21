/* DrawMap module */

#include "GuberClient.h"
/*#define debug*/
#define debug1

void DrawMap(GtkWidget *FrameL)
{
	assert(FrameL);
	#ifdef debug
	printf("\n\ntesting drawmap\n\n");
	#endif
	
	gtk_frame_set_label (GTK_FRAME (frameL), "City of New Irvine");
	gtk_frame_set_label_align(GTK_FRAME(frameL), 0.0, 0.0);
	/* Drawing area for map */
    	DrawArea = gtk_drawing_area_new();
    	gtk_container_add(GTK_CONTAINER(frameL), DrawArea);		
    	/* connect drawing area with function */
 	g_signal_connect(DrawArea, "expose_event", G_CALLBACK(DrawAreaExposed), NULL);

	g_signal_connect(DrawArea, "destroy",G_CALLBACK (gtk_main_quit), NULL);

}

/* cairo */
gboolean DrawAreaExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data)
{
	GtkWidget *DrawArea;
	gint Width, Height;
	/*map struct*/
	Map mapstruct;
	TaxiStandList *list = MakeTaxiStandList();
	mapstruct = Reader(mapstruct, list);
	assert(list);
	 
	#ifdef debug
	printf("\n W-E streets: %s\n\n", mapstruct.y_names);
	printf("\n N-S streets: %s\n\n", mapstruct.x_names);
	printf("\n rows: %d\n", mapstruct.x);
	printf("\n col: %d\n\n", mapstruct.y);
	#endif
	 
	#ifdef DEBUG
	printf("%s: DrawAreaExposed callback starting...\n", Program);
	#endif
	DrawArea = Widget;
	Width = DrawArea->allocation.width;
	Height = DrawArea->allocation.height;
	#ifdef DEBUG
	printf("%s: Drawing area width=%d, height=%d.\n", Program, Width, Height);
	#endif
	/* prepare a cairo context for the drawing */
	cairo_t *cr;
	cairo.cr = gdk_cairo_create(DrawArea->window);		
	cr = cairo.cr;		/* link cairo struct to local cr variable */
	/* draw a white rectangular background */
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_rectangle(cr, 0, 0, Width, Height);
	cairo_fill(cr);

	/*** draw streets lines ***/
	int map_border = Width/9;		/* border space to leave for street names */
	/** set line color and width **/
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);
	/** set text font and size **/
	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 11);

	int num_col = mapstruct.x;
	int num_row = mapstruct.y;
	int i;
	int col_width;
	int col_height;
	char *line = NULL;
	
	/*** draw vertical streets ***/
	for (i = 0; i < num_col; i++)
	{
		col_width = ((i * (Width - (2 * map_border))/num_col) + (2 * map_border));
		cairo_move_to(cr, col_width, map_border);
		cairo_line_to(cr, col_width, (Height - map_border/4));	
	}
	/* draw first vertical street name*/
	line = strtok(mapstruct.x_names, ",");
	col_width = (2 * map_border); 
	/* display first text at angle */
	cairo_save(cr);
	cairo_move_to(cr, (col_width), (map_border - map_border/12));
	cairo_rotate(cr, 5.1);	/* temporarily rotate context */
	cairo_show_text(cr, line); 
	cairo_restore(cr);
	
	/* draw rest of names */
	int j = mapstruct.x;
	i = 1;
	while (j > 0)
	{
		col_width = ((i * (Width - (2 * map_border))/num_col) + (2 * map_border));
		/* display text at angle */
		cairo_save(cr);
		cairo_move_to(cr, (col_width), (map_border - map_border/12));
		cairo_rotate(cr, 5.1);	/* temporarily rotate context */
		line = strtok(NULL, ",");
		cairo_show_text(cr, line); 
		cairo_restore(cr);
		i++;
		j--;	
			
	}
	/* draw horizontal lines */
	cairo_text_extents_t extents;
	for (i = 0; i < num_row; i++)
	{
		col_height = ((i * ((Height - (map_border))/num_row)) + (map_border));
		cairo_move_to(cr, (2 * map_border), col_height);
		cairo_line_to(cr, (Width - map_border/4), col_height);	
	}
	/* draw first horizontal street name*/
	line = strtok(mapstruct.y_names, ",");
	col_height = map_border; 
	/* get text width */
	cairo_text_extents(cr, line, &extents);		/* store width of street name */
	int x_pos = (2 * map_border) - extents.width - map_border/6;
	/* draw names */
	cairo_move_to(cr, (x_pos), col_height);
	cairo_show_text(cr, line); 
	
	/* draw rest of names */
	int h = mapstruct.y;
	i = 1;
	while (h > 0)
	{
		col_height = ((i * ((Height - (map_border))/num_row)) + (map_border));
		/* get text width */
		line = strtok(NULL, ",");
		cairo_text_extents(cr, line, &extents);		/* store width of street name */
		int x_pos = (2 * map_border) - extents.width - map_border/6;
		cairo_move_to(cr, (x_pos), col_height);
		cairo_show_text(cr, line); 
		i++;
		h--;		
	}
	cairo_stroke(cr);	/* show the lines */
    	
    	/*** draw landmarks ***/
    	#ifdef debug
    	printf("\nl_names: %s\n", mapstruct.l_names);
    	printf("\nl_index: %d\n", mapstruct.l_index[0]);
    	printf("\ntop left: %d\n", mapstruct.top_left[0]);
    	#endif
    	
    	int xTL, yTL;		/* top left coordinates from 1d array */
    	int xBR, yBR;		/* bottom right coordinates from 1d array */
    	int lWidth, lHeight;	/*width and height of rectangles */
    	int xTLpos, yTLpos;	/* coordinates for cairo */
    	int xBRpos, yBRpos;
    	int k = 0;		/* counter for number of landmarks */
    	char *landmark;
    	int index;
    	int xDropPos, yDropPos;		/* dropoff coordinates for cairo */
    	int xDrop, yDrop;		/* dropff coordinates from 1d array */
    	
    	landmark = strtok(mapstruct.l_names, ",");

	while (landmark != NULL)
	{
		index = mapstruct.l_index[k];
		
		xTL = (mapstruct.top_left[k])% mapstruct.x;
    		yTL = (int)((mapstruct.top_left[k])/mapstruct.x);
		xBR = (mapstruct.bot_right[k])% mapstruct.x;
    		yBR = (int)((mapstruct.bot_right[k])/mapstruct.x);
    		
    		yTLpos = ((yTL * ((Height - (map_border))/mapstruct.y)) + (map_border));
    		xTLpos = ((xTL * (Width - (2 * map_border))/mapstruct.x) + (2 * map_border));
    		yBRpos = ((yBR * ((Height - (map_border))/mapstruct.y)) + (map_border));
    		xBRpos = ((xBR * (Width - (2 * map_border))/mapstruct.x) + (2 * map_border));
    		
    		lWidth = xBRpos - xTLpos;
    		lHeight = yBRpos - yTLpos;
    		/* if landmark is a point and not a rectangle */
    		#ifdef debug
    		printf("\n %s\n", landmark);
    		#endif
    		if((searchword(landmark, "Station") == 1))
    		{
	    		/* draw dot */
	    		xDrop = index% mapstruct.x;
	    		yDrop = (int)(index/mapstruct.x);
	    		yDropPos = ((yDrop * ((Height - (map_border))/mapstruct.y)) + (map_border));
	    		xDropPos = ((xDrop * (Width - (2 * map_border))/mapstruct.x) + (2 * map_border));
	    		/* draw circle */
	    		cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 
	    		cairo_arc(cr, xDropPos, yDropPos, (Width/100), 0.0, 2 * 3.14);
	    		cairo_fill(cr);
	    		/* draw name */
	    		cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  			cairo_set_font_size(cr, 16);
  			cairo_move_to(cr, xDropPos -105, yDropPos + 30);
  			cairo_show_text(cr, landmark); 
  			
  			landmark = strtok(NULL, ",");
  			k++;
    			
    		}
    		else {
			/* when landmark is a rectangle */
			cairo_set_source_rgb(cr, 0.0, 0.5, 0.0);
	    		cairo_rectangle(cr, xTLpos, yTLpos, lWidth, lHeight);
	    		cairo_fill(cr);
	    		/* draw name */
	    		cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 
	  		cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	  		cairo_set_font_size(cr, 16);
	  		cairo_move_to(cr, (xTLpos + lWidth/8), (yTLpos + lHeight/2));
	  		cairo_show_text(cr, landmark); 
	  		/* draw dropoff point */
			xDrop = index% mapstruct.x;
	    		yDrop = (int)(index/mapstruct.x);
	    		yDropPos = ((yDrop * ((Height - (map_border))/mapstruct.y)) + (map_border));
	    		xDropPos = ((xDrop * (Width - (2 * map_border))/mapstruct.x) + (2 * map_border));
			/* draw circle */
	    		cairo_set_source_rgb(cr, 0.0, 0.8, 0.0); 
	    		cairo_arc(cr, xDropPos, yDropPos, (Width/100), 0.0, 2 * 3.14);
	    		cairo_fill(cr);
		
			landmark = strtok(NULL, ",");
			k++;
		}		
	}
	
   	#ifdef void
	cairo_rectangle(cr,100, 100, 200, 200);       
	cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
	cairo_fill(cr);
		cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 
  		cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  		cairo_set_font_size(cr, 16);

  		cairo_move_to(cr, 120, 200);
  		cairo_show_text(cr, "test name"); 
    	#endif
    	
	/*** draw taxi stands ***/
    	#ifdef debug
    	printf("\n showing first stand info for debug\n");
    	printf("\n total stands: %d\n", list->totalStands);
    	printf("\n stand location: %d\n", list->first->stand->location);
    	int x = (list->first->stand->location)% mapstruct.x;
    	int y = (int)((list->first->stand->location)/mapstruct.x);
    	printf("\n Y coord: %d\n", y);
    	printf("\n X coord: %d\n", x);
    	#endif
    	/* traverse through all stands */
    	int count = 0;
    	int sHeight, sWidth;	/* coord for draw area */
    	int xCoord, yCoord;	/* coord converted from 1d array */
    	int radius;
    	TaxiStandEntry *curr;
    	curr = list->first;
    	while(curr!= NULL)
    	{
    		xCoord = (curr->stand->location)% mapstruct.x;
    		yCoord = (int)((curr->stand->location)/mapstruct.x);
    		sHeight = ((yCoord * ((Height - (map_border))/mapstruct.y)) + (map_border));
    		sWidth = ((xCoord * (Width - (2 * map_border))/mapstruct.x) + (2 * map_border));
    		radius = (Width/100);
    		/* draw circle */
    		cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 
    		cairo_arc(cr, sWidth, sHeight, radius, 0.0, 2 * 3.14);
    		cairo_fill(cr);
    		/* show label */
    		cairo_set_source_rgb(cr, 0.0, 0.8, 0.8);
    		cairo_rectangle(cr, sWidth - 90, sHeight - 18, 80, 25);
    		cairo_fill(cr);
    		cairo_set_source_rgb(cr, 0, 0, 0); 
  		cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_OBLIQUE, CAIRO_FONT_WEIGHT_BOLD);
  		cairo_set_font_size(cr, 14);
  		cairo_move_to(cr, sWidth - 86, sHeight);
  		cairo_show_text(cr, "Taxi Stand"); 
  		/* go to next entry */
  		curr = curr->next;
  		count++;
    	}	


	/* render the compass */
        compass.image = cairo_image_surface_create_from_png("compResized.png");
	cairo_set_source_surface(cr, compass.image, (Width - 1.4*map_border), (1.4*map_border));
  	cairo_paint(cr);  

	  /*** Draw Taxi ***/
   /*============================================================================*/
    	
	/* testing draw taxi */
	
	/*For Location of taxis*/
	
	#ifdef debug
        printf("\n showing first stand info for debug\n");
        printf("\n total stands: %d\n", list->totalStands);
        printf("\n stand location: %d\n", list->first->stand->location);
     	int xT = (list->first->stand->location)% mapstruct.x;     /*Location for x coordinate to draw initial taxi*/
        int yT = (int)((list->first->stand->location)/mapstruct.x); /*Location for y coordinate to draw initial taxi*/
	printf("\n X coord: %d\n", xT);
        printf("\n Y coord: %d\n", yT);
        #endif
	
	/* traverse through all stands */
	
	/* traverse through all taxis */
	
	int counter = 0;
        int HeightT, WidthT;    /* coord for draw area */
        int xCoordT, yCoordT;     /* coord converted from 1d array */

	TaxiStandEntry *currT;
	currT = list->first;		
	/*render the taxi image*/
	glob.image = cairo_image_surface_create_from_png("taxi_clipart.png");
/*	
	int wi = cairo_image_surface_get_width (glob.image);
        int hi = cairo_image_surface_get_height (glob.image);
	cairo_scale(cr, 0.7,h);	
	
	int p = (list->first->stand->numTaxis);
	int il; 
	int tx = 5;
	int ty = 5;
*/	

	while(currT!= NULL)
        {
                xCoordT = (currT->stand->location)% mapstruct.x;
                yCoordT = (int)((currT->stand->location)/mapstruct.x);
                HeightT = ((yCoordT * ((Height - (map_border))/mapstruct.y)) + (map_border));
                WidthT = ((xCoordT * (Width - (2 * map_border))/mapstruct.x) + (2 * map_border));
                /* draw taxi */
                cairo_set_source_surface(cr, glob.image, WidthT - 40, HeightT - 30);
              	cairo_paint(cr); 
                /* go to next entry */
                currT = currT->next;
                counter++;
        }

	/*
	for (il = 0; il < p; il++)
	{
		if((tx < Width) && (tx <Height)){
		cairo_set_source_surface(cr, glob.image, tx, ty);	
        	cairo_paint(cr);
	 	}
		tx = tx +20;
		ty = ty +20;
	}*/        
  	



/*===================================================================================*/
	/* delete the cairo context and free memory */
	cairo_destroy(cr);
	cairo_surface_destroy(glob.image);
	return TRUE; /* area drawn, done with expose event */
} /* end of DrawAreaExposed */

/* end of DrawMap.c */

/* EOF */


