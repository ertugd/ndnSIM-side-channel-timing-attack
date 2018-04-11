/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Copyright (c) 2018, Algorithmi Research Centree-CCN LAB., University of Minho, Portugal


 * Authors: Ertugrul Dogruluk, Antonio Costa. <d7474@di.uminho.pt>, Department of Informatics
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"
#include "../extensions/BadGuy.h"
namespace ns3 {

int
main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);
  AnnotatedTopologyReader topologyReader("", 1);
  topologyReader.SetFileName("/home/ertugrul/Desktop/ndnSIM/scenario/topology/tree.txt");
  topologyReader.Read();

//Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
//CS Policies
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Nocache");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Random", "MaxSize", "100");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Random", "MaxSize", "100");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Probability::Random", "MaxSize", "100");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Stats::Random","MaxSize",  "100");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Lfu", "MaxSize", "100");
  	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Fifo", "MaxSize", "100");
  	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru");
	ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "100");
	ndnHelper.InstallAll();

//Choosing forwarding strategy
	//ndn::StrategyChoiceHelper::InstallAll("/google.com", "/localhost/nfd/strategy/broadcast");
	//ndn::StrategyChoiceHelper::InstallAll("/google.com", "/localhost/nfd/strategy/client-control");
	//ndn::StrategyChoiceHelper::InstallAll("/google.com", "/localhost/nfd/strategy/ncc");
	ndn::StrategyChoiceHelper::InstallAll("/google.com", "/localhost/nfd/strategy/best-route");
//Installing global routing interface on all nodes
	ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
	ndnGlobalRoutingHelper.InstallAll();

//Getting containers for the consumer/producer
	Ptr<Node> producer = Names::Find<Node>("gw-root");

	Ptr<Node> consumers[16] = {
	Names::Find<Node>("leaf-1"), Names::Find<Node>("leaf-2"),Names::Find<Node>("leaf-3"),Names::Find<Node>("leaf-4"),
	Names::Find<Node>("leaf-5"),Names::Find<Node>("leaf-6"),Names::Find<Node>("leaf-7"),Names::Find<Node>("leaf-8"),
	Names::Find<Node>("leaf-9"),Names::Find<Node>("leaf-10"),Names::Find<Node>("leaf-11"),Names::Find<Node>("leaf-12"),
	Names::Find<Node>("leaf-13"),Names::Find<Node>("leaf-14"),Names::Find<Node>("leaf-15"),
	Names::Find<Node>("leaf-16")
								};


//Legitimate Nodes configuration based on ConsumerCbr
	ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("exponential"));
	consumerHelper.Install(consumers[0]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("uniform"));
	consumerHelper.Install(consumers[2]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("exponential"));
	consumerHelper.Install(consumers[3]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("uniform"));
	consumerHelper.Install(consumers[4]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("exponential"));
	consumerHelper.Install(consumers[15]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("uniform"));
	consumerHelper.Install(consumers[6]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("exponential"));
	consumerHelper.Install(consumers[7]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("uniform"));
	consumerHelper.Install(consumers[1]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("exponential"));
	consumerHelper.Install(consumers[9]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("uniform"));
	consumerHelper.Install(consumers[10]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("exponential"));
	consumerHelper.Install(consumers[11]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("uniform"));
	consumerHelper.Install(consumers[13]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("exponential"));
	consumerHelper.Install(consumers[14]);

	consumerHelper.SetAttribute("Frequency", StringValue("100"));
	consumerHelper.SetPrefix("/google.com");
	consumerHelper.SetAttribute("Randomize",StringValue("uniform"));
	consumerHelper.Install(consumers[8]);

//malicious nodes configuration
	 ndn::AppHelper BadGuy("ns3::ndn::BadGuy");
	 BadGuy.SetAttribute("Frequency", StringValue("100"));
	 BadGuy.SetAttribute("Randomize",StringValue("uniform"));
	 BadGuy.SetAttribute("BadBehavior", BooleanValue(true));
	 BadGuy.SetAttribute("SpyPrefix", StringValue("/google.com/%FE%02"));
	 BadGuy.SetAttribute("SpySeq", IntegerValue(0));
	 ApplicationContainer node13 = BadGuy.Install(consumers[12]);
	 node13.Start(Seconds(1.0));
	 node13.Stop(Seconds(2.0));

	 BadGuy.SetAttribute("Frequency", StringValue("100"));
	 BadGuy.SetAttribute("Randomize",StringValue("uniform"));
	 BadGuy.SetAttribute("BadBehavior", BooleanValue(true));
	 BadGuy.SetAttribute("SpyPrefix", StringValue("/google.com/%FE%07%96"));
	 BadGuy.SetAttribute("SpySeq", IntegerValue(0));
	 ApplicationContainer node6 = BadGuy.Install(consumers[5]);
	 node6.Start(Seconds(19.0));
	 node6.Stop(Seconds(20.0));

////////////////////////////////////////////////////////////////////////////////////

//Producer configuration
	ndn::AppHelper producerHelper("ns3::ndn::Producer");
	producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
		// producerHelper.SetAttribute("Signature", UintegerValue(100));
		// producerHelper.SetAttribute("KeyLocator", StringValue("/unique/key/locator"));

	ndnGlobalRoutingHelper.AddOrigins("/google.com", producer);
	producerHelper.SetPrefix("/google.com");
	producerHelper.Install(producer).Start(Seconds(0));

// Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();

//Tracers
  ndn::CsTracer::InstallAll("/home/ertugrul/Desktop/ndnSIM/scenario/results/ndn_attack_Cs_tracer.txt");
  ndn::L3RateTracer::InstallAll("/home/ertugrul/Desktop/ndnSIM/scenario/results/ndn_attack_L3-rate-trace.txt");
  ndn::AppDelayTracer::InstallAll("/home/ertugrul/Desktop/ndnSIM/scenario/results/ndn_attack_app-delays-trace.txt");
  L2RateTracer::InstallAll("/home/ertugrul/Desktop/ndnSIM/scenario/results/ndn_attack_drop-trace.txt");

  // ndn::AppDelayTracer::InstallAll("-");
  //ns3::AnnotatedTopologyReader::SaveTopology{("/home/ertugrul/Desktop/ndnSIM/scenario/results/topology.pdf")};

  //ns3::Timer::RUNNING

  Simulator::Stop(Seconds(30));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
