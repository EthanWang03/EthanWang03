#include "mol.h"

void atomset( atom *atom, char element[3], double *x, double *y, double *z ){
    //copies values from inputs into atom
    strcpy(atom->element,element);
    atom->x = *x;
    atom->y = *y;
    atom->z = *z;
}

void atomget( atom *atom, char element[3], double *x, double *y, double *z ){
    //copies values from atom into variables
    strcpy(element,atom->element);
    *x = atom->x;
    *y = atom->y;
    *z = atom->z;
}

void bondset( bond *bond, atom *a1, atom *a2, unsigned char epairs ){
    //connects two atoms using bond stuct
    bond->a1 = a1;
    bond->a2 = a2;
    bond->epairs = epairs;
}

void bondget( bond *bond, atom **a1, atom **a2, unsigned char *epairs ){
    //copies values from bond into atom variables
    *a1 = bond->a1;
    *a2 = bond->a2;
    *epairs = bond->epairs;
}

molecule *molmalloc( unsigned short atom_max, unsigned short bond_max ){
    molecule *molecule = malloc(sizeof(struct molecule));

    //check for NULL malloc
    if(molecule == NULL){ 
        return NULL;
    }

    //set atom max and atom no
    molecule->atom_max = atom_max;
    molecule->atom_no = 0;

    molecule->atoms = malloc(atom_max * (sizeof(atom)));

    //check for NULL malloc
    if(molecule->atoms == NULL){ 
        return NULL;
    }

    molecule->atom_ptrs = malloc(atom_max * (sizeof(atom*)));

    //check for NULL malloc
    if(molecule->atom_ptrs == NULL){ 
        return NULL;
    }

    molecule->bond_max = bond_max;
    molecule->bond_no = 0;

    molecule->bonds = malloc(bond_max * (sizeof(bond)));

    //check for NULL malloc
    if(molecule->bonds == NULL){ 
        return NULL;
    }

    molecule->bond_ptrs = malloc(bond_max * (sizeof(bond*)));

    //check for NULL malloc
    if(molecule->bond_ptrs == NULL){ 
        return NULL;
    }

    return molecule;
}

molecule *molcopy( molecule *src ){
    //Initialize molecule to store values
    molecule *CopiedMolecule = molmalloc(src->atom_max,src->bond_max);

    //copy over atoms
    for(int i = 0; i < src->atom_no; i++){
        molappend_atom(CopiedMolecule,&src->atoms[i]);
    }

    //copy over bonds
    for(int i = 0; i < src->bond_no; i++){
        molappend_bond(CopiedMolecule,&src->bonds[i]);
    }
    return CopiedMolecule;
}

void molfree( molecule *ptr ){
    //free arrays first then whole struct
    free(ptr->atoms);
    free(ptr->bonds);
    free(ptr->atom_ptrs);
    free(ptr->bond_ptrs);
    free(ptr);
}

void molappend_atom( molecule *molecule, atom *atom ){

    //if atom max is reached
    if(molecule->atom_no == molecule->atom_max){
        //if molecule atom_max was malloced to size 0
        if(molecule->atom_max == 0) {
            molecule->atom_max = 1;
        
        }
        //double the maximum amount of atoms
        else{
            molecule->atom_max = molecule->atom_max * 2;
        }
        //realloc to new size
        molecule->atom_ptrs = realloc(molecule->atom_ptrs,sizeof(struct atom*) * molecule->atom_max);
        molecule->atoms = realloc(molecule->atoms,sizeof(struct atom) * molecule->atom_max);

        //after realloc update ptrs to point to newly allocated atoms
        for(int i = 0; i < molecule->atom_max; i++){
            molecule->atom_ptrs[i] = &molecule->atoms[i];
        }
    }

    //set atoms to value of atom
    molecule->atoms[molecule->atom_no] = *atom;
    //set atom_ptrs to point to atoms
    molecule->atom_ptrs[molecule->atom_no] = &molecule->atoms[molecule->atom_no];

    //increase atom counter by 1
    molecule->atom_no = molecule->atom_no + 1;
}

void molappend_bond( molecule *molecule, bond *bond ){

    //if max amount of bonds are reached
    if(molecule->bond_no == molecule->bond_max){
        //if molecule bond_max was malloced to size 0
        if(molecule->bond_max == 0) {
            molecule->bond_max = 1;
        }
        //double the maximum amount of bonds
        else{
            molecule->bond_max = molecule->bond_max * 2;
        }
        //realloc to new size
        molecule->bond_ptrs = realloc(molecule->bond_ptrs,sizeof(struct bond*) * molecule->bond_max);
        molecule->bonds = realloc(molecule->bonds,sizeof(struct bond) * molecule->bond_max);\

        //after realloc update ptrs to point to newly allocated atoms
        for (int i = 0; i < molecule->bond_max; i++) {
            molecule->bond_ptrs[i] = &molecule->bonds[i];
        }
    }

    //set bonds to value of bond
    molecule->bonds[molecule->bond_no] = *bond;
    //set atom_ptrs to point to bonds
    molecule->bond_ptrs[molecule->bond_no] = &molecule->bonds[molecule->bond_no];

    //increase bond counter by 1
    molecule->bond_no = molecule->bond_no + 1;
}

int zCompare(const void *a, const void *b){

    //create atom struct variables to compare
    struct atom *z_ptr_a;
    struct atom *z_ptr_b;

    //dereference the values of the pointers passed
    z_ptr_a = *(struct atom**)a;
    z_ptr_b = *(struct atom**)b;
    
    //if a < b
    if(z_ptr_a->z < z_ptr_b->z ){
        return -1; 
    }
    //if a > b
    else if(z_ptr_a->z > z_ptr_b->z){
        return 1;
    }
    //if a == b
    else{
        //compare total
        if(z_ptr_a->x + z_ptr_a->y + z_ptr_a->z > z_ptr_b->x + z_ptr_b->y + z_ptr_b->z){
            return 1;
        }
        else if(z_ptr_a->x + z_ptr_a->y + z_ptr_a->z < z_ptr_b->x + z_ptr_b->y + z_ptr_b->z){
            return -1;
        }
        return 0;
    }
}

int bondCompare(const void *a, const void *b){

    //create bond struct variables to compare
    struct bond *z_ptr_a;
    struct bond *z_ptr_b;

    //dereference the values of the pointers passed
    z_ptr_a = *(struct bond**)a;
    z_ptr_b = *(struct bond**)b;

    //if a < b
    if(z_ptr_a->a1->z + z_ptr_a->a2->z < z_ptr_b->a1->z + z_ptr_b->a2->z){ 
        //combines the values of the two atoms in bond to compare z values
        return -1; 
    }
    //if a > b
    else if(z_ptr_a->a1->z + z_ptr_a->a2->z > z_ptr_b->a1->z + z_ptr_b->a2->z){
        //combines the values of the two atoms in bond to compare z values
        return 1;
    }
    //if a == b
    else{
        return 0;
    }
}

void molsort( molecule *molecule ){
    //qsort atom_ptrs
    qsort(molecule->atom_ptrs,molecule->atom_no,sizeof(struct atom*), zCompare);
    //qsort bond_ptrs
    qsort(molecule->bond_ptrs,molecule->bond_no,sizeof(struct bond*), bondCompare);
}

void xrotation(xform_matrix xform_matrix, unsigned short deg) {

    //calculate radians
    double radians = ((deg * (PI/180)));

    //xform_matrix[row][col]
    //rotate matrix values for clockwise on x axis

    xform_matrix[0][0] = 1;
    xform_matrix[0][1] = 0;
    xform_matrix[0][2] = 0;

    xform_matrix[1][0] = 0;
    xform_matrix[1][1] = cos(radians);
    xform_matrix[1][2] = -sin(radians);

    xform_matrix[2][0] = 0;
    xform_matrix[2][1] = sin(radians);
    xform_matrix[2][2] = cos(radians);
}

void yrotation(xform_matrix xform_matrix, unsigned short deg) {

    //calculate radians
    double radians = ((deg * (PI/180)));

    //xform_matrix[row][col]
    //rotate matrix values for clockwise on y axis

    xform_matrix[0][0] = cos(radians);
    xform_matrix[0][1] = 0;
    xform_matrix[0][2] = sin(radians);

    xform_matrix[1][0] = 0;
    xform_matrix[1][1] = 1;
    xform_matrix[1][2] = 0;

    xform_matrix[2][0] = -sin(radians);
    xform_matrix[2][1] = 0;
    xform_matrix[2][2] = cos(radians);
}

void zrotation(xform_matrix xform_matrix, unsigned short deg) {

    //calculate radians
    double radians = ((deg * (PI/180)));

    //xform_matrix[row][col]
    //rotate matrix values for clockwise on z axis

    xform_matrix[0][0] = cos(radians);
    xform_matrix[0][1] = -sin(radians);
    xform_matrix[0][2] = 0;

    xform_matrix[1][0] = sin(radians);
    xform_matrix[1][1] = cos(radians);
    xform_matrix[1][2] = 0;

    xform_matrix[2][0] = 0;
    xform_matrix[2][1] = 0;
    xform_matrix[2][2] = 1;
}

void mol_xform(molecule *molecule, xform_matrix matrix) {
    
    //temp array to hold the final values of x y z
    double transformed[3];

    //run for number of atom
    for (int i = 0; i < molecule->atom_no; i++) {
        //run for x y and z
        for(int row = 0; row < 3; row++){
            //multiply matrix to find final value
            transformed[row] = molecule->atom_ptrs[i]->x * matrix[row][0] + molecule->atom_ptrs[i]->y * matrix[row][1] + molecule->atom_ptrs[i]->z * matrix[row][2];
        }
        //updating the x value
        molecule->atom_ptrs[i]->x = transformed[0];
        //updating the y value
        molecule->atom_ptrs[i]->y = transformed[1];
        //updating the z value
        molecule->atom_ptrs[i]->z = transformed[2];
    }
}