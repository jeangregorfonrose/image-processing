//
// Created by jeang on 11/13/2021.
//
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Header
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

class Image
{
private:
    Header fileInfo{};
    vector<Pixel> *pixelsData{};

public:
    Image();
    ~Image();
    // Read the file provided to get data for Image
    void readFile(const string& filePath, const string& fileName);

    // Write data of image class to file
    void writeFile(const string& path, const string& filename);

    // setters
    void setHeader(Header newHeader);
    void setPixelData(vector<Pixel> *data);
    void setWidth(int value);
    void setHeight(int value);

    //getters
    Header getHeader();
    vector<Pixel> *getPixelData();
    int getWidth();
    int getHeight();

    // Blending modes functions
    // Those are static methods
    static Image *multiply(Image *imageA, Image *imageB);
    static Image *subtract(Image *imageA, Image *imageB);
    static Image *screen(Image *imageA, Image *imageB);
    static Image *overlay(Image *imageA, Image *imageB);
    static Image *combineChannel(Image *blueChannel, Image *greenChannel, Image *redChannel);
    static Image *combineImages(Image *image1, Image *image2, Image *image3, Image *image4);

    // Other functions
    void addToGreenChannel(int value);
    void scaleRed(int value);
    void scaleBlue(int value);
    void writeChannelSeparately(string path, string filename);
    void flipVertically();
};