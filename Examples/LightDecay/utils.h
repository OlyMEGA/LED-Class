#define numLEDs 16

#define RIGHT 0
#define LEFT 1

#define primaryDecayAmount 0
#define secondaryDecayAmount 1
#define decayFactor .6f
#define addInterval 50

#define FRAME_DELAY ( (1.0 / 20.0) * 1000.0 )

struct Color {
 float red;
 float green;
 float blue;  
};

#define CZERO (Color){0,0,0}

Color makeColor(float r, float g, float b) { return (Color){constrain(r, 0, 127), constrain(g, 0, 127), constrain(b, 0, 127)}; }

Color   addRed(Color theColor, float redValue)   { return makeColor(theColor.red+redValue, theColor.green,            theColor.blue); }
Color addGreen(Color theColor, float greenValue) { return makeColor(theColor.red,          theColor.green+greenValue, theColor.blue); }
Color  addBlue(Color theColor, float blueValue)  { return makeColor(theColor.red,          theColor.green,            theColor.blue+blueValue); }

bool operator==(const Color &a, const Color &b) { return ( (a.red == b.red) && (a.green == b.green) && (a.blue == b.blue) ); }
bool operator!=(const Color &a, const Color &b) { return ( (a.red != b.red) || (a.green != b.green) || (a.blue != b.blue) ); }

Color operator+(const Color a, const float b) { return makeColor(a.red+b, a.green+b, a.blue+b); }
Color operator-(const Color a, const float b) { return makeColor(a.red-b, a.green-b, a.blue-b); }
Color operator*(const Color a, const float b) { return makeColor(a.red*b, a.green*b, a.blue*b); }
Color operator/(const Color a, const float b) { return makeColor(a.red/b, a.green/b, a.blue/b); }

Color operator+(const Color a, const Color b) { return makeColor(a.red+b.red, a.green+b.green, a.blue+b.blue); }
Color operator-(const Color a, const Color b) { return makeColor(a.red-b.red, a.green-b.green, a.blue-b.blue); }
Color operator*(const Color a, const Color b) { return makeColor(a.red*b.red, a.green*b.green, a.blue*b.blue); }
Color operator/(const Color a, const Color b) { return makeColor(a.red/b.red, a.green/b.green, a.blue/b.blue); }

Color averageColor(const Color a, const Color b) { return ( (a+b) / 2.0f ); }
  
typedef struct {
  Color color;
} LightEntity;



void HSVtoRGB(unsigned int *r, unsigned int *g, unsigned int *b, unsigned int h, unsigned int s, unsigned int v)
{
        int f;
        long p, q, t;
        if( s == 0 )
        {
                *r = *g = *b = v;
                return;
        }
 
        f = ((h%60)*255)/60;
        
        s = min(s,255);
        v = min(v,255);
        
        h %= 360;
        h /= 60;
        
        // In this section all the 255s used to be 256, which I think is an error.
       p = (v * (255 - s))/255;
       q = (v * (255 - (s * f)/255 ))/255;
       t = (v * (255- (s * ( 255 -f ))/255))/255;
 
        switch( h ) {
                case 0:
                        *r = v;
                        *g = t;
                        *b = p;
                        break;
                case 1:
                        *r = q;
                        *g = v;
                        *b = p;
                        break;
                case 2:
                        *r = p;
                        *g = v;
                        *b = t;
                        break;
                case 3:
                        *r = p;
                        *g = q;
                        *b = v;
                        break;
                case 4:
                        *r = t;
                        *g = p;
                        *b = v;
                        break;
                default:
                        *r = v;
                        *g = p;
                        *b = q;
                        break;
        }
        // *r = sqrt(*r)*16;
        *r *=16;
        *r +=15;
        *g = ((((*g)*(*g))/255)*(*g))/255; 
        *g *=16;
        *b = (((((*b)*(*b))/255)*(*b))/255); 
        *b *=16;
}

