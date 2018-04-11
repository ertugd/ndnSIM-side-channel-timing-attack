/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef BAD_GUY_H
#define BAD_GUY_H

#include "ns3/ndnSIM/model/ndn-common.hpp"
#include "ns3/ndnSIM/apps/ndn-consumer-cbr.hpp"


namespace ns3 {
namespace ndn {


/**
 * @ingroup ndn-apps
 * @brief Ndn application for sending out Interest packets at a "constant" rate (Poisson process)
 */
class BadGuy : public ConsumerCbr {
public:
  static TypeId
  GetTypeId();

  /**
   * \brief Default constructor
   * Sets up randomizer function and packet sequence number
   */
  BadGuy();
  virtual ~BadGuy();

  /**
   * dumpRttEstimate
   */
  void dumpRttEstimate();
  Time GetRTTValue(void) const;
  void SetRTTValue(Time newValue);

/////


  BadGuy(const std::string& prefix);

protected:
  /**
   * \brief Constructs the Interest packet and sends it using a callback to the underlying NDN
   * protocol
   */
  virtual void
  ScheduleNextPacket();

  void
  SendPacket();

  virtual void StartApplication();

protected:
  bool m_bad_behavior;     // if false, behave like CBR, if true, behave badly!
  std::string m_spy_prefix;  // the interest name to spy on (may be equal to the normal or not)
  uint32_t m_spy_seq;    // if 0 add no sufix, if greater than 0, append seq number to interest name

  EventId m_sendSpyEvent;
};

} // namespace ndn
} // namespace ns3

#endif
