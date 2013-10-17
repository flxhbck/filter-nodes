PImage img;
PImage imgEnhanced;

void setup() 
{
  //make this big enough so you can see all of your image
  size(600, 600);

  //put a test.jpg image in a folder called data inside the sketch folder
  img = loadImage("test.jpg");
  imgEnhanced = new PImage(img.width, img.height);
}



void draw() 

{

  background(0);
  
  //contrast - this probably doesn't need to be bigger than 5 or 10
  float contrast = 0.6f * ( mouseX / (float)width); //value should go from 0 to 5
  contrast += 0.8;
  println("contrast: " + contrast);



  //brightness - this is additive and we want to make it both brigher and darker so -128 to +128
  float bright = 255 * ( mouseY / (float)width  - 0.5); //value should go from -128 to +128
  bright = 0;
  println("contrast: " + contrast);

  //call out contrast and brightness function
  ContrastAndBrightness(img, imgEnhanced, contrast, bright); 

  //display the image
  image(imgEnhanced, 0, 0);
}

//image processing function to enhance contrast
//this doesn't make sense without also adjusting the brightness at the same time
void ContrastAndBrightness(PImage input, PImage output, float cont, float bright)
{
  int w = input.width;
  int h = input.height;

  //our assumption is the image sizes are the same
  //so test this here and if it's not true just return with a warning

  if (w != output.width || h != output.height)
  {
    println("error: image dimensions must agree");
    return;
  }

  //this is required before manipulating the image pixels directly
  input.loadPixels();
  output.loadPixels();

  //loop through all pixels in the image
  for (int i = 0; i < w*h; i++)
  {  
    //get color values from the current pixel (which are stored as a list of type 'color')
    color inColor = input.pixels[i];

    //slow version for illustration purposes - calling a function inside this loop
    //is a big no no, it will be very slow, plust we need an extra cast
    //as this loop is being called w * h times, that can be a million times or more!
    //so comment this version and use the one below

    int r = (int) red(input.pixels[i]);
    int g = (int) green(input.pixels[i]);
    int b = (int) blue(input.pixels[i]);



    //here the much faster version (uses bit-shifting) - uncomment to try
    //int r = (inColor >> 16) & 0xFF; //like calling the function red(), but faster
    //int g = (inColor >> 8) & 0xFF;
    //int b = inColor & 0xFF;      

    //apply contrast (multiplcation) and brightness (addition)
    r = (int)(r * cont + bright); //floating point aritmetic so convert back to int with a cast (i.e. '(int)');
    g = (int)(g * cont + bright);
    b = (int)(b * cont + bright);

    //slow but absolutely essential - check that we don't overflow (i.e. r,g and b must be in the range of 0 to 255)
    //to explain: this nest two statements, sperately it would be r = r < 0 ? 0 : r; and r = r > 255 ? 255 : 0;
    //you can also do this with if statements and it would do the same just take up more space
    r = r < 0 ? 0 : r > 255 ? 255 : r;
    g = g < 0 ? 0 : g > 255 ? 255 : g;
    b = b < 0 ? 0 : b > 255 ? 255 : b;

    //and again in reverse for illustration - calling the color function is slow so use the bit-shifting version below
    output.pixels[i] = color(r, g, b);

    //output.pixels[i]= 0xff000000 | (r << 16) | (g << 8) | b; //this does the same but faster
  }

  //so that we can display the new image we must call this for each image
  input.updatePixels();
  output.updatePixels();
}

