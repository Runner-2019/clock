#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextDocument>
#include <QTextCursor>
#include <QDateTime>
#include <QFont>
#include <QLCDNumber>
#include <QPalette>
#include <QGridLayout>
#include <QSizePolicy>
#include <QListWidgetItem>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置各个部件
    LCDSetting();
    LCDUpdateText();
    timerSetting();
    dateTimeSetting();
    clockShowSetting();
    voiceSetting();

    // 部件设置好后，将它们加入到MainLayout里
    setMainLayout();

    // 关联信号槽
    connect(settingYesBtn,SIGNAL(clicked()),this,SLOT(addOneAlarmItem()));
    connect(ui->rmBtn,SIGNAL(clicked()),this,SLOT(rmOneAlarmItem()));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(changeVoice()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setMainLayout()
{
    // 添加LCDNumber，显示当前时间
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(lcdNumber);

    // 添加一个gridLayout,用于设置闹钟
    QGridLayout* settingGridLayout = new QGridLayout;

    // 添加设置时钟
    /*
     *   0        1        2     3
     * 0 [label ] [      edit    ]
     * 1          [yesBtn] [NoBtn]
     */
    settingGridLayout->addWidget(settingLbl,0,0,1,1,Qt::AlignRight | Qt::AlignTop);
    settingGridLayout->addWidget(settingEdit,0,1,1,2,Qt::AlignTop);
    settingGridLayout->addWidget(settingYesBtn,1,1,1,1,Qt::AlignTop);
    settingGridLayout->addWidget(settingNoBtn,1,2,1,1,Qt::AlignTop);

    // 右侧添加textBrowser
    settingGridLayout->addWidget(ui->listWidget,0,3,10,10);
    settingGridLayout->addWidget(ui->rmBtn,10,11,1,1);
    settingGridLayout->addWidget(ui->cancelBtn,10,12,1,1);
    mainLayout->addLayout(settingGridLayout);

    // 添加一个声音设置和闹钟声音选择
    QGridLayout * voiceGridLayout = new QGridLayout;
    voiceGridLayout->addWidget(ui->label,0,0,1,1);
    voiceGridLayout->addWidget(ui->horizontalSlider,0,1,1,100,Qt::AlignLeft);
    mainLayout->addLayout(voiceGridLayout);

    mainLayout->setContentsMargins(10,10,10,10);
    ui->centralwidget->setLayout(mainLayout);

}

void MainWindow::timerSetting()
{
    // 定时器设置
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(LCDUpdateText()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkAlarmItem()));
    timer->start(1000);
}

void MainWindow::LCDSetting()
{
    lcdNumber = new QLCDNumber;
    lcdNumber->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    lcdNumber->setDigitCount(19);
    lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    lcdNumber->setStyleSheet("background:transparent;color:#000000;");

//    暂时不用调色板
//    QPalette palette = lcdNumber->palette();
//    palette.setColor(QPalette::Active,QPalette::WindowText,Qt::black);
//    palette.setColor(QPalette::Inactive,QPalette::WindowText,Qt::gray);
//    lcdNumber->setPalette(palette);

}

void MainWindow::dateTimeSetting()
{
    settingEdit = new QDateTimeEdit;
    settingLbl = new QLabel;
    settingYesBtn = new QPushButton;
    settingNoBtn = new QPushButton;
    settingLbl->setText(tr("时间设置"));
    settingYesBtn->setText("YES");
    settingNoBtn->setText("No");

    settingEdit->setDisplayFormat("yyyy-MM-dd hh:mm");
    settingEdit->setDateTime(QDateTime::currentDateTime());

}

void MainWindow::clockShowSetting()
{
    ui->rmBtn->setText("移除");
    ui->cancelBtn->setText("取消");

}

void MainWindow::voiceSetting()
{
    ui->label->setText("音量");
    ui->horizontalSlider->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setSingleStep(1);

    audioOutput = new QAudioOutput;
    player = new QMediaPlayer;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("/Users/zhangnaigang/Qt/QtProjects/clock/sounds/alarm-clock-01.wav"));
    audioOutput->setVolume(ui->horizontalSlider->value());

}




void MainWindow::LCDUpdateText()
{
    // 更新时间显示 & 设置初始时间的显示
    QDateTime curTime = QDateTime::currentDateTime();
    QString curTimeStr = curTime.toString("yyyy-MM-dd hh:mm:ss");
    lcdNumber->display(curTimeStr);
}

void MainWindow::addOneAlarmItem()
{
    // 1.首先获取QDateTimeEdit里用户设置的时间
    QString settingTimeStr = settingEdit->text();

    // 2.将textBrowser增加一条
    QListWidgetItem* item = new QListWidgetItem(QIcon(":/myImages/images/clock.png"),settingTimeStr);
    item->setFont(QFont("Helvetica",15));
    ui->listWidget->addItem(item);

}

void MainWindow::rmOneAlarmItem()
{
    // 首先获取当前用户想要删除哪一条
    int curRow = ui->listWidget->currentRow();
    ui->listWidget->takeItem(curRow);

}

void MainWindow::checkAlarmItem()
{
    // 每秒检查一次，当前是否需要响应闹钟
    int n = ui->listWidget->count();
    QDateTime curTime = QDateTime::currentDateTime();
    QString curTimeStr = curTime.toString("yyyy-MM-dd hh:mm");

    for(int i = 0; i < n; ++i){
        if(ui->listWidget->item(i)->text() == curTimeStr){
            player->play();// 振铃
        }
    }


}

void MainWindow::changeVoice()
{
    int v = ui->horizontalSlider->value();
    audioOutput->setVolume(v * 1.0 / 100.0);
}



