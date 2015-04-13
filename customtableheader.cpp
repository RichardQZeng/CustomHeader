//=========================================================================================================
//implementation
#include "customtableheader.h"

CheckedHeader::CheckedHeader(Qt::Orientation orientation, QWidget *parent)
	: QHeaderView(orientation, parent)
	, m_isOn(false)
{
	//setChecked(true);
}

void CheckedHeader::setChecked(bool checked)
{
	if (isEnabled() && m_isOn != checked)
	{
		m_isOn = checked;
		updateSection(0);
		emit toggled(m_isOn);
	}
}

void CheckedHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
	painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex);
	painter->restore();

	if (logicalIndex == 0)
	{
		QStyleOptionButton option;
		
		if (isEnabled())
			option.state |= QStyle::State_Enabled;
		
		option.rect = checkBoxRect(rect);
		
		if (m_isOn)
			option.state |= QStyle::State_On;
		else
			option.state |= QStyle::State_Off;

		style()->drawControl(QStyle::CE_CheckBox, &option, painter);
	}
}

void CheckedHeader::mousePressEvent(QMouseEvent *event)
{
	if (isEnabled() && logicalIndexAt(event->pos()) == 0)
	{
		m_isOn = !m_isOn;
		updateSection(0);
		emit toggled(m_isOn);
	}
	else
	{
		QHeaderView::mousePressEvent(event);
	}
}

QRect CheckedHeader::checkBoxRect(const QRect &sourceRect) const
{
	QStyleOptionButton checkBoxStyleOption;

	QRect checkBoxRect = style()->subElementRect(QStyle::SE_CheckBoxIndicator, 
		&checkBoxStyleOption);

	QPoint checkBoxPoint(sourceRect.x() + 3,
		sourceRect.y() + sourceRect.height() / 2 - checkBoxRect.height() / 2);

	return QRect(checkBoxPoint, checkBoxRect.size());
}

