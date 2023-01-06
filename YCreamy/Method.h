#ifndef METHOD_H
#endif
#define METHOD_H

#include <Qobject>
#include <Windows.h>
#include <SystemMediaTransportControlsInterop.h>

static HWND wid;

class Method : public QObject
{
	Q_OBJECT
public:
	explicit Method(QObject* parent = nullptr);

public slots:
	void Test();
};