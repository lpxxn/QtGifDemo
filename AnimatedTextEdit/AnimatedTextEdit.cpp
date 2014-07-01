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

         if(lstUrl.contains(url)){ //ͬһ��gif ʹ��ͬһ��movie
             return;
         }else{
            lstUrl.append(url);
         }

        QMovie* movie = new QMovie(this);
        movie->setFileName(fileName);
        movie->setCacheMode(QMovie::CacheNone);


        lstMovie.append(movie);   //��ȡ��movie,�Ա�ɾ��
        urls.insert(movie, url);

        //��֡ʱˢ��
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
               document()->addResource(QTextDocument::ImageResource,   //�滻ͼƬΪ��ǰ֡
                        urls.value(movie), movie->currentPixmap());

               setLineWrapColumnOrWidth(lineWrapColumnOrWidth()); // ..ˢ����ʾ
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

    edit->insertHtml("<img src='test'/>");  //   �˴���test �� url
    edit->addAnimation(QUrl("test"), ":/images/cat.gif");  //���һ������.
}
