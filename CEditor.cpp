#include "CEditor.h"
#include "common.h"

CEditor::CEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//ui.treeWidget->setWindowTitle(QStringList() << "Key");

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

void CEditor::slotShowBasic(bool)
{
	//TODO
}

void CEditor::slotShowAdvance(bool)
{
	//TODO
}

void CEditor::slotShowExpert(bool)
{
	//TODO
}

void CEditor::slotShowAll(bool)
{
	//TODO
}

void CEditor::slotLoadFile()
{
	loadJsonFileHelper([this](const QJsonObject& mJsonObj) {
		CTreeNode* pNode = getTree();
		if(pNode!=nullptr)
			return pNode->read(mJsonObj);
	});
}

void CEditor::slotSaveFile()
{
	CTreeNode* pNode = getTree();
	if (pNode != nullptr)
	{
		QJsonObject mJsonObj;
		pNode->write(mJsonObj);
		saveJsonFileHelper(mJsonObj);
	}
}

void CEditor::closeEvent(QCloseEvent*)
{
	CTreeNode* pNode = getTree();
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
