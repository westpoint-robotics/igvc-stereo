#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <triclops/triclops.h>

#include "usma_triclops/typedefs.h"
#include "usma_triclops/vision3d.h"

Vision3d::Vision3d()
{
}

int Vision3d::producePointCloud(cv::Mat const& disparityImage,
    cv::Mat const& maskImage,
    TriclopsContext const& triclops,
    PointCloud& returnedPoints)
{
    float x, y, z;
    int i = 0, j = 0;
    unsigned short disparity;
    unsigned char mask;
    cv::Vec3b colorPixel;

//     printf("[!] Searching through image at %p for obstacles..mask %d,%d,%d,%d,%d and dispar %d,%d,%d,%d,%d\n", \
//     &maskImage,maskImage.cols,maskImage.rows,int(maskImage.step),maskImage.channels(),int(maskImage.elemSize()),disparityImage.cols,disparityImage.rows,int(disparityImage.step),disparityImage.channels(),int(disparityImage.elemSize()));
// mask 640,480,640,1,1 and dispar 640,480,1280,1,2


     for ( i = 0; i < disparityImage.rows; i++ )
     {
         for ( j = 0; j < disparityImage.cols; j++ )
         {
             //disparity = disparityRow[j];
             //mask = maskRow[j];
             disparity = disparityImage.at<unsigned short>(i,j);
             mask = maskImage.at<unsigned char>(i,j);

             //convert from disparity to pointcloud
             triclopsRCD16ToXYZ( triclops, i, j, disparity, &x, &y, &z );

             // look at points within a range
             PointT pointLine;
             //only fill out for points that are cyan
             if (mask != 0)
             {
                 pointLine.x = z;
                 pointLine.y = -x;
                 pointLine.z = -y;
                 pointLine.r = 0xff;
                 pointLine.g = 0xff;
                 pointLine.b = 0xff;
                 returnedPoints.push_back(pointLine);
             }
             mask = 0;
         }
     }

    return 0;
}



