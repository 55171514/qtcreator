/**************************************************************************
**
** Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
**
** Contact: BlackBerry (qt@blackberry.com)
** Contact: KDAB (info@kdab.com)
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef QNX_INTERNAL_BLACKBERRYCREATEPACKAGESTEP_H
#define QNX_INTERNAL_BLACKBERRYCREATEPACKAGESTEP_H

#include "blackberryabstractdeploystep.h"

QT_BEGIN_NAMESPACE
class QFile;
QT_END_NAMESPACE

namespace Qnx {
namespace Internal {

class BlackBerryCreatePackageStep : public BlackBerryAbstractDeployStep
{
    Q_OBJECT
    friend class BlackBerryCreatePackageStepFactory;
    friend class BarDescriptorFileNodeManager;

public:
    enum PackageMode {
        SigningPackageMode,
        DevelopmentMode
    };

    enum BundleMode {
        PreInstalledQt,
        BundleQt,
        DeployedQt
    };

    enum EditMode {
        PlaceHolders = 0x01,
        QtEnvironment = 0x02
    };
    Q_DECLARE_FLAGS(EditModes, EditMode)

    explicit BlackBerryCreatePackageStep(ProjectExplorer::BuildStepList *bsl);

    bool init();
    ProjectExplorer::BuildStepConfigWidget *createConfigWidget();

    QString debugToken() const;

    bool fromMap(const QVariantMap &map);
    QVariantMap toMap() const;

    PackageMode packageMode() const;
    QString cskPassword() const;
    QString keystorePassword() const;
    bool savePasswords() const;

    BundleMode bundleMode() const;
    QString qtLibraryPath() const;

public slots:
    void setPackageMode(PackageMode packageMode);
    void setCskPassword(const QString &cskPassword);
    void setKeystorePassword(const QString &keystorePassword);
    void setSavePasswords(bool savePasswords);

    void setBundleMode(BundleMode bundleMode);
    void setQtLibraryPath(const QString &qtLibraryPath);
    void updateAppDescriptorFile();

signals:
    void cskPasswordChanged(QString);
    void keystorePasswordChanged(QString);

protected:
    BlackBerryCreatePackageStep(ProjectExplorer::BuildStepList *bsl, BlackBerryCreatePackageStep *bs);

    void processStarted(const ProjectExplorer::ProcessParameters &params);

private:
    void ctor();

    bool doUpdateAppDescriptorFile(const Utils::FileName &appDescriptorPath,
                                   QFlags<EditMode> types,
                                   bool skipConfirmation = false);

    QString fullDeployedQtLibraryPath() const;

    PackageMode m_packageMode;
    QString m_cskPassword;
    QString m_keystorePassword;
    bool m_savePasswords;
    BundleMode m_bundleMode;
    QString m_qtLibraryPath;
};

} // namespace Internal
} // namespace Qnx

Q_DECLARE_OPERATORS_FOR_FLAGS(Qnx::Internal::BlackBerryCreatePackageStep::EditModes)

#endif // QNX_INTERNAL_BLACKBERRYCREATEPACKAGESTEP_H
