//header
#ifndef CHECKEDHEADER_H
#define CHECKEDHEADER_H

#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>

class CheckedHeader : public QHeaderView
{
	Q_OBJECT
public:
	explicit CheckedHeader(Qt::Orientation orientation, QWidget *parent = 0);

	void setChecked(bool checked);

signals:
	void toggled(bool checked);

protected:
	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
	void mousePressEvent(QMouseEvent *event);

private:
	QRect checkBoxRect(const QRect &sourceRect) const;
	bool m_isOn;
};

#endif // CHECKEDHEADER_H
