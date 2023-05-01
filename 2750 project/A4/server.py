import sys;
import MolDisplay
import molesql

from http.server import HTTPServer, BaseHTTPRequestHandler;

class MyHandler( BaseHTTPRequestHandler ):
    def do_GET(self):
        if self.path == "/":
            self.send_response( 200 ); # OK
            self.send_header( "Content-type", "text/html" )
            self.send_header( "Content-length", len(home_page) )
            self.end_headers()

            self.wfile.write( bytes( home_page, "utf-8" ) )

        else:
            self.send_response( 404 )
            self.end_headers()
            self.wfile.write( bytes( "404: not found", "utf-8" ) )
    
    #display molecule after file upload
    def do_POST(self):
        #gets type
        content_type = self.headers['Content-Type']
        if content_type.startswith('multipart/form-data'):
            
            content_length = int(self.headers['Content-Length'])

            #read data use utf-8 to decode
            field_data = self.rfile.read(content_length).decode("utf-8") 

            molecule = MolDisplay.Molecule()

            #parse
            molecule.parse(field_data.splitlines()[4:])

            #sort
            molecule.sort()

            #create svg
            final_svg = molecule.svg()

            #SEND OK
            self.send_response(200)
            self.send_header('Content-type', 'image/svg+xml')
            self.send_header("Content-length", len(final_svg))
            self.end_headers()

            #display svg
            self.wfile.write(bytes(final_svg,"utf-8"))
            
        #if no file is uploaded
        else:
            self.send_response(400)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            self.wfile.write(bytes("Bad request: unsupported Content-Type", "utf-8"))


home_page = """
<html>
  <head>
    <title> File Upload </title>
  </head>
  <body>
    <h1> File Upload </h1>
    <form action="molecule" enctype="multipart/form-data" method="post">
      <p>
      <input type="file" id="sdf_file" name="filename"/>
      </p>
      <p>
      <input type="submit" value="Upload"/>
      </p>
    </form>
  </body>
</html>
"""

#1184940
httpd = HTTPServer( ( 'localhost', 54940 ), MyHandler );
httpd.serve_forever();
