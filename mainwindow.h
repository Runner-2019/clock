#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimerEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QLCDNumber>
#include <QDateTimeEdit>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QtMultimedia>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void LCDUpdateText();
    void addOneAlarmItem();
    void rmOneAlarmItem();
    void checkAlarmItem();
    void changeVoice();

private:
    void timerSetting();
    void LCDSetting();
    void dateTimeSetting();
    void clockShowSetting();
    void voiceSetting();


private:
    Ui::MainWindow *ui;
    QVBoxLayout* mainLayout;
    QTimer* timer;
    QLCDNumber* lcdNumber;
    QMediaPlayer * player;
    QAudioOutput *audioOutput;

    QLabel* settingLbl;
    QDateTimeEdit* settingEdit;
    QPushButton* settingYesBtn;
    QPushButton* settingNoBtn;



    // 整体设置
    void setMainLayout();


};
#endif // MAINWINDOW_H
