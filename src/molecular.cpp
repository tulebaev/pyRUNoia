// molecular.cpp
#include "molecular.h"

MolecularSystem molecularSystem;

MolecularSystem::MolecularSystem()
{
	representation = LINE;
	structuralModel.setHorizontalHeaderLabels(QStringList() << "Name" << "Type");
}

void MolecularSystem::clear()
{
	atoms.clear();
	molecules.clear();
	structuralModel.removeRows(0, structuralModel.rowCount());
	representation = LINE;
	diameter = 0.0;
	center = QVector3D();
}

void MolecularSystem::changeRepresentation()
{
	if (representation == LINE) { representation = VDW; return; }
	if (representation == VDW) { representation = LINE; return; }
}

bool MolecularSystem::load(const QString& filename)
{
	FileIO::CFileIOHIN hinReader;
	bool loaded = hinReader.ReadContents(filename.toStdString());
	if (!loaded) return false;
	QStandardItem *moleculeItem, *residueItem, *atomItem, *typeItem;
	for (auto& hinMolecule : hinReader.GetMolecules())
	{
		moleculeItem = new QStandardItem(hinMolecule.get()->GetName().c_str());
		moleculeItem->setCheckable(true);
		moleculeItem->setData(QVariant(MOLECULE_TAG), Qt::UserRole);
/*residueItem = new QStandardItem(residue->GetName());
residueItem->setCheckable(true);
residueItem->setData(QVariant(RESIDUE_TAG), Qt::UserRole);*/
		QVector3D moleculeMinimum(+FLT_MAX, +FLT_MAX, +FLT_MAX);
		QVector3D moleculeMaximum(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (auto& atom : hinMolecule.get()->GetAtoms())
		{
			atomItem = new QStandardItem(atom.GetLabel());
			atomItem->setCheckable(true);
			atomItem->setData(QVariant(ATOM_TAG), Qt::UserRole);
			atomItem->setData(QVariant(atom.GetElementID()), ELEMENT_GET);
			double x = atom.GetX();
			double y = atom.GetY();
			double z = atom.GetZ();
			atomItem->setData(QVariant(QVector3D(x,y,z)), POSITION_GET);
			if (moleculeMinimum.x() > x) moleculeMinimum.setX(x);
			if (moleculeMinimum.y() > y) moleculeMinimum.setY(y);
			if (moleculeMinimum.z() > z) moleculeMinimum.setZ(z);
			if (moleculeMaximum.x() < x) moleculeMaximum.setX(x);
			if (moleculeMaximum.y() < y) moleculeMaximum.setY(y);
			if (moleculeMaximum.z() < z) moleculeMaximum.setZ(z);
			QVector<Bond> bonds;
			for (int i = 0; i < atom.GetBondsNumber(); i++)
			{
				auto& bond = atom.GetBond(i);
				bonds.push_back(Bond(bond.first, bond.second));
			}
			atomItem->setData(QVariant::fromValue(bonds), BONDS_GET);
			typeItem = new QStandardItem("Atom"); typeItem->setEnabled(false);
			moleculeItem->appendRow(QList<QStandardItem*>() << atomItem << typeItem);
		}
		moleculeItem->setData(QVariant(moleculeMinimum), MINIMUM_GET);
		moleculeItem->setData(QVariant(moleculeMaximum), MAXIMUM_GET);
		typeItem = new QStandardItem("Molecule"); typeItem->setEnabled(false);
		structuralModel.appendRow(QList<QStandardItem*>() << moleculeItem << typeItem);
	}
	QModelIndex startIndex = structuralModel.index(0,0);
	atoms = structuralModel.match(startIndex, Qt::UserRole, QVariant(ATOM_TAG), -1, Qt::MatchRecursive);
	molecules = structuralModel.match(startIndex, Qt::UserRole, QVariant(MOLECULE_TAG), -1, Qt::MatchRecursive);
	return loaded;
}

void MolecularSystem::calculateScope()
{
	double sysMinX, sysMinY, sysMinZ;
	double sysMaxX, sysMaxY, sysMaxZ;
	sysMinX = sysMinY = sysMinZ = +DBL_MAX;
	sysMaxX = sysMaxY = sysMaxZ = -DBL_MAX;
	for (auto& molecule : molecules)
	{
		QVector3D moleculeMinimum = structuralModel.data(molecule, MINIMUM_GET).value<QVector3D>();
		QVector3D moleculeMaximum = structuralModel.data(molecule, MAXIMUM_GET).value<QVector3D>();
		if (sysMinX > moleculeMinimum.x()) sysMinX = moleculeMinimum.x();
		if (sysMinY > moleculeMinimum.y()) sysMinY = moleculeMinimum.y();
		if (sysMinZ > moleculeMinimum.z()) sysMinZ = moleculeMinimum.z();
		if (sysMaxX < moleculeMaximum.x()) sysMaxX = moleculeMaximum.x();
		if (sysMaxY < moleculeMaximum.y()) sysMaxY = moleculeMaximum.y();
		if (sysMaxZ < moleculeMaximum.z()) sysMaxZ = moleculeMaximum.z();
	}
	center.setX((sysMaxX + sysMinX)/2);
	center.setY((sysMaxY + sysMinY)/2);
	center.setZ((sysMaxZ + sysMinZ)/2);
	double edgeX = sysMaxX - sysMinX;
	double edgeY = sysMaxY - sysMinY;
	double edgeZ = sysMaxZ - sysMinZ;
	diameter = sqrt(edgeX*edgeX + edgeY*edgeY + edgeZ*edgeZ);
}
