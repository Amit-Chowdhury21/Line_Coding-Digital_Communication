#include "L138_LCDK_aic3106_init.h" //header file for
#include <stdio.h>
#include <math.h>

#define LOOPLENGTH 64

int16_t sample;
int output[3];
int k;
int level = 8;

int16_t DecisionLevels[8] = {-32767,-23405,-14043,-4681,4681,14043,23405,32767} ;

int16_t DummyV;
int16_t diff[100];

int16_t minDiff = 32767;
int captureIndex;



int16_t square_table1[LOOPLENGTH] =
{10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,
10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,
10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,
10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,
//-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
//-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
//-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
//-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000};
10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,
10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,
10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000,
10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000};




int16_t square_table2[LOOPLENGTH] =
{-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
 -10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
 -10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
 -10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
 -10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
 -10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
 -10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,
 -10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000};
 //0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
 //0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
 //0000, 0000,0000, 0000, 0000, 0000, 0000, 0000,
 //0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000};






int16_t loopindex = 0;



interrupt void interrupt4(void)  // interrupt service routine
{

  //uint32_t sample;  //16bit input variable
  //sample = input_sample();  // read L + R samples from ADC



  //output_sample(sample);   // write L + R samples to DAC

  sample = input_left_sample();     // 16bit input,output


  for(k=0; k < level; k++)
  {
     DummyV= DecisionLevels[k] - sample;
     diff[k]= abs(DummyV);  // TO MAKE ALL DISTANCE POSITIVE

              //printf("%f\n",diff[k]);
  }


  for(k=0; k< level; k++)
  {
      if(diff[k] <= minDiff)
      {
         minDiff = diff[k];
         captureIndex = k;
      }
  }


  switch(captureIndex)         // (quantized[n] = DecisionLevels[0)
  {
     case 0:
     output[0] = 0;          // for 3 bits = 8 levels
     output[1] = 0;
     output[2] = 0;
     break;

     case 1:
     output[0] = 0;
     output[1] = 0;
     output[2] = 10000;
     break;

     case 2:
     output[0] = 0;
     output[1] = 10000;
     output[2] = 0;
     break;

     case 3:
     output[0] = 0;
     output[1] = 10000;
     output[2] = 10000;
     break;

     case 4:
     output[0] = 10000;
     output[1] = 0;
     output[2] = 0;
     break;

     case 5:
     output[0] = 10000;
     output[1] = 0;
     output[2] = 10000;
     break;

     case 6:
     output[0] = 10000;
     output[1] = 10000;
     output[2] = 0;
     break;

     case 7:
     output[0] = 10000;
     output[1] = 10000;
     output[2] = 10000;
     break;

   }

  //output_left_sample(output[0]);
  //output_left_sample(output[0]);
  //output_left_sample(output[0]);
  //output_left_sample(output[0]);
  //output_left_sample(output[0]);
  //output_left_sample(output[0]);
  //output_left_sample(output[0]);
  //output_left_sample(output[0]);
  //output_left_sample(output[1]);
  //output_left_sample(output[1]);
  //output_left_sample(output[1]);
 // output_left_sample(output[1]);
  //output_left_sample(output[1]);
  //output_left_sample(output[1]);
  //output_left_sample(output[1]);
  //output_left_sample(output[1]);
  //output_left_sample(output[2]);
  //output_left_sample(output[2]);
  //output_left_sample(output[2]);
  //output_left_sample(output[2]);
  //output_left_sample(output[2]);
  //output_left_sample(output[2]);
  //output_left_sample(output[2]);
  //output_left_sample(output[2]);

  if (output[1] == 0)
  {
      output_left_sample(square_table2[loopindex++]);
      if (loopindex >= LOOPLENGTH)
      {
          loopindex = 0;
      }
  }

  else if (output[1] == 10000)
  {
      output_left_sample(square_table1[loopindex++]);
      if (loopindex >= LOOPLENGTH)
      {
          loopindex = 0;
      }
  }
  //output_sample(output[0]);   // write L + R samples to DAC
  //output_sample(output[1]);
  //output_sample(output[2]);



  return;

}

int main(void)
{

       L138_initialise_intr(FS_12000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
  while(1);

}