#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    te1 = new QTextEdit("Say this is a test");
    te1->setMinimumSize(410,530);
    te2 = new QTextEdit;
    te2->setMinimumSize(410,530);
    le = new QLineEdit("sk-YOUR API");
    pb = new QPushButton("Send");
    lb = new QLabel("API KEY:");

    QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addWidget(te1);
    hbox->addWidget(te2);

    QHBoxLayout* hbox1 = new QHBoxLayout;
    hbox1->addStretch();
    hbox1->addWidget(pb);
    hbox1->addStretch();

    QHBoxLayout* hbox2 = new QHBoxLayout;
    hbox2->addWidget(lb);
    hbox2->addWidget(le);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addLayout(hbox);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox1);

    this->setLayout(vbox);

    this->getapi(); //Get api from file：config.txt.
    nam = new QNetworkAccessManager;
    model = new OpenAIModel(nam, le->text());

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    connect(pb,SIGNAL(clicked(bool)),this,SLOT(sendmsg()));
}

Widget::~Widget()
{
}

