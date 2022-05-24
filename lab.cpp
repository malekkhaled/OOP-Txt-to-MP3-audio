#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include "wavemaker.h"
using namespace std;



int main ()
{
    vector <sample_t> sequence;
    ifstream input ("input.txt");
    istringstream tempStream, tempStream2;
    int tempo;
    int tempInt;
    char tempChar, tempChar2;
    double tempDuration;
    string str, str2;
    note_t tempNote;
    pitch_t tempPitch;
    vector <note_t> notes;
    vector <sample_t> empty;

    input >> tempo;

    while (!input.eof())
    {
        getline(input, str2);
        tempStream2.clear();
        tempStream2.str(str2);
        while(tempStream2 >> str)
        {
            tempStream.clear();
            tempStream.str(str);
            str.clear();
            tempStream >> tempChar;
            tempStream >> tempChar2;
            
            if(!isdigit(tempChar2))
            {
                str += tempChar;
                str += tempChar2;
                tempInt = tempStream.get() - '0';
            }
            else
            {
                str += tempChar;
                tempInt = tempChar2 - '0';
            }
            
            if(str == "C")
                tempPitch = C;
            else if (str == "Db" || str == "C#")
                tempPitch = Db;
            else if (str == "D")
                tempPitch = D;
            else if (str == "Eb" || str == "D#")
                tempPitch = Eb;
            else if (str == "E")
                tempPitch = E;
            else if (str == "F")
                tempPitch = F;
            else if (str == "Gb" || str == "F#")
                tempPitch = Gb;
            else if (str == "G")
                tempPitch = G;
            else if (str == "Ab" || str == "G#")
                tempPitch = Ab;
            else if (str == "A")
                tempPitch = A;
            else if (str == "Bb" || str == "A#")
                tempPitch = Bb;
            else if (str == "B")
                tempPitch = B;
            else if (str == "REST" || str == "R")
                tempPitch = REST;

            tempNote.pitch = tempPitch;

            tempNote.octave = tempInt;

            str.clear();
            tempStream >> tempChar;
            if(tempStream >> tempChar2)
            {
                str += tempChar;
                str += tempChar2;
            }
            else
                str += tempChar;

            if (str == "q")
                tempDuration = 1;
            else if (str == "q.")
                tempDuration = 1 * 1.5;
            else if (str == "h")
                tempDuration = 2;
            else if (str == "h.")
                tempDuration = 2 * 1.5;
            else if (str == "w")
                tempDuration = 4;
            else if (str == "w.")
                tempDuration = 4 * 1.5;
            else if (str == "e")
                tempDuration = 0.5;
            else if (str == "e.")
                tempDuration = 0.5 * 1.5;
            else if (str == "s")
                tempDuration = 0.25;
            else if (str == "s.")
                tempDuration = 0.25 * 1.5;

            tempNote.duration = tempDuration;

            notes.push_back(tempNote);
        }
        sequence.clear();
        sequence = convertNotesToSamples(notes, tempo);
        notes.clear();
        overlay(&empty,&sequence);
    }
    
    writeToWAV("output.wav", &empty);

    return 0;
}