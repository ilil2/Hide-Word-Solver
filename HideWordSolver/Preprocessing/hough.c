#define _GNU_SOURCE
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct line
{
	double theta;
	double rho;
	struct line* next;
};

struct cartline
{
	int x1;
	int x2;
	int y1;
	int y2;
	struct cartline* next;
};

SDL_Surface* load_image(const char* path)
{
    SDL_Surface * tempo = IMG_Load(path);
    if (tempo == NULL)
	    errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_Surface * r = SDL_ConvertSurfaceFormat(tempo,SDL_PIXELFORMAT_RGB888,0);
    if (r == NULL)
            errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_FreeSurface(tempo);
    return r;
}

void algo_hough_transform(SDL_Surface* surface, Uint32* A,int width,int height,
	double rho,double theta, int ntheta, int nrho)
{
	Uint32* pixels = surface->pixels;
    int x,y;
    double dtheta = M_PI/ntheta;
    double drho = (floor(sqrt(width*width + height*height)))/nrho;
    
    if (pixels == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
        
    SDL_PixelFormat* format = surface->format;
    if (format == 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
	
    if (SDL_LockSurface(surface) < 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    int itheta;
    int irho;
    
    for(y = 0; y< height; y++)
	{
		for(x = 0; x< width; x++)
		{
			if (pixels[x+y*width] != 0)
			{
				for (itheta = 0;itheta < ntheta;itheta++)
				{
					theta = itheta * dtheta;
					rho = x* cos(theta) + (height-y)* sin(theta);
					irho = (int)(rho/drho);
					if (irho>0 && irho<nrho)
					{
						A[irho + nrho*itheta]+=1;
					}
				}
			}
			
		}
		
	}
	
}

void threshold(Uint32* A,Uint32 threshld,int ntheta,int nrho)
{
	int itheta;
    int irho;
    for (itheta =0;itheta<ntheta;itheta++)
    {
		for (irho =0;irho<nrho;irho++)
		{
			if (A[irho+ nrho*itheta]<threshld)
				A[ irho+ nrho*itheta] = 0;
		}
	}
}

void avgthreshold(Uint32 * A, Uint32 average, int len)
{
	for (int i =0;i<len;i++)
	{
		if (A[i] < 7*average/8 || A[i] > 9*average/8)
			A[i] = 0;
	}
}

void getlines(Uint32* A,struct line *linee,int width, int height, int ntheta,
	int nrho)
{
	int itheta;
    int irho;
    double dtheta = M_PI/ntheta;
    double drho = (floor(sqrt(width*width + height*height)))/nrho;
    struct line *l = linee;
    for (itheta =0;itheta<ntheta;itheta++)
    {
		
		for (irho =0;irho<nrho;irho++)
		{
			
			if (A[irho+ nrho*itheta]!=0)
			{
				
				l->next = malloc(sizeof(struct line));
				l = l->next;
				l->rho = irho*drho;

				l->theta = itheta*dtheta;
				
			}
		}
	}
	l->next = NULL;
}

void displayline(struct line * linee, struct cartline* cartlinee) 
{
	double a,b,x0,y0,x1,y1,x2,y2;

	struct line* l = linee->next;
	struct cartline *cl = cartlinee;
	while (l!=NULL)
	{
		a = cos(l->theta);
		b = sin(l->theta);
		x0 = a*(l->rho);
		y0 = b*(l->rho);
		x1 = (int)(x0 + 1000*(-b));
		y1 = (int)(y0 + 1000*(a));
		x2 = (int)(x0 - 1000*(-b));
		y2 = (int)(y0 - 1000*(a));
		cl->next = malloc(sizeof(struct cartline));
		cl = cl->next;
		cl->x1 = x1;
		cl->x2 = x2;
		cl->y1 = y1;
		cl->y2 = y2;
		l = l->next;
	}
	cl->next = NULL;
}

void mergerline(struct line* lines,int rhothreshold,double thetathreshold)
{
	struct line * a = lines->next;
	struct line * b;
	struct line * prevb = lines;

	while( a !=NULL)
	{
		b = lines->next;
		while (b!=NULL)
		{
			if (a!=b)
			{
				if (a->rho +rhothreshold > b->rho && 
					a->rho - rhothreshold < b->rho)
				{
					if (a->theta +thetathreshold > b->theta &&
						a->theta - thetathreshold < b->theta)
					{
						struct line * tempo = b;
						prevb->next = b->next;
						b = prevb;
						free(tempo);
						
					}
				}
			}
			prevb = b;
			b = b->next;
		}
		a = a->next;
		
	}
	
}

Uint32 Aaverage(Uint32 *A,int len)
{
	long count = 0;
	long average = 0;
	for (int i = 0 ; i<len;i++)
	{
		if (A[i] != 0)
		{
			average += A[i];
			count+=1;
		}
	}
	return (Uint32)(average/count);
}


void createsubmatrix(Uint32* pixels,int x1,int y1,int x2,int y2,
	int width, int numcase)
{
	
	int wsb = x2-x1+1;
	int hsb = y2-y1+1;
	Uint32 * submatrix = malloc(wsb*hsb*4);
	for (int i =0; i<wsb;i++)
	{
		for (int j =0; j<hsb;j++)
		{
			submatrix[i+ j*(wsb)] = pixels[x1+i + (y2+j)*width];
		}
	}
	char* namefile;
	if (asprintf(&namefile,"case/case_%i.png",numcase)==-1)
		errx(-1,"invalid number of case");
	SDL_Surface* result;
	result = SDL_CreateRGBSurfaceFrom(submatrix, wsb,hsb,32,4*(wsb),0,0,0, 0);
	Uint32 * submatrixe = malloc(wsb*hsb*4);
	SDL_Surface* rresult = SDL_CreateRGBSurfaceFrom(submatrixe, 28, 28, 32,
		4*(28), 0, 0, 0, 0);
	
	
	if (SDL_BlitScaled(result, NULL, rresult,NULL)==-1)
		errx(-1,"invalid number of case");
	
	if (IMG_SavePNG(rresult,namefile)!=0)
		errx(EXIT_FAILURE,"%s", SDL_GetError());
	free(rresult);
}

void loadcase(Uint32*pixels,struct cartline* vline,struct cartline* hline,
	int width)
{
	struct cartline* vl = vline->next;
	struct cartline* hl;

	int casenum = 1;

	while ((vl->next)!=NULL)
	{
		hl = hline->next;
		
		while ((hl->next)!=NULL)
		{	
			
			createsubmatrix(pixels, vl->x1,hl->y1,(vl->next)->x1,
				(hl->next)->y1,width, casenum);
			casenum+=1;
			hl = hl->next;
		}
		
		vl = vl->next;
	}
}

void classhv(struct cartline* cline, struct cartline* vline,
	struct cartline* hline)
{
	struct cartline* cl = cline->next;
	struct cartline* vl = vline;
	struct cartline* hl = hline;
	while (cl != NULL)
	{

		if (abs(cl->x2 - cl->x1)<abs(cl->y2 - cl->y1))
		{
			vl->next = malloc(sizeof(struct cartline));
			vl = vl->next;
			vl->x1 = cl->x1;
			vl->x2 = cl->x2;
			vl->y1 = cl->y1;
			vl->y2 = cl->y2;
		}
		else
		{
			
			hl->next = malloc(sizeof(struct cartline));
			hl = hl->next;
			hl->x1 = cl->x1;
			hl->x2 = cl->x2;
			hl->y1 = cl->y1;
			hl->y2 = cl->y2;;
		}

		cl = cl->next;
		
	}
	vl->next = NULL;
	hl->next = NULL;
}

void freelist(void * l,char nat)
{
	if (nat == 'c')
	{
		struct cartline * cl = (struct cartline*)l;
		while (cl!= NULL)
		{
			struct cartline * prev = cl;
			cl = cl->next;
			free(prev);;
		}
	}
	else
	{
		struct line * rl = (struct line*)l;
		while (rl != NULL)
		{
			struct line * prev = rl;
			rl = rl->next;
			free(prev);;
		}
	}
}


int main(int argc, char**argv)
{
	// Checks the number of arguments.
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: 2*image-file");

    // Initializes the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    
    SDL_Surface * surface = load_image(argv[1]);
    //SDL_Surface * img = load_image(argv[2]);
    
    SDL_PixelFormat* format = surface->format;
    if (format == 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
        
    int width = surface->w;
    int height = surface->h;
	double rho = 1.0;
    double theta = 1.0;
    int ntheta = (int)(180.0/theta);
    int nrho =(int)((floor(sqrt(width*width + height*height)))/rho);
    struct line* linee= malloc(sizeof(struct line));
    struct cartline* cartlinee = malloc(sizeof(struct cartline));
    struct cartline* vartlinee = malloc(sizeof(struct cartline));
    struct cartline* hartlinee = malloc(sizeof(struct cartline));
    linee->next = NULL;
    Uint32 threshld = width/2;
    int rhothreshold = 10;
    double thetathreshold = 0.1;
    Uint32 average;
	
    Uint32* A = calloc(ntheta * nrho,4 );
    
    algo_hough_transform(surface,A,width,height,rho,theta,ntheta,nrho);
    
    threshold(A,threshld,ntheta,nrho);
    
    average = Aaverage(A,ntheta * nrho);
    avgthreshold(A,average,ntheta * nrho);
    
    getlines(A,linee,width,height,ntheta,nrho);
	
	mergerline(linee,rhothreshold,thetathreshold);
	
	displayline(linee,cartlinee);
	
	classhv(cartlinee,vartlinee,hartlinee);
    
    /*
     * loadcase(img->pixels,vartlinee,hartlinee,width	);*/
	
	
	freelist(cartlinee,'c');
	freelist(vartlinee,'c');
	freelist(hartlinee,'c');
	freelist(linee,' ');
	
	free(A);
	SDL_Quit();
    return EXIT_SUCCESS;
    
}
