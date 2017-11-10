#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "BigInt.h"
#include "BIStack.h"
static void printHelp();
static char textLine[10000];
BigInt power(0);
BigInt base(0);
static void Sign(char *Ifn, char *Sfn); // Input file name, Sign file name
static void Check(char *Ifn, char *Sfn); //Input file name, Sign file name
BigInt Hash(FILE * in); // Simple Hash
int main(int argc, char **argv)
{
if(argc!=4)
  {
    std::cerr << "Incorrect parameters" <<std::endl;
    printHelp();
    return -1;
  }
if(strcmp(argv[1], "sign")==0)
  {
     std::cout << "Signing initiated" << std::endl;
     Sign(argv[2], argv[3]);
  }
else
  {
    if(strcmp(argv[1], "check")==0)
      {
         std::cout << "Checking initiated"<<std::endl;
         Check(argv[2], argv[3]);
      }  
    else
      {
         std::cerr <<"Incorrect mode" <<std::endl;
         printHelp();
         return -1;
      }      
  }
return 0;
}
BigInt Hash(FILE * in)
{
int blockSize=1024;
char input[blockSize];
if(!in){std::cerr <<"No input in hash function" <<std::endl; return -1;}
BigInt rezult(0);
bool end = false;
int rB;
while(!end)
 {
   rB=fread(input, 1, blockSize, in);
   for(int i=0; i<rB; ++i)
     {
       rezult += ((int)input[i] * (i+1) ); 
       rezult=rezult%base;
     }
   if(feof(in)||ferror(in)){end=true;}
  }
return rezult;
}
static void Sign(char *Ifn, char *Sfn) // Input file name, Sign file name
{
char input[512];
FILE * key = fopen("PrivateKey", "r");
if(!key){std::cerr << "Key is not avaliable" << std::endl; return;}
fscanf(key, "%s", input);
base.fromString(input, strlen(input));
fscanf(key, "%s", input);
power.fromString(input, strlen(input));
FILE *in , *out;
in=fopen(Ifn, "r");
out=fopen(Sfn, "w");
if(!in){std::cerr << "No input file" << std::endl; return;}
if(!out){std::cerr << "Unable to create sign file" <<std::endl; return;}
BigInt SH = Hash(in);
SH=SH.powerMod(power, base);
fprintf(out,"%s", SH.toString(textLine, 4094));
fclose(in);
fclose(out);
std::cout << "Successful signing" << std::endl;
}
static void Check(char *Ifn, char *Sfn)
{
char input[512];
FILE * key = fopen("PublicKey", "r");
if(!key){std::cerr << "Key is not avaliable" << std::endl;}
fscanf(key, "%s", input);
base.fromString(input, strlen(input));
fscanf(key, "%s", input);
power.fromString(input, strlen(input));
FILE *in , *signin;
in=fopen(Ifn, "r");
signin=fopen(Sfn, "r");
if(!in){std::cerr << "No input file" << std::endl; return;}
if(!signin){std::cerr << "No sign file" <<std::endl; return;}
BigInt SH(0), toBeChecked(0);
SH=Hash(in);
fscanf(signin, "%s", input);
toBeChecked.fromString(input, strlen(input));
toBeChecked=toBeChecked.powerMod(power, base);
if(toBeChecked==SH)
  {
    std::cout << "Hashes are equal. File is confirmed" <<std::endl;
  }
else
  {
   std::cout << "Hashes are not equal" << std::endl;
  }
}
static void printHelp() {
    printf(
        "Electronic signature parameters:\n"
        "\tsign\tCreate sign file(input: File to be signed and name of sign file to be created)\n"
        "\tcheck\tCheck sign file (input: File and it's sign file)\n"
    );
}
