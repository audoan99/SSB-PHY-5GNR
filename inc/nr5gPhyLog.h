#ifndef __NR_5G_PHY_LOG_H__
#define __NR_5G_PHY_LOG_H__

#include "nr5gPhyCnInc.h"

void Loginit();
void Logstop();

extern FILE *flog;

#endif /*__NR_5G_PHY_LOG_H__*/