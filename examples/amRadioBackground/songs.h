/*
 * Define some songs to play
 */

#define MARYNOTES {E4, D4, C4, D4, E4, E4, E4, REST,\
               D4, D4, D4, REST, E4, G4, G4, REST,\
               E4, D4, C4, D4, E4, E4, E4, E4,\
               D4, D4, E4, D4, C4, REST}
/* 120 bpm = 500 ms per 1/4 note*/
#define MARYLENGTHS {500, 500, 500, 500, 500, 500, 500, 500,\
                 500, 500, 500, 500, 500, 500, 500, 500,\
                 500, 500, 500, 500, 500, 500, 500, 500,\
                 500, 500, 500, 500, 1000, 1000}

#define MARIONOTES {E5, E5, E5, REST, C5, E5, G5, REST, G4, REST,\
                C5, REST, G4, REST, E4, REST, A4, REST, B4, REST, Ax4, A4,\
                G4, E5, G5, A5, F5, G5, REST, E5, REST, C5, D5, B4, REST}
/* 90 bpm ~ 668 ms per 1/4 note */
#define MARIOLENGTHS {167, 334, 167, 167, 167, 334, 334, 334, 334, 334,\
                334, 167, 167, 334, 334, 167, 167, 167, 167, 167, 167, 334,\
                223, 223, 223, 334, 167, 167, 167, 167, 167, 167, 167, 167, 334}


#define SCALENOTES {REST, C4, Cx4, D4, Dx4, E4, F4, Fx4, G4, Gx4, A4, Ax4, B4,\
                    REST, C5, Cx5, D5, Dx5, E5, F5, Fx5, G5, Gx5, A5, Ax5, B5,\
                    REST, C6}
#define SCALELENGTHS {600, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334,\
                      600, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334,\
                      600, 334}

#define TESTTONE {REST, D4}
#define TESTLENGTH {334, 6000}