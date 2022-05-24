//William hendrix

#ifndef __WAVEMAKER_H
#define __WAVEMAKER_H

#include <cstdint>
#include <vector>
using namespace std;

//Enumerated type to represent a musical pitch
enum pitch_t { C, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B, REST };

//Struct representing a single musical note
//Contains a pitch, octave, and duration
//Each note is described by one word in the input file
//See lab for details on how notes are stored
typedef struct
{
  pitch_t pitch;
  uint16_t octave;
  double duration;
} note_t;

//sample_t:  base data type for WAV data
//Used in functions below
typedef int16_t sample_t;

//Takes a collection of notes and converts to WAV samples
//Instrument resembles an organ
//Defaults to 120 beats per minute and a volume level of 1000
vector<sample_t> convertNotesToSamples(vector<note_t> notes, int tempo = 120, int volume = 1000);

//Overlays source audio track on top of a target audio track
//Does not test for overflow or underflow
//May fail if final result is "too loud"
//Result has length equal to longer track
void overlay(vector<sample_t>* target, const vector<sample_t>* source);

//Writes the given audio data to a WAV file
void writeToWAV(string filename, const vector<sample_t>* samples);






///////////////////////////////////////////
//The rest of this header is not related //
//to the code you need to write.         //
///////////////////////////////////////////

//Useful constants
const int SECONDS_PER_MINUTE = 60;
const double EPSILON = 1e-10; //for floating point comparisons
const int NUM_PITCHES = 12;
//Frequency of each pitch (from https://pages.mtu.edu/~suits/notefreqs.html)
//Frequencies are given for octave 7
const double FREQUENCY[] = { 4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040, 7458.62, 7902.13, 0 };
const uint16_t OCTAVE_OFFSET = 7;

// Header information for the WAV file
// 3 parts:
//  * overall file header indicating the file type and some other info
//  * wave header indicating how the data is formatted
//  * data header indicating how big the data is
//
//  To learn more about WAV files, see:
//    http://soundfile.sapp.org/doc/WaveFormat/
struct RIFF_Header
{
  int8_t chunkID[4];
  int32_t chunkSize;
  int8_t format[4];
};
struct WAVE_Format
{
  int8_t subChunkID[4];
  int32_t subChunkSize;
  int16_t audioFormat;
  int16_t numChannels;
  int32_t sampleRate;
  int32_t byteRate;
  int16_t blockAlign;
  int16_t bitsPerSample;
};
struct WAVE_Data
{
	int8_t subChunkID[4];
	int32_t subChunkSize;
};

//Constants describing the WAV format
enum channel_t { MONO = 1, STEREO = 2 };
const channel_t NUM_CHANNELS = MONO;
const int BYTES_PER_SAMPLE = sizeof(sample_t);
const int BITS_PER_BYTE = 8;
const int SAMPLE_RATE = 44100; //CD quality (prob. not needed)

#endif