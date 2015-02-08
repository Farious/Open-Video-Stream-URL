#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int, char**) {
    cv::VideoCapture vcap;
    cv::Mat image;

	/*//
	Choose values for (H)eight, (W)idth and x(framerate).
	The port 554 is the default one, check in the camera settings though.
	Example:
	
	http://fabio:fabio1@192.168.0.153/axis-cgi/mjpg/video.cgi
	
	This should get the default configurations of the camera.
	
	The methods with the stream will need opencv compiled with ffmpeg, the one with jpeg won't need ffmpeg.
	//*/
	
    // This works on a D-Link CDS-932L
    const std::string videoStreamAddress = "http://<username:password>@<ip_address>/video.cgi?.mjpg";
	
	// Axis mjpg stream (this works, I've tested it before)
	const std::string videoStreamAddress = "http://<username:password>@<ip_address>/axis-cgi/mjpg/video.cgi?resolution=WxH&fps=x";
	
	// Axis RTSP stream (couldn't test this properly)
	const std::string videoStreamAddress = "rtsp://<username:password>@<ip_address>:554/axis-media/media.amp?videocodec=h264&streamprofile=Bandwidth";
	
	// Axis JPEG still image (this was the more reliable)
	const std::string imageAddress = "http://<username:password>@<ip_address>:554/axis-cgi/jpg/image.cgi"
	
	/*//
		Please choose which method (stream or jpg), and comment the one you don't want, if you have both it will die if the urls are not correct.
	//*/
	
    //open the video stream and make sure it's opened
    if(!vcap.open(videoStreamAddress)) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    for(;;) {
        if(!vcap.read(image)) {
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
        cv::imshow("Output Window", image);
        if(cv::waitKey(1) >= 0) break;
    }
	
	//open jpeg file
	for(;;) {
		image = cv::imread(imageAddress);
        if(!image) {
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
        cv::imshow("Output Window", image);
        if(cv::waitKey(1) >= 0) break;
    }
}