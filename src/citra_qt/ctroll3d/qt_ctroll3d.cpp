// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include "citra_qt/ctroll3d/qt_ctroll3d.h"

namespace CTroll3D {

QtCTroll3D::QtCTroll3D() {

}

void QtCTroll3D::UpdateStatus(char *addr, CTroll3DInfo *info) {
    static CTroll3DInfo buf = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    static char *ptr = (char *)&buf;
    static QTcpSocket sock;
    static unsigned int waitConnection = 0;

    if (addr && (sock.state() != QAbstractSocket::ConnectedState)) {
        if (!waitConnection) {
            waitConnection = 300;
            sock.connectToHost(QObject::tr((const char *)addr), CTROLL3D_INPUT_PORT);
            sock.waitForConnected(1000);
        }
        else waitConnection--;
    }

    if (sock.state() == QAbstractSocket::ConnectedState) {
        int bufRd = (ptr - ((char *)&buf));
        sock.waitForReadyRead(0);
        while(sock.bytesAvailable() > 0) {
            int toRead = CTROLL3DINFO_SZ - bufRd;
            int rd = sock.read(ptr, (toRead > sock.bytesAvailable()) ? sock.bytesAvailable() : toRead);

            if (rd > 0) {
                bufRd += rd;
                ptr += rd;
            }

            if (bufRd == CTROLL3DINFO_SZ) {
                info->pressedButtons = buf.pressedButtons;
                info->cPadX = buf.cPadX;
                info->cPadY = buf.cPadY;
                info->touchX = buf.touchX;
                info->touchY = buf.touchY;
                info->accelX = buf.accelX;
                info->accelY = buf.accelY;
                info->accelZ = buf.accelZ;
                info->gyroX = buf.gyroX;
                info->gyroY = buf.gyroY;
                info->gyroZ = buf.gyroZ;
                ptr = (char *)&buf;
                bufRd = 0;
            }
            sock.waitForReadyRead(0);
        }
    }
}


std::unique_ptr<CTroll3DInterface> QtCTroll3DFactory::Create() {
    return std::make_unique<QtCTroll3D>();
}

} // namespace CTroll3D
