# CMPT 365 Work

All assignments and projects will be put here

## Project 1

Both sections are developed in QT C++. Used only [QCustomPlot](https://www.qcustomplot.com/index.php/introduction)

- (Project_1_Audio) Audio section deals with reading WAV files, typically in mono/stereo with samples no greater 65536, and is PCM coded. The program displays the data as a waveform and can display gradual increase from 0dB to -20dB and vice versa (Via [QCustomPlot](https://www.qcustomplot.com/index.php/introduction)) . 

- (Project_1) Image section takes in images of 24 bit uncompressed BMP format and transforms into the following modifications: 
1. Grayscale
2. Ordered dithering with custom matrix
3. Color autoleveling 

## Project 2

Both sections are developed in QT C++. No external libraries used

- (Project_2_Audio) Compresses WAV files of similar format in Project_1_Audio via Linear Prediction, Channel Coupling, and LZW Entropy Encoding. Program converts sample data into string bytes, then compares file sizes between uncompressed / compressed data.

- (Project_2_Image) Reads an image of similar format in Project_1 and does the following steps:
1. RGB -> YCoCg Color Space
2. 2D Discrete Cosine Transform on 8x8 blocks
3. Lossy Quantization
4. Then steps 3 -> 1
