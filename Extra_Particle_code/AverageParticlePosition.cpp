
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <algorithm>


int particlenumber (int begin_file)
{
    int i_0, BIGNUMBER = 90000;
    float junk_0;
    float x=0,y=0,z=0,radius=0, v_x=0;
    int color=0;
    FILE *fp_0;
    
    char particlenumberfile[256];
    
    sprintf (particlenumberfile, "file%04d", begin_file);
    
    fp_0 = fopen (particlenumberfile, "r");
    
    for (i_0 = 0; i_0 < BIGNUMBER; i_0++) {
        if ((fscanf(fp_0, "%e %e %e %e %e %e %e %e %e %e %e %d\n", &x, &y, &z, &v_x, &junk_0, &junk_0, &junk_0, &junk_0, &junk_0, &radius, &junk_0, &color) == EOF))
        break;
    }
    fclose (fp_0);
    
    return (i_0);    
}

int main(int argc, char ** argv)
{
    int ft;
    char           infile[256];
    char           outfile[256];
    
    int begin_file=0000;
    int end_file=0000;
    int number_of_particles=0000;
    double x=0,y=0,z=0,radius=0,junk_0=0,time=0.0, Y_position=0.0, reference_y=100.0, wall_y;
    int color=0;
    int blue=0;
    FILE *fp, *fpout;
    int i;
    //int begin_file=0001;


    for (int i=1; i<argc;i++) {
        if (std::string(argv[i])=="-b") {
            i++;  //why needs i++ here?
            begin_file=atoi(argv[i]);
            std::cout<<"begin file number "<<begin_file<<std::endl;
        }
        
        if (std::string(argv[i])=="-e") {
            i++;  //why needs i++ here?
            end_file=atoi(argv[i]);
            std::cout<<"end file number "<<end_file<<std::endl;
        }
    }
    std::string usage= std::string("usage: -b to draw picture of a file number\n -e for the final file number");
    if (argc!=3) {
        std::cout << usage << std::endl;
    }
    std::cout<<"flip_time_is ? "<<std::endl;
    std::cin>>ft;

  //if using -b 1, begin_file will be file0001

    number_of_particles = particlenumber(begin_file);
    
    //std::cout<<"number_of_particles "<<number_of_particles<<std::endl;
    			sprintf(outfile, "blue_position_average_position_%d",ft);  //create output file
			    			if ((fpout = fopen(outfile, "w")) == NULL) {
							printf("Cannot Open File 290\n");
							exit(1);
							}
    
    for (int g=begin_file; g<end_file; g++)
{
    std::cout<<g<<std::endl;
    sprintf (infile, "file%04d", g);
    if((fp=fopen(infile, "r"))==NULL)
    {
        std::cout<<"no file number "<<g<<std::endl;
        exit(1);
    }
    time=g/30.0;

    for (i=0;i<number_of_particles;i++)
    {
       fscanf(fp, "%le %le %le %le %le %le %le %le %le %le %le %d\n", &x, &y, &z, &junk_0, &junk_0, &junk_0, &junk_0, &junk_0, &junk_0, &radius, &junk_0, &color);

         {
             if (color ==0)
             {
                 wall_y=y;
                 reference_y=std::min(wall_y,reference_y);
             }
				if (color==3)
				{
                Y_position+=y;
                    if (g==begin_file)
                    {
                        blue++;
                    }
			    }
        }
        
  }
    
    fprintf(fpout, "%e %e\n", time, Y_position/blue-reference_y);
    Y_position=0.0;
    reference_y=100.0;
    fclose(fp);
    
}
    fclose(fpout);
    std::cout<<"number of blue particles is "<<blue<<std::endl;
    std::cout<<"reference_y hieght is "<<reference_y<<std::endl;
    std::cout<< "Time & Average_Y_position "<<std::endl;
    
  return 0;
}