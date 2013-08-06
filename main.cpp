#include"globals.hpp" 

/*
 * TODO : Learn harwell-boeing format for dense matrix
 * TODO : Try if MNA matrix can be filled while reading circuit
 * TODO : See if MNA matrix can be filled in parallel
*/

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    cout<<"Error: Input circuit not found"<<endl;
    exit(1);
  }
  
  cout<<endl<<"***************************************START***************************************************"<<endl;
  
  
  GraphOfNetwork G;
  
  G.convertNetworkIntoGraph(argv[1]);
  G.findVoltage();
  G.printSolution();
  
  cout<<endl<<"***************************************END*****************************************************"<<endl;
  
  
  return 0;
}
