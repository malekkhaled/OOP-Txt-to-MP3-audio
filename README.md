# Txt-to-MP3-audio

Program capable of turning a text file describing the notes of a piece of music into an audio file. The main task is to read the contents of the file input.txt, construct vectors of structs describing the notes in the file. 

The input file will have at least 2 lines.  The first line will contain a single integer representing the tempo of the piece of music.  This will be an argument to a function later, so save it in a variable. 

The following lines will contain a sequence of words separated by spaces.  Each word on these lines represents one music note, which you will use to initialize a note_t struct.  These notes have a particular structure.  The first 1 or 2 characters represent the pitch of the note, the next character will be a single digit representing the octave for the note, and the final 1 or 2 characters represent the duration of the note.

The pitch of the note will be one of the following values:  R, A, B, C, D, E, F, G, Ab, Bb, Db, Eb, Gb, A#, C#, D#, F#, or G#.  These values correspond to the values of the pitch_t enumerated type in the provided header.  R stands for REST, while A#, C#, D#, F#, and G# correspond to Bb, Db, Eb, Gb, and Ab, respectively.  The octave will be a digit in the range 0-7, and you should store this in the octave field of the note_t.  Lastly, the duration will be one of the letters q, h, w, e, or s, possibly followed by a period.  The letters q, h, w, e, and s correspond to durations of 1, 2, 4, 0.5, and 0.25, respectively.  Any duration that is followed by a period (.) should be multiplied by 1.5 (e.g., "e." will have a duration of 0.75).

Afterwards, overlay() function in the provided header is called, where the first argument is an empty vector<sample_t> and the second is vector<sample_t> returned by convertNotesToSamples.  After that, next line of the file is read, extracting out all of the notes in this line, calling convertNotesToSamples(), and calling overlay() with the same arguments.  The first argument to overlay() should be defined outside of the loop that iterates through the lines in the input file--the purpose of repeatedly calling overlay() is to combine the sample data for every line so that they are all played simultaneously.

Finally, once you have used overlay() to combine all of the music together and there are no more lines left in the file, call writeToWAV with the file name output.wav and your overlaid vector<sample_t>.

More details about the provided functions, as well as the note_t struct and pitch_t enumerated type, appear in the provided header file.
