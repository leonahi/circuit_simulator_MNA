#include"globals.hpp" 

void GraphOfNetwork::printSolution()
{
  cout<<endl<<"------------------Solution-----------------"<<endl<<endl;
  cout<<"------------Node voltages-------------"<<endl;
  
  for(int i=0; i<(_NODES-1); i++)
  {
    cout<<"Voltage at node "<<i+1<<" : "<<solVec[i]<<endl;
  }
  for(int i=(_NODES-1); i<ORDER; i++)
  {
    cout<<"Current through Voltage source "<<i<<" : "<<solVec[i]<<endl;
  }
  
  //delete [] denseMatrix;
  //delete [] currentVector;
  //delete [] solVec;

}
