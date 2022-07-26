#include "nr5gPhyLog.h"

FILE *flog;

void Loginit()
{
 
    flog = fopen("output.log", "w");

    if(flog == NULL)
    {
        FILE *flog;
        fprintf(flog, "Error!");
        exit(1);
    }
    
    // fprintf(flog, "\n====== MATRIX 1024x1024 ======\n");

    // for(int i = 0; i < 1024; i++)
    // {
    //     for(int j = 0; j < 1024; j++)
    //     {
    //         fprintf(flog, "%d ", iMatrixWrite[i][j]);
    //     }
    //     fprintf(flog, "\n");
    // }
}

void Logstop()
{
   fclose(flog);
}