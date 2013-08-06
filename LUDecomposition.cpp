#include"globals.hpp"

void GraphOfNetwork::LUDecomposition()
{

  double* L = new double[ORDER*ORDER]();
  double* U = new double[ORDER*ORDER]();
  
  double dotProd=0;
//-----------------------LU Decomposition--------------------------

for(int i=0; i<ORDER; i++) L[i*ORDER + i] = 1;
     
  for(int row=0; row<ORDER; row++)
  {
    //------------Calculating elements of U-----------------
    for(int col=row; col<ORDER; col++)
    {             
      dotProd = 0;
      for(int j=0; j<row; j++)
      {
	dotProd = dotProd + L[row*ORDER + j]*U[j*ORDER + col];
      }      
      U[row*ORDER + col] = denseMatrix[row*ORDER + col] - dotProd;      
    }
    
    //------------Calculating elements of L-----------------
    for(int i=row+1; i<ORDER; i++)
    {
      dotProd = 0;
      for(int j=0; j<row; j++)
      {
	dotProd = dotProd + L[i*ORDER + j]*U[j*ORDER + row];
      }
      L[i*ORDER + row] = (denseMatrix[i*ORDER + row] - dotProd)/U[row*ORDER + row];
    }        
  } 

//---------------Forward substitution----------------------
double* y = new double[ORDER]();

for(int row=0; row<ORDER; row++)
{
  dotProd = 0;
  for(int j=0; j<row; j++)
  {
    dotProd = dotProd + L[row*ORDER + j]*y[j];
  }
  y[row] = currentVector[row] - dotProd;
} 
 
//---------------Backward substitution---------------------- 
for(int row=(ORDER-1); row>=0; row--)
{
  dotProd = 0;
  for(int j=(ORDER-1); j>=row; j--)
  {
    dotProd = dotProd + U[row*ORDER + j]*solVec[j];
  }
  solVec[row] = (y[row]-dotProd)/U[row*ORDER + row];
}


//---------------Display LU factors---------------
 /*cout<<"U decomposition"<<endl;
 for(int i=0;i<ORDER;i++)
 {
   for(int k=0;k<ORDER;k++) cout<<U[i*ORDER + k]<<"  ";
   cout<<endl;
 }
 
cout<<endl<<"L decomposition"<<endl; 
 for(int i=0;i<ORDER;i++)
 {
   for(int k=0;k<ORDER;k++) cout<<L[i*ORDER + k]<<"  ";
   cout<<endl;
 }*/
 
 
 delete [] L;
 delete [] U;
 delete [] y;
 
}
 
