/**
 * using bits from whoever made test 5 on discord as well as test 1,2,3
 * Made by Daniel
 */
#include "mol.h"

#ifndef STDIO_H
#include <stdio.h>
#endif // !STDIO_H

void displaySortedAtoms(molecule * molecule){
	for (int i=0;i<molecule->atom_no;i++)
	{
		char name[3];
		double x,y,z;
		atom *atom_ptr;

		// get pointer from atom_ptrs array
		atom_ptr = molecule->atom_ptrs[i];


		printf( "atom_ptrs[%d]", i);

		// get the info form the atom
		atomget( atom_ptr, name, &x, &y, &z );
		printf( "  -> atom[%lu] %-2s: %lf %lf %lf\n",
				(atom_ptr - molecule->atoms),
				name, x, y, z );
	}
	for (int i=0;i<molecule->bond_no;i++)
	{
		bond *bond_ptr;

		bond_ptr = molecule->bond_ptrs[i];
		printf( "bond_ptrs[%d]: %p", i, (void *)(molecule->bond_ptrs[i]) );

		printf( "  -> bond[%d] %p: %p(%s) %p(%s) %hhu\n",
				i, (void *)bond_ptr, (void *)bond_ptr->a1, bond_ptr->a1->element,
				(void *)bond_ptr->a2, bond_ptr->a2->element,
				bond_ptr->epairs );

	}
}

void display_mol(molecule *molecule)
{
	/* display the molecule */

	/* atoms */
	printf("atom_max: %hu, atom_no: %hu\n",
		   molecule->atom_max, molecule->atom_no);
	for (int i = 0; i < molecule->atom_no; i++)
	{
		char name[3];
		double x, y, z;
		atom *atom_ptr;

		atom_ptr = molecule->atoms + i;

		atomget(atom_ptr, name, &x, &y, &z);
		printf("atom[%d] %p %-2s: %lf %lf %lf\n",
			   i, (void *)atom_ptr, name, x, y, z);
	}

	for (int i = 0; i < molecule->atom_no; i++)
	{
		atom *atom_ptr = molecule->atom_ptrs[i];
		char name[3];
		double x, y, z;
		atomget(atom_ptr, name, &x, &y, &z);

		printf("atom_ptrs[%d] %p %-2s: %lf %lf %lf\n",
			   i, (void *)(molecule->atom_ptrs[i]), name, x, y, z);
	}

	/* bonds */
	printf("bond_max: %hu, bond_no: %hu\n",
		   molecule->bond_max, molecule->bond_no);
	for (int i = 0; i < molecule->bond_no; i++)
	{
		atom *a1, *a2;
		unsigned char epairs;
		bond *bond_ptr;

		bond_ptr = molecule->bonds + i;
		bondget(bond_ptr, &a1, &a2, &epairs);
		printf("bond[%d] %p: %p %p %hhu\n",
			   i, (void *)bond_ptr, (void *)a1, (void *)a2, epairs);
	}

	for (int i = 0; i < molecule->bond_no; i++)
	{
		printf("bond_ptrs[%d]: %p\n", i, (void *)(molecule->bond_ptrs[i]));
	}
}

void displayMolCoords(molecule * molecule){
	printf("atom_max: %hu, atom_no: %hu\n",
		   molecule->atom_max, molecule->atom_no);
	for (int i = 0; i < molecule->atom_no; i++)
	{
		char name[3];
		double x, y, z;
		atom *atom_ptr;

		atom_ptr = molecule->atoms + i;

		atomget(atom_ptr, name, &x, &y, &z);
		printf("atom[%d] %p %-2s: %lf %lf %lf\n",
			   i, (void *)atom_ptr, name, x, y, z);
	}
}
/**
 * updates the bond atoms to point to to atoms in molecule
 * @param molecule should have atleast 2 times the atoms for numToUpdate
 * @param b
 * @param bSize
 * @param numToUpdate
 */
void updateBonds(molecule * molecule, bond ** b, int bSize, int numToUpdate){
	for(int i = 0; i<numToUpdate; i++){
		bondset(&((*b)[i]), &(molecule->atoms[i*2]), &(molecule->atoms[i*2+1]), ((*b)[i]).epairs);
	}
}
void createAndFreeMol(){ //do the thing
	molecule *molecule;
	printf( "malloc and free a molecule with [2,2]\n");
	molecule = molmalloc(2,2);
	molfree(molecule);

	printf("malloc and free a molecule with [0,0]\n");
	molecule = molmalloc(0,0);
	molfree(molecule);
}

void addAllAtomsToMolecule(molecule * molecule, atom * a[], int aSize){
	for (int i = 0; i < aSize; ++i) {
		molappend_atom(molecule, &((*a)[i]));
	}
}
/**
 * this assumes that addAllAtomsToMolecule has been called
 * @param molecule
 * @param b
 * @param bSize
 */
void addAllBondsToMolecule(molecule * molecule, bond * b[], int bSize){
	for (int i = 0; i < bSize; ++i) {
		molappend_bond(molecule, &((*b)[i]));
	}
}

void createMolAddVariousAtomsBondsThenFree(atom **a , int aSize, bond **b, int bSize){
	molecule *molecule;
	printf("malloc molecule[2,2], add [2,2] - bond will be duplicate\n");
	//printf("%lld %lld, %lld", (long long int)a, (long long int) a[0], (long long int) a[1]);
	molecule = molmalloc(2,2);
	molappend_atom(molecule, &((*a)[0]));
	molappend_atom(molecule, &((*a)[1]));
	updateBonds(molecule, b, bSize, 1);
	molappend_bond(molecule, &((*b)[0]));
	molappend_bond(molecule, &((*b)[0]));
	display_mol(molecule);
	molfree(molecule);

	printf("malloc molecule[2,2], add [8,4]\n");
	molecule = molmalloc(2,2);
	addAllAtomsToMolecule(molecule, a, aSize);
	printf("added atoms. ");
	updateBonds(molecule, b, bSize, 4);
	addAllBondsToMolecule(molecule, b, bSize);
	printf("added bonds. \n");
	display_mol(molecule);
	molfree(molecule);

	printf("malloc molecule[0,0], add [8,4]\n");
	molecule = molmalloc(2,2);
	addAllAtomsToMolecule(molecule, a, aSize);
	printf("added atoms. ");
	updateBonds(molecule, b, bSize, 4);
	addAllBondsToMolecule(molecule, b, bSize);
	printf("added bonds. \n");
	display_mol(molecule);
	molfree(molecule);
}

int atmCmp(atom * a1, atom * a2){
	if(a1 == a2){
		printf("atom instance is the same <- ");
		return -1;
	}
	if(a1->x != a2->x){
		printf("atom x locations are different <- ");
		return -1;
	}
	if(a1->y != a2->y){
		printf("atom y locations are different <- ");
		return -1;
	}
	if(a1->z != a2->z) {
		printf("atom z locations are different <- ");
		return -1;
	}
	for(int i = 0; i<3;i++){
		if(a1->element[i] != a2->element[i]){
			printf("atom element is different <- ");
			return -1;
		}
		if(a1->element[i] == '\0'){
			break;
		}
		if(a2->element[i] == '\0'){
			break;
		}

	}
	return 0;
}

int bndCmp(bond * b1, bond * b2){
	if(b1 == b2){
		return -1;
	}
	if(b1->epairs != b2->epairs){
		return -1;
	}
	if(atmCmp(b1->a1, b2->a1) == -1){
		printf("Found difference between a1's <- ");
		return -1;
	}
	if(atmCmp(b1->a2, b2->a2) == -1){
		printf("Found difference between a2's <- ");
		return -1;
	}
	return 0;
}
int min(int a, int b){
	return (a < b) ? a : b;
}
/**
 * compare after molcopy, prints out anything wrong - differences between data, if there is any shared data, etc
 * @param m1
 * @param m2
 */
void compareTwoMolecules(molecule * m1, molecule * m2){
	if(m1 == m2){
		printf("Molecules are the same address\n");
	}
	if(m1->atom_no != m2->atom_no){
		printf("Molecules have differing atom_no\n");
	}
	if(m1->atom_max != m2->atom_max){
		printf("Molecules have differing atom_max\n");
	}
	if(m1->bond_no != m2->bond_no){
		printf("Molecules have differing bond_no\n");
	}
	if(m1->bond_max != m2->bond_max){
		printf("Molecules have differing bond_max\n");
	}
	for (int i = 0; i < min(m1->atom_no, m2->atom_no); ++i) {
		if(atmCmp(&(m1->atoms[i]), &(m2->atoms[i])) == -1){
			if(&(m1->atoms[i]) == &(m2->atoms[i])){
				printf("Atoms[%d] are the same instance\n", i);
			} else {
				printf("Atoms[%d] are different\n", i);
			}
		}
		for(int j = 0; j<min(m1->atom_no, m2->atom_no); j++){
			if(m1->atom_ptrs[i] == &(m2->atoms[j])){
				printf("atom_ptr[%d] in molecule 1 is pointing to atom[%d] in molecule 2\n",i, j);
			}
			if(m2->atom_ptrs[i] == &(m1->atoms[j])){
				printf("atom_ptr[%d] in molecule 2 is pointing to atom[%d] in molecule 1\n",i, j);
			}
		}
	}

	for (int i = 0; i < min(m1->bond_no, m2->bond_no); ++i) {
		if(bndCmp(&(m1->bonds[i]), &(m2->bonds[i])) == -1){
			if(&(m1->bonds[i]) == &(m2->bonds[i])){
				printf("Bonds[%d] are the same instance between molecules\n", i);
			} else {
				printf("Bonds[%d] are different between molecules\n", i);
			}
		}
		for(int j = 0; j<min(m1->atom_no, m2->atom_no); j++){
			if(m1->bond_ptrs[i] == &(m2->bonds[j])){
				printf("bond_ptr[%d] in molecule 1 is pointing to bond[%d] in molecule 2\n",i, j);
			}
			if(m2->bond_ptrs[i] == &(m1->bonds[j])){
				printf("bond_ptr[%d] in molecule 2 is pointing to bond[%d] in molecule 1\n",i, j);
			}
		}
	}
}


void testMolculeCopy(atom **a , int aSize, bond **b, int bSize){
	printf("Creating and copying a molecule[0,0]\n");
	molecule * molecule = molmalloc(0,0);
	struct molecule * moleculeCpy = molcopy(molecule);
	printf("Comparing molecules - any differences will be printed here:\n");
	compareTwoMolecules(molecule, moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);

	printf("\nCreating and copying a molecule[2,2] with no bonds or atoms added\n");
	molecule = molmalloc(2,2);
	moleculeCpy = molcopy(molecule);
	printf("Comparing molecules - any differences will be printed here:\n");
	compareTwoMolecules(molecule, moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);

	printf("\nCreating and copying a molecule[2,2] with atoms\n");
	molecule = molmalloc(2,2);
	molappend_atom(molecule, &((*a)[0]));
	molappend_atom(molecule, &((*a)[7]));
	moleculeCpy = molcopy(molecule);
	printf("Comparing molecules - any differences will be printed here:\n");
	compareTwoMolecules(molecule, moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);

	printf("\nCreating and copying a molecule[2,2] with atoms and bonds\n");
	molecule = molmalloc(2,2);
	molappend_atom(molecule, &((*a)[0]));
	molappend_atom(molecule, &((*a)[1]));
	updateBonds(molecule, b, bSize, 1);
	molappend_bond(molecule, &((*b)[0]));
	molappend_bond(molecule, &((*b)[0]));
	moleculeCpy = molcopy(molecule);
	printf("Comparing molecules - any differences will be printed here:\n");
	compareTwoMolecules(molecule, moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);

	printf("\nCreating and copying a molecule[0,0] with full atoms and bonds\n");
	molecule = molmalloc(0,0);
	addAllAtomsToMolecule(molecule, a, aSize);
	updateBonds(molecule, b, bSize, 4);
	addAllBondsToMolecule(molecule, b, bSize);
	moleculeCpy = molcopy(molecule);
	printf("Comparing molecules - any differences will be printed here:\n");
	compareTwoMolecules(molecule, moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);
}
void testMolSort(atom **a , int aSize, bond **b, int bSize){
	printf("Sorting a molecule[0,0]\n");
	molecule * molecule = molmalloc(0,0);
	molsort(molecule);
	displaySortedAtoms(molecule);
	molfree(molecule);

	printf("Sorting a molecule[1,0]\n");
	molecule = molmalloc(0,0);
	molappend_atom(molecule, &((*a)[0]));
	molsort(molecule);
	displaySortedAtoms(molecule);
	molfree(molecule);

	printf("Sorting a molecule[2,0]\n");
	molecule = molmalloc(0,0);
	molappend_atom(molecule, &((*a)[2]));
	molappend_atom(molecule, &((*a)[0]));
	molsort(molecule);
	displaySortedAtoms(molecule);
	molfree(molecule);

	printf("Sorting a molecule[2,1]\n");
	molecule = molmalloc(0,0);
	molappend_atom(molecule, &((*a)[0]));
	molappend_atom(molecule, &((*a)[2]));
	updateBonds(molecule, b, bSize, 1);
	molappend_bond(molecule, &((*b)[0]));
	molsort(molecule);
	displaySortedAtoms(molecule);
	molfree(molecule);

	printf("Sorting a molecule[4,2]\n");
	molecule = molmalloc(0,0);
	molappend_atom(molecule, &((*a)[0]));
	molappend_atom(molecule, &((*a)[2]));
	molappend_atom(molecule, &((*a)[1]));
	molappend_atom(molecule, &((*a)[7]));
	updateBonds(molecule, b, bSize, 2);
	molappend_bond(molecule, &((*b)[0]));
	molappend_bond(molecule, &((*b)[1]));
	molsort(molecule);
	displaySortedAtoms(molecule);
	molfree(molecule);


	printf("Sorting a copied molecule[0,0]\n");
	molecule = molmalloc(0,0);
	struct molecule * moleculeCpy = molcopy(molecule);
	molsort(moleculeCpy);
	printf("Original Molecule (unsorted)\n");
	displaySortedAtoms(molecule);
	printf("Copied Molecule (sorted)\n");
	displaySortedAtoms(moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);

	printf("Sorting a copied molecule[2,1]\n");
	molecule = molmalloc(0,0);
	molappend_atom(molecule, &((*a)[0]));
	molappend_atom(molecule, &((*a)[2]));
	molappend_atom(molecule, &((*a)[1]));
	molappend_atom(molecule, &((*a)[7]));
	updateBonds(molecule, b, bSize, 2);
	molappend_bond(molecule, &((*b)[0]));
	molappend_bond(molecule, &((*b)[1]));
	moleculeCpy = molcopy(molecule);
	molsort(moleculeCpy);
	printf("Original Molecule (unsorted)\n");
	displaySortedAtoms(molecule);
	printf("Copied Molecule (sorted)\n");
	displaySortedAtoms(moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);

	printf("Sorting a copied molecule[8,4]\n");
	molecule = molmalloc(0,0);
	addAllAtomsToMolecule(molecule, a, aSize);
	updateBonds(molecule, b, bSize, 4);
	addAllBondsToMolecule(molecule, b, bSize);
	moleculeCpy = molcopy(molecule);
	molsort(moleculeCpy);
	printf("Original Molecule (unsorted)\n");
	displaySortedAtoms(molecule);
	printf("Copied Molecule (sorted)\n");
	displaySortedAtoms(moleculeCpy);
	molfree(molecule);
	molfree(moleculeCpy);
}
void testRotationX(molecule * m1){
	xform_matrix x1,x2;
	molecule * m2 = molcopy(m1);
	xrotation(x1, 10);
	xrotation(x2, 190);

	printf("X rotations\nBefore rotations\n");
	displayMolCoords(m1);

	mol_xform(m1, x1);
	printf("After rotating 10");
	displayMolCoords(m1);
	for(int i = 0; i<18; i++){
		mol_xform(m1, x1);
	}
	mol_xform(m2, x2);
	printf("Comparing rotations from applying 10 deg matrix 19 times and 190 deg rotation\n");
	displayMolCoords(m1);
	displayMolCoords(m2);
	molfree(m2);
}
void testRotationY(molecule * m1){
	xform_matrix x1,x2;
	molecule * m2 = molcopy(m1);
	yrotation(x1, 10);
	yrotation(x2, 190);

	printf("Y rotations\nBefore rotations\n");
	displayMolCoords(m1);

	mol_xform(m1, x1);
	printf("After rotating 10");
	displayMolCoords(m1);
	for(int i = 0; i<18; i++){
		mol_xform(m1, x1);
	}
	mol_xform(m2, x2);
	printf("Comparing rotations from applying 10 deg matrix 19 times and 190 deg rotation\n");
	displayMolCoords(m1);
	displayMolCoords(m2);
	molfree(m2);
}
void testRotationZ(molecule * m1){
	xform_matrix x1,x2;
	molecule * m2 = molcopy(m1);
	zrotation(x1, 10);
	zrotation(x2, 190);

	printf("Z rotations\nBefore rotations\n");
	displayMolCoords(m1);

	mol_xform(m1, x1);
	printf("After rotating 10");
	displayMolCoords(m1);
	for(int i = 0; i<18; i++){
		mol_xform(m1, x1);
	}
	mol_xform(m2, x2);
	printf("Comparing rotations from applying 10 deg matrix 19 times and 190 deg rotation\n");
	displayMolCoords(m1);
	displayMolCoords(m2);
	molfree(m2);
}


void testRotations(atom **a , int aSize, bond **b, int bSize){
	printf("Rotations\n");
	molecule * m1 = molmalloc(8,4);
	addAllAtomsToMolecule(m1, a, aSize);
	updateBonds(m1, b, bSize, 4);
	testRotationX(m1);
	molfree(m1);

	m1 = molmalloc(8,4);
	addAllAtomsToMolecule(m1, a, aSize);
	updateBonds(m1, b, bSize, 4);
	testRotationY(m1);
	molfree(m1);

	m1 = molmalloc(8,4);
	addAllAtomsToMolecule(m1, a, aSize);
	updateBonds(m1, b, bSize, 4);
	testRotationZ(m1);
	molfree(m1);
}

int main(){
	atom * a = malloc(sizeof(atom)*8);
	bond * b = malloc(sizeof(bond)*4);
	double x[8] = {0.0, 1.0, -3.8345, 0.0, -1.0, 0.7483, 123, -0.001};
	double y[8] = {0.0, 1.0, 2.6969,  0.0, -1.0, 0.2895, 456, 0.23};
	double z[8] = {1.0, 1.0, -0.001,  0.0, -1.0, 0.1274, 789, -789};
	char e[8][3] = {"H", "a", " ", "LO", "NG", " ", "B", "ay"};
	char pair[4] = {'a', 'b', 'c', 'd'};
	//printf("Setting up atoms\n a[i]'s setup: ");
	for (int i = 0; i < 8; ++i) {
		atomset(&(a[i]), e[i], &x[i], &y[i], &z[i]);
		//printf("%d ", i);
	}
	printf("\nSetting up bonds\n b[i] setup: "); //the atoms will be overwritten but whatever
	for (int i = 0; i < 4; ++i) {
		bondset(&(b[i]), &(a[i*2]), &(a[i*2 + 1]), pair[i]);
		//printf("%d ", i);
	}
	printf("\n");

	createAndFreeMol();
	createMolAddVariousAtomsBondsThenFree(&a, 8, &b, 4);
	//testMolculeCopy(&a, 8, &b, 4);
	printf("\n");
	//testMolSort(&a, 8, &b, 4);
	printf("\n");
	testRotations(&a, 8, &b, 4);

	free(a);
	free(b);
}
