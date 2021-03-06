/***************************************************************************
 *   copyright       : (C) 2013 by Quentin BRAMAS                          *
 *   http://texiteasy.com                                                  *
 *                                                                         *
 *   This file is part of texiteasy.                                          *
 *                                                                         *
 *   texiteasy is free software: you can redistribute it and/or modify        *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   texiteasy is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with texiteasy.  If not, see <http://www.gnu.org/licenses/>.       *                         *
 *                                                                         *
 ***************************************************************************/

#ifndef WIDGETLINENUMBER_H
#define WIDGETLINENUMBER_H

#include <QWidget>
class WidgetTextEdit;
class WidgetFile;
class WidgetLineNumber : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetLineNumber(WidgetFile *parent);
    void setWidgetTextEdit(WidgetTextEdit * widgetTextEdit);
    void setCurrentLine(int line) { _currentLine = line; }
    void highlightCurrentLine() { _highlightCurrentLine = true; }
    void removeHighlight() { _highlightCurrentLine = false; }
signals:
    
public slots:
    void updateFirstVisibleBlock(int, int);
    void setBlockRange(int,int);
    void updateWidth(int lineCount);
protected:
    void paintEvent(QPaintEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
private:
    void drawFoldingBegin(QPainter* painter, int right, int top, int width);
    void drawFoldingEnd(QPainter* painter, int right, int top, int width);
    
    WidgetFile * _widgetFile;
    WidgetTextEdit * widgetTextEdit;
    int scrollOffset;
    int firstVisibleBlock;
    int firstVisibleBlockTop;
    int _startBlock;
    int _currentLine;
    int _endBlock;
    int _zeroWidth;
    int _foldableLineBegin;
    int _foldableLineEnd;
    int _unfoldableLine;
    bool _highlightCurrentLine;
    bool _isMouseOverFolding;
    bool _isMouseOverUnfolding;
    QRect _foldingHover;
    QRect _unfoldHover;
    QPoint _lastMousePos;

    struct UnfoldableLine
    {
        int lineNumber;
        QRect rect;
        bool isMouseOver;
    };
    QList<UnfoldableLine>_unfoldableLines;
};

#endif // WIDGETLINENUMBER_H
