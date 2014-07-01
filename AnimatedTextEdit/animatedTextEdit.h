#ifndef ANIMATEDTEXTEDIT_H
#define ANIMATEDTEXTEDIT_H
#include <QTextEdit>
#include <QWidget>
#include <QMovie>
#include <QHash>
#include <QUrl>
#include <QString>
#include <QPushButton>

class AnimatedTextEdit : public QTextEdit
{
        Q_OBJECT

public:
        AnimatedTextEdit(QWidget * p = 0);
        // QTextEdit *textEdit;

        void addAnimation(const QUrl& url, const QString& fileName);


private slots:
        void animate(int);


private:
        QList<QUrl> lstUrl;
        QList<QMovie *> lstMovie;
        QHash<QMovie*, QUrl> urls;
};
class Window : public QWidget
{
    Q_OBJECT
public:
    Window(QWidget *p = 0);
private:
    QPushButton *btn;
    AnimatedTextEdit *edit;
public slots:
    void btnClicked();
};
#endif // ANIMATEDTEXTEDIT_H
