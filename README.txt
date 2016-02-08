  _____               _______                        _____  ______          _____  __  __ ______ 
 |  __ \             |__   __|                      |  __ \|  ____|   /\   |  __ \|  \/  |  ____|
 | |__) |__ _ _   _     | |_ __ __ _  ___ ___ _ __  | |__) | |__     /  \  | |  | | \  / | |__   
 |  _  // _" | | | |    | | '__/ _" |/ __/ _ \ '__| |  _  /|  __|   / /\ \ | |  | | |\/| |  __|  
 | | \ \ (_| | |_| |    | | | | (_| | (_|  __/ |    | | \ \| |____ / ____ \| |__| | |  | | |____ 
 |_|  \_\__,_|\__, |    |_|_|  \__,_|\___\___|_|    |_|  \_\______/_/    \_\_____/|_|  |_|______|
               __/ |                                                                             
              |___/     Written by Brandon Davis in 100% native C++                           

---------------------------------------Compile Instructions--------------------------------------

    1. unzip this archive
    2. open a terminal and cd to the source directory
    3. run "./build.sh"
    4. run "./run.sh"
    5. images will be located in ./Images (should open automatically)

----------------------------------------Build Requirements---------------------------------------

    + Any OS capable of running a BASH script
    + The g++ compiler
        * Can be installed on ubuntu-based systems via "sudo apt-get install build-essential"
    + An image viewer that supports the .ppm format
        * Alternatively, use imagemagick to create a .png
        * "sudo apt-get install imagemagick"
        * "cd Images"
        * "convert <ppm image name>  <png image name>"
    + OpenGL is NOT required.

---------------------------------------Description of Parts---------------------------------------

    This project is build from a few basic components:
    + A room, which contains
        * Drawables - these implement an intersect function and a getOrtho, which returns an orthogonal ray for any point in space.
            - Sphere
            - Plane
            - Each drawable has a PhongProp - Phong properties that the tracer will use to compute lighting
        * A camera - a point in threespace to make the origin of each ray.
        * Any number of lights, each of which will be computed spearately in the trace function.
        * A View window - Can be set to any 3 coplanar points in space.  The room will generate initial camera rays based on the camera and view window
    + The Tracer, which only implements perspective tracing but could be easily refactored to allow for orthographic tracing.
        * Tracer logic: check if a camera ray has any intersections, then compute lighting for the closest intersect point it finds.
    + The Renderer, which encapsulates antialiasing and image resolution.  
        * The same room can be passed twice to the same tracer with different renderers to get either
            - Different resolutions
            - A different representation of the room (i.e. the ASCII preview you see)
    + Helper Classes such as
        * Color - normalized at the end of rendering based on the global min and max 
        * Vector3 - used for both vectors and points
        * Ray - Which wraps a vector and a point together, and is the basic unit for checking intersection