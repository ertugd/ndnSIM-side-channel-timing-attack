#include "BadGuy.h"
#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/packet.h"
#include "ns3/callback.h"
#include "ns3/string.h"
#include "ns3/boolean.h"
#include "ns3/uinteger.h"
#include "ns3/integer.h"
#include "ns3/double.h"


NS_LOG_COMPONENT_DEFINE("ndn.BadGuy");

namespace ns3 {
namespace ndn {

NS_OBJECT_ENSURE_REGISTERED(BadGuy);

TypeId
BadGuy::GetTypeId(void)
{
  static TypeId tid =
    TypeId("ns3::ndn::BadGuy")
      .SetGroupName("Ndn")
      .SetParent<ConsumerCbr>()
      .AddConstructor<BadGuy>()

      .AddAttribute("BadBehavior", "Am i a good guy or a bad guy",
                    BooleanValue(false),
                    MakeBooleanAccessor(&BadGuy::m_bad_behavior), MakeBooleanChecker())

      .AddAttribute("SpySeq", "The sequence number to Spy",
                    IntegerValue(0),
                    MakeIntegerAccessor(&BadGuy::m_spy_seq), MakeIntegerChecker<uint32_t>())

	.AddAttribute("SpyPrefix", "The prefix that we want to spy",
			StringValue("/"),
			MakeStringAccessor(&BadGuy::m_spy_prefix), MakeStringChecker())

    ;

  return tid;
}

BadGuy::BadGuy()
  : m_bad_behavior(false)
  , m_spy_prefix("/")
  , m_spy_seq(0)
{
  NS_LOG_FUNCTION_NOARGS();
}

BadGuy::~BadGuy()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void
BadGuy::StartApplication()
{
	//App::StartApplication();
	//BadGuy::ScheduleNextPacket();
	ConsumerCbr::StartApplication();

	//std::cout << "\n BadGuy(" << m_bad_behavior << ") is starting\n";
	std::cout << "Time\tNode\tESTIMATED_VALUE\n";
	BadGuy::dumpRttEstimate();
}



void
BadGuy::dumpRttEstimate()

{
  if (m_rtt) {
	  std::cout << Now() << "\t" << "Mailicious Node" << "\t" << m_rtt->GetCurrentEstimate() << "\n";
	//ObjectBase::ConstructSelf(AttributeConstructionList());
	  NS_LOG_DEBUG ("ESTIMATED VALUE: " << m_rtt->GetCurrentEstimate()<<"sec.");
  }
  Simulator::Schedule(Seconds(0.1), &BadGuy::dumpRttEstimate, this);
 }

Time
BadGuy::GetRTTValue(void) const
{
//	std::cout << "Getting the value";

	return m_rtt->GetCurrentEstimate();
	// return m_rtt_value;
}

void
BadGuy::SetRTTValue(Time newValue)
{
//	std::cout << "Setting the value to " << newValue << "\n";

	//m_rtt_value = newValue;
}

void
BadGuy::SendPacket()
{
  if (!m_active)
    return;

  NS_LOG_FUNCTION_NOARGS();

  uint32_t seq = m_spy_seq;
  // we set the prefix with the sequence number included! No need to add one...
  shared_ptr<Name> nameWithSequence = make_shared<Name>(m_spy_prefix);
  if (m_spy_seq > 0)
	  nameWithSequence->appendSequenceNumber(m_spy_seq);
  else
	 // try to obtain the seq number from the name...
	 seq = nameWithSequence->at(-1).toSequenceNumber();
  std::cout << "Bad guy Requesting Interest with seq =" << seq << "\n";

  //

  // shared_ptr<Interest> interest = make_shared<Interest> ();
  shared_ptr<Interest> interest = make_shared<Interest>();
  interest->setNonce(m_rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
  interest->setName(*nameWithSequence);
  time::milliseconds interestLifeTime(m_interestLifeTime.GetMilliSeconds());
  interest->setInterestLifetime(interestLifeTime);

  // NS_LOG_INFO ("Requesting Interest: \n" << *interest);
  NS_LOG_INFO("> Interest for " );
  //  std::cout << Now() << "\t" << "MailiciousNode" << "\t" << "Sending interest for " << nameWithSequence << "\n";

  WillSendOutInterest(seq);

  m_transmittedInterests(interest, this, m_face);
  m_appLink->onReceiveInterest(*interest);

  ScheduleNextPacket();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////

void
BadGuy::ScheduleNextPacket()
{
  // double mean = 8.0 * m_payloadSize / m_desiredRate.GetBitRate ();
  // std::cout << "next: " << Simulator::Now().ToDouble(Time::S) + mean << "s\n";

  if (m_firstTime) {
	if (m_bad_behavior)
		m_sendSpyEvent = Simulator::Schedule(Seconds(0.0), &BadGuy::SendPacket, this);
	else
		m_sendEvent = Simulator::Schedule(Seconds(0.0), &Consumer::SendPacket, this);
    m_firstTime = false;
  }
  else {
	  if (!m_bad_behavior && !m_sendEvent.IsRunning())
		  m_sendEvent = Simulator::Schedule((m_random == 0) ? Seconds(1.0 / m_frequency)
                                                      : Seconds(m_random->GetValue()),
                                      &Consumer::SendPacket, this);
      if (m_bad_behavior && !m_sendSpyEvent.IsRunning())
    	m_sendSpyEvent = Simulator::Schedule((m_random == 0) ? Seconds(1.0 / m_frequency)
                                                    : Seconds(m_random->GetValue()),
                                    &BadGuy::SendPacket, this);
  }
}


} // namespace ndn
} // namespace ns3
