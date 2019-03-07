// molecular.h
#ifndef MOLECULAR_H
#define MOLECULAR_H

#include "FileIOLib/FileIOHIN.h"
#include <QtGui/QVector3D>
#include <QtGui/QStandardItemModel>

typedef QPair<int, Common::BondFlags> Bond;
typedef QVector<Bond> BondsVector;
Q_DECLARE_METATYPE(BondsVector)

class MolecularSystem
{
public:
	MolecularSystem();
	~MolecularSystem() { clear(); }
	void clear();
	void changeRepresentation();
	bool load(const QString& filename);
	void calculateScope();
public:
	enum { INVISIBLE = 0, LINE, STICK, BALL_AND_STICK, VDW, SES, BACKBONE } representation;
	double diameter;
	QVector3D center;
	QModelIndexList atoms;
	//QModelIndexList residues;
	QModelIndexList molecules;
	QStandardItemModel structuralModel;
};

#define MOLECULE_TAG 101
#define RESIDUE_TAG  102
#define ATOM_TAG     103

#define MINIMUM_GET  Qt::UserRole+1
#define MAXIMUM_GET  Qt::UserRole+2

#define ELEMENT_GET  Qt::UserRole+1
#define POSITION_GET Qt::UserRole+2
#define BONDS_GET    Qt::UserRole+3

extern MolecularSystem molecularSystem;

inline int countAtomsInMolecule(const QModelIndex& moleculeIndex)
{
	return molecularSystem.structuralModel.rowCount(moleculeIndex);
}

inline const QVector3D getMoleculeMinimum(const QModelIndex& moleculeIndex)
{
	return molecularSystem.structuralModel.data(moleculeIndex, MINIMUM_GET).value<QVector3D>();
}

inline void setMoleculeMinimum(const QModelIndex& moleculeIndex, const QVector3D& minimum)
{
	molecularSystem.structuralModel.setData(moleculeIndex, minimum, MINIMUM_GET);
}

inline const QVector3D getMoleculeMaximum(const QModelIndex& moleculeIndex)
{
	return molecularSystem.structuralModel.data(moleculeIndex, MAXIMUM_GET).value<QVector3D>();
}

inline void setMoleculeMaximum(const QModelIndex& moleculeIndex, const QVector3D& maximum)
{
	molecularSystem.structuralModel.setData(moleculeIndex, maximum, MAXIMUM_GET);
}

inline int getElementID(const QModelIndex& atomIndex)
{
	return molecularSystem.structuralModel.data(atomIndex, ELEMENT_GET).toInt();
}

inline bool isAtomSelected(const QModelIndex& atomIndex)
{
	return (molecularSystem.structuralModel.data(atomIndex, Qt::CheckStateRole).toInt() == Qt::Checked);
}

inline QString getAtomLabel(const QModelIndex& atomIndex)
{
	return molecularSystem.structuralModel.data(atomIndex).toString();
}

inline const QVector3D getAtomPosition(const QModelIndex& atomIndex)
{
	return molecularSystem.structuralModel.data(atomIndex, POSITION_GET).value<QVector3D>();
}

inline void setAtomPosition(const QModelIndex& atomIndex, const QVector3D& position)
{
	molecularSystem.structuralModel.setData(atomIndex, position, POSITION_GET);
}

inline BondsVector getAtomBonds(const QModelIndex& atomIndex)
{
	return molecularSystem.structuralModel.data(atomIndex, BONDS_GET).value<BondsVector>();
}

#endif // MOLECULAR_H
