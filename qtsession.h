#ifndef QTSESSION_H
#define QTSESSION_H

#include <QObject>
#include "session.h"

class QtSession : public QObject , public spotify::session
{
  Q_OBJECT;
public:
  QtSession();
  virtual ~QtSession();

public slots:
  void processEvents();

private:
  // Overrides
  virtual void notify_main_thread();
  virtual void log_message(const char* data) const;

};

#endif

