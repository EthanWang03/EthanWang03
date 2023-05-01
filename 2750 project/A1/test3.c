#include "mol.h"

#include <stdio.h>
#include <string.h>

void display_mol( molecule *molecule )
{
  /* display the molecule */

  /* display the atom array parameters */
  printf( "atom_max: %hu, atom_no: %hu\n", 
          molecule->atom_max, molecule->atom_no );

  /* display all atoms */
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

  /* display atom pointers and the atoms that they point to */
  for (int i=0;i<molecule->atom_no;i++)
  {
    char name[3];
    double x,y,z;
    atom *atom_ptr;

    // get pointer from atom_ptrs array
    atom_ptr = molecule->atom_ptrs[i];


    printf( "atom_ptrs[%d]: %p", i, (void *)(atom_ptr) );

		// get the info form the atom
    atomget( atom_ptr, name, &x, &y, &z );
    printf( "  -> atom[%lu] %p %-2s: %lf %lf %lf\n", 
	          (atom_ptr - molecule->atoms), 
            (void *)atom_ptr, name, x, y, z );
  }

  /* bonds */
  printf( "bond_max: %hu, bond_no: %hu\n", 
          molecule->bond_max, molecule->bond_no );
  for (int i=0;i<molecule->bond_no;i++)
  {
    atom *a1, *a2;
    unsigned char epairs;
    bond *bond_ptr;

    bond_ptr = molecule->bonds+i;
    bondget( bond_ptr, &a1, &a2, &epairs );
    printf( "bond[%d] %p: %p(%s) %p(%s) %hhu\n",
            i, (void *)bond_ptr, (void *)a1, a1->element, 
                                 (void *)a2, a2->element, epairs );

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


int main( int argc, char **argv )
{
  /* create the molecule */
  molecule *molecule, *mx, *my, *mz;	// original and 3 rotated copies
  atom O, X, Y, Z;									  // atoms at origin and along axes
  bond OX, OY, OZ;									  // bonds from-to
  xform_matrix xrot, yrot, zrot;      // rotations around 3 axes

  strcpy( O.element, "O" );
  O.x = 0.0;
  O.y = 0.0;
  O.z = 0.0;

  strcpy( X.element, "X" );
  X.x = 1.0;
  X.y = 0.0;
  X.z = 0.0;

  strcpy( Y.element, "Y" );
  Y.x = 0.0;
  Y.y = 1.0;
  Y.z = 0.0;

  strcpy( Z.element, "Z" );
  Z.x = 0.0;
  Z.y = 0.0;
  Z.z = 1.0;

  molecule = molmalloc( 4, 3 );

	molappend_atom( molecule, &O );
	molappend_atom( molecule, &X );
	molappend_atom( molecule, &Y );
	molappend_atom( molecule, &Z );

  OX.a1 = molecule->atoms+0;
  OX.a2 = molecule->atoms+1;
  OX.epairs = 1;

  OY.a1 = molecule->atoms+0;
  OY.a2 = molecule->atoms+2;
  OY.epairs = 1;

  OZ.a1 = molecule->atoms+0;
  OZ.a2 = molecule->atoms+3;
  OZ.epairs = 1;

  molappend_bond( molecule, &OX );
  molappend_bond( molecule, &OY );
  molappend_bond( molecule, &OZ );

  //display_mol( molecule );

  mx = molcopy( molecule );
  my = molcopy( molecule );
  mz = molcopy( molecule );

  xrotation( xrot, 30 );
  yrotation( yrot, 45 );
  zrotation( zrot, 60 );

  mol_xform( mx, xrot );
  mol_xform( my, yrot );
  mol_xform( mz, zrot );

  display_mol( mx );
  display_mol( my );`
  display_mol( mz );

  molfree( molecule );
  molfree( mx );
  molfree( my );
  molfree( mz );
    
  return 0;
}

