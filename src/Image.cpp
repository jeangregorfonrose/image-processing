//
// Created by jeang on 11/13/2021.
//
#include "Image.h"

Image::Image(){
    this->pixelsData = new vector<Pixel>();
};
Image::~Image() {
    delete this->pixelsData;
}

// Read the data of the file provided
void Image::readFile(const string& filePath, const string& fileName) {
    // Try open file to read it
    ifstream rf(filePath + fileName, ios::in | ios::binary);
    if(!rf){
        cout << "Cannot open file" << endl;
    }

    // Read Header part of file
    rf.read( (char *) &fileInfo.idLength, sizeof(fileInfo.idLength) );
    rf.read( (char *) &fileInfo.colorMapType, sizeof(fileInfo.colorMapType) );
    rf.read( (char *) &fileInfo.dataTypeCode, sizeof(fileInfo.dataTypeCode) );
    rf.read( (char *) &fileInfo.colorMapOrigin, sizeof(fileInfo.colorMapOrigin) );
    rf.read( (char *) &fileInfo.colorMapLength, sizeof(fileInfo.colorMapLength) );
    rf.read( (char *) &fileInfo.colorMapDepth, sizeof(fileInfo.colorMapDepth) );
    rf.read( (char *) &fileInfo.xOrigin, sizeof(fileInfo.xOrigin) );
    rf.read( (char *) &fileInfo.yOrigin, sizeof(fileInfo.yOrigin) );
    rf.read( (char *) &fileInfo.width, sizeof(fileInfo.width) );
    rf.read( (char *) &fileInfo.height, sizeof(fileInfo.height) );
    rf.read( (char *) &fileInfo.bitsPerPixel, sizeof(fileInfo.bitsPerPixel) );
    rf.read( (char *) &fileInfo.imageDescriptor, sizeof(fileInfo.imageDescriptor) );

    // Read pixel data
    int numberOfPixels = (int) fileInfo.width * (int) fileInfo.height;

    // check if image was already loaded
    // if loaded already clear the pixel data vector
    if (this->pixelsData->size() > 0)
    {
        // erase all pixels in vector data
        this->pixelsData->clear();
    }

    // Read pixels into vector
    Pixel pixel;

    for (int i = 0; i < numberOfPixels; ++i) {
        rf.read( (char *) &pixel.blue, sizeof(pixel.blue) );
        rf.read( (char *) &pixel.green, sizeof(pixel.green) );
        rf.read( (char *) &pixel.red, sizeof(pixel.red) );

        this->pixelsData->push_back(pixel);
    }

    // close file
    rf.close();

    if(!rf.good()){
        cout << "Error occurred at reading time!" << endl;
    }
}

// write the class data to a file
void Image::writeFile(const string& path, const string& filename) {
    string outputFilePath;
    outputFilePath = path + filename;

    // Try to write file back
    ofstream wf(outputFilePath, ios::out | ios::binary);
    if(!wf) {
        cout << "Cannot open file!" << endl;
    }

    // write the header of the file
    wf.write( (char *) &fileInfo.idLength, sizeof(fileInfo.idLength) );
    wf.write( (char *) &fileInfo.colorMapType, sizeof(fileInfo.colorMapType) );
    wf.write( (char *) &fileInfo.dataTypeCode, sizeof(fileInfo.dataTypeCode) );
    wf.write( (char *) &fileInfo.colorMapOrigin, sizeof(fileInfo.colorMapOrigin) );
    wf.write( (char *) &fileInfo.colorMapLength, sizeof(fileInfo.colorMapLength) );
    wf.write( (char *) &fileInfo.colorMapDepth, sizeof(fileInfo.colorMapDepth) );
    wf.write( (char *) &fileInfo.xOrigin, sizeof(fileInfo.xOrigin) );
    wf.write( (char *) &fileInfo.yOrigin, sizeof(fileInfo.yOrigin) );
    wf.write( (char *) &fileInfo.width, sizeof(fileInfo.width) );
    wf.write( (char *) &fileInfo.height, sizeof(fileInfo.height) );
    wf.write( (char *) &fileInfo.bitsPerPixel, sizeof(fileInfo.bitsPerPixel) );
    wf.write( (char *) &fileInfo.imageDescriptor, sizeof(fileInfo.imageDescriptor) );

    Pixel pixel;

    for (Pixel current: *this->pixelsData) {
        wf.write( (char *) &current.blue, sizeof(pixel.blue) );
        wf.write( (char *) &current.green, sizeof(pixel.green) );
        wf.write( (char *) &current.red, sizeof(pixel.red) );
    }

    // close file
    wf.close();
}

// set the header of the image
void Image::setHeader(Header newFileHeader) {
    this->fileInfo = newFileHeader;
}

// set the pixels data of the image
void Image::setPixelData(vector<Pixel> *data) {
    this->pixelsData = data;
}

// set the width of the image
void Image::setWidth(int value) {
    this->fileInfo.width = (short) value;
}

// set the height of the image
void Image::setHeight(int value) {
    this->fileInfo.height = (short) value;
}

// get the header of the image
Header Image::getHeader() {
    return this->fileInfo;
}

// get the pixels data of the image
vector<Pixel> *Image::getPixelData() {
    return this->pixelsData;
}

// get the width of the image
int Image::getWidth() {
    return (int) this->fileInfo.width;
}

// get the height of the image
int Image::getHeight() {
    return (int) this->fileInfo.height;
}

// apply multiply blending mode
Image *Image::multiply(Image *imageA, Image *imageB) {
    auto *newImage = new Image();
    auto *newImageData = new vector<Pixel>();

    // set header for new image
    newImage->setHeader(imageA->getHeader());

    // get pixel data of both images
    vector<Pixel> *pixelsDataA = imageA->getPixelData();
    vector<Pixel> *pixelsDataB = imageB->getPixelData();

    // Multiply each pixel of A to B
    for (int index = 0; index < pixelsDataA->size(); index++) {
        // get image A current pixel at index and image B pixel
        Pixel imageAPixel = pixelsDataA->at(index);
        Pixel imageBPixel = pixelsDataB->at(index);

        // Do calculations and round result
        int newBlueValue = (int) ( ((float) imageAPixel.blue / 255.0 * (float) imageBPixel.blue) + 0.5f);
        int newGreenValue = (int) ( ((float) imageAPixel.green / 255.0 * (float) imageBPixel.green) + 0.5f);
        int newRedValue = (int) ( ((float) imageAPixel.red / 255.0 * (float) imageBPixel.red) + 0.5f);

        // assign value to pixel object and add to new vector
        Pixel newImagePixel;
        newImagePixel.blue = (unsigned char) newBlueValue;
        newImagePixel.green = (unsigned char) newGreenValue;
        newImagePixel.red = (unsigned char) newRedValue;

        newImageData->push_back(newImagePixel);
    }

    // set new image data pixels to new image
    newImage->setPixelData(newImageData);

    // return new image
    return newImage;
}

// Apply subtract belnding mode
Image *Image::subtract(Image *imageA, Image *imageB) {
    auto *newImage = new Image();
    auto *newImageData = new vector<Pixel>();

    // set header for new image
    newImage->setHeader(imageA->getHeader());

    // get pixel data of both images
    vector<Pixel> *pixelsDataA = imageA->getPixelData();
    vector<Pixel> *pixelsDataB = imageB->getPixelData();

    // Subtract each pixel
    for (int index = 0; index < pixelsDataA->size(); index++) {
        // get image A current pixel at index and image B pixel
        Pixel imageAPixel = pixelsDataA->at(index);
        Pixel imageBPixel = pixelsDataB->at(index);

        int newBlueValue = (int) imageAPixel.blue - (int) imageBPixel.blue;
        int newGreenValue = (int) imageAPixel.green - (int) imageBPixel.green;
        int newRedValue = (int) imageAPixel.red - (int) imageBPixel.red;

        // assign value to pixel object and add to new vector
        Pixel newImagePixel;
        newImagePixel.blue = (char) clamp(newBlueValue, 0, 255);
        newImagePixel.green = (char) clamp(newGreenValue, 0, 255);
        newImagePixel.red = (char) clamp(newRedValue, 0, 255);

        newImageData->push_back(newImagePixel);
    }

    // set new image data pixels to new image
    newImage->setPixelData(newImageData);

    // return new image
    return newImage;
}

// Apply screen belnding mode
Image *Image::screen(Image *imageA, Image *imageB) {
    auto *newImage = new Image();
    auto *newImageData = new vector<Pixel>();

    // set header for new image
    newImage->setHeader(imageA->getHeader());

    // get pixel data of both images
    vector<Pixel> *pixelsDataA = imageA->getPixelData();
    vector<Pixel> *pixelsDataB = imageB->getPixelData();

    // Perform screen calculation on each pixel
    for (int index = 0; index < pixelsDataA->size(); index++) {
        // get image A current pixel at index and image B pixel
        Pixel imageAPixel = pixelsDataA->at(index);
        Pixel imageBPixel = pixelsDataB->at(index);

        int newBlueValue = (int) (((1.0f - ((1.0f - ((float) imageAPixel.blue) / 255.0f) * (1.0f - ((float) imageBPixel.blue / 255.0f)))) * 255.0f) + 0.5f);
        int newGreenValue = (int) (((1.0f - ((1.0f - ((float) imageAPixel.green) / 255.0f) * (1.0f - ((float) imageBPixel.green / 255.0f)))) * 255.0f) + 0.5f);
        int newRedValue = (int) (((1.0f - ((1.0f - ((float) imageAPixel.red) / 255.0f) * (1.0f - ((float) imageBPixel.red / 255.0f)))) * 255.0f) + 0.5f);

        // assign value to pixel object and add to new vector
        Pixel newImagePixel;
        newImagePixel.blue = (char) newBlueValue;
        newImagePixel.green = (char) newGreenValue;
        newImagePixel.red = (char) newRedValue;

        newImageData->push_back(newImagePixel);
    }

    // set new image data pixels to new image
    newImage->setPixelData(newImageData);

    // return new image
    return newImage;
}

// Apply overlay blending mode
Image *Image::overlay(Image *imageA, Image *imageB) {
    auto *newImage = new Image();
    auto *newImageData = new vector<Pixel>();

    // set header for new image
    newImage->setHeader(imageA->getHeader());

    // get pixel data of both images
    vector<Pixel> *pixelsDataA = imageA->getPixelData();
    vector<Pixel> *pixelsDataB = imageB->getPixelData();

    for (int index = 0; index < pixelsDataA->size(); index++) {
        // get image A current pixel at index and image B pixel
        Pixel imageAPixel = pixelsDataA->at(index);
        Pixel imageBPixel = pixelsDataB->at(index);

        int newBlueValue;
        int newGreenValue;
        int newRedValue;

        if ( ( (float) imageBPixel.blue / 255.0f) <= 0.5 & ( (float) imageBPixel.green / 255.0f) <= 0.5f & ( (float) imageBPixel.red / 255.0f) <= 0.5f)
        {
            newBlueValue = (int) ((2.0f * ((float) imageAPixel.blue / 255.0f) * ((float) imageBPixel.blue / 255.0f)) * 255.0f + 0.5f);
            newGreenValue = (int) ((2.0f * ((float) imageAPixel.green / 255.0f) * ((float) imageBPixel.green / 255.0f)) * 255.0f + 0.5f);
            newRedValue = (int) ((2.0f * ((float) imageAPixel.red / 255.0f) * ((float) imageBPixel.red / 255.0f)) * 255.0f + 0.5f);
        }
        else
        {
            newBlueValue = (int) ((1 - (2 * ((1.0f - ((float) imageAPixel.blue / 255.0f)) * (1.0f - ((float) imageBPixel.blue / 255.0f))))) * 255.0f + 0.5f);
            newGreenValue = (int) ((1 - (2 * ((1.0f - ((float) imageAPixel.green / 255.0f)) * (1.0f - ((float) imageBPixel.green / 255.0f))))) * 255.0f + 0.5f);
            newRedValue = (int) ((1 - (2 * ((1.0f - ((float) imageAPixel.red / 255.0f)) * (1.0f - ((float) imageBPixel.red / 255.0f))))) * 255.0f + 0.5f);
        }

        // assign value to pixel object and add to new vector
        Pixel newImagePixel;
        newImagePixel.blue = (char) newBlueValue;
        newImagePixel.green = (char) newGreenValue;
        newImagePixel.red = (char) newRedValue;

        // add pixel to vector
        newImageData->push_back(newImagePixel);
    }

    // set new image data pixels to new image
    newImage->setPixelData(newImageData);

    // return new image
    return newImage;
}

// Combine the channel of an image from 3 different files
Image *Image::combineChannel(Image *blueChannel, Image *greenChannel, Image *redChannel) {
    auto *newImage = new Image();
    auto *newImageData = new vector<Pixel>();

    // set header for new image
    newImage->setHeader(greenChannel->getHeader());

    // get pixel data of both images
    vector<Pixel> *pixelsDataBlue = blueChannel->getPixelData();
    vector<Pixel> *pixelsDataGreen = greenChannel->getPixelData();
    vector<Pixel> *pixelsDataRed = redChannel->getPixelData();

    Pixel newPixel;
    // Perform screen calculation on each pixel
    for (int index = 0; index < pixelsDataBlue->size(); index++) {
        newPixel.blue = pixelsDataBlue->at(index).blue;
        newPixel.green = pixelsDataGreen->at(index).green;
        newPixel.red = pixelsDataRed->at(index).red;

        // add new pixel to new Image data vector
        newImageData->push_back(newPixel);
    }

    // set new image data pixels to new image
    newImage->setPixelData(newImageData);

    // return new image
    return newImage;
}

// Combine 4 images into one image
Image *Image::combineImages(Image *image1, Image *image2, Image *image3, Image *image4) {
    auto *newImage = new Image();
    auto *newImageData = new vector<Pixel>();

    // set Header of file
    newImage->setHeader(image1->getHeader());

    // calculate the new width y new height
    int newWidth = image1->getWidth() * 2;
    int newHeight = image1->getHeight() * 2;

    // set new width y height in the header file
    newImage->setWidth(newWidth);
    newImage->setHeight(newHeight);

    // get the pixel data of each image to combine
    vector<Pixel> *topLeft = image1->getPixelData();
    vector<Pixel> *topRight = image2->getPixelData();
    vector<Pixel> *bottomLeft = image3->getPixelData();
    vector<Pixel> *bottomRight = image4->getPixelData();

    // create index to get data of each image
    int topLeftIndex = 0;
    int topRightIndex = 0;
    int bottomLeftIndex = 0;
    int bottomRightIndex = 0;

    // Loop for looping through column
    for (int j = 0; j < newHeight; j++) {
        // loop for looping through row
        for (int i = 0; i < newWidth; i++) {
            // Top Left
            if (i < (newWidth/2) && j < (newHeight/2)) {
                if (topLeftIndex == ((newWidth/2) * (newHeight/2))) topLeftIndex -=1;
                newImageData->push_back(topLeft->at(topLeftIndex));
                topLeftIndex++;
            }
            // Top Right
            else if ((i > (newWidth/2-1) && j < (newHeight/2-1)) && topRightIndex < ((newWidth/2) * (newHeight/2))) {
                newImageData->push_back(topRight->at(topRightIndex));
                topRightIndex++;
            }
            // Bottom Left
            else if ((i < newWidth/2 && j > newHeight/2) && bottomLeftIndex < ((newWidth/2) * (newHeight/2))) {
                newImageData->push_back(bottomLeft->at(bottomLeftIndex));
                bottomLeftIndex++;
            }
            // Bottom Right
            else {
                if (bottomRightIndex == ((newWidth/2) * (newHeight/2))) bottomRightIndex -=1;
                newImageData->push_back(bottomRight->at(bottomRightIndex));
                bottomRightIndex++;
            }
        }
    }

    // set new image data pixels to new image
    newImage->setPixelData(newImageData);

    // return new image
    return newImage;
}

// Add to the value of the green channel of the pixels
void Image::addToGreenChannel(int value) {
    for (auto & pixel : *this->pixelsData)
        pixel.green = (char) clamp((int) pixel.green + value, 0, 255);
}

// Scale the red values of the pixels
void Image::scaleRed(int value) {
    for (Pixel & pixel : *this->pixelsData){
        int newRedValue = pixel.red * value;
        pixel.red = (char) clamp( newRedValue, 0 , 255);
    }
}

// Scale the blue values of the pixels
void Image::scaleBlue(int value) {
    for (Pixel & pixel : *this->pixelsData){
        int newBlueValue = pixel.blue * value;
        pixel.blue = (char) clamp( newBlueValue, 0 , 255);
    }
}

// Write each channel of an image to a different file
void Image::writeChannelSeparately(string path, string filename) {
    string redOutputFilePath = path + filename + "_r.tga";
    string greenOutputFilePath = path + filename + "_g.tga";
    string blueOutputFilePath = path + filename + "_b.tga";

    unsigned char replacingChannel = 0;

    Pixel pixel;

    // Write red channel for file
    ofstream wf(redOutputFilePath, ios::out | ios::binary);
    if(!wf) {
        cout << "Cannot open file!" << endl;
    }

    // write the header of the file
    wf.write( (char *) &fileInfo.idLength, sizeof(fileInfo.idLength) );
    wf.write( (char *) &fileInfo.colorMapType, sizeof(fileInfo.colorMapType) );
    wf.write( (char *) &fileInfo.dataTypeCode, sizeof(fileInfo.dataTypeCode) );
    wf.write( (char *) &fileInfo.colorMapOrigin, sizeof(fileInfo.colorMapOrigin) );
    wf.write( (char *) &fileInfo.colorMapLength, sizeof(fileInfo.colorMapLength) );
    wf.write( (char *) &fileInfo.colorMapDepth, sizeof(fileInfo.colorMapDepth) );
    wf.write( (char *) &fileInfo.xOrigin, sizeof(fileInfo.xOrigin) );
    wf.write( (char *) &fileInfo.yOrigin, sizeof(fileInfo.yOrigin) );
    wf.write( (char *) &fileInfo.width, sizeof(fileInfo.width) );
    wf.write( (char *) &fileInfo.height, sizeof(fileInfo.height) );
    wf.write( (char *) &fileInfo.bitsPerPixel, sizeof(fileInfo.bitsPerPixel) );
    wf.write( (char *) &fileInfo.imageDescriptor, sizeof(fileInfo.imageDescriptor) );

    for (Pixel current: *this->pixelsData) {
        wf.write( (char *) &current.red, sizeof(pixel.red) );
        wf.write( (char *) &current.red, sizeof(pixel.green) );
        wf.write( (char *) &current.red, sizeof(pixel.blue) );
    }
    wf.close();

    // Write green channel for file
    wf.open(greenOutputFilePath, ios::out | ios::binary);
    if(!wf) {
        cout << "Cannot open file!" << endl;
    }

    // write the header of the file
    wf.write( (char *) &fileInfo.idLength, sizeof(fileInfo.idLength) );
    wf.write( (char *) &fileInfo.colorMapType, sizeof(fileInfo.colorMapType) );
    wf.write( (char *) &fileInfo.dataTypeCode, sizeof(fileInfo.dataTypeCode) );
    wf.write( (char *) &fileInfo.colorMapOrigin, sizeof(fileInfo.colorMapOrigin) );
    wf.write( (char *) &fileInfo.colorMapLength, sizeof(fileInfo.colorMapLength) );
    wf.write( (char *) &fileInfo.colorMapDepth, sizeof(fileInfo.colorMapDepth) );
    wf.write( (char *) &fileInfo.xOrigin, sizeof(fileInfo.xOrigin) );
    wf.write( (char *) &fileInfo.yOrigin, sizeof(fileInfo.yOrigin) );
    wf.write( (char *) &fileInfo.width, sizeof(fileInfo.width) );
    wf.write( (char *) &fileInfo.height, sizeof(fileInfo.height) );
    wf.write( (char *) &fileInfo.bitsPerPixel, sizeof(fileInfo.bitsPerPixel) );
    wf.write( (char *) &fileInfo.imageDescriptor, sizeof(fileInfo.imageDescriptor) );

    for (Pixel current: *this->pixelsData) {
        wf.write( (char *) &current.green, sizeof(pixel.red) );
        wf.write( (char *) &current.green, sizeof(pixel.green) );
        wf.write( (char *) &current.green, sizeof(pixel.blue) );
    }
    wf.close();

    // Write blue channel for file
    wf.open(blueOutputFilePath, ios::out | ios::binary);
    if(!wf) {
        cout << "Cannot open file!" << endl;
    }

    // write the header of the file
    wf.write( (char *) &fileInfo.idLength, sizeof(fileInfo.idLength) );
    wf.write( (char *) &fileInfo.colorMapType, sizeof(fileInfo.colorMapType) );
    wf.write( (char *) &fileInfo.dataTypeCode, sizeof(fileInfo.dataTypeCode) );
    wf.write( (char *) &fileInfo.colorMapOrigin, sizeof(fileInfo.colorMapOrigin) );
    wf.write( (char *) &fileInfo.colorMapLength, sizeof(fileInfo.colorMapLength) );
    wf.write( (char *) &fileInfo.colorMapDepth, sizeof(fileInfo.colorMapDepth) );
    wf.write( (char *) &fileInfo.xOrigin, sizeof(fileInfo.xOrigin) );
    wf.write( (char *) &fileInfo.yOrigin, sizeof(fileInfo.yOrigin) );
    wf.write( (char *) &fileInfo.width, sizeof(fileInfo.width) );
    wf.write( (char *) &fileInfo.height, sizeof(fileInfo.height) );
    wf.write( (char *) &fileInfo.bitsPerPixel, sizeof(fileInfo.bitsPerPixel) );
    wf.write( (char *) &fileInfo.imageDescriptor, sizeof(fileInfo.imageDescriptor) );

    for (Pixel current: *this->pixelsData) {
        wf.write( (char *) &current.blue, sizeof(pixel.red) );
        wf.write( (char *) &current.blue, sizeof(pixel.green) );
        wf.write( (char *) &current.blue, sizeof(pixel.blue) );
    }
    wf.close();
}

// Flip image veritcally
void Image::flipVertically() {
    vector<Pixel> *pixelsFlipped = new vector<Pixel>();

    for (int i = (int) this->pixelsData->size() - 1; i >= 0; i--) {
        pixelsFlipped->push_back(this->pixelsData->at(i));
    }

    // store pointer of previous data
    vector<Pixel> *previousPixels = this->pixelsData;

    // change the pixel data of this object to the flipped one
    this->pixelsData = pixelsFlipped;

    // delete the previous pixels data
    delete previousPixels;
}
