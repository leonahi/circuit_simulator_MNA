#include"globals.hpp"

/*
 * TODO : Try if MNA matrix can be filled while reading circuit
 */




void GraphOfNetwork::convertNetworkIntoGraph(char *fileName)
{
  clock_t start, end;
  
  start = clock();
  
  ifstream file(fileName);
  
  if(!file.is_open())
  {
    cout<<endl<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Error: Unable to open circuit file"<<endl;
    cout<<endl<<"-----------------------------------------------------------------------"<<endl;
    exit(1);
  }
  
  unsigned int  sourceNodeNumber = 0;
  unsigned int  sinkNodeNumber = 0;
  unsigned int  edgeNumber = 0;
  double        branchValue = 0;
  string        edgeType;
  
  edgeType.reserve(3);
    
  unsigned int dummy;
  
  stringstream SS;
  string temp;
  temp.reserve(200);
  
  while(!file.eof())
  {    
   getline(file, temp);
   
   if(!temp.compare(".end")) break;
   
   SS.clear();
   SS.str("");
   
   SS.str(temp);
   
   SS >> edgeType >> sourceNodeNumber >> sinkNodeNumber >> branchValue;
   
   //cout<<edgeType<<" "<<sourceNodeNumber<<" "<<sinkNodeNumber<<" "<<branchValue<<endl;
      
   sourceNodeNumber = (sourceNodeNumber > sinkNodeNumber) ? sourceNodeNumber : sinkNodeNumber;
   if(sourceNodeNumber > _NODES) _NODES = sourceNodeNumber;
   
   ++_EDGES;   
   //cout<<"Getting right"<<endl;
  }
  
  ++_NODES;
  
  nodePtrList = new Node*[_NODES*sizeof(Node)];
  edgePtrList = new Edge*[_EDGES*sizeof(Edge)];
  
  
  file.close();
  file.open(fileName);
  string element;
  element.reserve(3);
  
  for(edgeNumber = 0; !file.eof(); edgeNumber++)
  {
    getline(file, temp);
    if(!temp.compare(".end")) break;
    
    SS.clear();
    SS.str("");
    
    SS.str(temp);
    
    SS >> element >> sourceNodeNumber >> sinkNodeNumber >> branchValue;
    
    if(nodePtrList[sourceNodeNumber] == NULL) nodePtrList[sourceNodeNumber] = new Node(sourceNodeNumber);
    if(nodePtrList[sinkNodeNumber] == NULL) nodePtrList[sinkNodeNumber] = new Node(sinkNodeNumber);
    
//-------------------------------------------------------------------------------------------------------------------------------    
    const string delims("RIVDQNQP");
    string::size_type begIdx, endIdx;
    
    begIdx = element.find_first_of(delims);
    if(begIdx == string::npos) 
    {
      cout<<"Error: Netlist is not in proper format"<<endl;
      exit(1);
    }
    endIdx = element.find_first_not_of(delims, begIdx);
    
    edgeType = element.substr(begIdx, endIdx);
//-------------------------------------------------------------------------------------------------------------------------------    
    
    if(edgeType == VoltageSource)
    {
      ++_VOLTAGESOURCE;
      addEdge(edgeType, sourceNodeNumber, sinkNodeNumber, branchValue, edgeNumber);
      //addEdge(edgeType, nodePtrList[sourceNodeNumber], nodePtrList[sinkNodeNumber], branchValue, edgeNumber);
    }
    else if(edgeType == CurrentSource)
    {
      ++_CURRENTSOURCE;
      addEdge(edgeType, sourceNodeNumber, sinkNodeNumber, branchValue, edgeNumber);
      //addEdge(edgeType, nodePtrList[sourceNodeNumber], nodePtrList[sinkNodeNumber], branchValue, edgeNumber);
    }
    else if(edgeType == Resistance)
    {
      branchValue = 1.0/branchValue;
      addEdge(edgeType, sourceNodeNumber, sinkNodeNumber, branchValue, edgeNumber);
      //addEdge(edgeType, nodePtrList[sourceNodeNumber], nodePtrList[sinkNodeNumber], branchValue, edgeNumber);
    }
    
  }
  
  file.close();
  
  
  cout<<endl<<"-----------------------------------------------------------------------------------------------"<<endl;
  cout<<"Total number of Nodes = "<<_NODES<<endl;
  cout<<"Total number of Edges = "<<_EDGES<<endl;
  cout<<"Total number of Current Source = "<<_CURRENTSOURCE<<endl;
  cout<<"Total number of Voltage Source = "<<_VOLTAGESOURCE<<endl;
  
  end = clock();
  
  cout<<"Time taken to build Graph from circuit : "<<(double)(end-start)/CLOCKS_PER_SEC<<" seconds"<<endl;
  cout<<"-----------------------------------------------------------------------------------------------"<<endl;
  /*
  Edge* Edg;
  int size=0;
  for(unsigned int i = 0; i<_NODES; i++)
  {
     
    size = nodePtrList[i]->edgeList.size();    
    for(unsigned int k=0; k<size; k++)
    {
      Edg = nodePtrList[i]->edgeList.back();
      cout<<Edg->edgeType<<" ";
      nodePtrList[i]->edgeList.pop_back();
    }
    cout<<endl;
  }*/
  
  
}


void GraphOfNetwork::addEdge(const string edgeType, const unsigned int sourceNodeNumber, const unsigned int sinkNodeNumber, const double weight, const unsigned int edgeNumber)
{
  edgePtrList[edgeNumber] = new Edge(edgeType, sourceNodeNumber, sinkNodeNumber, weight, _VOLTAGESOURCE);
  nodePtrList[sourceNodeNumber]->addEdge(edgePtrList[edgeNumber]);
  nodePtrList[sinkNodeNumber]->addEdge(edgePtrList[edgeNumber]);
}

void GraphOfNetwork::addEdge(const string edgeType, Node* sourceNode, Node* sinkNode, const double weight, const unsigned int edgeNumber)
{
  edgePtrList[edgeNumber] = new Edge(edgeType, sourceNode, sinkNode, weight, _VOLTAGESOURCE);
  
  sourceNode->addEdge(edgePtrList[edgeNumber]);
  sinkNode->addEdge(edgePtrList[edgeNumber]);
}

