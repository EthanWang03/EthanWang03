from http.server import HTTPServer, BaseHTTPRequestHandler;

import sys;
import urllib;
import cgi;
import sqlite3;
import json;

import MolDisplay
import molesql;
import molecule;

# list of files that we allow the web-server to serve to clients
# (we don't want to serve any file that the client requests)

class MyHandler( BaseHTTPRequestHandler ):
    def do_GET(self):

        if self.path == "/":
            self.send_response( 200 ); # OK
            self.send_header( "Content-type", "text/html" )
            fp = open("homePage.html")
            home_page = fp.read()
            fp.close()

            self.send_header( "Content-length", len(home_page) )
            self.end_headers()

            self.wfile.write( bytes( home_page, "utf-8" ) )

        elif self.path == "/sdf_upload.html":
            self.send_response( 200 ); # OK
            self.send_header( "Content-type", "text/html" )
            fp = open("sdf_upload.html")
            sdf = fp.read()
            fp.close()

            self.send_header( "Content-length", len(sdf) )
            self.end_headers()

            self.wfile.write( bytes( sdf, "utf-8" ) )   

        elif self.path == "/MoleculeList.html":

            # Connect to the database
            conn = sqlite3.connect('molecule.db')

            fp = open("MoleculeList.html")
            html = fp.read()

            query = """
                SELECT NAME FROM Molecules
                """
            names = conn.execute(query).fetchall()
            
            for name in names:
                
                query = """
                    SELECT COUNT(*)
                    FROM Molecules, MoleculeAtom, Atoms
                    WHERE (Molecules.NAME = ? 
                    AND Molecules.MOLECULE_ID = MoleculeAtom.MOLECULE_ID 
                    AND MoleculeAtom.ATOM_ID = Atoms.ATOM_iD)
                    """
                Atoms = conn.execute(query, name)

                numAtoms = Atoms.fetchone()[0]

                query = """
                    SELECT COUNT(*)
                    FROM Molecules, MoleculeBond, Bonds
                    WHERE (Molecules.NAME = ? 
                    AND Molecules.MOLECULE_ID = MoleculeBond.MOLECULE_ID 
                    AND MoleculeBond.BOND_ID = Bonds.BOND_ID)
                    """
                Bonds = conn.execute(query, name)

                numBonds = Bonds.fetchone()[0]

                html += f"""<tr>
                            <td><a href="http://localhost:54940/display{name[0]}.html"><button>View</button></a></td>
                            <td>{name[0]}</td>
                            <td>{numAtoms}</td>
                            <td>{numBonds}</td>
                            <td><button>Delete</button></td>
                            </tr>"""

            html += """</tbody>
                        </table>
                        <script>
                            const deleteButtons = document.querySelectorAll('button');
                            deleteButtons.forEach(button => {
                            button.addEventListener('click', (event) => {
                                const row = event.target.parentNode.parentNode;
                                const data = {row1: row.cells[1].textContent};
                                fetch('/deleteMolecule', {
                                    method: 'POST',
                                    headers: {'Content-Type': 'application/json'},
                                    body: JSON.stringify(data)
                                })
                                .then(response => response.json())
                                .then(data => console.log(data))
                                .catch(error => console.error(error));
                            });
                            });
                        </script>
                    </div>
                </body>
                </html>"""
            
            conn.close()
            
            self.send_response( 200 ); # OK
            self.send_header( "Content-type", "text/html" )
            self.send_header( "Content-length", len(html) )
            self.send_header("Cache-Control", "no-cache, no-store, must-revalidate")
            self.send_header("Pragma", "no-cache")
            self.send_header("Expires", "0")
            self.end_headers()
            self.wfile.write( bytes( html, "utf-8" ) )
            

        elif self.path.__contains__("/display"):

            db = molesql.Database(reset=False);

            MolDisplay.radius = db.radius();
            MolDisplay.element_name = db.element_name();
            MolDisplay.header += db.radial_gradients();

            self.send_response( 200 ); # OK

            name = self.path.split("/")[1].replace("display", "")
            name = name.rsplit(".", 1)[0].rsplit("/", 1)[-1]

            self.send_header( "Content-type", "text/html" )
            fp = open("display.html")
            page = fp.read()
            fp.close()

            mol = db.load_mol(name)
            mol.sort()

            svg = open(name + ".svg", "w")
            svg.write(mol.svg())
            svg.close()

            with open(name + ".svg", 'r') as f:
                final_svg = f.read()

            page += final_svg

            page += """	</div>
            </body>
            </html>
            """

            self.send_header( "Content-length", len(page) )
            self.end_headers()

            self.wfile.write( bytes( page, "utf-8" ) )

        elif self.path == "/ElementList.html":

            conn = sqlite3.connect('molecule.db')
            
            fp = open("ElementList.html")
            html = fp.read()

            query = """
                SELECT * FROM ELEMENTS
                """
            
            rows = conn.execute(query).fetchall()

            for row in rows:
                html += f"""<tr>
                            <td>{row[0]}</td>
                            <td>{row[1]}</td>
                            <td>{row[2]}</td>
                            <td>{row[3]}</td>
                            <td>{row[4]}</td>
                            <td>{row[5]}</td>
                            <td>{row[6]}</td>
                            <td><button>Delete</button></td>
                            </tr>"""
                
            html += """</tbody>
                        </table>
                        <script>
                            const deleteButtons = document.querySelectorAll('button');
                            deleteButtons.forEach(button => {
                            button.addEventListener('click', (event) => {
                                const row = event.target.parentNode.parentNode;
                                const data = {row1: row.cells[1].textContent};
                                fetch('/deleteElements', {
                                    method: 'POST',
                                    headers: {'Content-Type': 'application/json'},
                                    body: JSON.stringify(data)
                                })
                                .then(response => response.json())
                                .then(data => console.log(data))
                                .catch(error => console.error(error));
                            });
                            });
                        </script>
                    </div>
                </body>
                </html>"""
            
            conn.close()

            self.send_response( 200 ); # OK
            self.send_header( "Content-type", "text/html" )
            self.send_header( "Content-length", len(html) )
            self.send_header("Cache-Control", "no-cache, no-store, must-revalidate")
            self.send_header("Pragma", "no-cache")
            self.send_header("Expires", "0")
            self.end_headers()
            self.wfile.write( bytes( html, "utf-8" ) )

        elif self.path == "/add_Element.html":
            self.send_response( 200 ); # OK
            self.send_header( "Content-type", "text/html" )
            fp = open("add_Element.html")
            home_page = fp.read()
            fp.close()

            self.send_header( "Content-length", len(home_page) )
            self.end_headers()

            self.wfile.write( bytes( home_page, "utf-8" ) )

        else:
            # if the requested URL is not one of the public_files
            self.send_response( 404 );
            self.end_headers();
            self.wfile.write( bytes( "404: not found", "utf-8" ) );


    def do_POST(self):
        content_type = self.headers['Content-Type']
        if self.path == "/submit":
            
            self.send_response( 200 ); # OK

            db = molesql.Database(reset=False);

            content_length = int(self.headers['Content-Length'])
            data = self.rfile.read(content_length).decode('utf-8')
            post_data = urllib.parse.parse_qs(data)

            number = int(post_data["number"][0])
            code = post_data["code"][0]
            name = post_data["name"][0]
            colour1 = post_data["colour1"][0]
            colour2 = post_data["colour2"][0]
            colour3 = post_data["colour3"][0]
            radius = int(post_data["radius"][0])

            db['Elements'] = (number,code,name,colour1,colour2,colour3,radius)

        elif self.path == "/deleteElements":
            content_length = int(self.headers['Content-Length'])
            data = json.loads(self.rfile.read(content_length))
            code = data['row1']
        
            conn = sqlite3.connect('molecule.db')

            cursor = conn.cursor()

            cursor.execute('DELETE FROM Elements WHERE ELEMENT_CODE = ?', (code,))

            conn.commit()

            cursor.close()
            conn.close()

            self.send_response(303)  # 303 indicates a temporary redirect
            self.send_header('Location', 'http://localhost:54940/ElementList.html')
            self.end_headers()

        elif self.path == "/deleteMolecule":
            content_length = int(self.headers['Content-Length'])
            data = json.loads(self.rfile.read(content_length))

            name = data['row1']
        
            conn = sqlite3.connect('molecule.db')

            cursor = conn.cursor()
            
            #print(name)
            cursor.execute('DELETE FROM Molecules WHERE NAME = ?', (name,))

            conn.commit()

            cursor.close()
            conn.close()

            self.send_response(303)  # 303 indicates a temporary redirect
            self.send_header('Location', 'http://localhost:54940/MoleculeList.html')
            self.end_headers()

        elif self.path == "/rotate":
            content_length = int(self.headers['Content-Length'])
            data = self.rfile.read(content_length).decode('utf-8')
            post_data = urllib.parse.parse_qs(data)

            X = int(post_data["X"][0])
            Y = int(post_data["Y"][0])
            Z = int(post_data["Z"][0])

            #mx = molecule.mx_wrapper(X, Y, Z)

            #db = molesql.Database(reset=False)

            #mole = db.load_mol('apple')

            #mole.sort()

            #mole.xform(mx.xform_matrix)

            #print(X,Y,Z)
            self.send_response( 200 ); # OK

        elif self.path == "/upload":

            form = cgi.FieldStorage(
            fp=self.rfile,
            headers=self.headers,
            environ={
                'REQUEST_METHOD': 'POST',
                'CONTENT_TYPE': self.headers['Content-Type'],
            })

            # Get the uploaded file and its contents
            uploaded_file = form['file']
            uploaded_file_contents = uploaded_file.file.read().decode("utf-8") 

            # Get the username input
            username = form.getvalue('username')

            db = molesql.Database(reset=False);

            db.add_molecule(username, uploaded_file_contents)

            # Send response status code
            self.send_response(200)

        else:
            self.send_response( 404 );
            self.end_headers();
            self.wfile.write( bytes( "404: not found", "utf-8" ) );

httpd = HTTPServer( ( 'localhost', 54940 ), MyHandler );
httpd.serve_forever();
