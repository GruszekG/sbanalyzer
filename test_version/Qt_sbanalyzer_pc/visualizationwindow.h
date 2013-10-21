#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QMainWindow>
#include "dialogwindow.h"
#include "measurementData.h"
#include "glwidget.h"

#include <QMatrix>
#include <QMatrix4x4>
#include <QQuaternion>

// Math library required for `sqrt'
#include <math.h>
// System constants
#define deltat 0.005f // sampling period in seconds (shown as 1 ms)
#define gyroMeasError 3.14159265358979f * (26.0f / 180.0f) // gyroscope measurement error in rad/s (shown as 5 deg/s)
#define beta sqrt(3.0f / 4.0f) * gyroMeasError // compute beta
//#define M_PI 3.14159265358979f

namespace Ui {
class VisualizationWindow;
}

class VisualizationWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VisualizationWindow(QWidget *parent = 0);
    ~VisualizationWindow();
    
private:
    Ui::VisualizationWindow *ui;
    DialogWindow *dialWin;

    long double xAngle;
    long double yAngle;
    long double zAngle;

    QMatrix4x4 rotMatrix;

    GLWidget *glWidget;

    float SEq_1, SEq_2, SEq_3, SEq_4; // estimated orientation quaternion elements with initial conditions

    bool measurementState;

private slots:
    void onTerminalButton();
    void onStartButton();
    void onStopButton();

    void newData(QByteArray ext);
//   QVector<measurementData> ExtractData(QByteArray data);

    void filterUpdate(float w_x, float w_y, float w_z, float a_x, float a_y, float a_z);

    void getEuler(float * angles);
    void getYawPitchRoll(float * ypr);


};

#endif // VISUALIZATIONWINDOW_H
