#include "animatedTextEdit.h"
#include <QFile>
#include <QDebug>
#include <QVBoxLayout>
#include <QTime>
#include<QLabel>
AnimatedTextEdit::AnimatedTextEdit(QWidget * e)
    :QTextEdit(e)
{


}

void AnimatedTextEdit::addAnimation(const QUrl& url, const QString& fileName)
{
        QFile *file =new QFile(fileName);
        if(!file->open(QIODevice::ReadOnly)){
            qDebug()<<" open err";
        }

         if(lstUrl.contains(url)){ //同一个gif 使用同一个movie
             return;
         }else{
            lstUrl.append(url);
         }

        QMovie* movie = new QMovie(this);
        movie->setFileName(fileName);
        movie->setCacheMode(QMovie::CacheNone);


        lstMovie.append(movie);   //获取该movie,以便删除
        urls.insert(movie, url);

        //换帧时刷新
        connect(movie, SIGNAL(frameChanged(int)), this, SLOT(animate(int)));
        movie->start();
        file->close();
        delete file;

}
void AnimatedTextEdit::animate(int a)
{
       // qDebug()<<"hash count is "<<urls.count();
        if (QMovie* movie = qobject_cast<QMovie*>(sender()))
        {

           // qDebug()<<"No."<<lstMovie.indexOf(movie)<<a<<"time is"<<QTime::currentTime();
               document()->addResource(QTextDocument::ImageResource,   //替换图片为当前帧
                        urls.value(movie), movie->currentPixmap());

               setLineWrapColumnOrWidth(lineWrapColumnOrWidth()); // ..刷新显示
        }
}
Window::Window(QWidget *p)
    :QWidget(p){
    QVBoxLayout *layout = new QVBoxLayout(this);
    btn = new QPushButton("add a gif");
    edit = new AnimatedTextEdit();

    layout->addWidget(btn);
    layout->addWidget(edit);

    //label text
    QLabel * line =new QLabel();

    QMovie *move = new QMovie(":/images/cat.gif");


    line->setMovie(move);
    layout->addWidget(line);
    move->start();
    
    this->setLayout(layout);
    connect(btn,SIGNAL(clicked()),this,SLOT(btnClicked()));

}

void Window::btnClicked(){

    edit->insertHtml("<img src='test'/>");  //   此处的test 即 url
    edit->addAnimation(QUrl("test"), ":/images/cat.gif");  //添加一个动画.
}
