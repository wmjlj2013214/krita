/*
 *  Copyright (c) 2008 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef KIS_GENERATOR_LAYER_H_
#define KIS_GENERATOR_LAYER_H_

#include <QObject>
#include "kis_types.h"
#include "kis_layer.h"
#include <krita_export.h>
#include "kis_node_filter_interface.h"

class KisFilterConfiguration;
class KisNodeVisitor;

/**
 * A generator layer is a special kind of layer that can be prefilled
 * with some pixel pattern generated by a KisGenerator plugin. A KisGenerator
 * is similar to a filter, but doesn't take input pixel data and creates
 * new pixel data.
 *
 * It is not possible to destructively paint on a generator layer.
 *
 * XXX: what about threadedness?
 */
class KRITAIMAGE_EXPORT KisGeneratorLayer : public KisLayer, public KisIndirectPaintingSupport, public KisNodeFilterInterface
{
    Q_OBJECT

public:

    /**
     * Create a new Generator layer with the given configuration and selection.
     * Note that the selection will be _copied_.
     */
    KisGeneratorLayer(KisImageSP img, const QString &name, KisFilterConfiguration * kfc, KisSelectionSP selection);
    KisGeneratorLayer(const KisGeneratorLayer& rhs);
    virtual ~KisGeneratorLayer();

    KisNodeSP clone() const {
        return KisNodeSP(new KisGeneratorLayer(*this));
    }

    bool allowAsChild(KisNodeSP) const;

    void updateProjection(const QRect& r);

    /**
     * return the final result of the layer and all masks
     */
    KisPaintDeviceSP projection() const;

    /**
     * return paint device that the user can paint on. For paint layers,
     * this is the basic, wet painting device, for Generator layers it's
     * the selection.
     */
    KisPaintDeviceSP paintDevice() const;

    QIcon icon() const;
    KoDocumentSectionModel::PropertyList sectionModelProperties() const;

public:

    KisFilterConfiguration * generator() const;
    void setGenerator(KisFilterConfiguration * filterConfig);

    KisSelectionSP selection() const;

    /// Set the selection of this Generator layer to a copy of selection.
    void setSelection(KisSelectionSP selection);

    /**
     * overridden from KisBaseNode
     */
    qint32 x() const;

    /**
     * overridden from KisBaseNode
     */
    void setX(qint32 x);

    /**
     * overridden from KisBaseNode
     */
    qint32 y() const;

    /**
     * overridden from KisBaseNode
     */
    void setY(qint32 y);

    /// Returns an approximation of where the bounds on actual data are in this layer
    QRect extent() const;

    /// Returns the exact bounds of where the actual data resides in this layer
    QRect exactBounds() const;

    bool accept(KisNodeVisitor &);

    void resetCache();

    KisPaintDeviceSP cachedPaintDevice();

    bool showSelection() const;
    void setSelection(bool b);

    QImage createThumbnail(qint32 w, qint32 h);

    // KisIndirectPaintingSupport
    KisLayer* layer() {
        return this;
    }

    KisFilterConfiguration * filter() const { return generator(); }
    void setFilter(KisFilterConfiguration * filterConfig) { setGenerator( filterConfig ); }


private:

    /// re-run the generator. This happens over the bounds of the associated selection.
    void update();

private:

    class Private;
    Private * const m_d;
};

#endif

