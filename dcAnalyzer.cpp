#include"globals.hpp"

/*
 * TODO : Learn harwell-boeing format for dense matrix
 * TODO : Try if MNA matrix can be filled while reading circuit
 * TODO : See if MNA matrix can be filled in parallel
 */



void GraphOfNetwork::findVoltage()
{
  ORDER = _NODES + _VOLTAGESOURCE -1;
  
  clock_t start, end;
  
  denseMatrix = new double[ORDER*ORDER]();
  
  currentVector = new double[ORDER]();
  
  solVec = new double[ORDER]();
  
  //start = clock();
  fillMatrix_Dense();
  //end = clock();
  
  /*cout<<endl<<"-----------------------------------------------------------------------------------------------"<<endl;
  cout<<"Time taken by BFS : "<<(double)(end-start)/CLOCKS_PER_SEC<<" seconds"<<endl;
  cout<<"-----------------------------------------------------------------------------------------------"<<endl;
  */

  LUDecomposition();
  
}

void GraphOfNetwork::fillMatrix_Dense()
{
  queue<unsigned int> nodeQueue;
  
  register unsigned int nodeNo;
  register unsigned int sourceNodeNo;
  register unsigned int sinkNodeNo;
  
  list<Edge*>::iterator edgeItr;  
  list<Edge*>::iterator endEdgeList;
  
  bool* nodeCovered = new bool[_NODES]();
  
  unsigned int volt=1;
  
  Edge* e;
  
  nodeQueue.push(1);
  
  while(!nodeQueue.empty())
  {
    nodeNo = nodeQueue.front();
    
    edgeItr = nodePtrList[nodeNo]->edgeList.begin();
    endEdgeList = (nodePtrList[nodeNo]->edgeList).end();
    
    if(nodeCovered[nodeNo] != true)
    {
      nodeCovered[nodeNo] = true;
      
     for(edgeItr; edgeItr != endEdgeList; edgeItr++)
     {    
       sourceNodeNo = (*edgeItr)->sourceNodeNumber;
       sinkNodeNo   = (*edgeItr)->sinkNodeNumber;
 
       if( (*edgeItr)->edgeVisited == false )
       {
	
	 if((*edgeItr)->edgeType == "R")
	 {
	   if(sinkNodeNo == 0) denseMatrix[(sourceNodeNo-1)*ORDER + (sourceNodeNo-1)] = denseMatrix[(sourceNodeNo-1)*ORDER + (sourceNodeNo-1)] + (*edgeItr)->branchValue;
	   else if(sourceNodeNo == 0) denseMatrix[(sinkNodeNo-1)*ORDER + (sinkNodeNo-1)] = denseMatrix[(sinkNodeNo-1)*ORDER + (sinkNodeNo-1)] + (*edgeItr)->branchValue;
	   else
	   {
	     denseMatrix[(sinkNodeNo-1)*ORDER + (sinkNodeNo-1)] = denseMatrix[(sinkNodeNo-1)*ORDER + (sinkNodeNo-1)] + (*edgeItr)->branchValue;
	     denseMatrix[(sourceNodeNo-1)*ORDER + (sourceNodeNo-1)] = denseMatrix[(sourceNodeNo-1)*ORDER + (sourceNodeNo-1)] + (*edgeItr)->branchValue;
	     denseMatrix[(sourceNodeNo-1)*ORDER + (sinkNodeNo-1)] = denseMatrix[(sourceNodeNo-1)*ORDER + (sinkNodeNo-1)] - (*edgeItr)->branchValue;
	     denseMatrix[(sinkNodeNo-1)*ORDER + (sourceNodeNo-1)] = denseMatrix[(sinkNodeNo-1)*ORDER + (sourceNodeNo-1)] - (*edgeItr)->branchValue;    
	   }
	 }
	else if((*edgeItr)->edgeType == "I")
	{
	  if(sinkNodeNo == 0) currentVector[sourceNodeNo-1] = currentVector[sourceNodeNo-1] - (*edgeItr)->branchValue;
	  else if(sourceNodeNo == 0) currentVector[sinkNodeNo-1] = currentVector[sinkNodeNo-1] + (*edgeItr)->branchValue;
	  else
	  {
	    currentVector[sourceNodeNo-1] = currentVector[sourceNodeNo-1] - (*edgeItr)->branchValue;
	    currentVector[sinkNodeNo-1] =  currentVector[sinkNodeNo-1] + (*edgeItr)->branchValue;
	  }
	    
	}
	else if((*edgeItr)->edgeType == "V")
	{
	 //cout<<(*edgeItr)->voltEdgeNumber<<endl;
	 if(sinkNodeNo == 0)
	 { 
	   //cout<<sourceNodeNo<<" "<<ORDER<<" "<<_NODES<<endl;
	   denseMatrix[(sourceNodeNo-1)*ORDER + _NODES-2 + (*edgeItr)->voltEdgeNumber] = 1;
	   denseMatrix[((_NODES-1) + ((*edgeItr)->voltEdgeNumber-1))*ORDER + (sourceNodeNo-1)] = 1;
	   
	   currentVector[(_NODES-2) + (*edgeItr)->voltEdgeNumber] = (*edgeItr)->branchValue; 
	 }
	 else if(sourceNodeNo == 0)
	 {
	   denseMatrix[(sinkNodeNo-1)*ORDER + _NODES-2 + (*edgeItr)->voltEdgeNumber] = -1;
	   denseMatrix[((_NODES-1) + ((*edgeItr)->voltEdgeNumber-1))*ORDER + (sinkNodeNo-1)] = -1;
	   
	   currentVector[(_NODES-2) + (*edgeItr)->voltEdgeNumber] = (*edgeItr)->branchValue;
	 }
	 else
	 {
	   //cout<<(*edgeItr)->voltEdgeNumber<<endl;
	   denseMatrix[(sourceNodeNo-1)*ORDER + _NODES-2 + (*edgeItr)->voltEdgeNumber] = 1;
	   denseMatrix[((_NODES-1) + ((*edgeItr)->voltEdgeNumber-1))*ORDER + (sourceNodeNo-1)] = 1;
	   
	   denseMatrix[(sinkNodeNo-1)*ORDER + _NODES-2 + (*edgeItr)->voltEdgeNumber] = -1;
	   denseMatrix[((_NODES-1) + ((*edgeItr)->voltEdgeNumber-1))*ORDER + (sinkNodeNo-1)] = -1;
	   
	   currentVector[(_NODES-2) + (*edgeItr)->voltEdgeNumber] = (*edgeItr)->branchValue;
	 }
	  
	}
	
	
	
	if(nodeNo != sourceNodeNo && nodeCovered[sourceNodeNo] != true)
	{
	  if(sourceNodeNo != 0) nodeQueue.push(sourceNodeNo);
	}
	else if(sinkNodeNo != true)
	{
	  if(sinkNodeNo != 0) nodeQueue.push(sinkNodeNo);
	}
	
        //cout<<(*edgeItr)->edgeType;
	(*edgeItr)->edgeVisited = true;
      }       
    }
     
      
    }
    nodeQueue.pop();
  }


//-----------Display MNA matrix and current vector---------------  
/*
  for(int i = 0; i<ORDER; i++)
  {
    for(int k = 0; k<ORDER; k++)  cout<<denseMatrix[i*ORDER + k]<<"  ";
    cout<<endl;   
  }
  
  for(int i=0; i<ORDER; i++)
  {
    cout<<currentVector[i]<<endl;
  }  
*/    
}
