class Node;

class Edge
{
public:
  unsigned int sourceNodeNumber;
  unsigned int sinkNodeNumber;
  double branchValue;
  double Voltage;
  string edgeType;

  Node* sourceNode;
  Node* sinkNode;
   
  unsigned int voltEdgeNumber;
  
  bool edgeVisited;
  
  Edge(const string edgeT, const unsigned int sourceNodeNum, const unsigned int sinkNodeNum, const double weight, const unsigned int edgeNumber);
  Edge(const string edgeT, Node* sourceNode, Node* sinkNode, const double weight, const unsigned int edgeNumber);    
};


inline Edge::Edge(const string edgeT, const unsigned int sourceNodeNum, const unsigned int sinkNodeNum, const double weight, const unsigned int edgeNumber) : edgeVisited(false)
{
  edgeType = edgeT;
  sourceNodeNumber = sourceNodeNum;
  sinkNodeNumber = sinkNodeNum;
  branchValue = weight;
  voltEdgeNumber = edgeNumber;
}
  
  
inline Edge::Edge(const string edgeT, Node* sourceNode, Node* sinkNode, const double weight, const unsigned int edgeNumber) : edgeVisited(false)
{
  edgeType = edgeT;
  sourceNode = sourceNode;
  sinkNode = sinkNode;
  branchValue = weight;
  voltEdgeNumber = edgeNumber;
}