#include "node.h"
#include <iostream>

using namespace std;

void routingAlgo(vector<RoutingNode*> nd)
{
  //Your code here
	// for (int i = 0; i < nd.size(); ++i)
	// {
	int i=0;//a random first node to start
		routingtbl mytbl = nd[i]->getTable();
		string myip = mytbl.tbl[0].ip_interface;	//get ip of the random node selected

		for (int j = 0; j < nd.size(); ++j)
		{
			if ( nd[i]->isMyInterface(nd[j]->getname())  )
			{
				routingtbl histbl = nd[j]->getTable();
				string hisip = histbl.tbl[0].ip_interface;
		
				nd[i]->addTblEntry(myip,1);
				nd[i]->mytbl.tbl[tbl.size()-1].dstip = hisip;
				nd[i]->mytbl.tbl[tbl.size()-1].nextHop = hisip;
			}
		}
		nd[i].sendMsg();
//	}
}

void RoutingNode::recvMsg(R.outeMsg *msg) {
  //your code here
	string got_tbl_from = msg->from;
	Routingtbl newroutingtbl = *msg->mytbl;
	string tbl_recieverd_by = msg->recvip;

	newroutingtbl.tbl /*vector consisting routing entries jo mila wo*/

	this->mytbl;	//this is my own table jo pehle se hai
	
	for (auto pehle = (this->mytbl).tbl.begin(); pehle < this->mytbl.tbl.end(); ++pehle)
	{
		//check this
		for (auto naya = newroutingtbl.tbl.begin(); naya < newroutingtbl.tbl.end(); ++naya)
		{
			if(naya->dstip == pehle->dstip)
			{
				if (pehle->cost > (naya->cost)+1)
				{					
					erase(pehle--);
					(this->mytbl).tbl.push_back(*naya);
				}
			}
		}

	}












	// //Correct this
	 // findroutingentry.dstip= msg->from;
	// findroutingentry.nextHop = msg->from;
	// findroutingentry.ip_interface = msg->recvip;
	
}