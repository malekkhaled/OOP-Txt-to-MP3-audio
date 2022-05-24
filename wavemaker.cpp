#include <fstream>
#include <cmath>
using namespace std;

#include "wavemaker.h"
//See header file for descriptions of functions

vector<sample_t> convertNotesToSamples(vector<note_t> notes, int tempo, int volume)
{
  vector<sample_t> samples;
  for (int i = 0; i < notes.size(); i++)
  {
    double freq = FREQUENCY[notes[i].pitch] / (1 << (OCTAVE_OFFSET - notes[i].octave));
    double delta = 2 * M_PI * freq / SAMPLE_RATE;
    int num_samples = notes[i].duration * SECONDS_PER_MINUTE * SAMPLE_RATE / tempo + EPSILON;

    //Organ-like timbre comes from combining 1st, 2nd, and 3rd harmonics
    for (int i = 0; i < num_samples; i++)
      samples.push_back(volume * (sin(i * delta) + sin(i * delta * 2) + sin(i * delta * 3)));
  }
  return samples;
}

void overlay(vector<sample_t>* target, const vector<sample_t>* source)
{
  int min = target->size();
  if (source->size() < min)
    min = source->size();

  for (int i = 0; i < min; i++)
    target->at(i) += source->at(i);
  for (int i = min; i < source->size(); i++)
    target->push_back(source->at(i));
}

void writeToWAV(string filename, const vector<sample_t>* samples)
{
  struct WAVE_Data datahead;
  datahead.subChunkID[0] = 'd';
  datahead.subChunkID[1] = 'a';
  datahead.subChunkID[2] = 't';
  datahead.subChunkID[3] = 'a';
  datahead.subChunkSize = samples->size() * BYTES_PER_SAMPLE;

  struct WAVE_Format fmt;
  fmt.subChunkID[0] = 'f';
  fmt.subChunkID[1] = 'm';
  fmt.subChunkID[2] = 't';
  fmt.subChunkID[3] = ' ';
  fmt.subChunkSize = 16;
  fmt.audioFormat = 1;
  fmt.numChannels = NUM_CHANNELS;
  fmt.sampleRate = SAMPLE_RATE;
  fmt.byteRate = SAMPLE_RATE * BYTES_PER_SAMPLE;
  fmt.blockAlign = SAMPLE_RATE * NUM_CHANNELS;
  fmt.bitsPerSample = BYTES_PER_SAMPLE * BITS_PER_BYTE;

  struct RIFF_Header fileheader;
  fileheader.chunkID[0] = 'R';
  fileheader.chunkID[1] = 'I';
  fileheader.chunkID[2] = 'F';
  fileheader.chunkID[3] = 'F';
  fileheader.chunkSize = 36 + datahead.subChunkSize;
  fileheader.format[0] = 'W';
  fileheader.format[1] = 'A';
  fileheader.format[2] = 'V';
  fileheader.format[3] = 'E';

  ofstream out(filename, ios::binary);
  out.write((const char*) &fileheader, sizeof(struct RIFF_Header));
  out.write((const char*) &fmt, sizeof(struct WAVE_Format));
  out.write((const char*) &datahead, sizeof(struct WAVE_Data));
  out.write((const char*) samples->data(), samples->size() * BYTES_PER_SAMPLE);
  out.close();
}
