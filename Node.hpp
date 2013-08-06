class Node
{
public:
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
  double potential;
  unsigned long int nodeNumber;
  
  list<Edge*> edgeList;
  

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------  
  Node(unsigned long int num);
  ~Node();
  void addEdge(Edge* newEdge);
  
  
  
};

inline Node::Node(unsigned long int num) : nodeNumber(num), potential(0)
{
  
}

inline Node::~Node()
{
  edgeList.clear();
}



inline void Node::addEdge(Edge* newEdge)
{
  edgeList.push_back(newEdge);
}


