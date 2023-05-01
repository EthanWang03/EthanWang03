#include "mol.h"

#include <stdio.h>
#include <string.h>

#define PI 3.14159265359

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
  /* This program creates a strange molecule in which all the atoms are bonded
     to gether in a straight line.  The elements also consist of a number of
     abnormal elements, e.g. "e", "l" (not I), "o" (lower case oxygen?), 
     "w" (lower case tungsten?), "d", "r" and "!" (the element of surprise).
     After sorting the elements in z-order a "secret message" should be 
     revealed. */
  molecule *molecule;

  double zs[13] = { -5.0, -4.0, -2.0, 4.0, 0.0, 6.0, 2.0, 1.0, -6.0, 
                    -3.0, 5.0, 3.0, -1.0 };
  char *str = "elol !owHldr,";
  /* int bond_pairs[12][2] = { {5,10}, {10,3}, {3,11}, {11,6}, {6,7}, {7,4},
                            {4,12}, {12,2}, {2,9}, {9,1}, {1,0}, {0,8} }; */
  int bond_pairs[12][2] = { {2,9}, {7,4}, {1,0}, {9,1}, {0,8}, {4,12}, {6,7}, 
                            {10,3}, {3,11}, {11,6}, {12,2}, {5,10} };

  /* create the molecule */
  molecule = molmalloc( 0, 0 );

  /* set the atoms */
  for (int i=0;i<13;i++)
  {
    double x, y, z;
    char element[3] = "X";
    atom a1;

    x = 2.5369; y = -0.1550; z = zs[i];
    element[0] = str[i];
    atomset( &a1, element, &x, &y, &z );

    /* add atoms to molecule */
    molappend_atom( molecule, &a1 );
  }

	/* set the bonds */
	for (int i=0;i<12;i++)
  {
    bond b1;
    
    b1.a1 = molecule->atoms + bond_pairs[i][0];
    b1.a2 = molecule->atoms + bond_pairs[i][1];
    b1.epairs = 1;

    molappend_bond( molecule, &b1 );
  }

  display_mol( molecule );

  printf( "\nSorting molecule\n\n" );
  molsort( molecule );

  display_mol( molecule );

  molfree( molecule );
    
  return 0;
}

