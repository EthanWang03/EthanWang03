#include "mol.h"

void display_mol( molecule *molecule )
{

  printf( "atom_max: %hu, atom_no: %hu\n", 
          molecule->atom_max, molecule->atom_no );
  for (int i=0;i<molecule->atom_no;i++)
  {
    char name[3];
    double x,y,z;
    atom *atom_ptr;

    atom_ptr = molecule->atoms+i;

    atomget( atom_ptr, name, &x, &y, &z );
    printf( "atom[%d] %p %-2s: %lf %lf %lf\n", 
	    i, (void *)atom_ptr, name, x, y, z );

  }

  for (int i=0;i<molecule->atom_no;i++)
  {
    printf( "atom_ptrs[%d]: %p\n", i, (void *)(molecule->atom_ptrs[i]));
  }

  printf( "bond_max: %hu, bond_no: %hu\n", 
          molecule->bond_max, molecule->bond_no );
  for (int i=0;i<molecule->bond_no;i++)
  {
    atom *a1, *a2;
    unsigned char epairs;
    bond *bond_ptr;

    bond_ptr = molecule->bonds+i;
    bondget( bond_ptr, &a1, &a2, &epairs );
    printf( "bond[%d] %p: %p %p %hu\n",
            i, (void *)bond_ptr, (void *)a1, (void *)a2, epairs );

  }

  for (int i=0;i<molecule->bond_no;i++)
  {
    printf( "bond_ptrs[%d]: %p\n", i, (void *)(molecule->bond_ptrs[i]) );
  }

}


int main( int argc, char **argv )
/*
 * create a water molecule and display it 
 */
{
  double x, y, z;
  atom a1, a2, a3;
  bond bond1, bond2;
  molecule *molecule;

  /* set the atoms */
  x = 2.5369; y = -0.1550; z = 0.0000;
  atomset( &a1, "O", &x, &y, &z );
  
  x = 3.0739; y =  0.1550; z = 0.0000;
  atomset( &a2, "H", &x, &y, &z );

  x = 2.0000; y =  0.1550; z = 0.0000;
  atomset( &a3, "H", &x, &y, &z );

  //create the molecule 
  molecule = molmalloc( 0, 2 );

  molappend_atom( molecule, &a1 );
  molappend_atom( molecule, &a2 );
  molappend_atom( molecule, &a3 );

  bondset( &bond1, &(molecule->atoms[0]), &(molecule->atoms[1]), 1 );
  bondset( &bond2, &(molecule->atoms[0]), &(molecule->atoms[2]), 1 );

  molappend_bond( molecule, &bond1 );
  molappend_bond( molecule, &bond2 );

  display_mol( molecule );
  molfree( molecule );
  return 0;
}

