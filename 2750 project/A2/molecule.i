/* File:  mol.i */
%module molecule
%{
  #include "mol.h"
%}

%include "mol.h"

%extend atom {
  atom( char element[3], double x, double y, double z )
  {
    atom *a;
    a = (atom *)malloc( sizeof(atom) );
    atomset( a, element, &x, &y, &z );
    return a;
  }

  ~atom()
  {
    free($self);
  }
};

%extend bond {
  bond( bond *bond )
  {
    return bond;
  }
};

%extend molecule {
  molecule()
  {
    molecule *mol;
    mol = molmalloc( 0, 0 );
    return mol;
  }

  ~molecule()
  {
    molfree($self);
  }

  void append_atom( char element[3], double x, double y, double z )
  {
    atom a1;
    strcpy( a1.element, element );
    a1.x = x;
    a1.y = y;
    a1.z = z;

    molappend_atom( $self, &a1 );
  }

  void append_bond( unsigned short a1, unsigned short a2, unsigned char epairs )
  {
    bond b1;
    b1.a1 = a1-1;
    b1.a2 = a2-1;
    b1.atoms = $self->atoms;
    b1.epairs = epairs;
    compute_coords( &b1 );
    // printf( ">A> %hu %hu %lf\n", b1.a1, b1.a2, b1.z );

    molappend_bond( $self, &b1 );
  }

  atom *get_atom( unsigned short i )
  {
    return $self->atom_ptrs[i];
  }

  bond *get_bond( unsigned short i )
  {
    return $self->bond_ptrs[i];
  }

  void sort()
  {
    molsort( $self );
  }
};


