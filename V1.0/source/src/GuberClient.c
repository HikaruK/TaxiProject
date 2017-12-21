/* Client Application for Guber */
/* adapted from GTK_ClockClient.c by Rainer Doemer */

#include "GuberClient.h"

/*#define debug*/
#define DEBUG 	
#define BUFFSIZE 256
/*#define frame_size*/

void reqBtn_callback(GtkWidget *reqBtn, gpointer user_data);

static void enter_callback(GtkWidget *widget, GtkWidget *entry);

/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */
	= NULL;
struct sockaddr_in
	ServerAddress;	/* server address we connect with */

/*** global functions ****************************************************/

void FatalError(		/* print error diagnostics and abort */
	const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
    exit(20);
} /* end of FatalError */

char *Talk2Server(		/* communicate with the server */
	const char *Message,
	char *RecvBuf)
{
    int n;
    int SocketFD;

    SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketFD < 0)
    {   FatalError("socket creation failed");
    }
#ifdef DEBUG
    printf("%s: Connecting to the server at port %d...\n",
		Program, ntohs(ServerAddress.sin_port));
#endif
    if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		sizeof(struct sockaddr_in)) < 0)
    {   FatalError("connecting to server failed");
    }
#ifdef DEBUG
    printf("%s: Sending message '%s'...\n", Program, Message);
#endif
    n = write(SocketFD, Message, strlen(Message));
    if (n < 0)
    {   FatalError("writing to socket failed");
    }
#ifdef DEBUG
    printf("%s: Waiting for response...\n", Program);
#endif
    n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    if (n < 0) 
    {   FatalError("reading from socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received response: %s\n", Program, RecvBuf);
    printf("%s: Closing the connection...\n", Program);
#endif
    close(SocketFD);
    return(RecvBuf);
} /* end of Talk2Server */

void GetResponseFromServer(GtkWidget *Widget, gpointer Data)
{
    GtkWidget *ButtonClicked;
    GtkLabel *LabelToUpdate;
    char RecvBuf[BUFFSIZE];
    const char *Response;

#ifdef DEBUG
    printf("%s: GetMsgFromServer callback starting...\n", Program);
#endif
    ButtonClicked = Widget;
    LabelToUpdate = Data;
    assert(LabelToUpdate);
    Response = Talk2Server("TIME", RecvBuf);
    
	/*display status from server*/
	gtk_label_set_label(LabelToUpdate, Response);
    
} /* end of GetResponseFromServer */


/*======================== main =================================*/

int main(			
	int argc,
	char *argv[])
{
	Map map;

	TaxiStandList *list = MakeTaxiStandList();
	map = Reader(map, list);
	
	/* make taxi */
	int totalTaxis = list->totalTaxis; 
	Taxi *taxis = malloc(totalTaxis*sizeof(Taxi));
	Taxi *fleet = MakeTaxiFleet(map.list, taxis);
	/* make taxi */
	
	/* make landmark */
/*	LandmarkList *landmarklist;*/
/*	landmarklist = MakeLandmarkList();*/
	
#ifdef debug
int i, j;
	for(i = 0; i < map.y; i++){
		for(j = 0; j < map.x; j++){
			printf("%c ",map.arr[i*map.x + j]);
		}
		printf("\n");
	}
#endif
	
#ifdef debug1
	for(i = 0; i < map.num_taxis; i++)
	{
	 printf("%d", taxiFleet[i].taxiID);
	}
#endif
	
/* 	while(1)
	{
	printf("\n%f\n", getServerClock());
	} */
	/*make the array/taxis
	make requests
	service requests increment income and overhead
	refresh taxi locations/job */

     int PortNo;
    struct hostent *Server;

    Program = argv[0];
#ifdef DEBUG
    printf("%s: Starting...\n", argv[0]);
#endif
    if (argc < 3)
    {   fprintf(stderr, "Usage: %s hostname port\n", Program);
	exit(10);
    }
    Server = gethostbyname(argv[1]);
    if (Server == NULL)
    {   fprintf(stderr, "%s: no such host named '%s'\n", Program, argv[1]);
        exit(10);
    }
    PortNo = atoi(argv[2]);
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PortNo);
    ServerAddress.sin_addr = *(struct in_addr*)Server->h_addr_list[0];


    /*======================= Create the GUI =============================*/

	/*** create window ***/
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (!window)
    	{   
    		fprintf(stderr, "%s: cannot create GUI window\n", Program);
        	exit(15);
    	}
	/*center window title*/
	gtk_window_set_title(GTK_WINDOW(window), "Güber Taxi Services");
	/*choose window size*/		
	gtk_window_set_default_size(GTK_WINDOW(window), 1200, 700);
	/*center window on screen*/		
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	/*** load icon ***/
	icon = create_pixbuf("taxi_clipart.png");
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	
	/*** main frame ***/
	/* set border */
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	/* create frame*/
	frameMain = gtk_frame_new(NULL);
	gtk_widget_set_size_request(frameMain, 1150, 700);		/*set fixed size*/
	gtk_container_add(GTK_CONTAINER(window), frameMain);
	
	/*set style of frame*/
	gtk_frame_set_shadow_type(GTK_FRAME(frameMain), GTK_SHADOW_IN);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameMain), "frameMain");
#endif
	hboxMain = gtk_hbox_new(FALSE, 5);	/*FALSE means elements inside not same size*/
	gtk_container_add(GTK_CONTAINER(frameMain), hboxMain);
	
	/*** map and input boxes ***/
	/* left map box */
/*	vboxL = gtk_vbox_new(FALSE, 5);*/
/*	gtk_container_add(GTK_CONTAINER(frameMain), vboxL);*/
	
	frameL = gtk_frame_new(NULL);
/*	gtk_container_add(GTK_CONTAINER(frameL), vboxL);*/
	gtk_container_set_border_width(GTK_CONTAINER(frameL), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameL), "frameL - Map");
#endif	
	gtk_widget_set_size_request(frameL, 800, 700);		/*set fixed size*/
	
	halignL = gtk_alignment_new(0, 0, 0, 0);		/*align map box to left*/
	gtk_container_add(GTK_CONTAINER(halignL), frameL);
	gtk_box_pack_start(GTK_BOX(hboxMain), halignL, TRUE, TRUE, 5);
	
	/* right input box */
	vboxR = gtk_vbox_new(FALSE, 5);
	halignR = gtk_alignment_new(1,0,0,0);
	frameR = gtk_frame_new(NULL);
	gtk_container_set_border_width(GTK_CONTAINER(frameR), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameR), "frameR - Input");
#endif
	gtk_widget_set_size_request(frameR, 350, 700);		/*set fixed size*/
	gtk_container_add(GTK_CONTAINER(frameR), vboxR);
	gtk_container_add(GTK_CONTAINER(halignR), frameR);
	gtk_box_pack_start(GTK_BOX(hboxMain), halignR, TRUE, TRUE, 5);
	
	/* logo */
	valignLogo = gtk_alignment_new(0 ,0, 0, 0);
	gtk_container_add(GTK_CONTAINER(vboxR), valignLogo); 
	vboxLogo = gtk_vbox_new(FALSE, 5);
	gtk_widget_set_size_request(vboxLogo, 300, 250);		/*set fixed size*/
	gtk_container_add(GTK_CONTAINER(valignLogo), vboxLogo);
	GtkWidget *dareaLogo = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER (vboxLogo), dareaLogo);
	
	g_signal_connect(dareaLogo, "expose_event", G_CALLBACK(DrawAreaExposedLogo), NULL); 

	/*** widgets inside input box ***/
	
	/* entry struct - contains info for user entry and server responses */
	entry *entries = malloc(sizeof(entry));
   	if(!entries)
	 {
	  perror("\nOut of memory\n");
	  exit(30);
	 }
	
	/* status */
	frameStatus = gtk_frame_new(NULL);
	gtk_widget_set_size_request(frameStatus, 350, 250);		/*set fixed size*/
	gtk_container_set_border_width(GTK_CONTAINER(frameStatus), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameStatus), "status frame");
#endif
	valignStatus = gtk_alignment_new(0 ,0.6, 0, 0);
	gtk_container_add(GTK_CONTAINER(valignStatus), frameStatus);
	gtk_box_pack_start(GTK_BOX(vboxR), valignStatus, TRUE, TRUE, 5);
	
	/***  create chatbox style label - save last two responses and display newest one ***/
	entries->count = 0;		/* place first response in label 1, 2nd in 
					   label 2, and in LabelToUpdate for all responses after */
	vboxStatus = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(frameStatus), vboxStatus);
	
	/* line 1 label (oldest) */
	GtkWidget *Label1;
	Label1 = gtk_label_new("Hi, i'm Belle, your virtual assitant. How can I help you?");
	entries->Label1 = Label1;
	gtk_label_set_justify(GTK_LABEL(entries->Label1), GTK_JUSTIFY_LEFT);
	gtk_widget_set_size_request(Label1, 300, -1);		/* -1 means height can adjust */
	gtk_label_set_line_wrap(GTK_LABEL(entries->Label1), TRUE);
	gtk_label_set_line_wrap_mode(GTK_LABEL(entries->Label1), PANGO_WRAP_WORD);
/*	valignLabel1 = gtk_alignment_new(0.05, 0, 0, 0);*/
/*	gtk_container_add(GTK_CONTAINER(valignLabel1), entries->Label1);*/
	gtk_box_pack_start(GTK_BOX(vboxStatus), entries->Label1, FALSE, FALSE, 4);
	
	/* line 2 label */
	GtkWidget *Label2;
	Label2 = gtk_label_new("");
	entries->Label2 = Label2;
	gtk_label_set_justify(GTK_LABEL(entries->Label2), GTK_JUSTIFY_LEFT);
	gtk_widget_set_size_request(Label2, 300, -1); 
	gtk_label_set_line_wrap(GTK_LABEL(entries->Label2), TRUE);
	gtk_label_set_line_wrap_mode(GTK_LABEL(entries->Label2), PANGO_WRAP_WORD);
/*	valignLabel2 = gtk_alignment_new(0.05, 0, 0, 0);*/
/*	gtk_container_add(GTK_CONTAINER(valignLabel2), entries->Label2);*/
	gtk_box_pack_start(GTK_BOX(vboxStatus), entries->Label2, FALSE, FALSE, 4);
	
	/* label to update for each call */
	GtkWidget *LabelToUpdate;
	LabelToUpdate = gtk_label_new("");
	entries->LabelToUpdate = LabelToUpdate;
	gtk_label_set_justify(GTK_LABEL(entries->LabelToUpdate), GTK_JUSTIFY_LEFT);
	gtk_widget_set_size_request(LabelToUpdate, 300, -1);
	gtk_label_set_line_wrap(GTK_LABEL(entries->LabelToUpdate), TRUE);
	gtk_label_set_line_wrap_mode(GTK_LABEL(entries->LabelToUpdate), PANGO_WRAP_WORD);
/*	valignNewLabel = gtk_alignment_new(0.05, 0, 0, 0);*/
/*	gtk_container_add(GTK_CONTAINER(valignNewLabel), entries->LabelToUpdate);*/
	gtk_box_pack_start(GTK_BOX(vboxStatus), entries->LabelToUpdate, FALSE, FALSE, 4);
	/* align labels */
	gtk_misc_set_alignment((GtkMisc *)entries->Label1, 0.1, -1);
	gtk_misc_set_alignment((GtkMisc *)entries->Label2, 0.1, -1);
	gtk_misc_set_alignment((GtkMisc *)entries->LabelToUpdate, 0.1, -1);
	
	/* text entry  - adapted from https://developer.gnome.org/gtk-tutorial/stable/x939.html */
	frameEntry = gtk_frame_new(NULL);
	#ifdef frame_size
	gtk_widget_set_size_request(frameEntry, 350, 200);		/*set fixed size*/
	#endif
	gtk_container_set_border_width(GTK_CONTAINER(frameEntry), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameEntry), "frameEntry");
#endif
	valignEntry = gtk_alignment_new(0, 0.9, 0, 0);
	vboxEntry = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(frameEntry), vboxEntry);
	gtk_container_add(GTK_CONTAINER(valignEntry), frameEntry);
	
	gtk_box_pack_start(GTK_BOX(vboxR), valignEntry, TRUE, TRUE, 10);
	
	/* pickup entry */
	vboxPickup = gtk_vbox_new (FALSE, 0);
    	gtk_container_add (GTK_CONTAINER (vboxEntry), vboxPickup);
    	valignPick = gtk_alignment_new(0,0,0,0);
   
    	GtkWidget *entryPick = gtk_entry_new();
    	entries->entryPick = entryPick;
  	
    	gtk_widget_set_size_request(entries->entryPick, 300, 40);
    	gtk_container_add (GTK_CONTAINER (valignPick), entries->entryPick);
    	gtk_entry_set_alignment(GTK_ENTRY(entries->entryPick), 0.0);
    	gtk_entry_set_max_length(GTK_ENTRY(entries->entryPick), 100);
    	g_signal_connect(entries->entryPick, "activate", G_CALLBACK(enter_callback), entries->entryPick);
    	gtk_entry_set_text(GTK_ENTRY(entries->entryPick), "Enter request and click 'Send'");
/*    	tempPos = GTK_ENTRY(entry->entryPick)->text_length;*/
/*    	gtk_editable_insert_text(GTK_EDITABLE(entryPick), "Enter Pickup Location", -1, &tempPos);*/
/*    	gtk_editable_select_region(GTK_EDITABLE(entryPick), 0, GTK_ENTRY(entryPick)->text_length);	highlight word when double clicked*/
    	
    	gtk_box_pack_start (GTK_BOX (vboxPickup), valignPick, TRUE, TRUE, 10);
    	
    	#ifdef VOID
    	/* dropoff entry */
	vboxDropoff = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (vboxEntry), vboxDropoff);
	valignDrop = gtk_alignment_new(0,0.5,0,0);
    	
    	GtkWidget *entryDrop = gtk_entry_new();
    	entries->entryDrop = entryDrop;
    	
    	gtk_widget_set_size_request(entries->entryDrop, 300, 30);
    	gtk_container_add (GTK_CONTAINER (valignDrop), entries->entryDrop);
    	gtk_entry_set_max_length(GTK_ENTRY(entries->entryDrop), 50);
    	g_signal_connect(entries->entryDrop, "activate", G_CALLBACK(enter_callback), entries->entryDrop);
    	tempPos = GTK_ENTRY(entries->entryDrop)->text_length;
    	gtk_editable_insert_text(GTK_EDITABLE(entries->entryDrop), "Enter Dropoff Location", -1, &tempPos);
    	gtk_editable_select_region(GTK_EDITABLE(entries->entryDrop), 0, GTK_ENTRY(entries->entryDrop)->text_length);	/*highlight word when double clicked*/
    	
    	gtk_box_pack_start (GTK_BOX (vboxDropoff), valignDrop, TRUE, TRUE, 10);	
    	#endif
	
	/* buttons */
	valignBtn = gtk_alignment_new(0,1,0,0);	
	halignButtons = gtk_alignment_new(0.5,0,0,0);
	hboxBtn = gtk_hbox_new(TRUE,15);				/*TRUE means all buttons in box same size*/
	gtk_widget_set_size_request(hboxBtn, 250, 70);
	gtk_container_set_border_width(GTK_CONTAINER(hboxBtn), 10);
	reqBtn = gtk_button_new_with_label("Send");
	gtk_widget_set_size_request(reqBtn, 70,30);		/*sets minimum size of widget*/
	gtk_container_add(GTK_CONTAINER(hboxBtn), reqBtn);
	cnlBtn = gtk_button_new_with_label("Cancel");
	gtk_container_add(GTK_CONTAINER(hboxBtn), cnlBtn);
	gtk_container_add(GTK_CONTAINER(valignBtn), hboxBtn);
	gtk_container_add(GTK_CONTAINER(halignButtons), valignBtn);
	gtk_box_pack_start(GTK_BOX(vboxR), halignButtons, TRUE, FALSE, 10);
	
	/* call gsignal only for printing belle is typing... with delay here*/
	g_signal_connect(reqBtn, "clicked", G_CALLBACK(reqBtn_callback), entries);	/* activate when Request button clicked*/

	/*** Draw the map ***/
	/*DrawMap(frameL);*/
	
	/************************************/
	gtk_frame_set_label (GTK_FRAME (frameL), "City of New Irvine");
	gtk_frame_set_label_align(GTK_FRAME(frameL), 0.0, 0.0);
	/* Drawing area for map */
    	DrawArea = gtk_drawing_area_new();
    	gtk_container_add(GTK_CONTAINER(frameL), DrawArea);
    	
    	g_signal_connect(DrawArea, "expose_event", G_CALLBACK(DrawAreaExposed), NULL);
    	/*****************************************/

	/*	
	g_signal_connect(G_OBJECT(cairo.cr), "expose_event", G_CALLBACK(DrawTaxiExposed),NULL);
	*/
	/*** Draw taxi ***/
	
	/*
	g_signal_connect(G_OBJECT(DrawArea), "expose_event", G_CALLBACK(DrawTaxiExposed), NULL);


	*/	

	/*g_signal_connect(DrawArea, "expose_event", G_CALLBACK(DrawTaxiExposed), NULL);*/
	
/*********************************************************************************/

	/*** show elements on window ***/	 						
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);	
	gtk_widget_show_all(window);
	
	g_object_unref(icon);		/*free icon memory*/

	gtk_main();					/*program waits for events to occur*/
	cairo_surface_destroy(logo.image);		/* destroy surface when quitting */
	return 0;

} /* end of main */

/*=======================================================================*/

/* Icon */
GdkPixbuf *create_pixbuf(const gchar * filename)
{
	GdkPixbuf *pixbuf;
	GError *error = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if (!pixbuf)
	{
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	return pixbuf;
}

/* adapted from https://developer.gnome.org/gtk-tutorial/stable/x939.html */
static void enter_callback(GtkWidget *widget, GtkWidget *entry) 
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
	printf("Entry contents: %s\n", entry_text);
}

double getServerClock()
{
 clock_t serverClock = clock();
 double clockTimeF = serverClock;
 double clocksPerSec = CLOCKS_PER_SEC;
 return clockTimeF/clocksPerSec;

}

void reqBtn_callback(GtkWidget *reqBtn, gpointer user_data)
{
	/* signal callbacks for buttons */
	entry *entries = user_data;
	assert(entries);
	gchar *message;
	message = (gchar *)malloc(sizeof(gchar)*256);
	/* response message from server */
	char *response;
	
	/* create string containing request data for server */
	const gchar *pickup = gtk_entry_get_text(GTK_ENTRY(entries->entryPick));
/*	const gchar *dropoff = gtk_entry_get_text(GTK_ENTRY(entries->entryDrop));*/
	strcpy(message, pickup);
	/*strcat(message, " to ");*/	
/*	strcat(message, dropoff);*/
	
	#ifdef debug
	printf("\nrequest message is %s \n", message);
	#endif
	
	/* send message to server */
	response = Talk2Server(message, message);
	/* update label with new response */
	#ifdef debug
	printf("\ncount is %d\n", entries->count);
	#endif
	if ((entries->count) == 0)
	{
		gtk_label_set_label(GTK_LABEL(entries->Label2),response/*"this shows when count is 0 in label 2."*/);
		entries->count++;
	}
	else if ((entries->count) == 1)
	{
		gtk_label_set_label(GTK_LABEL(entries->LabelToUpdate), response/*"this shows when count is 1 in labelToUpdate. Testing to see if this line will wrap to the next row. Words should not get cutoff at the ends. If it does then re adjust the label sizes."*/);
		entries->count++;
	}
	else 
	{
		const gchar *prev;
		const gchar *oldest;
		gchar *prevResp = (gchar *)malloc(sizeof(gchar)*256);
		prev = gtk_label_get_text(GTK_LABEL(entries->LabelToUpdate));
		strcpy(prevResp, prev);
		
		gchar *oldResp = (gchar *)malloc(sizeof(gchar)*256);
		oldest = gtk_label_get_text(GTK_LABEL(entries->Label2));
		strcpy(oldResp, oldest);
		
		gtk_label_set_label(GTK_LABEL(entries->LabelToUpdate), response/*"this shows when count is greater than 2"*/);
		gtk_label_set_label(GTK_LABEL(entries->Label2), prevResp);		/* show last response in line 2 */
		gtk_label_set_label(GTK_LABEL(entries->Label1), oldResp);	/* show 2 responses before text in line 1 */
	}	
}

gboolean DrawAreaExposedLogo(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data)
{
	GtkWidget *dareaLogo;
	gint Width, Height;
	cairo_t *crLogo;		/* cairo context for logo */
	dareaLogo = Widget;
	Width = dareaLogo->allocation.width;
	Height = dareaLogo->allocation.height;
	
	/* render the logo */
	crLogo = gdk_cairo_create(dareaLogo->window);
	logo.image = cairo_image_surface_create_from_png("logo.png");
	cairo_set_source_surface(crLogo, logo.image, 10, 10);
  	cairo_paint(crLogo);  

	/* delete the cairo context and free memory */
	cairo_destroy(crLogo);
	return TRUE; /* area drawn, done with expose event */
} /* end of DrawAreaExposedLogo */

/* EOF GuberClient.c */
