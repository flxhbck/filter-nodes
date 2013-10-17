import com.jhlabs.vecmath.*;
import com.jhlabs.image.*;
import com.jhlabs.composite.*;
import com.jhlabs.math.*;

import java.awt.image.BufferedImage;

import processing.serial.*;

PImage img, edited_img;
BufferedImage bufferImageSrc, bufferImageTemp ;
RGBAdjustFilter rgbSaturation;
ContrastFilter contrastFilter;
float imgScale = 1;
float imgScaleTemp = 1;

void setup() {
  img = loadImage("test.jpg");
  size(img.width, img.height);
  imageMode(CENTER);
  
  bufferImageSrc = (BufferedImage) img.getImage();  
  
  contrastFilter = new ContrastFilter();
  
  rgbSaturation = new RGBAdjustFilter(0,0,0);
  bufferImageTemp = rgbSaturation.filter(bufferImageSrc, null);
  
  edited_img = new PImage(bufferImageTemp);
}

public void draw() {
  background(0);  
  
  
  bufferImageTemp = bufferImageSrc;
  
  float cont = (float(mouseY) / float(img.height) ) + 0.5;
  applyContrast(cont);
  
  float rSat = ( float(mouseX) / float(img.width))*2 - 1;
  applyRGBSaturation(rSat, 0,0);
  
  
  
  imgScaleTemp = imgScaleTemp + ((imgScale - imgScaleTemp)*4/frameRate);
  
  if ( abs(imgScale - imgScaleTemp) < 0.005 ){
    imgScaleTemp = imgScale;
  }
    
  if ( mousePressed ) {
    image(img, img.width/2, img.height/2);
  } 
  else {
    image(edited_img, img.width/2, img.height/2 , img.width*imgScaleTemp, img.height*imgScaleTemp);
  }
}


void applyRGBSaturation(float rSat, float gSat, float bSat){
  rgbSaturation.setRFactor(rSat);
  rgbSaturation.setGFactor(gSat);
  rgbSaturation.setBFactor(bSat);
  
  bufferImageTemp = rgbSaturation.filter(bufferImageTemp, null);
  edited_img = new PImage(bufferImageTemp);
}


void applyContrast(float fContrast){
  contrastFilter.setContrast(fContrast);
  
  bufferImageTemp = contrastFilter.filter(bufferImageTemp, null);
  edited_img = new PImage(bufferImageTemp);
}



void keyPressed() {
  if (key == CODED) {
    if (keyCode == UP) {
      imgScale *= 1.3f;
      println(imgScale);
    } else if (keyCode == DOWN){
      imgScale /= 1.3f;
      println(imgScale);
    }
  }
}






