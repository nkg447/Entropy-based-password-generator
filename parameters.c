/*
* A header file to get all the parameters 
*/
#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <dirent.h>
#include <time.h>

static int mousex,mousey;
/*
* A fuction to call the program's supplied error handler if any sort of
  system call error occurs.
* Requied parameters - pointers to Display and XErrorEvent
*/
static int _XlibErrorHandler(Display *display, XErrorEvent *event) 
{
    fprintf(stderr, "An error occured detecting the mouse position\n");
    return True;
}

/*
* A function that returns the value of mouse X
*/
int getMouseX(){
    return mousex;
}

/*
* A function that returns the value of mouse Y
*/
int getMouseY(){
    return mousey;
}

/*
* A function to get the position of mouse(x, y) using the X11 library
*/
void evaluateMousePointer() 
{
    int number_of_screens;          //To store no. of screens currently on a system
    int i;                          //Loop Variable
    Bool result;                    
    Window *root_windows;
    Window window_returned;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask_return;

    /*XOpenDisplay to connect application to the X server so that all of the
    screens in the display may be used by the client.*/
    Display *display = XOpenDisplay(NULL);

//  function to display error message if any and terminating program execution.
    assert(display);

    /* A fuction to call the program's supplied error handler if any sort of
       system call error occurs.
    */
    XSetErrorHandler(_XlibErrorHandler);

    //Fuction to return the number of available screens.
    number_of_screens = XScreenCount(display);

    root_windows = malloc(sizeof(Window) * number_of_screens);

    for (i = 0; i < number_of_screens; i++) 
    {
        //Fuction to return root window
        root_windows[i] = XRootWindow(display, i);
    }
    for (i = 0; i < number_of_screens; i++) 
    {

        /*Function returns the root window the pointer is logically on and the pointer coordinates 
          relative to the root window's origin.*/
        result = XQueryPointer(display, root_windows[i], &window_returned,
                &window_returned, &root_x, &root_y, &win_x, &win_y,
                &mask_return);
        if (result == True) 
        {
            break;
        }
    }
    if (result != True)  
    {
        fprintf(stderr, "No mouse found.\n");
        return ;
    }
    //printf("Mouse is at (%d,%d)\n", root_x, root_y);
    mousex=root_x;
    mousey=root_y;
    //Free() deallocates the memory allocated by malloc
    free(root_windows);

    //Close the connection opened to X server
    XCloseDisplay(display);

}

/*
* A function to calculate the number of process currently
  running in the system, by calculating the number of 
  files and folder in the "/proc" folder in linux system
*/
int getProcessCount()
{
	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;

	dirp = opendir("/proc"); 
	while ((entry = readdir(dirp)) != NULL) {
    	
    	file_count++;
	    
	}
	closedir(dirp);
	return file_count;
}

/*
* A function to get the current time in milliseconds
*/
int getTime()   
{   
    clock_t t1;  
    t1 = clock();   
    return t1;   
}

/*
* A function to find the temperature from the html content
* Requires Parameter - FILE pointer which stores the html content
* Returns the temperature of Dehradun, IN
*/
int getTempFromQuery(FILE *fp){
    char find[]="temp";
    char path[10000];
    int i=0,j=0;
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        i=0;
        while(path[i]!='\0'){
            j=0;
            while(path[i]==find[j]){
                i++;
                j++;
            }
            if(j==4){
                break;
            }
            //printf("%d\n",j);
            i++;
        }
        if(j==4)
            break;
    }
    int temperature=(path[i+3]-48)*10+(path[i+4]-48);
    return temperature;
}

/*
* A function to get the current weather from the yahooapi using curl
* Returns the temperature of Dehradun, IN
*/
int getTemperature()
{

    FILE *fp;
    char path[1035];

    /* Open the command for reading. */
    char str[]="curl \"https://query.yahooapis.com/v1/public/yql?q=select%20item.condition%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22dehradun%2C%20in%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys\"";
    fp = popen(str, "r");
    if (fp == NULL) {
        printf("Failed to run command,  check internet connection\n" );
        exit(1);
    }
    int temperature=getTempFromQuery(fp);
    //printf("temp - %d\n",temperature);
    // close connection
    pclose(fp);

    return temperature;
}