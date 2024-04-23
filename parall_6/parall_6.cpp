// parall_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


int main()
{
    Mat img = imread("image.jpg", IMREAD_COLOR);
    if (img.empty()) {
        cout << "Изображение не загружено" << endl;
        return -1;
    }
    imshow("Original", img);
    Mat gray, sepia, negatiw, sobel;
#pragma omp parallel sections num_threads(4)
    {
#pragma omp section
        {
            cvtColor(img, gray, COLOR_BGR2GRAY);;
        }
#pragma omp section
        {
            Mat sepia_filter = (Mat_<float>(3, 3) <<
                0.393, 0.769, 0.189,
                0.349, 0.686, 0.168,
                0.272, 0.534, 0.131);
            transform(img, sepia, sepia_filter);
        }
#pragma omp section
        {
            bitwise_not(img, negatiw);
        }
#pragma omp section
        {
            Mat sobelX, sobelY;
            Sobel(img, sobelX, CV_16S, 1, 0);
            Sobel(img, sobelY, CV_16S, 0, 1); 
            Mat absSobelX, absSobelY;
            convertScaleAbs(sobelX, absSobelX);
            convertScaleAbs(sobelY, absSobelY);
            addWeighted(absSobelX, 0.5, absSobelY, 0.5, 0, sobel);
        }
    }
    imshow("Gray", gray);
    imshow("Sepia", sepia);
    imshow("Negatiw", negatiw);
    imshow("Sobel", sobel);
    waitKey(0);
    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
