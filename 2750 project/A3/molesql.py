import sqlite3
import os
import MolDisplay
import ctypes

class Database:
    
    def __init__(self, reset=False):

        if reset:
            os.remove("molecule.db")

        self.conn = sqlite3.connect("molecule.db")
        self.conn.commit()

    def create_tables(self):

        #Elements
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Elements(
                ELEMENT_NO INTEGER NOT NULL, 
                ELEMENT_CODE VARCHAR(3) NOT NULL, 
                ELEMENT_NAME VARCHAR(32) NOT NULL, 
                COLOUR1 CHAR(6) NOT NULL, 
                COLOUR2 CHAR(6) NOT NULL, 
                COLOUR3 CHAR(6) NOT NULL, 
                RADIUS DECIMAL(3) NOT NULL,
                PRIMARY KEY (ELEMENT_CODE));
                ''')

        #Atoms
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Atoms(
                ATOM_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                ELEMENT_CODE VARCHAR(3) NOT NULL,
                X DECIMAL(7,4) NOT NULL,
                Y DECIMAL(7,4) NOT NULL,
                Z DECIMAL(7,4) NOT NULL,
                FOREIGN KEY (ELEMENT_CODE) REFERENCES Elements(ELEMENT_CODE));
                ''')
        
        #Bonds
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Bonds(
                BOND_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                A1 INTEGER NOT NULL,
                A2 INTEGER NOT NULL,
                EPAIRS INTEGER NOT NULL);
                ''')

        #Molecules
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Molecules(
                MOLECULE_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                NAME TEXT UNIQUE NOT NULL);
                ''')
        
        #MoleculeAtom
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS MoleculeAtom(
                MOLECULE_ID INTEGER NOT NULL,
                ATOM_ID INTEGER NOT NULL,
                PRIMARY KEY (MOLECULE_ID, ATOM_ID),
                FOREIGN KEY (MOLECULE_ID) REFERENCES Molecules(MOLECULE_ID),
                FOREIGN KEY (ATOM_ID) REFERENCES Atoms(ATOM_ID));
                ''')
        
        #MoleculeBond
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS MoleculeBond(
                MOLECULE_ID INTEGER NOT NULL,
                BOND_ID INTEGER NOT NULL,
                PRIMARY KEY (MOLECULE_ID, BOND_ID),
                FOREIGN KEY (MOLECULE_ID) REFERENCES Molecules(MOLECULE_ID),
                FOREIGN KEY (BOND_ID) REFERENCES Atoms(BOND_ID));
                ''')

    def __setitem__(self, table, values):
        # Insert values into tables
        placeholders = ','.join('?' * len(values))
        query = f"INSERT INTO {table} VALUES ({placeholders})"
        self.conn.execute(query, values)
        self.conn.commit()
        
    def add_atom(self, molname, atom):
        # Insert values into Atoms table
        self["Atoms"] = (None, atom.element, atom.x, atom.y, atom.z)

        # Get the atom ID that was just inserted
        atom_id = self.conn.execute("SELECT last_insert_rowid()").fetchone()[0]

        # Insert values into MoleculeAtom table
        molecule_id = self.conn.execute("SELECT MOLECULE_ID FROM Molecules WHERE NAME = ?", (molname,)).fetchone()[0]
        
        self["MoleculeAtom"] = (molecule_id, atom_id)

    def add_bond(self, molname, bond):
        # Add bond to the Bonds table
        self['Bonds'] = (None, bond.a1, bond.a2, bond.epairs)
        
        # Get the ID of the newly added bond
        bond_id = self.conn.execute("SELECT last_insert_rowid()").fetchone()[0]
        
        # Add entry to the MoleculeBond table
        molecule_id = self.conn.execute("SELECT MOLECULE_ID FROM Molecules WHERE NAME = ?", (molname,)).fetchone()[0]
        self['MoleculeBond'] = (molecule_id, bond_id)

    def add_molecule(self, name, fp):
        # Create a MolDisplay.Molecule object and parse the file
        mol = MolDisplay.Molecule()

        #skip top lines
        mol.parse(fp.splitlines()[4:])

        # Add entry to Molecules table
        self["Molecules"] = (None, name)

        i = 0
        # Add atoms and bonds to the database for the molecule
        while i < mol.atom_no:
            atom = mol.get_atom(i)
            i = i + 1
            self.add_atom(name, atom)

        i = 0
        while i < mol.bond_no:
            bond = mol.get_bond(i)
            i = i + 1
            self.add_bond(name, bond)
        
    def load_mol(self, name):
        # Retrieve all the atoms associated with the named molecule from the database
        query = """
                SELECT *
                FROM Molecules, MoleculeAtom, Atoms
                WHERE (Molecules.NAME = ? 
                AND Molecules.MOLECULE_ID = MoleculeAtom.MOLECULE_ID 
                AND MoleculeAtom.ATOM_ID = Atoms.ATOM_iD)
                ORDER BY Atoms.ATOM_ID ASC
                """
        rows = self.conn.execute(query, (name,))
        
        # Initialize a Molecule object with the retrieved atoms and bonds
        molecule = MolDisplay.Molecule()

        # Add atoms to molecule
        for row in rows:
            molecule.append_atom(row[5], row[6], row[7], row[8])
        
        # Retrieve all the bonds associated with the named molecule from the database
        query = """
                SELECT *
                FROM Molecules, MoleculeBond, Bonds
                WHERE (Molecules.NAME = ? 
                AND Molecules.MOLECULE_ID = MoleculeBond.MOLECULE_ID 
                AND MoleculeBond.BOND_ID = Bonds.BOND_ID)
                ORDER BY Bonds.BOND_ID ASC
                """
        rows = self.conn.execute(query, (name,))

        # Add bonds to molecule
        for row in rows:
            molecule.append_bond(row[5], row[6], row[7])
        
        return molecule
    
    def radius(self):
        # Find ELEMENT_CODE and radius from Element data table
        query = "SELECT ELEMENT_CODE, RADIUS FROM Elements"
        cursor = self.conn.execute(query)
        element_data = cursor.fetchall()
        radius_dict = {}

        # Set radius dictionary index ELEMENT_CODE to the radius of element
        for row in element_data:
            radius_dict[row[0]] = row[1]
        return radius_dict

    def element_name(self):
        # Find ELEMENT_NAME and ELEMENT_CODE from Element data table
        query = "SELECT ELEMENT_CODE, ELEMENT_NAME FROM Elements"
        cursor = self.conn.execute(query)
        element_data = cursor.fetchall()
        element_dict = {}

        # Set element dictionary index ELEMENT_CODE to the ELENMENT_NAME
        for row in element_data:
            element_dict[row[0]] = row[1]
        return element_dict
    
    def radial_gradients(self):
        gradients = []
        # Get element name, colours 123 from table
        for element_name, colour1, colour2, colour3 in self.conn.execute("SELECT ELEMENT_NAME, COLOUR1, COLOUR2, COLOUR3 FROM Elements"):
            gradient = f"""
            <radialGradient id="{element_name}" cx="-50%" cy="-50%" r="220%" fx="20%" fy="20%">
                <stop offset="0%" stop-color="#{colour1}"/>
                <stop offset="50%" stop-color="#{colour2}"/>
                <stop offset="100%" stop-color="#{colour3}"/>
            </radialGradient>"""
            gradients.append(gradient.strip())
        return "\n".join(gradients)
