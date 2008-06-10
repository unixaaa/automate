//
// C++ Interface: GraphicsScene
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPersistentModelIndex>
#include <QGraphicsTextItem>
#include <QVariant>
#include <QDebug>
#include <QKeyEvent>

#include <QPrinter>
#include <QPrintDialog>

#include "Model.h"
#include "SceneItem_Node.h"
#include "SceneItem_Connection.h"

/**
 @author Joachim Schiele <js@lastlog.de>
*/
class GraphicsScene : public QGraphicsScene {
    friend class SceneItem_Node;
    friend class SceneItem_Connection;
    friend class ItemView;
    Q_OBJECT
  public:
    GraphicsScene( Model *model );
    ~GraphicsScene();
    bool want_highlight();
    bool want_boundingBox();
    bool want_drawItemShape();
    bool want_coloredConnectionHelper();
    bool want_customNodeLabels();
    bool want_customConnectionLabels();
  protected:
    QGraphicsItem* nodeInserted( QPersistentModelIndex item );
    QGraphicsItem* connectionInserted( QPersistentModelIndex item );
    void updateNode( QPersistentModelIndex item );
    void updateConnection( QPersistentModelIndex item );
    bool nodeRemoved( QPersistentModelIndex item );
    bool connectionRemoved( QPersistentModelIndex item );
    void reset();

  protected:
    QVariant data( const QModelIndex &index, int role ) const;

  private:
    bool m_want_highlight;
    bool m_want_boundingBox;
    bool m_want_drawItemShape;
    bool m_want_coloredConnectionHelper;
    bool m_want_customNodeLabels;
    bool m_want_customConnectionLabels;
    QGraphicsItem* modelToSceenIndex( QPersistentModelIndex index );
    QGraphicsLineItem *line;
    Model *model;
    void keyPressEvent( QKeyEvent * keyEvent );
    void mousePressEvent( QGraphicsSceneMouseEvent * event );
    void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );

    void updateNode( QGraphicsItem* item );
    void updateConnection( QGraphicsItem* item );
    bool compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b );

  public slots:
    void insertNode();

  private slots:
    void selectionChanged();
    void toggleHighlight();

  protected slots:
    void toggleEvent( int role );
    void toggleFinalEvent();
    void toggleStartEvent();
    void removeEvent();
    void print();
    void toggleBoundingBox();
    void toggleDrawItemShape();
    void toggle_coloredConnectionHelper();
    void toggle_customConnectionLabels();
    void toggle_customNodeLabels();
  signals:
    void hideView();
    void toggleRenderHints();
    void zoomOut();
    void zoomIn();
};

#endif