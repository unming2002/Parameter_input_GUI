#pragma once

#include "ui_CEditor.h"
#include "CTreeNodes.h"

#include <QWidget>

// The qidget to handle data editor
class CEditor : public QWidget
{
	Q_OBJECT

public:
	CEditor(QWidget *parent = Q_NULLPTR);
	~CEditor();

	// set the data to display, shoulde be called before show()
	void setDataTree(CTreeNode* pNode);

private:
	Ui::CEditor ui;
	CTreeNode*	m_pTree;

public slots:
	// The slot used to update information panel, show been trigger when the selected item changed
	void slotItemChanged(QTreeWidgetItem* pCurrent, QTreeWidgetItem* pPrevious);
	void slotShowBasic(bool);
	void slotShowAdvance(bool);
	void slotShowExpert(bool);
	void slotShowAll(bool);
	void slotLoadFile();
	void slotSaveFile();

protected:
	// clear dynmamatic created, linked resource
	void closeEvent(QCloseEvent *event) override;
	CTreeNode* getTree()
	{
		return (CTreeNode*)ui.treeWidget->topLevelItem(0);
	}
};
