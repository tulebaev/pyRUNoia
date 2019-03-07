#include "PeriodicTable.h"

namespace Common
{
	// http://periodictable.com/Properties/A/AtomicWeight.an.html
	// http://www.crystalmaker.com/support/tutorials/crystalmaker/atomicradii/
	// http://periodictable.com/Properties/A/Electronegativity.an.html
	// For some elements, absent parameters are substituted with defaults of '0'/'1'.

	CPeriodicTable::Element CPeriodicTable::m_Elements[ePTENumberOfElements + 1] =
	{
		//Number	Element	Period	Group	Block	Weight	FullName	ShortName	AtomicRadius,A	IonicRadius,A	CovalentRadius,A	VdWRadius,A	"Crystal"Radius,A	Electronegativity
		CPeriodicTable::Element( 0,		LP,	0,	0,	_ComStr('-'),	0,				_ComStr("Lone_pair"),		_ComStr("LP"),	0,		0,		0,		0,		0,		0		 ),
		CPeriodicTable::Element( 1,		H,	1,	1,	_ComStr('s'),	1.00794,	_ComStr("Hydrogen"),		_ComStr("H"),		0.53,	0.25,	0.37,	1,		0.10,	2.2	 ),
		CPeriodicTable::Element( 2,		He,	1,	18,	_ComStr('p'),	4.002602,	_ComStr("Helium"),			_ComStr("He"),	0.31,	0.31,	0.32,	1.40,	1,		0		 ),
		CPeriodicTable::Element( 3,		Li,	2,	1,	_ComStr('s'),	6.941,		_ComStr("Lithium"),			_ComStr("Li"),	1.67,	1.45,	1.34,	1.82,	0.90,	0.98 ),
		CPeriodicTable::Element( 4,		Be,	2,	2,	_ComStr('s'),	9.012182,	_ComStr("Beryllium"),		_ComStr("Be"),	1.12,	1.05,	0.90,	1,		0.41,	1.57 ),
		CPeriodicTable::Element( 5,		B,	2,	13,	_ComStr('p'),	10.811,		_ComStr("Boron"),				_ComStr("B"),		0.87,	0.85,	0.82,	1,		0.25,	2.04 ),
		CPeriodicTable::Element( 6,		C,	2,	14,	_ComStr('p'),	12.0107,	_ComStr("Carbon"),			_ComStr("C"),		0.67,	0.70,	0.77,	1.63,	0.29,	2.55 ),
		CPeriodicTable::Element( 7,		N,	2,	15,	_ComStr('p'),	14.0067,	_ComStr("Nitrogen"),		_ComStr("N"),		0.56,	0.65,	0.75,	1.51,	0.30,	3.04 ),
		CPeriodicTable::Element( 8,		O,	2,	16,	_ComStr('p'),	15.9994,	_ComStr("Oxygen"),			_ComStr("O"),		0.48,	0.60,	0.73,	1.36,	1.21,	3.44 ),
		CPeriodicTable::Element( 9,		F,	2,	17,	_ComStr('p'),	18.9984032,_ComStr("Fluorine"),		_ComStr("F"),		0.42,	0.50,	0.71,	1.47,	1.19,	3.98 ),
		CPeriodicTable::Element( 10,	Ne,	2,	18,	_ComStr('p'),	20.1797,	_ComStr("Neon"),				_ComStr("Ne"),	0.38,	0.38,	0.69,	1.54,	1,		0		 ),
		CPeriodicTable::Element( 11,	Na,	3,	1,	_ComStr('s'),	22.98977,	_ComStr("Sodium"),			_ComStr("Na"),	1.90,	1.80,	1.54,	1.50,	1.16,	0.93 ),
		CPeriodicTable::Element( 12,	Mg,	3,	2,	_ComStr('s'),	24.305,		_ComStr("Magnesium"),		_ComStr("Mg"),	1.45,	1.50,	1.30,	1.50,	0.86,	1.31 ),
		CPeriodicTable::Element( 13,	Al,	3,	13,	_ComStr('p'),	26.981538,_ComStr("Aluminum"),		_ComStr("Al"),	1.18,	1.25,	1.18,	1,		0.53,	1.61 ),
		CPeriodicTable::Element( 14,	Si,	3,	14,	_ComStr('p'),	28.0855,	_ComStr("Silicon"),			_ComStr("Si"),	1.11,	1.10,	1.11,	2.10,	0.40,	1.9	 ),
		CPeriodicTable::Element( 15,	P,	3,	15,	_ComStr('p'),	30.973761,_ComStr("Phosphorus"),	_ComStr("P"),		0.98,	1.00,	1.06,	1.90,	0.31,	2.19 ),
		CPeriodicTable::Element( 16,	S,	3,	16,	_ComStr('p'),	32.065,		_ComStr("Sulfur"),			_ComStr("S"),		0.88,	1.00,	1.02,	1.85,	0.43,	2.58 ),
		CPeriodicTable::Element( 17,	Cl,	3,	17,	_ComStr('p'),	35.453,		_ComStr("Chlorine"),		_ComStr("Cl"),	0.79,	1.00,	0.99,	1.85,	1.67,	3.16 ),
		CPeriodicTable::Element( 18,	Ar,	3,	18,	_ComStr('p'),	39.948,		_ComStr("Argon"),				_ComStr("Ar"),	0.71,	0.71,	0.97,	1.88,	1,		0		 ),
		CPeriodicTable::Element( 19,	K,	4,	1,	_ComStr('s'),	39.0983,	_ComStr("Potassium"),		_ComStr("K"),		2.43,	2.20,	1.96,	1.50,	1.52,	0.82 ),
		CPeriodicTable::Element( 20,	Ca,	4,	2,	_ComStr('s'),	40.078,		_ComStr("Calcium"),			_ComStr("Ca"),	1.94,	1.80,	1.74,	1.50,	1.14,	1		 ),
		CPeriodicTable::Element( 21,	Sc,	4,	3,	_ComStr('d'),	44.95591,	_ComStr("Scandium"),		_ComStr("Sc"),	1.84,	1.60,	1.44,	1,		0.89,	1.36 ),
		CPeriodicTable::Element( 22,	Ti,	4,	4,	_ComStr('d'),	47.867,		_ComStr("Titanium"),		_ComStr("Ti"),	1.76,	1.40,	1.36,	1,		0.75,	1.54 ),
		CPeriodicTable::Element( 23,	V,	4,	5,	_ComStr('d'),	50.9415,	_ComStr("Vanadium"),		_ComStr("V"),		1.71,	1.35,	1.25,	1,		0.68,	1.63 ),
		CPeriodicTable::Element( 24,	Cr,	4,	6,	_ComStr('d'),	51.9961,	_ComStr("Chromium"),		_ComStr("Cr"),	1.66,	1.40,	1.27,	1,		0.76,	1.66 ),
		CPeriodicTable::Element( 25,	Mn,	4,	7,	_ComStr('d'),	54.938049,_ComStr("Manganese"),		_ComStr("Mn"),	1.61,	1.40,	1.39,	1,		0.81,	1.55 ),
		CPeriodicTable::Element( 26,	Fe,	4,	8,	_ComStr('d'),	55.845,		_ComStr("Iron"),				_ComStr("Fe"),	1.56,	1.40,	1.25,	1.5,	0.69,	1.83 ),
		CPeriodicTable::Element( 27,	Co,	4,	9,	_ComStr('d'),	58.9332,	_ComStr("Cobalt"),			_ComStr("Co"),	1.52,	1.35,	1.26,	1,		0.54,	1.88 ),
		CPeriodicTable::Element( 28,	Ni,	4,	10,	_ComStr('d'),	58.6934,	_ComStr("Nickel"),			_ComStr("Ni"),	1.49,	1.35,	1.21,	1.63,	0.70,	1.91 ),
		CPeriodicTable::Element( 29,	Cu,	4,	11,	_ComStr('d'),	63.546,		_ComStr("Copper"),			_ComStr("Cu"),	1.45,	1.35,	1.38,	1.40,	0.71,	1.9	 ),
		CPeriodicTable::Element( 30,	Zn,	4,	12,	_ComStr('d'),	65.409,		_ComStr("Zinc"),				_ComStr("Zn"),	1.42,	1.35,	1.31,	1.50,	0.74,	1.65 ),
		CPeriodicTable::Element( 31,	Ga,	4,	13,	_ComStr('p'),	69.723,		_ComStr("Gallium"),			_ComStr("Ga"),	1.36,	1.30,	1.26,	1.87,	0.76,	1.81 ),
		CPeriodicTable::Element( 32,	Ge,	4,	14,	_ComStr('p'),	72.64,		_ComStr("Germanium"),		_ComStr("Ge"),	1.25,	1.25,	1.22,	1,		0.53,	2.01 ),
		CPeriodicTable::Element( 33,	As,	4,	15,	_ComStr('p'),	74.9216,	_ComStr("Arsenic"),			_ComStr("As"),	1.14,	1.15,	1.19,	1.85,	0.72,	2.18 ),
		CPeriodicTable::Element( 34,	Se,	4,	16,	_ComStr('p'),	78.96,		_ComStr("Selenium"),		_ComStr("Se"),	1.03,	1.15,	1.16,	1.90,	0.56,	2.55 ),
		CPeriodicTable::Element( 35,	Br,	4,	17,	_ComStr('p'),	79.904,		_ComStr("Bromine"),			_ComStr("Br"),	0.94,	1.15,	1.14,	1.85,	1.82,	2.96 ),
		CPeriodicTable::Element( 36,	Kr,	4,	18,	_ComStr('p'),	83.798,		_ComStr("Krypton"),			_ComStr("Kr"),	0.88,	0.88,	1.10,	2.02,	1,		3		 ),
		CPeriodicTable::Element( 37,	Rb,	5,	1,	_ComStr('s'),	85.4678,	_ComStr("Rubidium"),		_ComStr("Rb"),	2.65,	2.35,	2.11,	1,		1.66,	0.82 ),
		CPeriodicTable::Element( 38,	Sr,	5,	2,	_ComStr('s'),	87.62,		_ComStr("Strontium"),		_ComStr("Sr"),	2.19,	2.00,	1.92,	1,		1.32,	0.95 ),
		CPeriodicTable::Element( 39,	Y,	5,	3,	_ComStr('d'),	88.90585,	_ComStr("Yttrium"),			_ComStr("Y"),		2.12,	1.85,	1.62,	1,		1.04,	1.22 ),
		CPeriodicTable::Element( 40,	Zr,	5,	4,	_ComStr('d'),	91.224,		_ComStr("Zirconium"),		_ComStr("Zr"),	2.06,	1.55,	1.48,	1,		0.86,	1.33 ),
		CPeriodicTable::Element( 41,	Nb,	5,	5,	_ComStr('d'),	92.90638,	_ComStr("Niobium"),			_ComStr("Nb"),	1.98,	1.45,	1.37,	1,		0.78,	1.6	 ),
		CPeriodicTable::Element( 42,	Mo,	5,	6,	_ComStr('d'),	95.94,		_ComStr("Molybdenum"),	_ComStr("Mo"),	1.90,	1.45,	1.45,	1,		0.79,	2.16 ),
		CPeriodicTable::Element( 43,	Tc,	5,	7,	_ComStr('d'),	98,				_ComStr("Technetium"),	_ComStr("Tc"),	1.83,	1.35,	1.56,	1,		0.79,	1.9	 ),
		CPeriodicTable::Element( 44,	Ru,	5,	8,	_ComStr('d'),	101.07,		_ComStr("Ruthenium"),		_ComStr("Ru"),	1.78,	1.30,	1.26,	1,		0.82,	2.2	 ),
		CPeriodicTable::Element( 45,	Rh,	5,	9,	_ComStr('d'),	102.9055,	_ComStr("Rhodium"),			_ComStr("Rh"),	1.73,	1.35,	1.35,	1,		0.81,	2.28 ),
		CPeriodicTable::Element( 46,	Pd,	5,	10,	_ComStr('d'),	106.42,		_ComStr("Palladium"),		_ComStr("Pd"),	1.69,	1.40,	1.31,	1.63,	0.78,	2.2	 ),
		CPeriodicTable::Element( 47,	Ag,	5,	11,	_ComStr('d'),	107.8682,	_ComStr("Silver"),			_ComStr("Ag"),	1.65,	1.60,	1.53,	1.72,	1.29,	1.93 ),
		CPeriodicTable::Element( 48,	Cd,	5,	12,	_ComStr('d'),	112.411,	_ComStr("Cadmium"),			_ComStr("Cd"),	1.61,	1.55,	1.48,	1.58,	0.92,	1.69 ),
		CPeriodicTable::Element( 49,	In,	5,	13,	_ComStr('p'),	114.818,	_ComStr("Indium"),			_ComStr("In"),	1.56,	1.55,	1.44,	1.93,	0.94,	1.78 ),
		CPeriodicTable::Element( 50,	Sn,	5,	14,	_ComStr('p'),	118.71,		_ComStr("Tin"),					_ComStr("Sn"),	1.45,	1.45,	1.41,	2.17,	0.69,	1.96 ),
		CPeriodicTable::Element( 51,	Sb,	5,	15,	_ComStr('p'),	121.76,		_ComStr("Antimony"),		_ComStr("Sb"),	1.33,	1.45,	1.38,	1,		0.90,	2.05 ),
		CPeriodicTable::Element( 52,	Te,	5,	16,	_ComStr('p'),	127.6,		_ComStr("Tellurium"),		_ComStr("Te"),	1.23,	1.40,	1.35,	2.06,	1.11,	2.1	 ),
		CPeriodicTable::Element( 53,	I,	5,	17,	_ComStr('p'),	126.90447,_ComStr("Iodine"),			_ComStr("I"),		1.15,	1.40,	1.33,	1.50,	2.06,	2.66 ),
		CPeriodicTable::Element( 54,	Xe,	5,	18,	_ComStr('p'),	131.293,	_ComStr("Xenon"),				_ComStr("Xe"),	1.08,	1.08,	1.30,	2.16,	0.62,	2.6	 ),
		CPeriodicTable::Element( 55,	Cs,	6,	1,	_ComStr('s'),	132.90545,_ComStr("Cesium"),			_ComStr("Cs"),	2.98,	2.60,	2.25,	1,		1.81,	0.79 ),
		CPeriodicTable::Element( 56,	Ba,	6,	2,	_ComStr('s'),	137.327,	_ComStr("Barium"),			_ComStr("Ba"),	2.53,	2.15,	1.98,	1,		1.49,	0.89 ),
		CPeriodicTable::Element( 57,	La,	6,	0,	_ComStr('f'),	138.9055,	_ComStr("Lanthanum"),		_ComStr("La"),	1.95,	1.95,	1.69,	1,		1.36,	1.1	 ),
		CPeriodicTable::Element( 58,	Ce,	6,	0,	_ComStr('f'),	140.116,	_ComStr("Cerium"),			_ComStr("Ce"),	1.85,	1.85,	1,		1,		1.15,	1.12 ),
		CPeriodicTable::Element( 59,	Pr,	6,	0,	_ComStr('f'),	140.90765,_ComStr("Praseodymium"),_ComStr("Pr"),	2.47,	1.85,	1,		1,		1.32,	1.13 ),
		CPeriodicTable::Element( 60,	Nd,	6,	0,	_ComStr('f'),	144.24,		_ComStr("Neodymium"),		_ComStr("Nd"),	2.06,	1.85,	1,		1,		1.30,	1.14 ),
		CPeriodicTable::Element( 61,	Pm,	6,	0,	_ComStr('f'),	145,			_ComStr("Promethium"),	_ComStr("Pm"),	2.05,	1.85,	1,		1,		1.28,	0		 ),
		CPeriodicTable::Element( 62,	Sm,	6,	0,	_ComStr('f'),	150.36,		_ComStr("Samarium"),		_ComStr("Sm"),	2.38,	1.85,	1,		1,		1.10,	1.17 ),
		CPeriodicTable::Element( 63,	Eu,	6,	0,	_ComStr('f'),	151.964,	_ComStr("Europium"),		_ComStr("Eu"),	2.31,	1.85,	1,		1,		1.31,	0		 ),
		CPeriodicTable::Element( 64,	Gd,	6,	0,	_ComStr('f'),	157.25,		_ComStr("Gadolinium"),	_ComStr("Gd"),	2.33,	1.80,	1,		1,		1.08,	1.2	 ),
		CPeriodicTable::Element( 65,	Tb,	6,	0,	_ComStr('f'),	158.92534,_ComStr("Terbium"),			_ComStr("Tb"),	2.25,	1.75,	1,		1,		1.18,	0		 ),
		CPeriodicTable::Element( 66,	Dy,	6,	0,	_ComStr('f'),	162.5,		_ComStr("Dysprosium"),	_ComStr("Dy"),	2.28,	1.75,	1,		1,		1.05,	1.22 ),
		CPeriodicTable::Element( 67,	Ho,	6,	0,	_ComStr('f'),	164.93032,_ComStr("Holmium"),			_ComStr("Ho"),	2.26,	1.75,	1,		1,		1.04,	1.23 ),
		CPeriodicTable::Element( 68,	Er,	6,	0,	_ComStr('f'),	167.259,	_ComStr("Erbium"),			_ComStr("Er"),	2.26,	1.75,	1,		1,		1.03,	1.24 ),
		CPeriodicTable::Element( 69,	Tm,	6,	0,	_ComStr('f'),	168.93421,_ComStr("Thulium"),			_ComStr("Tm"),	2.22,	1.75,	1,		1,		1.02,	1.25 ),
		CPeriodicTable::Element( 70,	Yb,	6,	0,	_ComStr('f'),	173.04,		_ComStr("Ytterbium"),		_ComStr("Yb"),	2.22,	1.75,	1,		1,		1.13,	0	 ),
		CPeriodicTable::Element( 71,	Lu,	6,	3,	_ComStr('d'),	174.967,	_ComStr("Lutetium"),		_ComStr("Lu"),	2.17,	1.75,	1.60,	1,		1.00,	1.27 ),
		CPeriodicTable::Element( 72,	Hf,	6,	4,	_ComStr('d'),	178.49,		_ComStr("Hafnium"),			_ComStr("Hf"),	2.08,	1.55,	1.50,	1,		0.85,	1.3	 ),
		CPeriodicTable::Element( 73,	Ta,	6,	5,	_ComStr('d'),	180.9479,	_ComStr("Tantalum"),		_ComStr("Ta"),	2.00,	1.45,	1.38,	1,		0.78,	1.5	 ),
		CPeriodicTable::Element( 74,	W,	6,	6,	_ComStr('d'),	183.84,		_ComStr("Tungsten"),		_ComStr("W"),		1.93,	1.35,	1.46,	1,		0.74,	2.36 ),
		CPeriodicTable::Element( 75,	Re,	6,	7,	_ComStr('d'),	186.207,	_ComStr("Rhenium"),			_ComStr("Re"),	1.88,	1.35,	1.59,	1,		0.77,	1.9	 ),
		CPeriodicTable::Element( 76,	Os,	6,	8,	_ComStr('d'),	190.23,		_ComStr("Osmium"),			_ComStr("Os"),	1.85,	1.30,	1.28,	1,		0.77,	2.2	 ),
		CPeriodicTable::Element( 77,	Ir,	6,	9,	_ComStr('d'),	192.217,	_ComStr("Iridium"),			_ComStr("Ir"),	1.80,	1.35,	1.37,	1,		0.77,	2.2	 ),
		CPeriodicTable::Element( 78,	Pt,	6,	10,	_ComStr('d'),	195.078,	_ComStr("Platinum"),		_ComStr("Pt"),	1.77,	1.35,	1.28,	1.75,	0.74,	2.28 ),
		CPeriodicTable::Element( 79,	Au,	6,	11,	_ComStr('d'),	196.96655,_ComStr("Gold"),				_ComStr("Au"),	1.74,	1.35,	1.44,	1.66,	1.51,	2.54 ),
		CPeriodicTable::Element( 80,	Hg,	6,	12,	_ComStr('d'),	200.59,		_ComStr("Mercury"),			_ComStr("Hg"),	1.71,	1.50,	1.49,	1.55,	0.83,	2		 ),
		CPeriodicTable::Element( 81,	Tl,	6,	13,	_ComStr('p'),	204.3833,	_ComStr("Thallium"),		_ComStr("Tl"),	1.56,	1.90,	1.48,	1.96,	1.03,	1.62 ),
		CPeriodicTable::Element( 82,	Pb,	6,	14,	_ComStr('p'),	207.2,		_ComStr("Lead"),				_ComStr("Pb"),	1.54,	1.80,	1.47,	2.02,	1.49,	2.33 ),
		CPeriodicTable::Element( 83,	Bi,	6,	15,	_ComStr('p'),	208.98038,_ComStr("Bismuth"),			_ComStr("Bi"),	1.43,	1.60,	1.46,	1,		1.17,	2.02 ),
		CPeriodicTable::Element( 84,	Po,	6,	16,	_ComStr('p'),	209,			_ComStr("Polonium"),		_ComStr("Po"),	1.35,	1.90,	1,		1,		1.08,	2		 ),
		CPeriodicTable::Element( 85,	At,	6,	17,	_ComStr('p'),	210,			_ComStr("Astatine"),		_ComStr("At"),	1.27,	1.27,	1,		1,		0.76,	2.2	 ),
		CPeriodicTable::Element( 86,	Rn,	6,	18,	_ComStr('p'),	222,			_ComStr("Radon"),				_ComStr("Rn"),	1.20,	1.20,	1.45,	1,		1,		0		 ),
		CPeriodicTable::Element( 87,	Fr,	7,	1,	_ComStr('s'),	223,			_ComStr("Francium"),		_ComStr("Fr"),	1,		1,		1,		1,		1.94,	0.7	 ),
		CPeriodicTable::Element( 88,	Ra,	7,	2,	_ComStr('s'),	226,			_ComStr("Radium"),			_ComStr("Ra"),	1,		2.15,	1,		1,		1.62,	0.9	 ),
		CPeriodicTable::Element( 89,	Ac,	7,	0,	_ComStr('f'),	227,			_ComStr("Actinium"),		_ComStr("Ac"),	1.95,	1.95,	1,		1,		1.26,	1.1	 ),
		CPeriodicTable::Element( 90,	Th,	7,	0,	_ComStr('f'),	232.0381,	_ComStr("Thorium"),			_ComStr("Th"),	1.80,	1.80,	1,		1,		1.19,	1.3	 ),
		CPeriodicTable::Element( 91,	Pa,	7,	0,	_ComStr('f'),	231.03588,_ComStr("Protactinium"),_ComStr("Pa"),	1.80,	1.80,	1,		1,		1.09,	1.5	 ),
		CPeriodicTable::Element( 92,	U,	7,	0,	_ComStr('f'),	238.02891,_ComStr("Uranium"),			_ComStr("U"),		1.75,	1.75,	1,		1.86,	0.87,	1.38 ),
		CPeriodicTable::Element( 93,	Np,	7,	0,	_ComStr('f'),	247,			_ComStr("Neptunium"),		_ComStr("Np"),	1.75,	1.75,	1,		1,		1,		1.36 ),
		CPeriodicTable::Element( 94,	Pu,	7,	0,	_ComStr('f'),	244,			_ComStr("Plutonium"),		_ComStr("Pu"),	1.75,	1.75,	1,		1,		1.00,	1.28 ),
		CPeriodicTable::Element( 95,	Am,	7,	0,	_ComStr('f'),	243,			_ComStr("Americium"),		_ComStr("Am"),	1.75,	1.75,	1,		1,		1.12,	1.3	 ),
		CPeriodicTable::Element( 96,	Cm,	7,	0,	_ComStr('f'),	247,			_ComStr("Curium"),			_ComStr("Cm"),	1,		1,		1,		1,		1.11,	1.3	 ),
		CPeriodicTable::Element( 97,	Bk,	7,	0,	_ComStr('f'),	247,			_ComStr("Berkelium"),		_ComStr("Bk"),	1,		1,		1,		1,		1,		1.3	 ),
		CPeriodicTable::Element( 98,	Cf,	7,	0,	_ComStr('f'),	251,			_ComStr("Californium"),	_ComStr("Cf"),	1,		1,		1,		1,		1,		1.3	 ),
		CPeriodicTable::Element( 99,	Es,	7,	0,	_ComStr('f'),	254,			_ComStr("Einsteinium"),	_ComStr("Es"),	1,		1,		1,		1,		1,		1.3	 ),
		CPeriodicTable::Element( 100,	Fm,	7,	0,	_ComStr('f'),	257,			_ComStr("Fermium"),			_ComStr("Fm"),	1,		1,		1,		1,		1,		1.3	 ),
		CPeriodicTable::Element( 101,	Md,	7,	0,	_ComStr('f'),	258,			_ComStr("Mendelevium"),	_ComStr("Md"),	1,		1,		1,		1,		1,		1.3	 ),
		CPeriodicTable::Element( 102,	No,	7,	0,	_ComStr('f'),	259,			_ComStr("Nobelium"),		_ComStr("No"),	1,		1,		1,		1,		1,		1.3	 ),
		CPeriodicTable::Element( 103,	Lr,	7,	3,	_ComStr('d'),	262,			_ComStr("Lawrencium"),	_ComStr("Lr"),	1,		1,		1,		1,		1,		1.3	 ),
		CPeriodicTable::Element( 104,	Rf,	7,	4,	_ComStr('d'),	261,			_ComStr("Rutherfordium"),_ComStr("Rf"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 105,	Db,	7,	5,	_ComStr('d'),	262,			_ComStr("Dubnium"),			_ComStr("Db"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 106,	Sg,	7,	6,	_ComStr('d'),	266,			_ComStr("Seaborgium"),	_ComStr("Sg"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 107,	Bh,	7,	7,	_ComStr('d'),	264,			_ComStr("Bohrium"),			_ComStr("Bh"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 108,	Hs,	7,	8,	_ComStr('d'),	277,			_ComStr("Hassium"),			_ComStr("Hs"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 109,	Mt,	7,	9,	_ComStr('d'),	268,			_ComStr("Meitnerium"),	_ComStr("Mt"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 110,	Ds,	7,	10,	_ComStr('d'),	281,			_ComStr("Darmstadtium"),_ComStr("Ds"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 111,	Rg,	7,	11,	_ComStr('d'),	272,			_ComStr("Roentgenium"),	_ComStr("Rg"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 112,	Uub,7,	12,	_ComStr('d'),	285,			_ComStr("ununbium"),		_ComStr("Uub"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 113,	Uut,7,	13,	_ComStr('p'),	284,			_ComStr("ununtrium"),		_ComStr("Uut"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 114,	Uuq,7,	14,	_ComStr('p'),	289,			_ComStr("ununquadium"),	_ComStr("Uuq"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 115,	Uup,7,	15,	_ComStr('p'),	288,			_ComStr("ununpentium"),	_ComStr("Uup"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 116,	Uuh,7,	16,	_ComStr('p'),	292,			_ComStr("ununhexium"),	_ComStr("Uuh"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 117,	Uus,7,	17,	_ComStr('p'),	0,				_ComStr("ununseptium"),	_ComStr("Uus"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 118,	Uuo,7,	18,	_ComStr('p'),	294,			_ComStr("ununoctium"),	_ComStr("Uuo"),	1,		1,		1,		1,		1,		0		 ),
		CPeriodicTable::Element( 119,ePTEUnknown,0,0,_ComStr('-'),	0,			_ComStr("??"),					_ComStr("??"),	0,		0,		0,		0,		0,		0		 )
	};

	CPeriodicTable g_PT;

} //namespace Common
