#pragma once

#include "ui_CMain.h"

#include "CTreeModel.h"
#include "CEditor.h"

#include <map>

#include <QtWidgets/QWidget>

// The widget of main UI
class CMain : public QWidget
{
	Q_OBJECT
public:
	CMain(QWidget *parent = Q_NULLPTR);

public slots:
	// load JSON file
	void slotLoadProject();

	// save JSON file
	void slotSaveProject();

	// Not implement yet
	void slotPreference();

protected:
	// Structure to map button and node
	struct SMainGroup
	{
		CTreeNode*		pTreeNode;
		QPushButton*	pButton;
	};

protected:
	CEditor*	m_pEditor;		// Editor window
	CTreeNode*	m_pRootNode;	// root of JSON data tree
	std::map<std::string, SMainGroup>	m_mapGroups;	// groups mapiing of JSON

private:
	Ui::CMainClass ui;
};
