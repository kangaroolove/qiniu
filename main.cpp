#include <QCoreApplication>
#include "qiniu/resumable_io.h"
#include "qiniu/rs.h"
#include <QDebug>
#include "qiniu/base.h"
#include <QTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   // qDebug()<<"11111111111111";
    Qiniu_Global_Init(-1);
    //qDebug()<<"222222222222222";
    Qiniu_Rio_PutRet putRet;
    Qiniu_Client client;
    Qiniu_RS_PutPolicy putPolicy;
    Qiniu_Rio_PutExtra putExtra;
    //qDebug()<<"444444444444444";

    char *accessKey = "HJAa5YajD7sicz6QHIeiWkUD8OGm1HNEI2szkI77";
    char *secretKey = "UzTg5NH5aHF-SAghkTVi1cu0WQC0zK4VNP2CTcmd";
    char *bucket = "kangaroo";
    char *key = "FT1JN3PC.rar";
    char *localFile = "C:\\Users\\pangkuanxin\\Desktop\\FT1JN3PC.rar";
    //qDebug()<<"55555555555555555";

    Qiniu_Mac mac;
    mac.accessKey = accessKey;
    mac.secretKey = secretKey;

    Qiniu_Zero(putPolicy);
    Qiniu_Zero(putExtra);

    putPolicy.scope = bucket;
    //qDebug()<<"666666666666";
    char *uptoken = Qiniu_RS_PutPolicy_Token(&putPolicy, &mac);
    //qDebug()<<"33333333333333";
    Qiniu_Use_Zone_Huanan(Qiniu_False);


    Qiniu_Client_InitMacAuth(&client, 1024, &mac);

    QTime time;
    time.start();
    Qiniu_Error error = Qiniu_Rio_PutFile(&client, &putRet, uptoken, key, localFile, &putExtra);
    qDebug()<<time.elapsed()/1000.0<<"s";
    if (error.code != 200)
    {
        qDebug()<<error.code;
        qDebug()<<QString("upload file %1:%2 error").arg(bucket).arg(key);
    }
    else
    {
        qDebug()<<QString("upload file %1:%2 success").arg(bucket).arg(key);
        qDebug()<<QString("key: %1").arg(putRet.key);
        qDebug()<<QString("hash: %1").arg(putRet.hash);
    }

    Qiniu_Free(uptoken);
    Qiniu_Client_Cleanup(&client);

    return a.exec();
}

