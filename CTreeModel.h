#pragma once

#pragma region Qt Header Files
#include <QJsonObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QTextEdit>
#pragma endregion

// The basic class of tree node
class CTreeNode : public QObject, public QTreeWidgetItem
{
public:
	enum EGroup
	{
		NoGroup,
		BasicGroup,
		AdvanceGroup,
		ExpertGroup
	};

public:
	CTreeNode(const QString& sKey, const EGroup& eGroup, CTreeNode* pParent);

	// Helper function to apply a function to each nodes
	template<typename FUNC>
	void forEachNode(FUNC func)
	{
		func(this);
		for (int i = 0; i < childCount(); ++i)
		{
			CTreeNode* pNode = (CTreeNode*)(child(i));
			pNode->forEachNode(func);
		}
	}

	template<typename FUNC>
	void forEachNode(FUNC func) const
	{
		func(this);
		for (int i = 0; i < childCount(); ++i)
		{
			CTreeNode* pNode = (CTreeNode*)(child(i));
			pNode->forEachNode(func);
		}
	}

	// Helper function to apply a function to each sub-nodes
	template<typename FUNC>
	void forEachSubNode(FUNC func)
	{
		for (int i = 0; i < childCount(); ++i)
			func((CTreeNode*)(child(i)));
	}

	template<typename FUNC>
	void forEachSubNode(FUNC func) const
	{
		for (int i = 0; i < childCount(); ++i)
			func((CTreeNode*)(child(i)));
	}

	// get the name of this node
	const QString getKey() const
	{
		return text(0);
	}

	// set m_pInforDocument by default format
	virtual void setInfoDocument(const QString& sTitle, const QString& sDesc, const QString& sOptions);
	virtual void setInfoDocument(const QString& sTitle, const QString& sDesc, const QStringList& aOptions);
	virtual void setInfoDocument(const QString& sDesc)
	{
		setInfoDocument(getKey(),sDesc, m_sValueOptions);
	}

	// read from JSON object, need to re-implement
	virtual bool read(const QJsonObject& rJsonNode)
	{
		return false;
	}

	// write to JSON object, need to re-implement
	virtual bool write(QJsonObject& rJsonNode) const
	{
		return false;
	}

	virtual void setValueEditorToTreeWidget();
	virtual void removeValueEditorFromTreeWidget();
	virtual void hideNode(const EGroup& eGroup, bool bHide);

public:
	QWidget*		m_pValueEditor;		// Widget to display, edit value
	QTextDocument*	m_pInforDocument;	// Data to show in information panel
	QStringList		m_sValueOptions;	// Helper data for setInfoDocument(), m_pInforDocument
	EGroup			m_eGroup;			// Group tag to help controlling show/hide

protected:
	bool eventFilter(QObject *obj, QEvent *event);	// special event handler to make show the row is selected
};
