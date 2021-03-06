#include "Renderer.h"
#include <iostream>
#include <cstdio>
#include <fstream>

Renderer::Renderer(int width, int height, int rtype, bool antialias, int s_index, double gamma): 
width(width), height(height), rtype(rtype), antialias(antialias), gamma(gamma)
{
    //Type is:
    // 0 for black and white
    // 1 for grayscale
    // 2 for color
    if (!antialias){
        sample_index = 1;
    } else {
        sample_index = s_index;
    }
    rowlen = width * sample_index;
    pixels = new Color[width*height*sample_index*sample_index];
    top = 1;
}

void Renderer::set_pixel(int x, int y, Color c){
    int dex = y * rowlen + x;
    //implement clamping

    if (c.r > top){
        c.r = top;
    } else if (c.g > top) {
        c.g = top;
    } else if (c.b > top) {
        c.b = top;
    }
    pixels[dex] = c;
}

Color Renderer::get_pixel(int x, int y){
    int dex = y * rowlen + x;
    return pixels[dex];
}
void Renderer::render_text(){
    for (int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            Color text_color = get_pixel(i, j);
            std::cout << text_color.to_text() << " ";
        }
        std::cout << std::endl;
    }
//    std::printf("done\n");
}
void Renderer::render_ppm(const char *filename){
    std::cout << top << std::endl;
    std::ofstream myfile;
    myfile.open (filename);
    myfile << "P3\n";
    myfile << width;
    myfile << " ";
    myfile << height;
    myfile << "\n255\n";
    for (int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            Color pcolor;
            
            if (antialias){
                Color sum;
                for (int si=0;si<sample_index;si++){
                    for(int sj=0; sj<sample_index;sj++){
                        //dex = sample^2 * width * y + sj * width * sample + x * sample + si
                        int dex = sample_index * sample_index * j * width + sj * width * sample_index + i * sample_index + si;
                        Color sample = pixels[dex];
                        sum = Color(sample.r + sum.r, sample.g + sum.g, sample.b + sum.b);
                    }
                }
                double ssquared = sample_index * sample_index * 1.0;
                pcolor = Color(sum.r / ssquared, sum.g / ssquared, sum.b / ssquared);
            } else {
                pcolor = get_pixel(i, j);
            }

            //check if min = max = 0 DONT DIVIDE BY 0
            if (top == 0){
                myfile << "0 0 0";
            } else {
                myfile << pcolor.to_ppm(top, 255, gamma) << " ";
            }
        }
        myfile << "\n";
    }
    myfile.close();
    
    std::cout << "Rendered to file " << filename << std::endl;
}
int Renderer::getHeight(){
    return height * sample_index;
}
int Renderer::getWidth(){
    return width * sample_index;
}

Renderer::~Renderer()
{
    //delete[] pixels;
}