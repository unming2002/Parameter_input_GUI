#include "CTreeModel.h"

#include <QEvent>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>

#pragma region Functions of CTreeNode
CTreeNode::CTreeNode(const QString& sKey, CTreeNode* pParent) : QTreeWidgetItem(pParent)
{
	// Set key value
	setText(0, sKey);
	
	// set size based on second column widget
	setSizeHint(1, QSize(0,24));

	// setup m_pValueEditor
	{
		m_pValueEditor = new QWidget();
		QLayout* pLayout = new QHBoxLayout();
		pLayout->setContentsMargins(1, 1, 1, 1);
		m_pValueEditor->setLayout(pLayout);

		// if created after apply to QTreeWidget, setup widget automatically
		setValueEditorToTreeWidget();
	}

	// default information panel
	m_pInforDocument = new QTextDocument();
}

void CTreeNode::setInfoDocument(const QString & sTitle, const QString & sDesc, const QString & sOptions)
{
	m_pInforDocument->setHtml(
		QString("<H2>%1</H2><HR/><DIV>%2</DIV><HR><DIV>%3</DIV>").arg(sTitle).arg(sDesc).arg(sOptions)
	);
}

void CTreeNode::setInfoDocument(const QString & sTitle, const QString & sDesc, const QStringList & aOptions)
{
	QString sOptionStr;
	if (aOptions.size() > 0)
	{
		sOptionStr = "<P>" + aOptions[0] + "</P>";
		if (aOptions.size() > 1)
		{
			sOptionStr += "<P>Description:</P><UL>";
			for (int i = 1; i < aOptions.size(); ++ i)
				sOptionStr += ("<LI>" + aOptions[i] + "</LI>");
			sOptionStr += "</UL>";
		}
	}
	else
	{
		sOptionStr = "No value limit description";
	}
	setInfoDocument(sTitle,sDesc, sOptionStr);
}
void CTreeNode::setValueEditorToTreeWidget()
{
	QTreeWidget* pTreeWidget = treeWidget();
	if (pTreeWidget != nullptr)
	{
		QWidget* pW = new QWidget();
		QVBoxLayout* pLayout = new QVBoxLayout(pW);
		pLayout->addWidget(m_pValueEditor);
		pLayout->setSpacing(0);
		pLayout->setContentsMargins(0,0,0,0);

		pTreeWidget->setItemWidget(this, 1, pW);
		setExpanded(true);
	}
}

void CTreeNode::removeValueEditorFromTreeWidget()
{
	m_pValueEditor->parentWidget()->layout()->removeWidget(m_pValueEditor);
	m_pValueEditor->setParent(nullptr);
}

bool CTreeNode::eventFilter(QObject * obj, QEvent * pEvent)
{
	if (pEvent->type() == QEvent::FocusIn)
	{
		QTreeWidget* pTWidget = treeWidget();
		if (pTWidget != nullptr)
		{
			pTWidget->setCurrentItem(this, QItemSelectionModel::Rows);
		}
	}
	return false;
}
#pragma endregion
