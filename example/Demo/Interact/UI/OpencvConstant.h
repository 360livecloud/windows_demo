#ifndef __OPENCV_H__
#define __OPENCV_H__

#pragma once


#include "../../opencv/include/opencv2/highgui/highgui.hpp"
#include "../../opencv/include/opencv2/imgproc/imgproc.hpp"

#ifdef DEBUG
#pragma comment(lib, "opencv/lib/opencv_core2413d.lib")
#pragma comment(lib, "opencv/lib/opencv_highgui2413d.lib")
#pragma comment(lib, "opencv/lib/opencv_imgproc2413d.lib")
#else
#pragma comment(lib, "opencv/lib/opencv_core2413.lib")
#pragma comment(lib, "opencv/lib/opencv_highgui2413.lib")
#pragma comment(lib, "opencv/lib/opencv_imgproc2413.lib")
#endif


#endif
