#ifndef WORKER_HPP
#define WORKER_HPP

#include <QObject>

class Worker : public QObject
{
  Q_OBJECT
public:
    Worker();
    ~Worker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    // add your variables here

};

#endif // WORKER_HPP
