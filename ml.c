#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgcodecs/imgcodecs_c.h"

#include "stdio.h"


int main()

{
	//load colored image
    IplImage *img  = cvLoadImage("test2.jpg",1);

    //load gray image
    IplImage *g_img = cvLoadImage("test2.jpg",0);

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

    //average lightness of image
    CvScalar avg_lightness = cvAvg(img,NULL);
    printf("average lightness =%d\n", avg_lightness);
    

    //BGR value of image
    //Gray value of image
    int totalB;
    int totalG;
    int totalR;
    int totalGray;
    totalGray = 0;
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

			totalB += bVal;
			totalG += gVal;
			totalR += rVal;
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
    printf("avgB=%d, avgG=%d, avgR=%d, avgGray=%d\n", avgB, avgG, avgR, avgGray);

    if (avgB < 150){
    	printf("Predict: Cloudy\n");
    }
    else{
    	printf("Predict: Clear\n");
    }

    printf("Processing end.\n");
    return 0;

}