import sys
import os

HELP_MSG = "Call: python config.py [options]\n"
HELP_MSG += "--help or -h: print this message\n"
HELP_MSG += "--vtkHeaders=/path/to/vtk/headers: Specify path to the vtk library header files\n"

OUTFILE = "makefilepaths.sh"
def main(argv):
    for arg in argv:
        if ( (arg.find("--help") != -1) or (arg.find("-h") != -1) ):
            print "Usage: %s\n"%(HELP_MSG)
            return

    vtkHeader = ""
    for arg in argv:
        if ( arg.find("--vtkHeaders=") != -1 ):
            vtkHeader = arg.split("--vtkHeaders=")[1]
 
    # Check if the file already exist
    if ( os.path.isfile( OUTFILE ) ):
        print ("makefilepaths.sh already exist")
        ans = input("Overwrite or append (a/o)?")
    else:
        ans = "o"

    if ( ans == "o" ):
        out = open( OUTFILE, "w" )
    else:
        out = open( OUTFILE, "a" )

    if ( vtkHeader != "" ):
        out.write("VTK_HEADER=%s\n"%(vtkHeader))
    out.close()
    print ("Paths written to %s"%(OUTFILE))
    
if __name__ == "__main__":
    main(sys.argv[1:])
