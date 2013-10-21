#include "visualizationwindow.h"
#include "ui_visualizationwindow.h"
#include <qmath.h>


VisualizationWindow::VisualizationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisualizationWindow),
    measurementState(false),
    xAngle(0),
    yAngle(0),
    zAngle(0)
{
    ui->setupUi(this);

    setWindowTitle("SkateboardAnalyzer v0.5 measuring");

    //--------------SETS VARIABLES--------------//
    SEq_1 = 1.0f; SEq_2 = 0.0f; SEq_3 = 0.0f; SEq_4 = 0.0f; // estimated orientation quaternion elements with initial conditions
    dialWin = new DialogWindow(this);

   glWidget = new GLWidget;
 //   GLWidget->initializeGL();
  // glWidget->initializeGL();
   // delete ui->GLObj;
    //ui->GLObj = new GLWidget();
  // ui->mainLayout->addWidget(glWidget);
   //ui->verticalLayout->addWidget(glWidget);
   //QWidget

   glWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
   ui->verticalLayout_3->addWidget(glWidget);

    connect(ui->terminalButton, SIGNAL(clicked()), this, SLOT(onTerminalButton()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStartButton()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(onStopButton()));
    //dialog window
    connect(dialWin, SIGNAL(dataAvaible(QByteArray)), this, SLOT(newData(QByteArray)));

}

VisualizationWindow::~VisualizationWindow()
{
    delete ui;
}

void VisualizationWindow::onTerminalButton()
{
  //  dialWin->show();
    dialWin->showNormal();
}
void VisualizationWindow::onStartButton()
{
     dialWin->onStartButton();
     measurementState = true;
     xAngle = 180;
     yAngle = 180;
     zAngle = 180;
}
void VisualizationWindow::onStopButton()
{
    dialWin->onStopButton();
    measurementState = false;
}

void VisualizationWindow::newData(QByteArray ext)
{

//    double przelicznik = 6103515625;//prescaler value
    double przelicznikRad = 0.00106526443603170;


  //  long double sredniaX = 0, sredniaY = 0, sredniaZ = 0, deltax, deltay, deltaz;

    QVector<measurementData> data = ExtractData(ext);//extract data from dialogwinndow

    quint16 newDataSize = data.size();
    QVector<double> key(newDataSize);

    QVector<double> ax(newDataSize);
    QVector<double> ay(newDataSize);
    QVector<double> az(newDataSize);

    QVector<double> gx(newDataSize);
    QVector<double> gy(newDataSize);
    QVector<double> gz(newDataSize);
    double sampleTime;
    sampleTime = 0.5/newDataSize;
   // qDebug()<<"znacznik";
    for(double i = 0; i<newDataSize; i++)
    {
        ax[i] = ((double)data.at(i).ax.as_word);
        ay[i] = ((double)data.at(i).ay.as_word)*(-1);
        az[i] = ((double)data.at(i).az.as_word)*(-1);

        gx[i] = ((double)data.at(i).gx.as_word)*przelicznikRad;
        gy[i] = ((double)data.at(i).gy.as_word)*przelicznikRad*(-1);
        gz[i] = ((double)data.at(i).gz.as_word)*przelicznikRad*(-1);

        filterUpdate(gx[i], gy[i], gz[i], ax[i], ay[i],az[i]);
    }


//       SEq_1 w
//       SEq_2 x
//       SEq_3 y
//       SEq_4 z
 //   double q[4];
//           float w =  SEq_1;
//           float x =  SEq_2;
//           float y =  SEq_3;
//           float z =  SEq_4;

            ui->q1LCD->display(SEq_1);
            ui->q2LCD->display(SEq_2);
            ui->q3LCD->display(SEq_3);
            ui->q4LCD->display(SEq_4);
           //QVector3D zeroVector(0,0,-1);

           QQuaternion rot(SEq_1,SEq_2,SEq_3,SEq_4);
           //rot.normalize();
         //  QVector3D rotVect = rot.rotatedVector(zeroVector);

           glWidget->setRotation(rot);

//           float angleX, angleY, angleZ, angle;

//           angleX = rotVect.x()*180/PI;
//           angleY = rotVect.y()*180/PI;
//           angleZ = rotVect.z()*180/PI;

        //   QVector3D rotAngle(angleX, angleY, angleZ);

//           ui->q1LCD->display(angleX);
//           ui->q2LCD->display(angleY);
//          ui->q3LCD->display(angleZ);

//          //glWidget->setRotation(rotAngle);
//           QVector4D rotAfter = rot.toVector4D();
//        //   qDebug()<<rotAfter.w();
//           angle = acos(rotAfter.w())*360/PI;

//           if(angle < 0) angle+=360;
//           if(angle >= 360) angle-=360;
//            angle = acos(rotAfter.w())*360/PI;

//           ui->q4LCD->display(angle);

//                  float x2 = x * x;
//                  float y2 = y * y;
//                  float z2 = z * z;
//                  float xy = x * y;
//                  float xz = x * z;
//                  float yz = y * z;
//                  float wx = w * x;
//                  float wy = w * y;
//                  float wz = w * z;

//           QMatrix4x4 rotation( 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
//                                2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
//                                2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
//                                0.0f, 0.0f, 0.0f, 1.0f);

//           glWidget->setRotation(rotAngle,(int)angle, rotation);





}


//-----------------FREE IMU FILTER-------------------------//

void VisualizationWindow::filterUpdate(float w_x, float w_y, float w_z, float a_x, float a_y, float a_z)
{

    // Local system variables
    float norm; // vector norm
    float SEqDot_omega_1, SEqDot_omega_2, SEqDot_omega_3, SEqDot_omega_4; // quaternion derrivative from gyroscopes elements
    float f_1, f_2, f_3; // objective function elements
    float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33; // objective function Jacobian elements
    float SEqHatDot_1, SEqHatDot_2, SEqHatDot_3, SEqHatDot_4; // estimated direction of the gyroscope error


    // Axulirary variables to avoid reapeated calcualtions
    float halfSEq_1 = 0.5f * SEq_1;
    float halfSEq_2 = 0.5f * SEq_2;
    float halfSEq_3 = 0.5f * SEq_3;
    float halfSEq_4 = 0.5f * SEq_4;
    float twoSEq_1 = 2.0f * SEq_1;
    float twoSEq_2 = 2.0f * SEq_2;
    float twoSEq_3 = 2.0f * SEq_3;

    // Normalise the accelerometer measurement
    norm = sqrt(a_x * a_x + a_y * a_y + a_z * a_z);
    a_x /= norm;
    a_y /= norm;
    a_z /= norm;

    // Compute the objective function and Jacobian
    f_1 = twoSEq_2 * SEq_4 - twoSEq_1 * SEq_3 - a_x;
    f_2 = twoSEq_1 * SEq_2 + twoSEq_3 * SEq_4 - a_y;
    f_3 = 1.0f - twoSEq_2 * SEq_2 - twoSEq_3 * SEq_3 - a_z;
    J_11or24 = twoSEq_3; // J_11 negated in matrix multiplication
    J_12or23 = 2.0f * SEq_4;
    J_13or22 = twoSEq_1; // J_12 negated in matrix multiplication
    J_14or21 = twoSEq_2;
    J_32 = 2.0f * J_14or21; // negated in matrix multiplication
    J_33 = 2.0f * J_11or24; // negated in matrix multiplication


    // Compute the gradient (matrix multiplication)
    SEqHatDot_1 = J_14or21 * f_2 - J_11or24 * f_1;
    SEqHatDot_2 = J_12or23 * f_1 + J_13or22 * f_2 - J_32 * f_3;
    SEqHatDot_3 = J_12or23 * f_2 - J_33 * f_3 - J_13or22 * f_1;
    SEqHatDot_4 = J_14or21 * f_1 + J_11or24 * f_2;


    // Normalise the gradient
    norm = sqrt(SEqHatDot_1 * SEqHatDot_1 + SEqHatDot_2 * SEqHatDot_2 + SEqHatDot_3 * SEqHatDot_3 + SEqHatDot_4 * SEqHatDot_4);
    SEqHatDot_1 /= norm;
    SEqHatDot_2 /= norm;
    SEqHatDot_3 /= norm;
    SEqHatDot_4 /= norm;


    // Compute the quaternion derrivative measured by gyroscopes
    SEqDot_omega_1 = -halfSEq_2 * w_x - halfSEq_3 * w_y - halfSEq_4 * w_z;
    SEqDot_omega_2 = halfSEq_1 * w_x + halfSEq_3 * w_z - halfSEq_4 * w_y;
    SEqDot_omega_3 = halfSEq_1 * w_y - halfSEq_2 * w_z + halfSEq_4 * w_x;
    SEqDot_omega_4 = halfSEq_1 * w_z + halfSEq_2 * w_y - halfSEq_3 * w_x;


    // Compute then integrate the estimated quaternion derrivative
    SEq_1 += (SEqDot_omega_1 - (beta * SEqHatDot_1)) * deltat;
    SEq_2 += (SEqDot_omega_2 - (beta * SEqHatDot_2)) * deltat;
    SEq_3 += (SEqDot_omega_3 - (beta * SEqHatDot_3)) * deltat;
    SEq_4 += (SEqDot_omega_4 - (beta * SEqHatDot_4)) * deltat;


    // Normalise quaternion
    norm = sqrt(SEq_1 * SEq_1 + SEq_2 * SEq_2 + SEq_3 * SEq_3 + SEq_4 * SEq_4);
    SEq_1 /= norm;
    SEq_2 /= norm;
    SEq_3 /= norm;
    SEq_4 /= norm;

}

void VisualizationWindow::getYawPitchRoll(float * ypr)
{
    //float q[4]; // quaternion
      float gx, gy, gz; // estimated gravity direction
      //getQ(q);

      gx = 2 * (SEq_2 *SEq_4 - SEq_1*SEq_3);
      gy = 2 * (SEq_1*SEq_2 + SEq_3*SEq_4);
      gz = SEq_1*SEq_1 - SEq_2 *SEq_2  - SEq_3*SEq_3 + SEq_4*SEq_4;

      ypr[0] = atan2(2 * SEq_2 * SEq_3 - 2 * SEq_1 * SEq_4, 2 * SEq_1*SEq_1 + 2 * SEq_2 * SEq_2 - 1) * 180/M_PI;
      ypr[1] = atan(gx / sqrt(gy*gy + gz*gz))  * 180/M_PI;
      ypr[2] = atan(gy / sqrt(gx*gx + gz*gz))  * 180/M_PI;
}

void VisualizationWindow::getEuler(float *angles)
{
    //float q[4]; // quaternion
     // getQ(q);
      angles[0] = atan2(2 * SEq_2 * SEq_3 - 2 * SEq_1 * SEq_4, 2 * SEq_1*SEq_1 + 2 * SEq_2 * SEq_2 - 1) * 180/M_PI; // psi
      angles[1] = -asin(2 * SEq_2 * SEq_4 + 2 * SEq_1 * SEq_3) * 180/M_PI; // theta
      angles[2] = atan2(2 * SEq_3 * SEq_4 - 2 * SEq_1 * SEq_2, 2 * SEq_1 * SEq_1 + 2 * SEq_4 * SEq_4 - 1) * 180/M_PI; // phi
}

//QVector<measurementData> VisualizationWindow::ExtractData(QByteArray data)
//{
//    QVector<measurementData> measurements;

//    while(data.size()/frameLenght != 0)
//    {
//        data.remove(0,1);//removing start char
//        QByteArray rawData = data;
//        rawData.truncate(16);

//        quint8 controlSumThere = data.at(16);
//        data.remove(0,17);

//        quint8 controlSumHere = 0;
//        for(int j = 0; j<16; j++)//calculate control sum
//        {
//            controlSumHere += rawData[j];
//        }
//        if(controlSumThere == controlSumHere)//check control sum
//        {
//           measurementData temp;

//           temp.ax.as_bytes.lo = rawData.at(6);
//           temp.ax.as_bytes.hi = rawData.at(7);
//           temp.ay.as_bytes.lo = rawData.at(8);
//           temp.ay.as_bytes.hi = rawData.at(9);
//           temp.az.as_bytes.lo = rawData.at(10);
//           temp.az.as_bytes.hi = rawData.at(11);

//           temp.gx.as_bytes.lo = rawData.at(0);
//           temp.gx.as_bytes.hi = rawData.at(1);
//           temp.gy.as_bytes.lo = rawData.at(2);
//           temp.gy.as_bytes.hi = rawData.at(3);
//           temp.gz.as_bytes.lo = rawData.at(4);
//           temp.gz.as_bytes.hi = rawData.at(5);

//           temp.an_gx.as_bytes.lo = rawData.at(12);
//           temp.an_gx.as_bytes.hi = rawData.at(13);
//           temp.an_gz.as_bytes.lo = rawData.at(14);
//           temp.an_gz.as_bytes.hi = rawData.at(15);

//            measurements.append(temp);
//        }
//        else
//        {
//            qDebug()<<"Invalid frame detected";
//        }
//    }

//    return measurements;

//}
