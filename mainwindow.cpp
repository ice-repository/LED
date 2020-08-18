#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QPainter>
#include <QTimer>

#define LINE_LENGTH     150
#define LINE_BLOCK_SIZE 6
#define BLOCK_SIZE 25
#define FastLED m_MainWindow->update(); msleep(10); //change the speed of refresh
#define delay(a) msleep(a)
unsigned long leds[256];
#define NUM(a) ((a * 255) / 100)
#define CRGB(r,g,b) (NUM(b) | NUM(g) << 8 | NUM(r) << 16)

//COLORS
#define GREY CRGB(20, 20, 20)
#define BLACK CRGB(0, 0, 0)

//This function starts the Thread
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    memset(leds, 0, sizeof(leds));
    setMinimumSize(BLOCK_SIZE*16, BLOCK_SIZE*16);
    show();

    m_thread = new MyThread(this);
    m_thread->start();
}
//This function creates the MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

//This function paints the screen
void MainWindow::paintEvent(QPaintEvent *)
{
    int i, j;
    QPainter p(this);

    p.setBrush(Qt::SolidPattern);
    p.setPen(Qt::NoPen);

    // FLIP EVEN ROWS
    for (i = 0; i < 16; i += 2)
    {
        for (j = 0; j < 16; j++)
        {
            p.setBrush((QColor)leds[(i*16)+15-j]);
            p.drawRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }

    // NOFLIP ODD ROWS
    for (i = 1; i < 16; i += 2)
    {
        for (j = 0; j < 16; j++)
        {
            p.setBrush((QColor)leds[(i*16)+j]);
            p.drawRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }

    for (i = 0; i < LINE_LENGTH; i++)
    {
        p.setBrush((QColor)leds[i]);
        p.drawRect((i*LINE_BLOCK_SIZE), (16*BLOCK_SIZE) + 40, LINE_BLOCK_SIZE, LINE_BLOCK_SIZE*3);
    }
}

//This function creates snakes that run across the screen, left to right
//Input:                                     (color, index, start_location)
void MyThread::snake(unsigned long color, int index, int start_location)
{
    int i = start_location + index;
    int x = start_location;

    if(i == x){
        leds[x+13] = BLACK;
        leds[i] = color;
    }
    else if(i == x+1){
        leds[x+14] = BLACK;
        leds[i] = color;
        leds[i-1] = color;
    }
    else if(i == x+2){
        leds[x+15] = BLACK;
        leds[i] = color;
        leds[i-1] = color;
        leds[i-2] = color;
    }
    else {
        leds[i-3] = BLACK;
        leds[i] = color;
        leds[i-1] = color;
        leds[i-2] = color;
    }

    FastLED
}

/**************************************
              Main Thread
 **************************************/
void MyThread::run()
{

    for(;;) //void loop()
    {
        for(int i = 0; i < 16 ; i++) //loops over all 16 spaces
        {
            delay(10);
            //              (color, index, start_location)
            snake(GREY, i, 16);
            snake(GREY, i, 32);
            snake(GREY, i, 80);
            snake(GREY, i, 96);
            snake(GREY, i, 144);
            snake(GREY, i, 160);
            snake(GREY, i, 208);
            snake(GREY, i, 224);
        }

    }
}






