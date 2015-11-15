#include "texture.hpp"

// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint loadImage(const char* theFileName)
{
    ILuint imageID;             // Create an image ID as a ULuint
 
    GLuint textureID;           // Create a texture ID as a GLuint
 
    ILboolean success;          // Create a flag to keep track of success/failure
 
    ILenum error;               // Create a flag to keep track of the IL error state
 
    ilGenImages(1, &imageID);       // Generate the image ID
 
    ilBindImage(imageID);           // Bind the image
 
    success = ilLoadImage(theFileName);     // Load the image file
 
    // If we managed to load the image, then we can start to do things with it...
    if (success)
    {
        // If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
        ILinfo ImageInfo;
        iluGetImageInfo(&ImageInfo);
        if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
        {
            iluFlipImage();
        }
 
        // Convert the image into a suitable format to work with
        // NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
        success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
 
        // Quit out if we failed the conversion
        if (!success)
        {
            error = ilGetError();
            std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
            exit(-1);
        }
 
        // Generate a new texture
        glGenTextures(1, &textureID);
 
        // Bind the texture to a name
        glBindTexture(GL_TEXTURE_2D, textureID);
 
        // Set texture clamping method
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 

        // Set texture interpolation method to the highest visual quality it can be:
        // GL_LINEAR_MIPMAP_LINEAR for minification - i.e. trilinear filtering
        // GL_LINEAR for magnification (choices are either GL_NEAREST or GL_LINEAR - we do not use any MIPMAP settings for magnification!!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
        // Specify the texture specification
        glTexImage2D(GL_TEXTURE_2D,                 // Type of texture
                     0,             // Pyramid level (for mip-mapping) - 0 is the top level
                     ilGetInteger(IL_IMAGE_FORMAT), // Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
                     ilGetInteger(IL_IMAGE_WIDTH),  // Image width
                     ilGetInteger(IL_IMAGE_HEIGHT), // Image height
                     0,             // Border width in pixels (can either be 1 or 0)
                     ilGetInteger(IL_IMAGE_FORMAT), // Format of image pixel data
                     GL_UNSIGNED_BYTE,      // Image data type
                     ilGetData());          // The actual image data itself
        glGenerateMipmap(GL_TEXTURE_2D); // Note: This requires OpenGL 3.0 or higher

    }
    else // If we failed to open the image file in the first place...
    {
        error = ilGetError();
        std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
        exit(-1);
    }
 
    ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.
 
    std::cout << "Texture creation successful." << std::endl;
 
    return textureID; // Return the GLuint to the texture so you can use it!
}

// GLuint loadBMP_custom(const char * imagepath){

// 	// printf("Reading image %s\n", imagepath);

// 	// Data read from the header of the BMP file
// 	unsigned char header[54];
// 	unsigned int dataPos;
// 	unsigned int imageSize;
// 	unsigned int width, height;
// 	// Actual RGB data
// 	unsigned char * data;

// 	// Open the file
// 	FILE * file = fopen(imagepath,"rb");
// 	if (!file)							    {printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); return 0;}

// 	// Read the header, i.e. the 54 first bytes

// 	// If less than 54 bytes are read, problem
// 	if ( fread(header, 1, 54, file)!=54 ){ 
// 		printf("Not a correct BMP file\n");
// 		return 0;
// 	}
// 	// A BMP files always begins with "BM"
// 	if ( header[0]!='B' || header[1]!='M' ){
// 		printf("Not a correct BMP file\n");
// 		return 0;
// 	}
// 	// Make sure this is a 24bpp file
// 	if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
// 	if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

// 	// Read the information about the image
// 	dataPos    = *(int*)&(header[0x0A]);
// 	imageSize  = *(int*)&(header[0x22]);
// 	width      = *(int*)&(header[0x12]);
// 	height     = *(int*)&(header[0x16]);

// 	// Some BMP files are misformatted, guess missing information
// 	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
// 	if (dataPos==0)      dataPos=54; // The BMP header is done that way

// 	// Create a buffer
// 	data = new unsigned char [imageSize];

// 	// Read the actual data from the file into the buffer
// 	fread(data,1,imageSize,file);

// 	// Everything is in memory now, the file wan be closed
// 	fclose (file);

// 	// Create one OpenGL texture
// 	GLuint textureID;
// 	glGenTextures(1, &textureID);
	
// 	// "Bind" the newly created texture : all future texture functions will modify this texture
// 	glBindTexture(GL_TEXTURE_2D, textureID);

// 	// Give the image to OpenGL
// 	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

// 	// OpenGL has now copied the data. Free our own version
// 	delete [] data;

// 	// Poor filtering, or ...
// 	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

// 	// ... nice trilinear filtering.
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
// 	glGenerateMipmap(GL_TEXTURE_2D);

// 	// Return the ID of the texture we just created
// 	return textureID;
// }

