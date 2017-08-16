#include "CTreeNodes.h"

#include <typeinfo>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QDoubleValidator>
#include <QEvent>
#include <QFileDialog>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextDocument>
#include <QTextEdit>
#include <QSpinBox>

#include <QJsonArray>
#include <QJsonDocument>

#pragma region Functions of CStringNode
CStringNode::CStringNode(const QString& sKey, const EGroup& eGroup, const QString & sText, CTreeNode * pParent)
	: CTreeNode(sKey, eGroup, pParent)
{
	m_pTextEdit = new QLineEdit(sText);
	m_pTextEdit->installEventFilter(this);
	m_pValueEditor->layout()->addWidget(m_pTextEdit);

	if(sText=="")
		m_sValueOptions << "No default value.";
	else
		m_sValueOptions << "Default value: " + sText;
	setInfoDocument("Input text");
}

bool CStringNode::read(const QJsonObject & rJsonNode)
{
	m_pTextEdit->setText(rJsonNode[getKey()].toString(m_pTextEdit->text()));
	return true;
}

bool CStringNode::write(QJsonObject & rJsonNode) const
{
	rJsonNode[getKey()] = m_pTextEdit->text();
	return true;
}
#pragma endregion

#pragma region Functions of CIntegerNode
CIntegerNode::CIntegerNode(const QString& sKey, const EGroup& eGroup, const int & iValue, TValueLimit<int> mLimit, CTreeNode * pParent)
	: CTreeNode(sKey, eGroup, pParent)
{
	m_pIntegerEdit = new QSpinBox();
	m_pIntegerEdit->installEventFilter(this);
	m_pValueEditor->layout()->addWidget(m_pIntegerEdit);

	m_pIntegerEdit->setRange(mLimit.mMin, mLimit.mMax);
	m_pIntegerEdit->setValue(iValue);
	m_pIntegerEdit->setSingleStep(mLimit.mStep);

	m_sValueOptions << QString( "Default value: %1").arg(iValue)
					<< QString( "Minimum: %1").arg(mLimit.mMin)
					<< QString( "Maximum: %1" ).arg(mLimit.mMax);
	setInfoDocument("Input integer value");
}

bool CIntegerNode::read(const QJsonObject & rJsonNode)
{
	m_pIntegerEdit->setValue(rJsonNode[getKey()].toInt(m_pIntegerEdit->value()));
	return true;
}

bool CIntegerNode::write(QJsonObject & rJsonNode) const
{
	rJsonNode[getKey()] = m_pIntegerEdit->value();
	return true;
}
#pragma endregion

#pragma region Functions of CDoubleNode
CDoubleNode::CDoubleNode(const QString& sKey, const EGroup& eGroup, const double & iValue, const int& iDecimal, TValueLimit<double> mLimit, CTreeNode * pParent)
	: CTreeNode(sKey, eGroup, pParent)
{
	m_pDoubleEdit = new QDoubleSpinBox();
	m_pDoubleEdit->installEventFilter(this);
	m_pValueEditor->layout()->addWidget(m_pDoubleEdit);

	m_pDoubleEdit->setDecimals(iDecimal);
	m_pDoubleEdit->setRange(mLimit.mMin, mLimit.mMax);
	m_pDoubleEdit->setValue(iValue);
	m_pDoubleEdit->setSingleStep(mLimit.mStep);

	m_sValueOptions << QString("Default value: %1").arg(iValue)
					<< QString("Minimum: %1").arg(mLimit.mMin)
					<< QString("Maximum: %1").arg(mLimit.mMax);
	setInfoDocument("Input integer value");
}

bool CDoubleNode::read(const QJsonObject & rJsonNode)
{
	m_pDoubleEdit->setValue(rJsonNode[getKey()].toDouble(m_pDoubleEdit->value()));
	return true;
}

bool CDoubleNode::write(QJsonObject & rJsonNode) const
{
	rJsonNode[getKey()] = m_pDoubleEdit->value();
	return true;
}
#pragma endregion

#pragma region Functions of QScientificSpinBox
class QScientificSpinBox : public QDoubleSpinBox
{
public:
	virtual QString textFromValue(double value) const
	{
		return QString("%1").arg(value);
	}

	virtual QValidator::State validate(QString &text, int &pos) const
	{
		return m_Validator.validate(text, pos);
	}

	virtual void stepBy(int steps)
	{
		setValue(value() + steps * singleStep());
	}

protected:
	QDoubleValidator m_Validator;
};

CScientificNode::CScientificNode(const QString& sKey, const EGroup& eGroup, const double & iValue, const int & iDecimal, TValueLimit<double> mLimit, CTreeNode * pParent)
	: CTreeNode(sKey, eGroup, pParent)
{
	m_pValueEdit = new QScientificSpinBox();
	m_pValueEdit->installEventFilter(this);
	m_pValueEditor->layout()->addWidget(m_pValueEdit);

	m_pValueEdit->setDecimals(iDecimal);
	m_pValueEdit->setRange(mLimit.mMin, mLimit.mMax);
	m_pValueEdit->setValue(iValue);
	m_pValueEdit->setSingleStep(mLimit.mStep);

	m_sValueOptions << QString("Default value: %1").arg(iValue)
		<< QString("Minimum: %1").arg(mLimit.mMin)
		<< QString("Maximum: %1").arg(mLimit.mMax);
	setInfoDocument("Input integer value");
}

bool CScientificNode::read(const QJsonObject & rJsonNode)
{
	m_pValueEdit->setValue(rJsonNode[getKey()].toDouble(m_pValueEdit->value()));
	return true;
}

bool CScientificNode::write(QJsonObject & rJsonNode) const
{
	rJsonNode[getKey()] = m_pValueEdit->value();
	return true;
}
#pragma endregion

#pragma region Functions of CComboBoxNode
CComboBoxNode::CComboBoxNode(const QString& sKey, const EGroup& eGroup, const QStringList & aOptions, int iDefaultOption, CTreeNode * pParent)
	: CTreeNode(sKey, eGroup, pParent)
{
	m_pComboBox = new QComboBox();
	m_pComboBox->installEventFilter(this);
	m_pValueEditor->layout()->addWidget(m_pComboBox);

	m_pComboBox->addItems(aOptions);
	m_pComboBox->setCurrentIndex(iDefaultOption);

	m_sValueOptions << QString("Default value: %1").arg(m_pComboBox->currentText()) << aOptions;
	setInfoDocument("Select an option.");
}

bool CComboBoxNode::read(const QJsonObject & rJsonNode)
{
	m_pComboBox->setCurrentText(rJsonNode[getKey()].toString(m_pComboBox->currentText()));
	return true;
}

bool CComboBoxNode::write(QJsonObject & rJsonNode) const
{
	rJsonNode[getKey()] = m_pComboBox->currentText();
	return true;
}
#pragma endregion

#pragma region Functions of CBooleanNode
bool CBooleanNode::read(const QJsonObject & rJsonNode)
{
	m_pComboBox->setCurrentIndex(rJsonNode[getKey()].toBool(m_pComboBox->currentIndex() == 0) ? 0 : 1 );
	return true;
}

bool CBooleanNode::write(QJsonObject & rJsonNode) const
{
	rJsonNode[getKey()] = ( m_pComboBox->currentIndex() == 0 );
	return true;
}
#pragma endregion

#pragma region Functions of CFileSelectNode
CFileSelectNode::CFileSelectNode(const QString& sKey, const EGroup& eGroup, const QString & sDefaultName, const SFileDialogSetting &sFDS, CTreeNode * pParent)
	: CStringNode(sKey, eGroup, sDefaultName, pParent)
{
	QPushButton* pOpenButton = new QPushButton("...");
	pOpenButton->setFixedWidth(20);

	QLayout* pLayout = m_pValueEditor->layout();
	pLayout->addWidget(pOpenButton);

	CFileSelectNode* pThis = this;
	QObject::connect(pOpenButton, &QPushButton::clicked, [pThis, sFDS]()
	{
		QString sFileName = QFileDialog::getOpenFileName(pThis->m_pTextEdit, sFDS.sCaption, sFDS.sPath, sFDS.sFilter);
		if (sFileName != "")
			pThis->m_pTextEdit->setText(sFileName);
	});

	setInfoDocument("Select a file.");
}
#pragma endregion

#pragma region Functions of CValueListNode
template<typename TYPE>
CValueListNode<TYPE>::CValueListNode(const QString& sKey, const EGroup& eGroup, const QVector<QStringRef>& rList, CTreeNode * pParent)
	: CTreeNode(sKey, eGroup, pParent)
{
	m_pValueList = new QLineEdit();
	m_pValueList->installEventFilter(this);
	m_pValueEditor->layout()->addWidget(m_pValueList);
	
	m_sValueOptions << QString("Value type: %1").arg(typeid(TYPE).name());
	setInfoDocument("<p>This is a list item.</p><p>Please separate each item with comma sign(,).</p>");
}

template<typename TYPE>
bool CValueListNode<TYPE>::read(const QJsonObject & rJsonNode)
{
	QJsonArray mThisNode = rJsonNode[getKey()].toArray();
	QString sValue;
	for (auto rItem : mThisNode)
	{
		QString s = getValue(rItem);
		if(rItem == mThisNode[0])
			sValue = s;
		else
			sValue = sValue + "," + s;
	}
	m_pValueList->setText(sValue);
	return true;
}

template<typename TYPE>
bool CValueListNode<TYPE>::write(QJsonObject & rJsonNode) const
{
	QJsonArray mThisNode;
	QStringList listValue = m_pValueList->text().split(',', QString::SkipEmptyParts);
	for (auto s : listValue)
		mThisNode << setValue(s);
	rJsonNode[getKey()] = mThisNode;
	return true;
}

template<>
QString CValueListNode<int>::getValue(const QJsonValueRef mValue) const
{
	return QString("%1").arg(mValue.toInt());
}

template<>
QString CValueListNode<double>::getValue(const QJsonValueRef mValue) const
{
	return QString("%1").arg(mValue.toDouble());
}

template<>
QString CValueListNode<QString>::getValue(const QJsonValueRef mValue) const
{
	return mValue.toString();
}

template<>
QJsonValue CValueListNode<int>::setValue(const QString& sVal) const
{
	return QJsonValue(sVal.toInt());
}

template<>
QJsonValue CValueListNode<double>::setValue(const QString& sVal) const
{
	return QJsonValue(sVal.toDouble());
}

template<>
QJsonValue CValueListNode<QString>::setValue(const QString& sVal) const
{
	return QJsonValue(sVal);
}

// explicit template specialization
template class CValueListNode<int>;
template class CValueListNode<double>;
template class CValueListNode<QString>;
#pragma endregion

#pragma region Functions of CGroupNode
bool CGroupNode::read(const QJsonObject & rJsonNode)
{
	QJsonObject mThisNode = rJsonNode[getKey()].toObject();
	forEachSubNode([mThisNode](CTreeNode* pNode) {
		pNode->read(mThisNode);
	});
	return true;
}

bool CGroupNode::write(QJsonObject & rJsonNode) const
{
	QJsonObject mThisNode;
	forEachSubNode([&mThisNode](const CTreeNode* pNode) {
		pNode->write(mThisNode);
	});
	rJsonNode[getKey()] = mThisNode;
	return true;
}
#pragma endregion

#pragma region Functions of CListGroup
CListGroup::CListGroup(const QString& sKey, const EGroup& eGroup, const SFileDialogSetting &sFDS, CTreeNode * pParent)
	: CGroupNode(sKey, eGroup, pParent)
{
	CListGroup* pThis = this;
	m_pValueEditor->setFixedWidth(90);
	QLayout* pLayout = m_pValueEditor->layout();

	pLoadButton = new QPushButton("Load");
	if (sFDS.bEnable)
	{
		pLayout->addWidget(pLoadButton);

		QObject::connect(pLoadButton, &QPushButton::clicked, [pThis, sFDS]()
		{
			QString sFileName = QFileDialog::getOpenFileName(pThis->m_pValueEditor, sFDS.sCaption, sFDS.sPath, sFDS.sFilter);
			if (sFileName != "")
				emit pThis->fileSelected(sFileName);
		});
	}

	pAddButton = new QPushButton("Add");
	pLayout->addWidget(pAddButton);

	m_pValueEditor->setLayout(pLayout);

	setInfoDocument("<P>A list group.</P><P>Click \"Load\" to load a file, or click \"Add\" to add a new item.</P>");

	QObject::connect(pAddButton, &QPushButton::clicked, [pThis]()
	{
		pThis->addListItem();
	});
}

bool CListGroup::load(const QString & sFilename)
{
	bool bOK = false;
	QFile loadFile(sFilename);
	if (loadFile.open(QIODevice::ReadOnly))
	{
		// Load JSON File
		QByteArray saveData = loadFile.readAll();
		QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
		if (!loadDoc.isNull())
		{
			QJsonObject mJsonObj = loadDoc.object();
			if (mJsonObj.contains(getKey()))
			{
				bOK = true;
				QJsonArray mThisNode = mJsonObj[getKey()].toArray();
				for (auto rItem : mThisNode)
				{
					CTreeNode* pNode = addListItem();
					if (!pNode->read(rItem.toObject()))
						bOK = false;
				}
			}
		}
	}

	if (!bOK)
	{
		QMessageBox::warning(nullptr, QObject::tr("File format warning"), QObject::tr("There are some format error in this file"));
	}
	return bOK;
}

bool CListGroup::read(const QJsonObject & rJsonNode)
{
	while (childCount() > 0)
		removeChild(child(0));

	QJsonArray mThisNode = rJsonNode[getKey()].toArray();
	for (auto rItem : mThisNode)
	{
		CTreeNode* pNode = addListItem();
		pNode->read(rItem.toObject());
	}
	return true;
}

bool CListGroup::write(QJsonObject & rJsonNode) const
{
	QJsonArray  mThisNode;
	forEachSubNode([&mThisNode](const CTreeNode* pNode) {
		QJsonObject mSubNode;
		pNode->write(mSubNode);
		mThisNode.append(mSubNode);
	});
	rJsonNode[getKey()] = mThisNode;
	return true;
}

void CListGroup::setLoadFromJsonFile()
{
	CListGroup* pThis = this;
	QObject::connect(this, &CListGroup::fileSelected, [pThis](const QString& sFilename)
	{
		pThis->load(sFilename);
	});
}

CTreeNode* CListGroup::addListItem()
{
	CListItemNode* pItem = new CListItemNode(this);
	return pItem;
}
#pragma endregion

#pragma region Functions of CListItemNode
CListItemNode::CListItemNode(CTreeNode * pParent)
	: CGroupNode("<------------------------------------------------->", NoGroup, pParent)
{
	m_pValueEditor->setFixedWidth(90);
	QLayout* pLayout = m_pValueEditor->layout();

	QPushButton* pDelButton = new QPushButton("Delete");
	pLayout->addWidget(pDelButton);

	m_pValueEditor->setLayout(pLayout);

	setInfoDocument("List Item", "<P>A list item.</P><P>Click \"Delete\" to remove this item.</P>", m_sValueOptions);

	QTreeWidgetItem* pThis = this;
	QObject::connect(pDelButton, &QPushButton::clicked, [pThis]() {
		pThis->parent()->removeChild(pThis);
	});
}

bool CListItemNode::read(const QJsonObject & rJsonNode)
{
	forEachSubNode([&rJsonNode](CTreeNode* pNode) {
		pNode->read(rJsonNode);
	});
	return true;
}

bool CListItemNode::write(QJsonObject & rJsonNode) const
{
	forEachSubNode([&rJsonNode](const CTreeNode* pNode) {
		pNode->write(rJsonNode);
	});
	return true;
}
#pragma endregion
