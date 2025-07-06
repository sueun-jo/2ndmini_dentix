#ifndef LOGUTIL_H
#define LOGUTIL_H

#include <QDebug>

#define dprint(msg) \
qDebug().noquote().nospace() << "[DEBUG] [" << __FILE__ << ":" << __LINE__ << "] " << msg

#define wprint(msg) \
                                                                                      qWarning().noquote().nospace() << "[WARN] [" << __FILE__ << ":" << __LINE__ << "] " << msg

#define eprint(msg) \
                                                                                     qCritical().noquote().nospace() << "[ERROR] [" << __FILE__ << ":" << __LINE__ << "] " << msg

#endif // LOGUTIL_H
