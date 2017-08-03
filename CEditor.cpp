#include "CEditor.h"
#include "NodeUltrapica.h"

CEditor::CEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	#pragma region Header setting
	{
		ui.treeWidget->setHeaderLabels(QStringList() << "Key" << "Value");
		auto pHeader = ui.treeWidget->header();
		pHeader->setDefaultAlignment(Qt::AlignHCenter);
		pHeader->resizeSection(0, 290);
		pHeader->resizeSection(1, 100);
	}
	#pragma endregion

	QList<int> aSizes;
	aSizes << 400 << 220;
	ui.splitter->setSizes(aSizes);
}

CEditor::~CEditor()
{
	
}

void CEditor::setDataTree(CTreeNode * pNode)
{
	if (pNode != nullptr)
	{
		QTreeWidget* pTreeWidget = ui.treeWidget;
		pTreeWidget->insertTopLevelItem(0, pNode);
		pNode->forEachNode([pTreeWidget](CTreeNode* pNode) {
			pNode->setValueEditorToTreeWidget();
			pNode->setExpanded(true);
		});
	}
}

void CEditor::closeEvent(QCloseEvent*)
{
	CTreeNode* pNode = (CTreeNode*)ui.treeWidget->topLevelItem(0);
	if (pNode != nullptr)
	{
		QTreeWidget* pTreeWidget = ui.treeWidget;
		pNode->forEachNode([pTreeWidget](CTreeNode* pSubNode) {
			pSubNode->removeValueEditorFromTreeWidget();
		});
		ui.treeWidget->takeTopLevelItem(0);
	}
}

void CEditor::slotItemChanged(QTreeWidgetItem* pCurrent, QTreeWidgetItem* pPrevious)
{
	if (pCurrent != nullptr)
	{
		CTreeNode* pCurrNode = (CTreeNode*)pCurrent;
		ui.textEdit->setDocument(pCurrNode->m_pInforDocument);;
	}
}
