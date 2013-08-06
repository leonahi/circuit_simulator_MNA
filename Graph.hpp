class GraphOfNetwork
{
private:
  unsigned int _NODES;                                           // Number of nodes in the network
  unsigned int _EDGES;                                           // Number of branches in the network
  unsigned int _VOLTAGESOURCE;                                   // Number of Voltage Source
  unsigned int _CURRENTSOURCE;                                   // Number of Current Source
  
//-------Dense Matrix-----------------------  
  double* denseMatrix;                                           // Dense matrix for MNA system of equations
  unsigned int ORDER;                                            // Order of matrix;
//------------------------------------------  

//-------Current Vector---------------------
  double* currentVector;                                         // Right hand side of Ax = b
//------------------------------------------  
  
//-------Solution Vector--------------------
  double* solVec;
//------------------------------------------
  
  Node** nodePtrList;
  Edge** edgePtrList;
  
  void addEdge(const string edgeType, const unsigned int sourceNodeNumber, const unsigned int sinkNodeNumber, const double weight, const unsigned int edgeNumber);
  void addEdge(const string edgeType, Node* sourceNode, Node* sinkNode, const double weight, const unsigned int edgeNumber);
  
  void fillMatrix_Dense();
  
  void LUDecomposition();
  
public:
  GraphOfNetwork();
  void convertNetworkIntoGraph(char *argv);
  void findVoltage();                                            // For Dense Matrix
  void printSolution();
 
};

inline GraphOfNetwork::GraphOfNetwork()
{
  _NODES = 0;
  _EDGES = 0;
  _VOLTAGESOURCE = 0;
  _CURRENTSOURCE = 0;
  nodePtrList = NULL;
  edgePtrList = NULL;
}
