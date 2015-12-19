#include "texture.hpp"


GLuint loadImage(const char* theFileName)
{

    GLint n, i;
    glGetIntegerv(GL_NUM_EXTENSIONS, &n);
    for (i = 0; i < n; i++) {
        // printf("%d\n", glGetStringi(GL_EXTENSIONS, i));
        // printf("%s\n", glGetStringi(GL_EXTENSIONS, i));

    }
    printf("loading image\n");
    GLuint tex_2d = SOIL_load_OGL_texture
    (
        theFileName,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS 
    );

    if (0 == tex_2d)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
    }
    return tex_2d;
}

//Prev used for devil
// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
// GLuint loadImage(const char* theFileName)
// {
//     ILuint imageID;             // Create an image ID as a ULuint
 
//     GLuint textureID;           // Create a texture ID as a GLuint
 
//     ILboolean success;          // Create a flag to keep track of success/failure
 
//     ILenum error;               // Create a flag to keep track of the IL error state
 
//     ilGenImages(1, &imageID);       // Generate the image ID
 
//     ilBindImage(imageID);           // Bind the image
 
//     success = ilLoadImage(theFileName);     // Load the image file
 
//     // If we managed to load the image, then we can start to do things with it...
//     if (success)
//     {
//         // If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
//         ILinfo ImageInfo;
//         iluGetImageInfo(&ImageInfo);
//         if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
//         {
//             iluFlipImage();
//         }
 
//         // Convert the image into a suitable format to work with
//         // NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
//         success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
 
//         // Quit out if we failed the conversion
//         if (!success)
//         {
//             error = ilGetError();
//             std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
//             exit(-1);
//         }
 
//         // Generate a new texture
//         glGenTextures(1, &textureID);
 
//         // Bind the texture to a name
//         glBindTexture(GL_TEXTURE_2D, textureID);
 
//         // Set texture clamping method
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 

//         // Set texture interpolation method to the highest visual quality it can be:
//         // GL_LINEAR_MIPMAP_LINEAR for minification - i.e. trilinear filtering
//         // GL_LINEAR for magnification (choices are either GL_NEAREST or GL_LINEAR - we do not use any MIPMAP settings for magnification!!
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
//         // Specify the texture specification
//         glTexImage2D(GL_TEXTURE_2D,                 // Type of texture
//                      0,             // Pyramid level (for mip-mapping) - 0 is the top level
//                      ilGetInteger(IL_IMAGE_FORMAT), // Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
//                      ilGetInteger(IL_IMAGE_WIDTH),  // Image width
//                      ilGetInteger(IL_IMAGE_HEIGHT), // Image height
//                      0,             // Border width in pixels (can either be 1 or 0)
//                      ilGetInteger(IL_IMAGE_FORMAT), // Format of image pixel data
//                      GL_UNSIGNED_BYTE,      // Image data type
//                      ilGetData());          // The actual image data itself
//         glGenerateMipmap(GL_TEXTURE_2D); // Note: This requires OpenGL 3.0 or higher

//     }
//     else // If we failed to open the image file in the first place...
//     {
//         error = ilGetError();
//         std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
//         exit(-1);
//     }
 
//     ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.
 
//     std::cout << "Texture creation successful." << std::endl;
 
//     return textureID; // Return the GLuint to the texture so you can use it!
// }



