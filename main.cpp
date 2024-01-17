
#include "main.h"
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//using namespace cv;
//int main()
//{
//    std::string image_path = "C:/Users/Veta/OneDrive/Изображения/photo_me.jpg";
//    Mat img = imread(image_path, IMREAD_COLOR);
//
//    imshow("Display window", img);
//    int k = waitKey(0); // Wait for a keystroke in the window
//    return 0;
//}
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap("C:/Users/Veta/Downloads/ssstik.io_1705437356318.mp4");

    if (!cap.isOpened()) {
        std::cerr << "Ошибка при открытии видеофайла" << std::endl;
        return -1;
    }

    double fps = cap.get(cv::CAP_PROP_FPS);
    int frameCount = cap.get(cv::CAP_PROP_FRAME_COUNT);
    cv::Size frameSize(
        static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
        static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))
    );

    // Создаем видеоврайтер для сохранения видео с наложенной информацией
    cv::VideoWriter writer("output.mp4", cv::VideoWriter::fourcc('X', '2', '6', '4'), fps, frameSize);

    if (!writer.isOpened()) {
        std::cerr << "Ошибка при создании видеоврайтера" << std::endl;
        return -1;
    }

    for (int i = 0; i < frameCount; ++i) {
        cv::Mat frame;
        cap >> frame; 

        if (frame.empty()) {
            std::cerr << "Ошибка при чтении кадра" << std::endl;
            break;
        }

        std::ostringstream info;
        /*info << "Frame: " << i + 1 << " / " << frameCount
            << " | Resolution: " << frameSize.width << "x" << frameSize.height
            << " | Codec: " << cap.get(cv::CAP_PROP_FOURCC);*/

        info << "Frame: " << i + 1 << " / " << frameCount;
        cv::putText(frame, info.str(), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
        info.str("");
        info << "Resolution: " << frameSize.width << "x" << frameSize.height;
        cv::putText(frame, info.str(), cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
        info.str(""); 
        info << "Codec: " << cap.get(cv::CAP_PROP_FOURCC);
        cv::putText(frame, info.str(), cv::Point(10, 90), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);

        //cv::putText(frame, info.str(), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);

        writer << frame;

        cv::imshow("Video with Info", frame);
        if (cv::waitKey(30) == 27) // Ждем нажатия клавиши ESC
            break;
    }

    cv::destroyAllWindows();

    return 0;
}
