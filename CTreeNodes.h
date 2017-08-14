#pragma once

#include "CTreeModel.h"

#include <QObject>

class QComboBox;
class QDoubleSpinBox;
class QLineEdit;
class QPushButton;
class QSpinBox;

// A helper structure for CIntegerNode and CDoubleNode
template<typename DType>
struct TValueLimit
{
	DType	mMin;
	DType	mMax;
	DType	mStep;
};

// A helper structure for CListGroup and CFileSelectNode
struct SFileDialogSetting
{
	bool	bEnable;	// false to hide button in CListGroup
	QString	sCaption;	// dialog caption
	QString	sPath;		// default path
	QString	sFilter;	// Example: "Mesh file (*.uns);;All files (*.*)"
};

// The node for general text
class CStringNode : public CTreeNode
{
public:
	// parameters: key, default value, parent node
	CStringNode(const QString& sKey, const QString& sText, CTreeNode* pParent);
	virtual bool read(const QJsonObject& rJsonNode) override;
	virtual bool write(QJsonObject& rJsonNode) const override;

public:
	QLineEdit* m_pTextEdit;
};

// The node for int value
class CIntegerNode : public CTreeNode
{
public:
	// parameters: key, default value, limits and step, parent node
	CIntegerNode(const QString& sKey, const int& iValue, TValueLimit<int> mLimit, CTreeNode* pParent);
	bool read(const QJsonObject & rJsonNode) override;
	bool write(QJsonObject & rJsonNode) const override;

public:
	QSpinBox*	m_pIntegerEdit;
};

// The node for double value
class CDoubleNode : public CTreeNode
{
public:
	// parameters: key, default value, decimal to use, limits and step, parent node
	CDoubleNode(const QString& sKey, const double& iValue, const int& iDecimal, TValueLimit<double> mLimit, CTreeNode* pParent);
	bool read(const QJsonObject & rJsonNode) override;
	bool write(QJsonObject & rJsonNode) const override;

public:
	QDoubleSpinBox*	m_pDoubleEdit;
};

// General case for multiple options value
class CComboBoxNode : public CTreeNode
{
public:
	// parameters: key, option list, default index, parent node
	CComboBoxNode(const QString& sKey, const QStringList& aOptions, int iDefaultOption, CTreeNode* pParent);
	virtual bool read(const QJsonObject& rJsonNode) override;
	virtual bool write(QJsonObject& rJsonNode) const override;

public:
	QComboBox* m_pComboBox;
};

// A special case of CComboBoxNode, true / false only
class CBooleanNode : public CComboBoxNode
{
public:
	// parameters: key, default value, parent node
	CBooleanNode(const QString& sKey, bool bDefaultValue, CTreeNode* pParent)
		: CComboBoxNode(sKey, QStringList() << "True" << "False", (bDefaultValue ? 0 : 1), pParent){}

	virtual bool read(const QJsonObject& rJsonNode) override;
	virtual bool write(QJsonObject& rJsonNode) const override;
};

// The node to select file
class CFileSelectNode : public CStringNode
{
public:
	// parameters: key, default value, file dialog setting, parent node
	CFileSelectNode(const QString& sKey, const QString& sDefaultName, const SFileDialogSetting &sFDS, CTreeNode* pParent);
};

// Simple type list node, support int, double, QString
//TODO: may need a better editor design
template<typename TYPE>
class CValueListNode : public CTreeNode
{
public:
	// parameters: key, a list of values, parent node
	CValueListNode(const QString& sKey, const QVector<QStringRef>& rList, CTreeNode* pParent);
	virtual bool read(const QJsonObject& rJsonNode) override;
	virtual bool write(QJsonObject& rJsonNode) const override;

protected:
	QLineEdit*	m_pValueList;

protected:
	QString getValue(const QJsonValueRef mValue) const;
	QJsonValue setValue(const QString& sVal) const;
};

// General group
class CGroupNode : public CTreeNode
{
public:
	// parameters: key, parent node
	CGroupNode(const QString& sKey, CTreeNode* pParent) : CTreeNode(sKey, pParent){}
	virtual bool read(const QJsonObject& rJsonNode) override;
	virtual bool write(QJsonObject& rJsonNode) const override;
};

// A special case of CGroupNode, which own multiple childe(CListItemNode)
// Have load, add button.
class CListGroup : public CGroupNode
{
	Q_OBJECT

public:
	// parameters: key, file dialog setting, parent node
	CListGroup(const QString& sKey, const SFileDialogSetting &sFDS, CTreeNode* pParent);
	virtual bool load(const QString& sFilename);
	virtual bool read(const QJsonObject& rJsonNode) override;
	virtual bool write(QJsonObject& rJsonNode) const override;

	void setLoadFromJsonFile();
	// return a sub item node, recommand to base on CListItemNode
	virtual CTreeNode* addListItem();

signals:
	// signal for open file
	void fileSelected(const QString& sFilename);

protected:
	QPushButton* pLoadButton;
	QPushButton* pAddButton;
};

// The sub-item of CListGroup
class CListItemNode : public CGroupNode
{
public:
	// This node work wit no-key
	CListItemNode(CTreeNode* pParent);
	virtual bool read(const QJsonObject& rJsonNode) override;
	virtual bool write(QJsonObject& rJsonNode) const override;
};
