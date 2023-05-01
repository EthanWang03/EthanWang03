import molecule;
import math;

#radius = { 'H': 25,
#        'C': 40,
#        'O': 40,
#        'N': 40,
#        }
#element_name = { 'H': 'grey',
#        'C': 'black',
#        'O': 'red',
#        'N': 'blue',
#        }
header = """<svg version="1.1" width="1000" height="1000" xmlns="http://www.w3.org/2000/svg">"""
footer = """</svg>"""
offsetx = 500
offsety = 500

class Atom:
    def __init__(self, c_atom):
        self.c_atom = c_atom
        self.z = c_atom.z

    def __str__(self):
        return f'Element = {self.c_atom.element}, x = {self.c_atom.x}, y = {self.c_atom.y}, z = {self.c_atom.z}'
    
    def svg (self):
        x = float(self.c_atom.x * 100.0) + offsetx
        y = float(self.c_atom.y * 100.0) + offsety

        r = 40
        fill = 'Default'
        #find element in dictionary 
        if self.c_atom.element in radius:
            r = radius[self.c_atom.element]
        if self.c_atom.element in element_name:
            fill = element_name[self.c_atom.element]

        #return circles for molecule
        return f'  <circle cx="{x:.2f}" cy="{y:.2f}" r="{40}" fill="url(#{fill})"/>\n'

class Bond:
    def __init__(self, c_bond):
        self.c_bond = c_bond
        self.z = c_bond.z

    def __str__(self):
        return f'Element1 = {self._c_bond.a1}, Element2 = {self._c_bond.a2}'

    def svg (self):
        #find points
        x1 = (self.c_bond.x1 * 100.0) + offsetx
        x2 = (self.c_bond.x2 * 100.0) + offsetx

        y1 = (self.c_bond.y1 * 100.0) + offsety
        y2 = (self.c_bond.y2 * 100.0) + offsety

        dy = y2-y1
        dx = x2-x1

        len = math.sqrt(dx*dx + dy*dy)

        #find dy and dx
        dx = dx * 10 / len
        dy = dy * 10 / len

        #return rectangle for bonds
        return f'  <polygon points="{x1-dy:.2f},{y1+dx:.2f} {x1+dy:.2f},{y1-dx:.2f} {x2+dy:.2f},{y2-dx:.2f} {x2-dy:.2f},{y2+dx:.2f}" fill="green"/>\n'


class Molecule(molecule.molecule):
    def __str__(self):

        #get atom prints and bond prints
        atomString = "Atoms: "
        i = 0
        while i < self.atom_no:
            atom = self.get_atom(i)
            atomString += f" {atom.element} {atom.x} {atom.y} {atom.z}\n"
            i = i + 1

        i = 0
        bondString = "Bonds: "
        while i < self.bond_no:
            bond = self.get_bond(i)
            bondString += f" {bond.a1} {bond.a2} {bond.epairs}"
            i = i + 1

        atomString += bondString

        return atomString

    def svg(self):
        
        string = ""
        string += header
        bondCount = 0
        atomCount = 0
        
        i = 0

        #for i < total amount of bonds and atoms
        while i  < (self.atom_no + self.bond_no):
            
            #if there are still atoms or bonds left
            if(bondCount < self.bond_no and atomCount < self.atom_no):

                #bond and atom objects
                bond = Bond(self.get_bond(bondCount))
                atom = Atom(self.get_atom(atomCount))

                #compare z
                if atom.z < bond.z:
                    #add to svg string
                    append = Atom(self.get_atom(atomCount)).svg()
                    string += append
                    #incriment atoms
                    atomCount = atomCount + 1
                else:
                    #add to svg string
                    append = Bond(self.get_bond(bondCount)).svg()
                    string += append
                    #incriment bonds
                    bondCount = bondCount + 1
            #if there are no more bonds or there are no more atoms
            else:
                #if there are no more bonds
                if(bondCount >= self.bond_no):
                    #add to svg string
                    append = Atom(self.get_atom(atomCount)).svg()
                    string += append
                    #incriment atoms
                    atomCount = atomCount + 1
                #if there are no more atoms
                else:
                    #add to svg string
                    append = Bond(self.get_bond(bondCount)).svg()
                    string += append
                    #incriment bonds
                    bondCount = bondCount + 1
            i = i + 1
        
        #add footer
        string += footer

        return string
    
    def parse(self, file_obj):

        #for number of lines in object
        for line in file_obj:

            #if line contains x y z for elements
            if '.' in line:  

                #split to get x y z
                xyz = line.split('   ') # 3 space   

                #split z and element from each other             
                element = xyz[3].split(' ') # 1 space

                #if z is negative
                if '-' in xyz[3]:
                    x = float(xyz[1])
                    y = float(xyz[2])
                    z = float(element[0])

                    #append to molecule
                    self.append_atom(element[1],x,y,z)

                #if z is positive
                else:
                    x = float(xyz[1])
                    y = float(xyz[2])
                    z = float(element[1])

                    #append to molecule
                    self.append_atom(element[2],x,y,z)

            #if line contains bond data
            elif '  ' in line:

                if '999 V2000' not in line:
                    if 'M  END' not in line:

                        a1 = line.split()[0]
                        a2 = line.split()[1]
                        epairs = line.split()[2]

                        #if epairs is 0x
                        if '0' in epairs:
                            epairs = epairs[1:]

                        #append to molecule
                        self.append_bond(int(a1)-1,int(a2)-1,int(epairs))
                    elif 'M  END' in line:
                        return
        