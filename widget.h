#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLocale>
#include <QTranslator>

#include "openaimodel.h"

class Widget : public QWidget
{
    Q_OBJECT
public slots:
    void sendmsg()
    {
        model->generateText(te1->toPlainText());
    }

    void onFinished(QNetworkReply *reply) {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Error:" << reply->errorString();
            return;
        }

        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject object = doc.object();

        if (object.contains("choices")) {
            QJsonArray choices = object.value("choices").toArray();
            for (int i = 0; i < choices.size(); i++) {
                QJsonObject choice = choices.at(i).toObject();
                QString text = choice.value("text").toString();
                qDebug() << text;
                te2->setText(text);
            }
        }
    }

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTextEdit* te1, *te2;
    QLineEdit* le;
    QPushButton* pb;
    QString* apikey;

    QNetworkAccessManager* nam;
    OpenAIModel* model;
};
#endif // WIDGET_H
