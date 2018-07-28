/*
	command:  gcc ml.c -o ml `pkg-config --cflags --libs opencv`
			  ./ml imageName
*/


#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgcodecs/imgcodecs_c.h"

#include "stdio.h"
#include "dirent.h"

#define txtSize 8


int main(int argc, char *argv[])

{
	//get the folder dir to access images
	//DIR *dir;
	//char *namelist;
	//struct dirent *entry;
	//if ((dir=opendir("Cloudy")) == NULL){
	//	printf("Error opening folder.\n");
	//}
	//else{
	//	while((entry=readdir(dir)) !=NULL){

			//printf((char)entry->d_name);
	//	}
	//}


	//char imageName[txtSize];
	//FILE *fp;
	//fp = fopen("test/test.txt", "r");
	//if (!fp){
	//	printf("cannot open image name txt file.\n");
	//	return 1;
	//}
	
	//while(fgets(imageName, txtSize, fp) != NULL){
	//	printf("%s", imageName);
	//}
	


	//load colored image
    IplImage *img  = cvLoadImage(argv[1],1);

    //load gray image
    IplImage *g_img = cvLoadImage(argv[1],0);

    if (!img){
        printf("problem loading the colored image.\n");
    }
    if (!g_img){
    	printf("problem loading the gray image.\n");
    }

    //width，height and size of image
    printf("width=%d, height=%d\n", img->width, img->height);
    double size;
    size = img->width * img->height;
    printf("size=%f\n", size);

    
   
    //BGR value of image
    //Gray value of image
    int totalB;
    int totalG;
    int totalR;
    int totalY;
    int totalGray;
    totalGray = 0;
    totalY = 0;
    totalB = 0;
    totalG = 0;
    totalR = 0;

    for (int i=0; i<img->height; i++){
        for (int j=0; j<img->width; j++){
        	//CvScalar s = cvGet2D(img, i, j);
        	//CvScalar g_s = cvGet2D(g_img, i, j);
        	//printf("B=%d, G=%d, R=%d, grayVal=%d\n", s.val[0], s.val[1], s.val[2], g_s.val[0]);
        	//printf("Gray=%d\t", g_s.val[0]);

        	int bVal = ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 0]; // B
			int gVal = ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 1]; // G
			int rVal = ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 2]; // R
			//printf("B=%d, G=%d, R=%d\n",bVal,gVal,rVal);

			int luma = 0.299*rVal + 0.587*gVal + 0.144*bVal;
			//printf("Y=%d\n", luma);

			totalB += bVal;
			totalG += gVal;
			totalR += rVal;
			totalY += luma;
        }
    }

    for (int k=0; k<g_img->height; k++){
    	for (int l=0; l<g_img->height; l++){
    		int grayVal = ((uchar *)(g_img->imageData + k*g_img->widthStep))[l*g_img->nChannels +0];//Gray
    		//printf("Gray=%d\n", grayVal);

    		totalGray += grayVal;
    	}
    }

    int avgB = totalB/size;
    int avgR = totalR/size;
    int avgG = totalG/size;
    int avgGray = totalGray/size;
    int avgLuma = totalY/size;
    printf("avgB=%d, avgG=%d, avgR=%d, avgGray=%d, avgLuma=%d\n", avgB, avgG, avgR, avgGray, avgLuma);

    //average lightness of image
    //CvScalar avg_lightness = cvAvg(img,NULL);
    //printf("average lightness =%d\n", avg_lightness);


    if (avgLuma > 140){
    	printf("Predict: Rainy or Cloudy\n");
    }
    else{
    	if (avgGray > 110){
    		printf("Predict: Rainy or Cloudy\n");
    	}
    	else{
    		if (avgB < 125){
    			printf("Predict: Rainy or Cloudy\n");
    		}
    		else{
    			printf("Predict: Clear\n");
    		}
    	}
    }

    printf("Predict weather end.\n");

    return 0;
}






