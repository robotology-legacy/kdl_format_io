/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2013 Istituto Italiano di Tecnologia
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Silvio Traversaro */

#include "kdl_urdf/symoro_par/symoro_par_model.hpp"
#include "kdl_urdf/symoro_par/symoro_par_import.hpp"


using namespace KDL;
using namespace std;
using namespace symoro_par;

void printLink(const SegmentMap::const_iterator& link, const std::string& prefix)
{
  cout << prefix << "- Segment " << link->second.segment.getName() << " has " << link->second.children.size() << " children" << endl;
  for (unsigned int i=0; i<link->second.children.size(); i++)
    printLink(link->second.children[i], prefix + "  ");
}



int main(int argc, char** argv)
{
  if (argc < 2){
    std::cerr << "Expect .par file to parse" << std::endl;
    return -1;
  }
  
  symoro_par_model mdl;
  
  if( !parModelFromFile(argv[1],mdl) ) {cerr << "Could not parse SyMoRo par robot model" << endl; return false;}
  
  std::cout << "Extracted par file" << std::endl;
  std::cout << mdl.toString() << std::endl;

  
  Tree my_tree;
  if (!symoro_par::treeFromFile(argv[1],my_tree)) 
  {cerr << "Could not generate robot model and extract kdl tree" << endl; return false;}

  // walk through tree
  cout << " ======================================" << endl;
  cout << " Tree has " << my_tree.getNrOfSegments() << " link(s) and a root link" << endl;
  cout << " ======================================" << endl;
  SegmentMap::const_iterator root = my_tree.getRootSegment();
  printLink(root, "");
 
}


