#ifndef OPENAIMODEL_H
#define OPENAIMODEL_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>

class OpenAIModel : public QObject
{
    Q_OBJECT
public:
    OpenAIModel(QNetworkAccessManager *nam, const QString &apiKey, QObject *parent = nullptr)
        : nam(nam), apiKey(apiKey), parent(parent) {}

    void generateText(const QString &prompt) {
        QUrl url("https://api.openai.com/v1/completions");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization", QString("Bearer %1").arg(apiKey).toUtf8());

        QJsonObject data;
        data["model"] = "text-davinci-003";
        data["prompt"] = prompt;
        //data["prompt"] = "Hello";
        data["max_tokens"] = 2048;
        data["temperature"] = 0;
        //data["stop"] = "\n";

        QJsonDocument doc(data);

        qDebug() << doc.toJson();
        nam->post(request, doc.toJson());
    }

private:
    QNetworkAccessManager *nam;
    QString apiKey;
    QObject *parent;

private slots:

};

#endif // OPENAIMODEL_H
