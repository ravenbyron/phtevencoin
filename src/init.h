// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Phtevencoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PHTEVENCOIN_INIT_H
#define PHTEVENCOIN_INIT_H

#include <string>

class CScheduler;
class CWallet;

namespace boost
{
class thread_group;
} // namespace boost

extern CWallet* pwalletMain;

void StartShutdown();
bool ShutdownRequested();
/** Interrupt threads */
void Interrupt(boost::thread_group& threadGroup);
void Shutdown();
bool AppInit2(boost::thread_group& threadGroup, CScheduler& scheduler);

/** The help message mode determines what help message to show */
enum HelpMessageMode {
    HMM_PHTEVENCOIND,
    HMM_PHTEVENCOIN_QT
};

/** Help for options shared between UI and daemon (for -help) */
std::string HelpMessage(HelpMessageMode mode);
/** Returns licensing information (for -version) */
std::string LicenseInfo();

#endif // PHTEVENCOIN_INIT_H
