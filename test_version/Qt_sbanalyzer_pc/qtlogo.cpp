/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGLWidget>
#include <QMatrix4x4>
#include <QVector3D>

#include <qmath.h>

#include "qtlogo.h"
#include <qgl.h>
#include <gl/GLU.h>
#include <gl/GLU.h>
#include <QGLWidget>
#include <QtGui>
//#include <QGLWidget>

static const qreal tee_height = 0.311126;
static const qreal cross_width = 0.25;
static const qreal bar_thickness = 0.113137;
static const qreal inside_diam = 0.20;
static const qreal outside_diam = 0.30;
static const qreal logo_depth = 0.10;
static const int num_divisions = 32;

//! [0]
struct Geometry
{
    QVector<GLushort> faces;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    void appendSmooth(const QVector3D &a, const QVector3D &n, int from);
    void appendFaceted(const QVector3D &a, const QVector3D &n);
    void finalize();
    void loadArrays() const;
};
//! [0]

//! [1]
class Patch
{
public:
    enum Smoothing { Faceted, Smooth };
    Patch(Geometry *);
    void setSmoothing(Smoothing s) { sm = s; }
    void translate(const QVector3D &t);
    void rotate(qreal deg, QVector3D axis);
    void draw() const;
    void addTri(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &n);
    void addQuad(const QVector3D &a, const QVector3D &b,  const QVector3D &c, const QVector3D &d);

    GLushort start;
    GLushort count;
    GLushort initv;

    GLfloat faceColor[4];
    QMatrix4x4 mat;
    Smoothing sm;
    Geometry *geom;
};
//! [1]

static inline void qSetColor(float colorVec[], QColor c)
{
    colorVec[0] = c.redF();
    colorVec[1] = c.greenF();
    colorVec[2] = c.blueF();
    colorVec[3] = c.alphaF();
}

void Geometry::loadArrays() const
{
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glNormalPointer(GL_FLOAT, 0, normals.constData());
}

void Geometry::finalize()
{
    // TODO: add vertex buffer uploading here

    // Finish smoothing normals by ensuring accumulated normals are returned
    // to length 1.0.
    for (int i = 0; i < normals.count(); ++i)
        normals[i].normalize();
}

void Geometry::appendSmooth(const QVector3D &a, const QVector3D &n, int from)
{
    // Smooth normals are acheived by averaging the normals for faces meeting
    // at a point.  First find the point in geometry already generated
    // (working backwards, since most often the points shared are between faces
    // recently added).
    int v = vertices.count() - 1;
    for ( ; v >= from; --v)
        if (qFuzzyCompare(vertices[v], a))
            break;
    if (v < from)
    {
        // The vert was not found so add it as a new one, and initialize
        // its corresponding normal
        v = vertices.count();
        vertices.append(a);
        normals.append(n);
    }
    else
    {
        // Vert found, accumulate normals into corresponding normal slot.
        // Must call finalize once finished accumulating normals
        normals[v] += n;
    }
    // In both cases (found or not) reference the vert via its index
    faces.append(v);
}

void Geometry::appendFaceted(const QVector3D &a, const QVector3D &n)
{
    // Faceted normals are achieved by duplicating the vert for every
    // normal, so that faces meeting at a vert get a sharp edge.
    int v = vertices.count();
    vertices.append(a);
    normals.append(n);
    faces.append(v);
}

Patch::Patch(Geometry *g)
   : start(g->faces.count())
   , count(0)
   , initv(g->vertices.count())
   , sm(Patch::Smooth)
   , geom(g)
{
    qSetColor(faceColor, QColor(Qt::darkGray));
}

void Patch::rotate(qreal deg, QVector3D axis)
{
    mat.rotate(deg, axis);
}

void Patch::translate(const QVector3D &t)
{
    mat.translate(t);
}

static inline void qMultMatrix(const QMatrix4x4 &mat)
{
    if (sizeof(qreal) == sizeof(GLfloat))
        glMultMatrixf((GLfloat*)mat.constData());
#ifndef QT_OPENGL_ES
    else if (sizeof(qreal) == sizeof(GLdouble))
        glMultMatrixd((GLdouble*)mat.constData());
#endif
    else
    {
        GLfloat fmat[16];
        qreal const *r = mat.constData();
        for (int i = 0; i < 16; ++i)
            fmat[i] = r[i];
        glMultMatrixf(fmat);
    }
}

//! [2]
void Patch::draw() const
{
    glPushMatrix();
    qMultMatrix(mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faceColor);

    const GLushort *indices = geom->faces.constData();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, indices + start);
    glPopMatrix();
}
//! [2]

void Patch::addTri(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &n)
{
    QVector3D norm = n.isNull() ? QVector3D::normal(a, b, c) : n;
    if (sm == Smooth)
    {
        geom->appendSmooth(a, norm, initv);
        geom->appendSmooth(b, norm, initv);
        geom->appendSmooth(c, norm, initv);
    }
    else
    {
        geom->appendFaceted(a, norm);
        geom->appendFaceted(b, norm);
        geom->appendFaceted(c, norm);
    }
    count += 3;
}

void Patch::addQuad(const QVector3D &a, const QVector3D &b,  const QVector3D &c, const QVector3D &d)
{
    QVector3D norm = QVector3D::normal(a, b, c);
    if (sm == Smooth)
    {
        addTri(a, b, c, norm);
        addTri(a, c, d, norm);
    }
    else
    {
        // If faceted share the two common verts
        addTri(a, b, c, norm);
        int k = geom->vertices.count();
        geom->appendSmooth(a, norm, k);
        geom->appendSmooth(c, norm, k);
        geom->appendFaceted(d, norm);
        count += 3;
    }
}

static inline QVector<QVector3D> extrude(const QVector<QVector3D> &verts, qreal depth)
{
    QVector<QVector3D> extr = verts;
    for (int v = 0; v < extr.count(); ++v)
        extr[v].setZ(extr[v].z() - depth);
    return extr;
}

class Rectoid
{
public:
    void translate(const QVector3D &t)
    {
        for (int i = 0; i < parts.count(); ++i)
            parts[i]->translate(t);
    }
    void rotate(qreal deg, QVector3D axis)
    {
        for (int i = 0; i < parts.count(); ++i)
            parts[i]->rotate(deg, axis);
    }

    // No special Rectoid destructor - the parts are fetched out of this member
    // variable, and destroyed by the new owner
    QList<Patch*> parts;
};

class RectPrism : public Rectoid
{
public:
    RectPrism(Geometry *g, qreal width, qreal height, qreal depth);
};

RectPrism::RectPrism(Geometry *g, qreal width, qreal height, qreal depth)
{
    enum { bl, br, tr, tl };
    Patch *fb = new Patch(g);
    fb->setSmoothing(Patch::Faceted);

    // front face
    QVector<QVector3D> r(4);
    r[br].setX(width);
    r[tr].setX(width);
    r[tr].setY(height);
    r[tl].setY(height);
    QVector3D adjToCenter(-width / 2.0, -height / 2.0, depth / 2.0);
    for (int i = 0; i < 4; ++i)
        r[i] += adjToCenter;
    fb->addQuad(r[bl], r[br], r[tr], r[tl]);

    // back face
    QVector<QVector3D> s = extrude(r, depth);
    fb->addQuad(s[tl], s[tr], s[br], s[bl]);

    // side faces
    Patch *sides = new Patch(g);
    sides->setSmoothing(Patch::Faceted);
    sides->addQuad(s[bl], s[br], r[br], r[bl]);
    sides->addQuad(s[br], s[tr], r[tr], r[br]);
    sides->addQuad(s[tr], s[tl], r[tl], r[tr]);
    sides->addQuad(s[tl], s[bl], r[bl], r[tl]);

    parts << fb << sides;
}

class RectTorus : public Rectoid
{
public:
    RectTorus(Geometry *g, qreal iRad, qreal oRad, qreal depth, int numSectors);
};

RectTorus::RectTorus(Geometry *g, qreal iRad, qreal oRad, qreal depth, int k)
{
    QVector<QVector3D> inside;
    QVector<QVector3D> outside;
    for (int i = 0; i < k; ++i) {
        qreal angle = (i * 2 * M_PI) / k;
        inside << QVector3D(iRad * qSin(angle), iRad * qCos(angle), depth / 2.0);
        outside << QVector3D(oRad * qSin(angle), oRad * qCos(angle), depth / 2.0);
    }
    inside << QVector3D(0.0, iRad, 0.0);
    outside << QVector3D(0.0, oRad, 0.0);
    QVector<QVector3D> in_back = extrude(inside, depth);
    QVector<QVector3D> out_back = extrude(outside, depth);

    // Create front, back and sides as separate patches so that smooth normals
    // are generated for the curving sides, but a faceted edge is created between
    // sides and front/back
    Patch *front = new Patch(g);
    for (int i = 0; i < k; ++i)
        front->addQuad(outside[i], inside[i],
                       inside[(i + 1) % k], outside[(i + 1) % k]);
    Patch *back = new Patch(g);
    for (int i = 0; i < k; ++i)
        back->addQuad(in_back[i], out_back[i],
                      out_back[(i + 1) % k], in_back[(i + 1) % k]);
    Patch *is = new Patch(g);
    for (int i = 0; i < k; ++i)
        is->addQuad(in_back[i], in_back[(i + 1) % k],
                    inside[(i + 1) % k], inside[i]);
    Patch *os = new Patch(g);
    for (int i = 0; i < k; ++i)
        os->addQuad(out_back[(i + 1) % k], out_back[i],
                    outside[i], outside[(i + 1) % k]);
    parts << front << back << is << os;
}

QtLogo::QtLogo(QObject *parent, int divisions, qreal scale)
    : QObject(parent)
    , geom(new Geometry())
{
    buildGeometry(divisions, scale);
}

QtLogo::~QtLogo()
{
    qDeleteAll(parts);
    delete geom;
}

void QtLogo::setColor(QColor c)
{
    for (int i = 0; i < parts.count(); ++i)
        qSetColor(parts[i]->faceColor, c);
}

//! [3]
void QtLogo::buildGeometry(int divisions, qreal scale)
{
//    qreal cw = cross_width * scale;
//       qreal bt = bar_thickness * scale;
//       qreal ld = logo_depth * scale;
//       qreal th = tee_height *scale;

   //    RectPrism cross(geom, cw, bt, ld);
   //    RectPrism stem(geom, bt, th, ld);
   //    RectPrism stem(geom, bt, th, ld);

       QVector3D z(0.0, 0.0, 1.0);
       QVector3D x(1.0, 0.0, 0.0);
       QVector3D y(0.0, 1.0, 0.0);
     //  cross.rotate(45.0, z);
     //  stem.rotate(45.0, z);

       //qreal stem_downshift = (th + bt) / 2.0;
       //stem.translate(QVector3D(0.0, -stem_downshift, 0.0));
       QColor black(0,0,0);
        QColor brown(240,120,0);
        QColor deck(232,100,36);
        QColor wheel(0,0,70);
        QColor truck(100,100,100);


       RectPrism blat(geom, 0.6, 0.2, 0.015);
       qSetColor(blat.parts[0]->faceColor, black);
       qSetColor(blat.parts[1]->faceColor, brown);

       RectTorus nose(geom, 0.0/*20*/, 0.1, 0.015, divisions);
       nose.translate(QVector3D(0.3, 0.0, 0.0));

       qSetColor(nose.parts[0]->faceColor, black);
       qSetColor(nose.parts[1]->faceColor, black);
       qSetColor(nose.parts[2]->faceColor, black);
       qSetColor(nose.parts[3]->faceColor, brown);

       RectTorus tail1(geom, 0.0/*20*/, 0.07, 0.015, divisions);
       tail1.translate(QVector3D(-0.3, 0.03, 0.0));
       qSetColor(tail1.parts[0]->faceColor, black);
       qSetColor(tail1.parts[1]->faceColor, black);
       qSetColor(tail1.parts[2]->faceColor, black);
       qSetColor(tail1.parts[3]->faceColor, brown);

       RectTorus tail2(geom, 0.0/*20*/, 0.07, 0.015, divisions);
       tail2.translate(QVector3D(-0.3, -0.03, 0.0));
       qSetColor(tail2.parts[0]->faceColor, black);
       qSetColor(tail2.parts[1]->faceColor, black);
       qSetColor(tail2.parts[2]->faceColor, black);
       qSetColor(tail2.parts[3]->faceColor, brown);

       RectPrism tail3(geom, 0.2, 0.06, 0.015);
       tail3.translate(QVector3D(-0.27, 0.0, 0.0));
       qSetColor(tail3.parts[0]->faceColor, black);
       qSetColor(tail3.parts[1]->faceColor, brown);

       RectPrism blat2(geom, 0.6, 0.2, 0.015);
       blat2.translate(QVector3D(0.0, 0.0, -0.005));
       qSetColor(blat2.parts[0]->faceColor, deck);
       qSetColor(blat2.parts[1]->faceColor, brown);

       RectTorus nose2(geom, 0.0/*20*/, 0.1, 0.015, divisions);
       nose2.translate(QVector3D(0.3, 0.0, -0.005));
       qSetColor(nose2.parts[0]->faceColor, deck);
       qSetColor(nose2.parts[1]->faceColor, deck);
       qSetColor(nose2.parts[2]->faceColor, deck);
       qSetColor(nose2.parts[3]->faceColor, brown);

       RectTorus tail12(geom, 0.00/*20*/, 0.07, 0.015, divisions);
       tail12.translate(QVector3D(-0.3, 0.03, -0.005));
       qSetColor(tail12.parts[0]->faceColor, deck);
       qSetColor(tail12.parts[1]->faceColor, deck);
       qSetColor(tail12.parts[2]->faceColor, deck);
       qSetColor(tail12.parts[3]->faceColor, brown);

       RectTorus tail22(geom, 0.0/*20*/, 0.07, 0.015, divisions);
       tail22.translate(QVector3D(-0.3, -0.03, -0.005));
       qSetColor(tail22.parts[0]->faceColor, deck);
       qSetColor(tail22.parts[1]->faceColor, deck);
       qSetColor(tail22.parts[2]->faceColor, deck);
       qSetColor(tail22.parts[3]->faceColor, brown);

       RectPrism tail32(geom, 0.2, 0.06, 0.015);
       tail32.translate(QVector3D(-0.27, 0.0, -0.005));
       qSetColor(tail32.parts[0]->faceColor, deck);
       qSetColor(tail32.parts[1]->faceColor, brown);

       RectTorus weel1(geom, 0.01/*20*/, 0.035, 0.04, divisions);
       weel1.translate(QVector3D(0.24, 0.07, -0.05));
       weel1.rotate(90,x);
       qSetColor(weel1.parts[0]->faceColor, wheel);
       qSetColor(weel1.parts[1]->faceColor, wheel);
       qSetColor(weel1.parts[2]->faceColor, wheel);
       qSetColor(weel1.parts[3]->faceColor, wheel);

       RectTorus weel2(geom, 0.01/*20*/, 0.035, 0.04, divisions);
       weel2.translate(QVector3D(0.24, -0.07, -0.05));
       weel2.rotate(90,x);
       qSetColor(weel2.parts[0]->faceColor, wheel);
       qSetColor(weel2.parts[1]->faceColor, wheel);
       qSetColor(weel2.parts[2]->faceColor, wheel);
       qSetColor(weel2.parts[3]->faceColor, wheel);

       RectTorus weel3(geom, 0.01/*20*/, 0.035, 0.04, divisions);
       weel3.translate(QVector3D(-0.23, 0.07, -0.05));
       weel3.rotate(90,x);
       qSetColor(weel3.parts[0]->faceColor, wheel);
       qSetColor(weel3.parts[1]->faceColor, wheel);
       qSetColor(weel3.parts[2]->faceColor, wheel);
       qSetColor(weel3.parts[3]->faceColor, wheel);

       RectTorus weel4(geom, 0.01/*20*/, 0.035, 0.04, divisions);
       weel4.translate(QVector3D(-0.23, -0.07, -0.05));
       weel4.rotate(90,x);
       qSetColor(weel4.parts[0]->faceColor, wheel);
       qSetColor(weel4.parts[1]->faceColor, wheel);
       qSetColor(weel4.parts[2]->faceColor, wheel);
       qSetColor(weel4.parts[3]->faceColor, wheel);

       RectTorus ax1(geom, 0.0/*20*/, 0.015, 0.10, divisions);
       ax1.translate(QVector3D(-0.23, 0.0, -0.05));
       ax1.rotate(90,x);
       qSetColor(ax1.parts[0]->faceColor, truck);
       qSetColor(ax1.parts[1]->faceColor, truck);
       qSetColor(ax1.parts[2]->faceColor, truck);
       qSetColor(ax1.parts[3]->faceColor, truck);

       RectTorus ax2(geom, 0.0/*20*/, 0.015, 0.10, divisions);
       ax2.translate(QVector3D(0.24, 0.0, -0.05));
       ax2.rotate(90,x);
       qSetColor(ax2.parts[0]->faceColor, truck);
       qSetColor(ax2.parts[1]->faceColor, truck);
       qSetColor(ax2.parts[2]->faceColor, truck);
       qSetColor(ax2.parts[3]->faceColor, truck);

       RectTorus truck1(geom, 0.008/*20*/, 0.025, 0.045, divisions);
       truck1.translate(QVector3D(0.23, 0.0, -0.03));
       qSetColor(truck1.parts[0]->faceColor, truck);
       qSetColor(truck1.parts[1]->faceColor, truck);
       qSetColor(truck1.parts[2]->faceColor, truck);
       qSetColor(truck1.parts[3]->faceColor, truck);

       RectTorus truck2(geom, 0.008/*20*/, 0.025, 0.045, divisions);
       truck2.translate(QVector3D(-0.22, 0.0, -0.03));
       qSetColor(truck2.parts[0]->faceColor, truck);
       qSetColor(truck2.parts[1]->faceColor, truck);
       qSetColor(truck2.parts[2]->faceColor, truck);
       qSetColor(truck2.parts[3]->faceColor, truck);

        RectPrism truck3(geom, 0.08, 0.06, 0.015);
        truck3.translate(QVector3D(0.23, 0.0, -0.01));
        qSetColor(truck3.parts[0]->faceColor, truck);
        qSetColor(truck3.parts[1]->faceColor, truck);

        RectPrism truck4(geom, 0.08, 0.06, 0.015);
        truck4.translate(QVector3D(-0.22, 0.0, -0.01));
        qSetColor(truck4.parts[0]->faceColor, truck);
        qSetColor(truck4.parts[1]->faceColor, truck);
       //ax2.rotate(90,y);
       //body.rotate(90, x);
      // body.translate(QVector3D(0.0, -stem_downshift, 0.0));

       parts<< blat.parts <<nose.parts
                               <<tail1.parts<<tail2.parts<<tail3.parts
                              << blat2.parts <<nose2.parts
                               <<tail12.parts<<tail22.parts<<tail32.parts
                               << weel1.parts<< weel2.parts<< weel3.parts<< weel4.parts
                               <<ax1.parts<<ax2.parts
                                 <<truck1.parts<<truck2.parts<<truck3.parts<<truck4.parts;

       geom->finalize();
}
//! [3]

//! [4]
void QtLogo::draw() const
{
    geom->loadArrays();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for (int i = 0; i < parts.count(); ++i)
        parts[i]->draw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
//! [4]
