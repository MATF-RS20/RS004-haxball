#include "worker.hpp"

#include <QDebug>

// --- CONSTRUCTOR ---
Worker::Worker() {
    // you could copy data from constructor arguments to internal variables here.
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void Worker::process() {
  qDebug() << "[process] Worker";

  while(true)
    {
      qDebug("Hello World!");
    }
    emit finished();
}
