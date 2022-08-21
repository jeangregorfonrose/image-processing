#include <iostream>
#include <string>
#include <assert.h>
#include "src/Image.h"

using namespace std;

// Functions Definitions
void verifyOutput(Image *imageOutput, Image *expectedImage);

int main() {
    // Path on my computer
//    string inputFilePath = "../input/";
//    string outputFilePath = "../output/";
//    string exampleFilesPath = "../examples/";
    string inputFilePath = "input/";
    string outputFilePath = "output/";
    string exampleFilesPath = "examples/";
    string inputFileName;
    string outputFileName;

    Image *image1 = new Image();
    Image *image2 = new Image();
    Image *image3 = new Image();
    Image *image4 = new Image();
    Image *expectedImage = new Image();
    Image *temporary = nullptr;
    Image *resultImage = nullptr;

    // Part 1) Use the multiply blending mode to combine layer1.tga with pattern1.tga
    cout << "Executing part 1 : Use the multiply blending mode to combine layer1.tga with pattern1.tga" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file layer1.tga . . ." << endl;
        // load layer1.tga in image1
        inputFileName = "layer1.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Reading file pattern1.tga . . ." << endl;
        // load pattern1.tga in image2
        inputFileName = "pattern1.tga";
        image2->readFile(inputFilePath, inputFileName);

        cout << "multiplying file layer1.tga with pattern1.tga . . ." << endl;
        // multiply the two images and set the result vectors to the result
        resultImage = Image::multiply(image2, image1);

        cout << "writing result image in file named part1.tga . . ." << endl;
        // write result image to new file named part1.tga
        outputFileName = "part1.tga";
        resultImage->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part1.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(resultImage,expectedImage); // verify results


    // free result image for new data
    delete resultImage;

    // Part 2) Use subtract blending mode to combine layer2.tga (top layer) with car.tga (bottom layer).
    cout << "Executing part 2 : Use subtract blending mode to combine layer2.tga (top layer) with car.tga (bottom layer)" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file layer2.tga . . ." << endl;
        // load layer2.tga in image1
        inputFileName = "layer2.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Reading file car.tga . . ." << endl;
        // load car.tga in image2
        inputFileName = "car.tga";
        image2->readFile(inputFilePath, inputFileName);

        cout << "Subtracting file layer2.tga with car.tga . . ." << endl;
        // subtract the two images and set the result vectors to the result
        resultImage = Image::subtract(image2, image1);

        cout << "Writing result image in file named part2.tga . . ." << endl;
        // write result image to new file named part2.tga
        outputFileName = "part2.tga";
        resultImage->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part2.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(resultImage,expectedImage); // verify results

    // free result image for new data
    delete resultImage;



    // Part 3) Use the Multiply blending mode to combine layer1.tga with pattern2.tga, and store the
    // results temporarily. Load the image “text.tga” and, using that as the top layer, combine it with
    // the previous results of layer1/pattern2 using the Screen blending mode.
    cout << "Executing part 3 : Use the Multiply blending mode to combine “layer1.tga” with “pattern2.tga”, and store the \n"
            "results temporarily. Load the image “text.tga” and, using that as the top layer, combine it with \n"
            "the previous results of layer1/pattern2 using the Screen blending mode. " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file layer1.tga . . ." << endl;
        // load layer1.tga in image1
        inputFileName = "layer1.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Reading file pattern2.tga . . ." << endl;
        // load pattern2.tga in image2
        inputFileName = "pattern2.tga";
        image2->readFile(inputFilePath, inputFileName);

        cout << "Multiply file layer1.tga with pattern2.tga . . ." << endl;
        // subtract the two images and set the result vectors to the result
        temporary = Image::multiply(image1,image2);

        cout << "Reading file text.tga . . ." << endl;
        // load text.tga in image1
        inputFileName = "text.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Combining file text.tga with the previous result of multiplying layer1.tga with pattern2.tga using screen blending mode . . ." << endl;
        // Combine the two images and set the result vectors to the result
        //resultImage.setPixelData(temporary.screen(image1.getPixelData()));
        resultImage = Image::screen(temporary, image1);

        cout << "Writing result image in file named part2.tga . . ." << endl;
        // write result image to new file named part2.tga
        outputFileName = "part3.tga";
        resultImage->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part3.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(resultImage,expectedImage); // verify results

    // free result image and temporary image for new data
    delete resultImage;
    delete temporary;


    // Part 4) Multiply “layer2.tga” with “circles.tga”, and store it. Load pattern2.tga and, using that as the
    // top layer, combine it with the previous result using the Subtract blending mode.
    cout << "Executing part 4 : Multiply layer2.tga with circles.tga, and store it. Load pattern2.tga and, using that as the "
            "top layer, combine it with the previous result using the Subtract blending mode.  " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file layer2.tga . . ." << endl;
        // load layer2.tga in image1
        inputFileName = "layer2.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Reading file circles.tga . . ." << endl;
        // load circles.tga in image2
        inputFileName = "circles.tga";
        image2->readFile(inputFilePath, inputFileName);

        cout << "Multiply file layer2.tga with circles.tga . . ." << endl;
        // Multiply the two images and set the result vectors to the result
        temporary = Image::multiply(image1,image2);

        cout << "Reading file pattern2.tga . . ." << endl;
        // load pattern2.tga in image1
        inputFileName = "pattern2.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Subtract file pattern2.tga with the previous result of multiplying layer2.tga with circles.tga . . ." << endl;
        // Combine the two images and set the result vectors to the result
        resultImage = Image::subtract(temporary,image1);

        cout << "Writing result image in file named part4.tga . . ." << endl;
        // write result image to new file named part4.tga
        outputFileName = "part4.tga";
        resultImage->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part4.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(resultImage,expectedImage); // verify results

    // free result image for new data
    delete resultImage;

    // Part 5) Combine “layer1.tga” (as the top layer) with “pattern1.tga” using the Overlay blending mode.
    cout << "Executing part 5 : Combine layer1.tga (as the top layer) with pattern1.tga using the Overlay blending mode. " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file layer1.tga . . ." << endl;
        // load layer1.tga in image1
        inputFileName = "layer1.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Reading file pattern1.tga . . ." << endl;
        // load pattern1.tga in image2
        inputFileName = "pattern1.tga";
        image2->readFile(inputFilePath, inputFileName);

        cout << "Combining the file layer1.tga with pattern1.tga using overlay blending mode . . ." << endl;
        // Combine the two images and set the result vectors to the result
        resultImage = Image::overlay(image1,image2);

        cout << "Writing result image in file named part5.tga . . ." << endl;
        // write result image to new file named part5.tga
        outputFileName = "part5.tga";
        resultImage->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part5.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(resultImage,expectedImage); // verify results

    // free result image for new data
    //delete resultImage;


    // Part 6) Load “car.tga” and add 200 to the green channel.
    cout << "Executing part 6: Load car.tga and add 200 to the green channel." << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file car.tga . . ." << endl;
        // load car.tga in image1
        inputFileName = "car.tga";
        image1->readFile(inputFilePath, inputFileName);

        // add 200 to blue channel
        image1->addToGreenChannel(200);

        cout << "Writing result image in file named part6.tga . . ." << endl;
        // write result image to new file named part6.tga
        outputFileName = "part6.tga";
        image1->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part6.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(image1,expectedImage); // verify results


    // Part 7) Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0. This will
    // increase the intensity of any red in the image, while negating any blue it may have.
    cout << "Executing part 7: Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0. This will \n"
            "increase the intensity of any red in the image, while negating any blue it may have. " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file car.tga . . ." << endl;
        // load car.tga in image2
        inputFileName = "car.tga";
        image2->readFile(inputFilePath, inputFileName);

        // scale red channel by 4
        image2->scaleRed(4);
        // scale blue channel by 0
        image2->scaleBlue(0);

        cout << "Writing result image in file named part7.tga . . ." << endl;
        // write result image to new file named part7.tga
        outputFileName = "part7.tga";
        image2->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part7.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(image2,expectedImage); // verify results


    // Part 8) Load car.tga and write each channel to a separate file: the red channel should be
    // part8_r.tga, the green channel should be part8_g.tga, and the blue channel should be
    // part8_b.tga
    cout << "Executing part 8: Load car.tga and write each channel to a separate file." << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file car.tga . . ." << endl;
        // load car.tga in image1
        inputFileName = "car.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Writing result image in file named part8.tga . . ." << endl;
        // write result image to new file named part8.tga
        outputFileName = "part8";
        image1->writeChannelSeparately(outputFilePath, outputFileName);

        // verify results for blue channel
        inputFileName = "EXAMPLE_part8_b.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        // load result image
        image1->readFile(outputFilePath, "part8_b.tga");
        verifyOutput(image1,expectedImage); // verify results

        // verify results for green channel
        inputFileName = "EXAMPLE_part8_g.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        // load result image
        image2->readFile(outputFilePath, "part8_g.tga");
        verifyOutput(image2,expectedImage); // verify results

        // verify results for red channel
        inputFileName = "EXAMPLE_part8_r.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        // load result image
        image3->readFile(outputFilePath, "part8_r.tga");
        verifyOutput(image3,expectedImage); // verify results



    // Part 9) Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”, and combine the three files into
    //one file. The data from “layer_red.tga” is the red channel of the new image, layer_green is
    //green, and layer_blue is blue.
    cout << "Executing part 9: Load layer_red.tga, layer_green.tga and layer_blue.tga, and combine the three files into \n"
            "one file. The data from layer_red.tga is the red channel of the new image, layer_green is \n"
            "green, and layer_blue is blue. " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file layer_red.tga . . ." << endl;
        // load layer_red.tga in image1
        inputFileName = "layer_red.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Reading file layer_green.tga . . ." << endl;
        // load layer_green.tga in image2
        inputFileName = "layer_green.tga";
        image2->readFile(inputFilePath, inputFileName);

        cout << "Reading file layer_blue.tga . . ." << endl;
        // load layer_blue.tga in image3
        inputFileName = "layer_blue.tga";
        image3->readFile(inputFilePath, inputFileName);

        cout << "Combining file layer_red.tga, layer_green.tga, layer_blue.tga . . ." << endl;
        // Combine each channel image
        resultImage = Image::combineChannel(image3,image2,image1);

        cout << "Writing result image in file named part9.tga . . ." << endl;
        // write result image to new file named part9.tga
        outputFileName = "part9.tga";
        resultImage->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part9.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(resultImage,expectedImage); // verify results


    // Part 10) Load “text2.tga”, and rotate it 180 degrees, flipping it upside down.
    cout << "Executing part 10: Load text2.tga, and rotate it 180 degrees, flipping it upside down. " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file text2.tga . . ." << endl;
        // load text2.tga in image1
        inputFileName = "text2.tga";
        image1->readFile(inputFilePath, inputFileName);

        // Rotate image
        image1->flipVertically();

        cout << "Writing result image in file named part10.tga . . ." << endl;
        // write result image to new file named part10.tga
        outputFileName = "part10.tga";
        image1->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_part10.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(image1,expectedImage); // verify results



    // Part Extra Credit) Create a new file that is the combination of car.tga, circles.tga, pattern1.tga, and text.tga.
    // Each source image will be in a quadrant of the final image.
    cout << "Create a new file that is the combination of car.tga, circles.tga, pattern1.tga, and text.tga. Each \n"
            "source image will be in a quadrant of the final image." << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "Reading file car.tga . . ." << endl;
        // load car.tga in image1
        inputFileName = "car.tga";
        image1->readFile(inputFilePath, inputFileName);

        cout << "Reading file circles.tga . . ." << endl;
        // load circles.tga in image2
        inputFileName = "circles.tga";
        image2->readFile(inputFilePath, inputFileName);

        cout << "Reading file text.tga . . ." << endl;
        // load text.tga in image3
        inputFileName = "text.tga";
        image3->readFile(inputFilePath, inputFileName);

        cout << "Reading file pattern1.tga . . ." << endl;
        // load pattern1.tga in image4
        inputFileName = "pattern1.tga";
        image4->readFile(inputFilePath, inputFileName);

        // Combine all four images together
        resultImage = Image::combineImages(image3, image4, image1, image2);

        cout << "Writing result image in file named extracredit.tga . . ." << endl;
        // write result image to new file named part10.tga
        outputFileName = "extracredit.tga";
        resultImage->writeFile(outputFilePath, outputFileName);

        // verify results
        inputFileName = "EXAMPLE_extracredit.tga";
        expectedImage->readFile(exampleFilesPath,inputFileName); // load expected image
        verifyOutput(resultImage,expectedImage); // verify results


    // delete all pointers created with the new
    delete image1;
    delete image2;
    delete image3;
    delete temporary;
    delete resultImage;

    return 0;
}

void verifyOutput(Image *imageOutput, Image *expectedImage){

    // verify header data of both image
    Header headerImageOutput = imageOutput->getHeader();
    Header headerExpectedImage = expectedImage->getHeader();

    assert(headerImageOutput.idLength == headerExpectedImage.idLength);
    assert(headerImageOutput.colorMapType == headerExpectedImage.colorMapType);
    assert(headerImageOutput.dataTypeCode == headerExpectedImage.dataTypeCode);
    assert(headerImageOutput.colorMapOrigin == headerExpectedImage.colorMapOrigin);
    assert(headerImageOutput.colorMapLength == headerExpectedImage.colorMapLength);
    assert(headerImageOutput.colorMapDepth == headerExpectedImage.colorMapDepth);
    assert(headerImageOutput.xOrigin == headerExpectedImage.xOrigin);
    assert(headerImageOutput.yOrigin == headerExpectedImage.yOrigin);
    assert(headerImageOutput.width == headerExpectedImage.width);
    assert(headerImageOutput.height == headerExpectedImage.height);
    assert(headerImageOutput.bitsPerPixel == headerExpectedImage.bitsPerPixel);
    assert(headerImageOutput.imageDescriptor == headerExpectedImage.imageDescriptor);


    // verify pixel data of image
    vector<Pixel> *imageOutputPixels = imageOutput->getPixelData();
    vector<Pixel> *expectedImagePixels = expectedImage->getPixelData();

    for (int index = 0; index < expectedImagePixels->size(); index++)
    {
        assert(imageOutputPixels->at(index).blue == expectedImagePixels->at(index).blue);
        assert(imageOutputPixels->at(index).green == expectedImagePixels->at(index).green);
        assert(imageOutputPixels->at(index).red == expectedImagePixels->at(index).red);
    }

    cout << "Test successful !!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n\n" << endl;
}