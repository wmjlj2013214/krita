/* This file is part of the KDE project
 * Made by Tomislav Lukman (tomislav.lukman@ck.tel.hr)
 * Copyright (C) 2012 Jean-Nicolas Artaud <jeannicolasartaud@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef FILLCONFIGWIDGET_H
#define FILLCONFIGWIDGET_H

#include "kritaui_export.h"

#include <QWidget>
#include <QSharedPointer>
#include <KoFlake.h>
#include <KoFlakeTypes.h>

class KoCanvasBase;
class KoShapeBackground;
class KoShape;

/// A widget for configuring the fill of a shape
class KRITAUI_EXPORT KoFillConfigWidget : public QWidget
{
    Q_OBJECT
    enum StyleButton {
        None = 0,
        Solid,
        Gradient,
        Pattern
    };

public:
    explicit KoFillConfigWidget(KoFlake::FillVariant fillVariant, QWidget *parent);
    ~KoFillConfigWidget();

    void setNoSelectionTrackingMode(bool value);

    /// Returns the list of the selected shape
    /// If you need to use only one shape, call currentShape()
    QList<KoShape*> currentShapes();

    KoShapeStrokeSP createShapeStroke();

    void activate();
    void deactivate();

private Q_SLOTS:
    void styleButtonPressed(int buttonId);

    void noColorSelected();

    /// apply color changes to the selected shape
    void colorChanged();

    /// the pattern of the fill changed, apply the changes
    void patternChanged(QSharedPointer<KoShapeBackground> background);

    void shapeChanged();

    void slotUpdateFillTitle();

    void slotCanvasResourceChanged(int key, const QVariant &value);

    void slotSavePredefinedGradientClicked();

    void activeGradientChanged();
    void gradientResourceChanged();

    void slotGradientTypeChanged();
    void slotGradientRepeatChanged();

    void slotProposeCurrentColorToResourceManager();

Q_SIGNALS:
    void sigFillChanged();

    void sigInternalRequestColorToResourceManager();

private:
    /// update the widget with the KoShape background
    void updateWidget(KoShape *shape);

    void uploadNewGradientBackground(const QGradient *gradient);
    void setNewGradientBackgroundToShape();
    void updateGradientSaveButtonAvailability();
    void loadCurrentFillFromResourceServer();

    class Private;
    Private * const d;
};

#endif // FILLCONFIGWIDGET_H
