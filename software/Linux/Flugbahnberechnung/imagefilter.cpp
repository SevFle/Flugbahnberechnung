#include "imagefilter.h"

using namespace imagefilter;

C_ImageFilter::C_ImageFilter()
  {

  }
C_ImageFilter::~C_ImageFilter()
  {

  }

void C_ImageFilter::gpufErode(cv::cuda::GpuMat *gpu_src, cv::cuda::GpuMat *gpu_dst, int erodeKernelSize, int erodeIterations)
  {
  cv::Mat                   erode_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * erodeKernelSize,2 * erodeKernelSize));
  cv::Ptr<cv::cuda::Filter> erode                     = cv::cuda::createMorphologyFilter (cv::MORPH_ERODE,gpu_src->type(),erode_structuring_element,cv::Point (-1,-1),erodeIterations);
  erode->apply (*gpu_src,*gpu_dst);
  }

void C_ImageFilter::gpufDilate(cv::cuda::GpuMat *gpu_src, cv::cuda::GpuMat *gpu_dst, int dilateKernelSize, int dilateIterations)
  {
  cv::Mat                   dilate_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * dilateKernelSize,2 * dilateKernelSize));
  cv::Ptr<cv::cuda::Filter> dilate                     = cv::cuda::createMorphologyFilter (cv::MORPH_DILATE,gpu_src->type(),dilate_structuring_element,cv::Point (-1,-1),dilateIterations);
  dilate->apply (*gpu_src,*gpu_dst);
  }

void C_ImageFilter::gpufOpen(cv::cuda::GpuMat *gpu_src, cv::cuda::GpuMat *gpu_dst, int openKernelSize, int openIterations)
  {
  cv::Mat                   opening_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * openKernelSize,2 * openKernelSize));
  cv::Ptr<cv::cuda::Filter> opening                     = cv::cuda::createMorphologyFilter (cv::MORPH_OPEN,gpu_src->type(),opening_structuring_element,cv::Point (-1,-1),openIterations);
  opening->apply (*gpu_src,*gpu_dst);
  }

void C_ImageFilter::gpufClose(cv::cuda::GpuMat *gpu_src, cv::cuda::GpuMat *gpu_dst, int closeKernelSize, int closeIterations)
  {
  cv::Mat                   closing_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * closeKernelSize,2 * closeKernelSize));
  cv::Ptr<cv::cuda::Filter> closing                     = cv::cuda::createMorphologyFilter (cv::MORPH_CLOSE,gpu_src->type(),closing_structuring_element,cv::Point (-1,-1),closeIterations);
  closing->apply (*gpu_src,*gpu_dst);
  }

void C_ImageFilter::gpufBilateral(cv::cuda::GpuMat *gpu_src, cv::cuda::GpuMat *gpu_dst, int bilateralKernelSize, float bilateralSigmaColor, float bilateralSigmaSpatial)
  {
  cv::cuda::bilateralFilter (*gpu_src,*gpu_dst,bilateralKernelSize,bilateralSigmaColor,bilateralSigmaSpatial,cv::BORDER_DEFAULT);
  }

void C_ImageFilter::gpufGaussian(cv::cuda::GpuMat *gpuSrc, cv::cuda::GpuMat *gpuDst, int gaussianKernelSize, double gaussianSigma)
  {
  cv::Ptr<cv::cuda::Filter> gauss = cv::cuda::createGaussianFilter (gpuSrc->type(),-1,this->getfGaussianKernel(gaussianKernelSize, gaussianSigma).size(),gaussianSigma,gaussianSigma,cv::BORDER_DEFAULT);
  gauss->apply (*gpuSrc,*gpuDst);
  }

cv::cuda::GpuMat C_ImageFilter::getfGaussianKernel(int gaussianKernelSize, double gaussianSigma)
  {
  cv::cuda::GpuMat gpuGaussianKernel;
  cv::Mat cpu_gaussian = cv::getGaussianKernel (gaussianKernelSize,gaussianSigma, CV_32F);
  gpuGaussianKernel.upload (cpu_gaussian);
  return gpuGaussianKernel;
  }

void C_ImageFilter::gpufMorphGradient(cv::cuda::GpuMat *gpu_src, cv::cuda::GpuMat *gpu_dst)
  {
  cv::Mat                   morph_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * morph_kernel_size,2 * morph_kernel_size));
  cv::Ptr<cv::cuda::Filter> morph                     = cv::cuda::createMorphologyFilter (cv::MORPH_GRADIENT,gpu_src->type(),morph_structuring_element,cv::Point (-1,-1),morph_iterations);
  morph->apply (*gpu_src,*gpu_dst);
  }

void C_ImageFilter::gpufHSV(cv::cuda::GpuMat *gpu_src, cv::cuda::GpuMat *gpu_dst)
  {
  cv::Scalar min(this->hue_min,this->saturation_min,this->value_min);
  cv::Scalar max(this->hue_max,this->saturation_max,this->value_max);

  gpu_gaussian_filter (gpu_src,gpu_temp);

  cv::cuda::cvtColor (*gpu_temp,*gpu_filtered,cv::COLOR_BGR2HSV);

  cudaKernel::inRange_gpu (*gpu_filtered,min, max,*gpu_color_threshold);

  gpu_open (gpu_color_threshold,gpu_temp);

  gpu_close (gpu_temp,gpu_filtered);

  cv::cuda::cvtColor (*gpu_filtered,*gpu_temp,cv::COLOR_GRAY2BGR);

  bitwise_and (*gpu_src,*gpu_temp,*gpu_dst);
  }

void C_ImageFilter::findContours(cv::Mat *thresholded_source_image, cv::Mat *dst_contoured_image, int offset[])
  {

  {
  objekt_anzahl = 0;
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i>              hirarchy;
  //dst_contoured_image->copyTo(*dst_contoured_image);
  //*dst_contoured_image = cv::Mat::zeros(dst_contoured_image->rows, dst_contoured_image->cols, dst_contoured_image->type());


  //OpenCV Hirarchy: https://docs.opencv.org/3.4/d9/d8b/tutorial_py_contours_hierarchy.html

// Zeichne Bildmittelpunkt ein
  Mittelpunkt_x = dst_contoured_image->cols / 2;
  Mittelpunkt_y = dst_contoured_image->rows / 2;
  circle (*dst_contoured_image,cv::Point (static_cast<int> (Mittelpunkt_x),static_cast<int> (Mittelpunkt_y)),2,cv::Scalar (0,255,0));

  // Zeichne kalibrierten Bildmittelpunkt ein
  cx = this->Intrinsic->at<double> (0,2);
  cy = this->Intrinsic->at<double> (1,2);
  circle (*dst_contoured_image,cv::Point (static_cast<int> (cx),static_cast<int> (cy)),15,cv::Scalar (255,255,0));


  findContours (*thresholded_source_image,contours,hirarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE,cv::Point (offset[0],offset[1]));


  objekt_anzahl = hirarchy.size();


  if (objekt_anzahl > 0)
    {
    // Vorinitialisierung des Abstands des Konturschwerpunktes zum Bildmittelpunkt
    cv::Moments Image_Moments = moments (static_cast<cv::Mat> (contours[0]));

    KonturIndex        = 0;
    Ist_x              = 0.0;
    Ist_y              = 0.0;
    Soll_x             = 0.0;
    Soll_y             = 0.0;
    Delta_x            = 0.0;
    Delta_y            = 0.0;
    contour_found      = false;
    Vec_Object[0]      = 0.0;
    Vec_Object[1]      = 0.0;
    Vec_Object[2]      = 0.0;
    max_Moment_m00     = 0.0;
    Moment_0_Ordnung   = 0.0;
    Moment_1_Ordnung_x = 0.0;
    Moment_1_Ordnung_y = 0.0;
    Schwerpunkt_x      = 0.0;
    Schwerpunkt_y      = 0.0;

    cv::Point2f Center;
    Radius = 0.0;


    // Größte Kontur anhand der Fläche suchen
    for (int i = 0; i < objekt_anzahl; i++)
      {
      Image_Moments    = moments (static_cast<cv::Mat> (contours[i]));
      Moment_0_Ordnung = Image_Moments.m00;

      if (Moment_0_Ordnung > max_Moment_m00)
        {
        max_Moment_m00 = Moment_0_Ordnung;
        KonturIndex    = i;
        }
      else
        {
        // tue nichts
        }
      }

    // Bestimmen der Flchenmomente 0. (Flche) und 1. Ordnung (Flche * x bzw. Flche * y) zur Bestimmung des Flchenschwerpunktes: x_ = summe(m1) / summe(m0);
    Image_Moments    = moments (static_cast<cv::Mat> (contours[KonturIndex]));
    Moment_0_Ordnung = Image_Moments.m00;


    //std::cout << "Objektgröße "<< std::to_string(Moment_0_Ordnung) << std::endl << std::endl;
    if (Object_Size_min > Moment_0_Ordnung || Moment_0_Ordnung > Object_Size_max)
      {
      return;
      }

    // Bestimme Flchenmoment 1. Ordnung (Flche * x bzw.Flche * y) zur Bestimmung des Flchenschwerpunktes: x_ = summe(m1) / summe(m0);
    Moment_1_Ordnung_x = Image_Moments.m10;
    Moment_1_Ordnung_y = Image_Moments.m01;
    Schwerpunkt_x      = Moment_1_Ordnung_x / Moment_0_Ordnung;
    Schwerpunkt_y      = Moment_1_Ordnung_y / Moment_0_Ordnung;

    // Den Radius und den Mittelpunkt des kleinstes Kreises einer gefundenen Kontur ermitteln.
    minEnclosingCircle (static_cast<cv::Mat> (contours[KonturIndex]),Center,Radius);

    // Mittelpunkt / schwerpunkt der kontur einzeichnen
    circle (*dst_contoured_image,cv::Point (static_cast<int> (Schwerpunkt_x),static_cast<int> (Schwerpunkt_y)),2,cv::Scalar (0,255,255));

    // Konturumfang zeichnen
    circle (*dst_contoured_image,Center,static_cast<int> (Radius),cv::Scalar (0,255,255));

    // Schwerpunktkoordinaten als Text im Bild darstellen
    //S_x = std::to_string (Schwerpunkt_x);
    //S_y = std::to_string (Schwerpunkt_y);
    //putText (*dst_contoured_image,"S_x: " + S_x,cv::Point (0,20),1,1,cv::Scalar (255,255,255),2);
    //putText (*dst_contoured_image,"S_y: " + S_y,cv::Point (0,50),1,1,cv::Scalar (255,255,255),2);

    // Bestimme den Abstand des Mittelpunktes der gefundenen Kontur zum Bildmittelpunkt
    contour_found = true;
    Ist_x         = Schwerpunkt_x;
    Ist_y         = Schwerpunkt_y;
    Soll_x        = cx;
    Soll_y        = cy;
    Delta_x       = Ist_x - Soll_x;
    Delta_y       = Ist_y - Soll_y;

    // Bestimme den Lichtstrahlvektor der Kontur bezogen auf das Kamera-KS
    x_Kamera_KS    = Delta_x;
    y_Kamera_KS    = Delta_y;
    fx             = this->Intrinsic->at<double> (0,0);
    fy             = this->Intrinsic->at<double> (1,1);
    f              = (fx + fy) / 2.0; // Mittelwert der Brennweite
    Vec_Object[0]  = x_Kamera_KS;
    Vec_Object[1]  = y_Kamera_KS;
    Vec_Object[2]  = f;
    Vec_Object_Abs = sqrt (x_Kamera_KS * x_Kamera_KS + y_Kamera_KS * y_Kamera_KS + f * f);
    Vec_Object[0] /= Vec_Object_Abs;
    Vec_Object[1] /= Vec_Object_Abs;
    Vec_Object[2] /= Vec_Object_Abs;


    // Schreibe die Delta-Werte auf das Bild
    //Delta_x_str = std::to_string (Delta_x);
    //Delta_y_str = std::to_string (Delta_y);
    //putText (*dst_contoured_image,"Delta_x: " + Delta_x_str,cv::Point (0,80),1,1,cv::Scalar (255,255,255),2);
    //putText (*dst_contoured_image,"Delta_y: " + Delta_y_str,cv::Point (0,110),1,1,cv::Scalar (255,255,255),2);

    // Zeichne eine Linie zwischen kalibriertem Bildmittelpunkt und dem Objektschwerpunkt
    line (*dst_contoured_image,cv::Point (static_cast<int> (Ist_x),static_cast<int> (Ist_y)),cv::Point (static_cast<int> (Soll_x),static_cast<int> (Soll_y)),cv::Scalar (0,0,255),4,8,0);
    }
  else
    {
    contour_found = false;
    //this->Vec_Object[0] = 0.0;
    //this->Vec_Object[1] = 0.0;
    //this->Vec_Object[2] = 0.0;
    max_Moment_m00 = 0.0;

    //putText (*dst_contoured_image,"S_x:     Object not found",cv::Point (0,20),1,1,cv::Scalar (255,255,255),2);
    //putText (*dst_contoured_image,"S_y:     Object not found",cv::Point (0,50),1,1,cv::Scalar (255,255,255),2);
    //putText (*dst_contoured_image,"Delta_x: Object not found",cv::Point (0,80),1,1,cv::Scalar (255,255,255),2);
    //putText (*dst_contoured_image,"Delta_y: Object not found",cv::Point (0,110),1,1,cv::Scalar (255,255,255),2);
    }
  }

  }

void C_ImageFilter::gpufUnidstord(cv::Mat *cpuSrc, cv::Mat *cpuDst, cv::cuda::GpuMat *gpuMap1, cv::cuda::GpuMat *gpuMap2)
  {
  cv::cuda::GpuMat gpuSrcImg, gpuTemp;
  gpuSrcImg.upload (*cpuSrc);
  cv::cuda::remap (gpuSrcImg,gpuTemp,*gpuMap1,*gpuMap2,cv::INTER_NEAREST,cv::BORDER_CONSTANT,0);
  gpuTemp.download (*cpuDst);

  }

