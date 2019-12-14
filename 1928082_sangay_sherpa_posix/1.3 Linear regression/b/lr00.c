#include <stdio.h>

/******************************************************************************
 * This is the first program in a series on linear regression. The purpose of
 * this program is to enable the understanding of how the data to be processed 
 * is stored and how to access it. The program simply writes the comma delimited
 * data points to stdout. In order to understand what the data looks like it 
 * should be redirected into a text file and plotted using a scatter graph in 
 * a spreadsheet. You should analyse the graph and estimate the slope (m) and 
 * intercept (c) of the optimum regression line.
 * 
 * To compile:
 *   cc -o lr00 lr00.c
 * 
 * To run and direct the output into a file:
 *   ./lr00 > lr00_results.csv
 * 
 * To load results into a spreadsheet:
 *   libreoffice lr00_results.csv
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/

typedef struct point_t {
  double x;
  double y;
} point_t;

int n_data = 1000;

point_t data[];

void print_data() {
  int i;
  for(i=0; i<n_data; i++) {
    printf("%0.2lf,%0.2lf\n", data[i].x, data[i].y);
  }
}

int main() {
  print_data();
  return 0;
}

point_t data[] =  {
  {82.84,131.77},{79.77,115.50},{66.33,106.77},{83.91,114.78},
  {79.52,128.79},{78.99,114.43},{76.47,133.93},{65.89,107.63},
  {87.76,139.69},{83.50,145.47},{79.21,140.09},{78.13,116.96},
  { 5.65,41.87},{65.75,113.96},{ 5.37,28.57},{ 7.19, 7.21},
  {49.67,75.70},{95.98,156.10},{28.88,74.90},{96.28,163.11},
  {62.62,105.37},{10.33,37.78},{55.89,105.08},{92.38,142.46},
  {59.82,107.46},{32.76,64.63},{85.83,115.65},{85.09,125.33},
  {74.27,118.27},{61.10,103.34},{91.78,159.68},{ 4.48,15.88},
  {32.13,61.43},{25.85,48.19},{57.36,106.37},{77.57,140.32},
  {73.94,111.47},{16.13,39.67},{57.11,81.44},{10.26,44.77},
  {89.81,122.04},{54.75,83.15},{43.19,84.66},{49.32,83.37},
  {42.91,73.34},{10.91,38.62},{95.01,143.00},{75.84,122.17},
  {51.63,93.74},{91.19,131.96},{39.31,63.67},{92.97,147.54},
  { 0.72,30.38},{18.81,40.69},{79.87,135.19},{ 2.51,26.48},
  {61.00,97.60},{53.16,76.71},{66.45,106.76},{51.71,85.09},
  {64.67,106.44},{73.65,111.98},{50.33,82.13},{59.77,100.26},
  {95.68,138.45},{53.62,84.38},{ 4.24,32.23},{31.03,57.21},
  {83.61,124.00},{69.96,92.26},{ 4.48,45.87},{36.39,87.43},
  {79.05,113.28},{65.55,89.75},{82.00,136.49},{ 2.58,32.24},
  {67.53,95.80},{19.08,51.31},{43.00,90.48},{28.64,74.42},
  {62.27,96.64},{99.24,162.92},{51.33,69.02},{36.61,65.45},
  {37.97,69.43},{61.06,93.52},{34.90,71.86},{60.08,103.88},
  {52.73,97.43},{ 6.41,32.08},{22.94,50.80},{80.69,134.79},
  {15.06,44.04},{43.48,72.52},{33.21,77.52},{20.13,58.45},
  {40.63,69.57},{91.51,133.16},{62.50,104.10},{37.69,76.84},
  {58.08,88.35},{23.93,39.10},{56.37,88.39},{76.90,132.12},
  {26.25,40.52},{22.12,63.17},{14.15,51.74},{67.64,133.43},
  { 0.22,12.81},{ 1.78, 9.43},{ 3.38,13.12},{12.57,40.20},
  {60.21,97.21},{13.80,40.80},{81.02,134.27},{79.70,145.82},
  {64.24,103.49},{88.51,129.72},{70.05,108.91},{85.34,132.50},
  {16.00,66.32},{ 1.29,35.63},{11.98,34.39},{14.16,57.06},
  {67.55,108.51},{39.32,72.37},{34.71,74.84},{84.08,144.52},
  {29.65,71.63},{27.55,61.32},{70.25,108.96},{92.80,145.67},
  { 6.77,30.66},{79.60,137.19},{31.03,75.68},{56.32,107.55},
  {36.54,92.00},{56.00,109.40},{30.55,50.53},{95.46,128.04},
  {11.56,43.33},{66.96,127.53},{51.67,90.03},{26.44,68.23},
  {63.06,100.48},{ 4.00,36.34},{68.94,122.78},{62.12,79.62},
  {78.99,142.48},{60.21,116.54},{60.66,105.46},{27.17,58.25},
  { 3.74,26.85},{24.48,67.21},{75.69,116.85},{95.34,129.28},
  {32.36,61.32},{49.57,97.62},{ 9.61,46.66},{31.66,65.07},
  {19.01,56.53},{51.37,78.85},{62.35,98.59},{25.48,66.65},
  { 6.87,29.36},{46.91,62.94},{95.53,164.08},{43.91,79.76},
  {24.77,57.13},{ 4.27,32.09},{76.73,121.49},{78.83,119.05},
  {96.68,136.73},{36.15,77.78},{59.75,97.12},{73.33,107.99},
  {75.21,129.63},{79.18,127.84},{96.62,151.32},{ 3.76,26.13},
  { 1.77,17.82},{27.01,50.09},{14.94,56.08},{ 7.84,11.78},
  {82.00,130.84},{23.81,42.80},{91.10,154.02},{ 9.16,30.25},
  {33.55,80.55},{95.93,143.00},{35.63,79.83},{12.26,50.36},
  {92.56,147.23},{95.27,124.20},{18.24,56.02},{71.77,114.69},
  {39.51,67.28},{11.71,59.00},{43.06,74.76},{58.63,92.04},
  {50.81,89.86},{ 5.51,41.55},{72.63,114.81},{16.89,49.43},
  {83.17,132.95},{67.30,116.33},{ 6.68,38.95},{13.11,33.03},
  {85.58,147.14},{58.43,101.68},{93.79,148.56},{88.64,142.44},
  {50.00,103.38},{45.42,69.50},{78.36,123.53},{62.82,115.73},
  {58.11,123.10},{29.68,69.09},{92.50,146.61},{ 9.25,49.50},
  { 1.65,20.78},{57.03,101.69},{39.14,60.02},{60.54,110.13},
  {43.47,80.17},{20.81,53.16},{25.21,50.70},{96.86,157.76},
  {79.88,120.82},{36.87,60.42},{98.04,152.74},{80.00,122.99},
  {48.23,92.00},{89.21,144.62},{57.58,101.38},{80.51,136.35},
  {42.15,68.36},{47.35,78.24},{ 4.08,21.93},{92.57,131.72},
  {49.23,74.34},{28.09,51.03},{73.95,118.35},{49.62,99.21},
  {43.40,75.24},{30.75,67.51},{65.52,98.35},{13.93,17.36},
  {13.71,28.69},{78.18,132.55},{30.76,67.78},{64.94,110.11},
  {96.08,142.50},{83.25,111.30},{39.26,73.39},{30.70,67.12},
  { 3.25,48.31},{52.65,88.92},{34.46,65.10},{77.45,117.62},
  {37.27,69.85},{85.21,131.07},{36.98,81.19},{49.35,75.45},
  {91.09,149.73},{60.95,116.54},{71.35,120.17},{86.46,144.74},
  {64.79,124.42},{ 6.45,25.49},{87.51,128.79},{37.58,65.20},
  { 2.87,25.38},{ 7.45,41.19},{57.79,108.53},{14.53,27.31},
  {98.65,162.77},{90.06,140.23},{54.27,83.51},{14.30,38.35},
  {58.56,116.91},{21.03,45.74},{ 7.00,19.93},{83.38,136.74},
  { 6.53,30.38},{87.73,145.37},{56.99,96.67},{64.65,98.20},
  {54.24,86.45},{79.16,125.74},{85.48,138.67},{57.57,90.42},
  {45.51,98.44},{ 0.88,16.10},{90.67,133.36},{21.97,39.72},
  { 0.52,11.06},{11.02,23.86},{37.08,77.40},{80.88,135.98},
  {51.53,105.59},{77.32,119.80},{54.14,76.86},{16.62,66.00},
  {12.21,40.93},{90.27,134.55},{92.95,134.65},{69.37,125.43},
  {13.86,46.87},{70.01,117.47},{52.59,108.39},{37.63,80.20},
  {81.74,129.47},{63.77,120.09},{58.03,91.79},{91.67,139.73},
  {84.55,127.51},{51.00,94.06},{ 1.22,46.13},{83.80,125.56},
  {25.88,59.23},{17.11,27.41},{88.92,140.89},{82.26,119.11},
  {44.93,86.28},{ 4.18,27.89},{77.50,112.07},{24.85,66.76},
  {96.71,142.11},{71.48,118.39},{75.19,137.45},{73.80,113.89},
  {54.39,99.15},{63.10,103.82},{35.52,82.22},{91.83,141.98},
  {95.22,167.54},{27.95,54.89},{81.14,133.51},{61.15,113.33},
  { 4.55,45.26},{95.96,153.50},{83.02,112.06},{46.27,93.71},
  {60.32,119.27},{80.59,117.87},{42.44,93.38},{79.49,120.04},
  {50.99,92.46},{12.55,54.26},{70.55,103.38},{62.97,103.71},
  {12.47,25.75},{45.14,82.30},{16.51,55.48},{49.68,97.97},
  {82.38,142.82},{61.93,94.02},{92.25,159.71},{17.73,50.64},
  {26.96,64.24},{79.82,133.67},{23.20,45.97},{ 9.07,36.96},
  {93.98,158.90},{40.08,71.71},{24.55,66.11},{48.46,72.57},
  {55.16,97.59},{83.20,128.88},{63.81,111.42},{76.93,115.58},
  {77.93,126.64},{89.53,132.12},{ 6.35,36.34},{72.40,129.09},
  {78.28,120.31},{30.58,58.68},{28.95,78.28},{61.68,93.98},
  {71.95,115.50},{ 0.13,-3.00},{ 5.11, 8.96},{65.70,110.07},
  {13.26,22.35},{ 4.54,36.49},{10.04,47.48},{99.11,144.29},
  {39.69,84.48},{95.20,148.80},{78.70,133.20},{64.07,102.62},
  {87.07,137.60},{14.79,27.85},{12.77,39.51},{83.99,139.11},
  {54.71,107.67},{72.44,110.57},{96.60,155.35},{45.34,79.12},
  {37.69,58.67},{43.56,69.93},{10.15,33.67},{91.84,141.44},
  {53.77,112.28},{79.11,146.58},{ 7.81,35.01},{66.95,101.44},
  {45.59,87.47},{33.73,57.95},{34.52,62.37},{11.44,25.40},
  {90.51,143.73},{57.66,101.03},{33.89,52.16},{31.37,57.32},
  {66.51,110.58},{99.29,142.99},{10.54,33.75},{16.30,52.62},
  {58.20,113.87},{46.71,78.32},{98.18,136.66},{69.28,119.37},
  { 1.04,30.42},{85.24,135.35},{81.34,153.50},{91.54,156.76},
  {90.30,140.83},{16.38,49.58},{32.98,54.55},{69.07,114.77},
  {11.55,37.01},{31.99,65.14},{84.38,123.41},{64.02,112.59},
  {66.12,81.00},{55.92,85.22},{78.61,127.98},{86.70,148.63},
  { 6.69,17.92},{ 4.26,32.49},{10.37,42.40},{ 1.02,22.92},
  {13.19,56.23},{41.78,68.19},{53.74,79.08},{85.17,146.37},
  {58.46,99.17},{78.58,137.97},{63.18,96.10},{ 1.81,28.05},
  {12.15,51.83},{ 8.81,42.04},{18.80,42.35},{12.13,32.26},
  {20.66,51.94},{74.74,116.76},{60.01,98.66},{77.98,141.26},
  {92.13,126.73},{98.39,133.75},{18.66,42.27},{48.27,64.32},
  {94.54,133.99},{65.24,96.77},{85.97,123.36},{12.88,47.99},
  {82.41,118.20},{14.77,40.30},{86.28,119.33},{97.72,162.74},
  {71.69,109.49},{ 7.94,25.01},{30.34,70.69},{47.97,82.58},
  { 4.79, 3.24},{46.70,87.51},{91.69,131.68},{14.35,56.39},
  {95.12,153.30},{24.12,48.95},{59.14,88.31},{36.00,73.46},
  {58.68,102.50},{72.29,94.89},{54.85,96.07},{41.13,61.76},
  {79.10,131.91},{ 8.70,23.50},{93.68,147.64},{98.39,145.06},
  {62.46,119.65},{74.75,113.04},{ 3.20,10.44},{48.11,87.51},
  {35.41,76.73},{ 0.82,31.10},{39.81,81.63},{98.21,145.79},
  {46.02,87.50},{11.83,35.48},{51.54,95.66},{66.41,102.48},
  {41.48,66.36},{27.89,60.76},{65.43,122.49},{79.67,127.63},
  {44.12,83.40},{89.23,136.74},{14.56,56.48},{49.57,99.25},
  {32.39,61.89},{74.01,117.63},{27.08,53.41},{53.26,83.56},
  {51.51,94.35},{ 7.02,30.73},{28.11,60.48},{84.53,111.44},
  {72.71,123.55},{78.52,134.94},{56.30,69.95},{26.90,37.06},
  {10.88,45.04},{23.01,61.56},{81.37,123.68},{ 1.62,30.43},
  {42.50,94.10},{63.92,98.59},{91.94,125.15},{ 0.34, 6.13},
  {72.58,121.75},{43.80,73.32},{78.17,139.20},{69.58,108.92},
  {52.17,114.75},{71.36,102.88},{55.54,102.48},{51.46,105.80},
  {51.21,83.80},{32.92,72.60},{82.69,101.29},{52.79,71.88},
  {55.76,94.48},{ 6.45,16.76},{28.98,55.65},{82.17,128.98},
  {20.71,39.36},{23.01,44.99},{58.63,94.37},{83.98,115.84},
  { 8.12,30.27},{24.45,61.61},{49.19,74.93},{74.81,130.98},
  {78.03,144.61},{72.89,118.26},{65.73,116.48},{57.92,106.85},
  {94.65,151.86},{ 5.62,38.26},{28.47,49.43},{32.26,77.83},
  {50.13,80.74},{ 6.13,40.95},{97.32,141.24},{15.39,44.29},
  {18.02,50.61},{40.59,64.06},{44.62,66.48},{23.33,57.47},
  {96.17,157.02},{37.70,71.34},{46.62,78.05},{81.16,122.52},
  {55.12,96.68},{ 7.85,17.11},{54.57,117.71},{83.13,133.65},
  {57.79,108.03},{14.27,31.81},{ 4.38,22.34},{80.25,103.20},
  { 9.68,35.48},{29.99,78.50},{82.53,120.94},{71.35,111.91},
  {51.80,95.16},{39.04,72.03},{68.75,99.36},{75.58,100.42},
  {72.28,116.64},{91.69,146.99},{61.34,108.02},{94.38,143.63},
  {19.18,32.10},{91.85,151.62},{53.05,93.03},{96.69,172.78},
  {34.34,61.88},{28.41,65.85},{72.57,115.87},{27.32,60.23},
  {79.82,141.47},{37.55,81.67},{38.47,66.45},{15.70,38.36},
  {78.77,128.67},{47.30,102.03},{93.27,158.92},{62.30,121.58},
  {65.18,105.08},{10.63,46.60},{99.29,161.65},{ 4.14,39.91},
  {12.73,51.20},{24.22,49.49},{19.30,50.17},{87.57,154.12},
  {23.17,53.91},{90.47,125.91},{10.50,29.42},{19.27,56.30},
  {84.06,131.71},{45.95,82.97},{71.11,123.72},{53.25,93.03},
  {46.30,88.90},{ 7.50,45.89},{36.95,60.20},{97.67,152.71},
  {97.36,136.65},{22.47,48.51},{83.52,140.54},{57.37,74.03},
  {73.75,119.87},{90.49,116.90},{97.21,160.82},{52.01,100.36},
  {78.62,134.11},{70.57,119.44},{90.65,132.44},{50.82,73.95},
  {22.88,47.83},{28.48,62.31},{64.19,101.88},{81.82,122.23},
  {52.04,96.00},{64.79,114.48},{86.17,125.10},{94.80,147.36},
  {21.77,67.47},{88.20,130.82},{38.33,73.64},{88.70,156.21},
  {65.18,117.51},{26.03,56.67},{47.33,84.89},{52.35,103.95},
  {80.01,134.23},{ 4.97,42.23},{ 9.94,34.76},{55.49,101.71},
  {96.12,169.82},{34.35,49.85},{29.58,67.28},{29.64,53.13},
  { 2.57, 1.11},{92.35,157.70},{22.36,62.56},{54.30,93.73},
  {80.31,120.10},{40.97,56.86},{31.83,49.01},{84.99,159.79},
  {39.73,80.09},{94.91,148.33},{87.07,127.36},{45.09,97.63},
  {70.49,145.10},{ 7.10,29.50},{79.50,127.42},{23.54,50.62},
  {25.52,55.11},{78.47,153.21},{12.32,28.21},{81.44,138.77},
  {33.20,70.03},{ 4.58,19.40},{ 3.74,38.49},{69.25,106.63},
  {70.79,107.36},{90.51,133.99},{ 2.89,15.24},{70.65,127.70},
  {48.34,102.23},{93.26,127.40},{ 0.02,14.10},{65.81,121.48},
  {13.53,32.14},{56.72,77.87},{60.46,93.00},{49.53,84.81},
  {33.05,69.67},{26.38,50.84},{27.05,58.99},{61.95,89.05},
  {57.02,98.47},{91.34,138.29},{51.76,85.76},{45.04,96.27},
  {22.41,53.63},{59.30,96.57},{35.32,69.37},{46.29,74.66},
  {37.62,56.23},{90.85,137.09},{20.68,49.04},{15.03,40.15},
  {30.32,85.51},{98.75,139.23},{95.13,126.19},{72.67,122.53},
  {20.84,45.18},{63.99,113.93},{65.35,95.83},{ 0.73, 6.26},
  {67.18,111.88},{74.11,117.92},{31.19,74.31},{52.82,95.82},
  {66.51,120.31},{99.03,147.01},{97.00,140.95},{50.77,77.54},
  {51.31,97.78},{31.66,61.98},{37.82,61.22},{94.39,149.45},
  {70.85,136.21},{86.58,147.62},{17.45,46.77},{50.91,116.26},
  {39.00,74.10},{ 5.77,23.43},{ 3.20,24.24},{33.74,88.53},
  {43.32,88.08},{75.28,126.25},{78.66,114.54},{70.81,111.16},
  {24.26,42.27},{93.48,123.13},{94.64,147.03},{61.38,95.41},
  { 2.45,24.15},{ 0.08,26.58},{81.05,116.10},{65.79,114.04},
  {36.07,73.42},{85.20,133.37},{23.50,60.52},{53.43,97.47},
  {73.26,113.26},{60.42,90.80},{69.19,121.24},{90.96,158.27},
  {83.83,138.78},{99.91,162.42},{99.55,137.02},{71.84,129.33},
  {75.42,132.83},{65.22,109.22},{16.70,54.76},{17.34,41.23},
  { 9.62,28.37},{26.12,65.66},{50.43,91.96},{46.11,88.45},
  {84.17,137.84},{63.71,113.54},{58.45,116.81},{18.35,57.59},
  {17.26,31.35},{ 7.78,55.79},{84.73,136.28},{ 2.37,24.80},
  {68.32,104.57},{44.41,89.33},{21.85,55.24},{58.64,101.30},
  {12.51,34.69},{53.17,115.89},{59.11,78.69},{50.57,97.68},
  { 7.53,38.16},{79.69,124.64},{28.83,74.77},{20.74,61.23},
  {98.18,156.53},{ 0.96,33.70},{98.21,143.94},{15.72,34.79},
  {74.77,120.44},{51.61,77.68},{67.92,111.64},{22.73,65.66},
  {86.50,112.46},{17.04,32.13},{97.62,161.75},{61.35,86.52},
  {24.76,51.82},{ 0.37,19.51},{19.94,62.61},{12.37,46.66},
  {91.73,140.41},{14.56,52.57},{28.73,44.14},{42.01,81.09},
  {68.20,117.68},{95.60,152.72},{72.17,127.08},{97.93,135.88},
  {92.93,140.54},{24.12,60.42},{ 6.67,56.55},{29.21,74.94},
  {16.61,48.42},{69.06,99.80},{34.30,79.27},{ 7.57,34.59},
  {80.51,119.71},{80.16,127.50},{37.48,69.90},{25.07,49.61},
  {98.83,140.97},{46.88,74.11},{52.21,127.50},{76.55,141.74},
  { 9.96,33.33},{75.97,109.93},{70.27,91.54},{27.46,62.31},
  {49.55,81.58},{96.55,166.77},{ 0.10,13.73},{53.44,90.56},
  {26.79,64.12},{70.82,114.72},{27.88,60.29},{83.60,138.44},
  {95.20,148.55},{58.57,114.03},{73.88,135.88},{58.31,107.22},
  {18.10,42.27},{47.06,85.72},{31.87,61.94},{28.70,64.87},
  {59.79,87.81},{52.81,88.19},{84.03,124.65},{15.84,48.75},
  {65.30,104.46},{ 7.17,29.25},{76.86,129.43},{ 2.46,21.28},
  {34.94,79.19},{58.24,100.49},{14.81,45.00},{63.80,103.06},
  {64.33,115.38},{10.64,42.94},{98.66,157.77},{25.25,51.17},
  {24.47,52.71},{43.05,94.38},{22.25,51.06},{92.88,141.27},
  {33.33,61.39},{79.18,103.62},{25.70,61.59},{66.33,104.70},
  {58.88,88.84},{57.97,103.43},{32.18,64.30},{22.47,75.07},
  {80.92,119.09},{25.35,55.17},{ 2.79,49.94},{16.18,33.87},
  {21.37,48.25},{54.28,98.83},{74.04,128.45},{23.90,45.40},
  { 4.51,40.98},{17.32,34.97},{91.17,143.25},{ 0.61,42.49},
  {73.22,123.94},{35.11,58.44},{22.37,56.22},{27.98,57.23},
  {15.03,55.81},{83.00,131.14},{72.64,125.71},{ 3.78,24.98},
  {38.20,79.67},{ 2.35,24.83},{60.82,94.71},{98.87,163.29},
  {48.53,92.50},{54.51,89.83},{90.15,138.66},{64.79,122.01},
  {10.17,37.74},{96.25,146.18},{39.35,82.32},{79.85,103.50},
  {51.94,107.64},{21.93,63.48},{81.45,127.37},{55.29,100.66},
  {91.71,144.44},{30.10,55.86},{18.31,40.56},{48.34,91.21},
  { 1.31,31.15},{ 9.94,23.96},{97.89,150.85},{42.44,86.10},
  {89.35,142.02},{12.64,39.51},{65.88,99.23},{ 3.64,26.72},
  {89.66,152.60},{95.18,168.20},{23.04,52.63},{42.25,67.57},
  {93.07,137.23},{18.20,52.61},{19.68,51.31},{ 7.05,31.93},
  {89.82,111.42},{48.95,87.34},{46.56,86.17},{ 4.72,41.94},
  { 0.61,13.48},{69.36,110.44},{82.12,143.64},{70.48,125.96},
  {45.01,89.76},{65.81,104.69},{73.63,129.45},{67.32,103.72},
  {60.75,103.61},{11.13,30.87},{92.61,137.20},{89.78,147.97},
  {64.01,121.01},{25.27,59.93},{54.12,93.89},{18.15,52.86},
  {86.91,151.61},{52.71,91.90},{62.31,79.01},{15.86,72.02},
  {25.77,69.24},{37.51,67.15},{51.27,96.22},{63.94,97.58},
  {44.99,85.04},{87.87,129.26},{83.16,130.89},{96.83,161.96},
  {26.82,73.77},{96.37,153.51},{56.33,83.27},{ 4.13,32.50},
  { 7.54,36.18},{38.84,76.34},{ 9.33,67.52},{14.69,26.38},
  {47.84,86.04},{26.31,65.23},{15.86,44.55},{64.71,111.35},
  {16.14,32.77},{59.47,101.17},{ 6.83,35.88},{97.46,148.30},
  {85.60,131.37},{78.07,119.63},{56.93,89.96},{59.54,105.97},
  {92.13,157.77},{81.40,124.16},{11.27,42.38},{ 3.52,13.82}
};
