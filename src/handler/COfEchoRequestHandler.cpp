/*
 * GNFlush SDN Controller GPL Source Code
 * Copyright (C) 2016, Greenet <greenet@greenet.net.cn>
 *
 * This file is part of the GNFlush SDN Controller. GNFlush SDN
 * Controller is a free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, , see <http://www.gnu.org/licenses/>.
 */

/******************************************************************************
*                                                                             *
*   File Name   : COfEchoRequestHandler.cpp           *
*   Author      : bnc zgzhao           *
*   Create Date : 2016-7-6           *
*   Version     : 1.0           *
*   Function    : .           *
*                                                                             *
******************************************************************************/
#include "COfEchoRequestHandler.h"
#include "openflow-common.h"
#include "openflow-10.h"
#include "openflow-13.h"
#include "COfMsgUtil.h"
#include "log.h"

// 测试用
UINT8 test_count = 0;

struct timeval start_time;
struct timeval end_time;



COfEchoRequestHandler::COfEchoRequestHandler()
{
}

COfEchoRequestHandler::~COfEchoRequestHandler()
{
}

void COfEchoRequestHandler::handle(CSmartPtr<CMsgQueue>& queue)
{
    LOG_DEBUG_FMT("%s recv new msg ..., queue size = %lu", toString().c_str(), queue->size());
    UINT1 version = 0;
    INT4 sockfd = 0;
    CSmartPtr<CMsg> msg;
    while (queue->try_pop(msg))
    {
        sockfd = msg->getSockfd();
        version = msg->getVersion();
        if (OFP13_VERSION == version)
        {
            COfMsgUtil::sendOfpMsg(sockfd, OFP13_VERSION, OFPT13_ECHO_REPLY, sizeof(struct ofp_header), 0);
            LOG_DEBUG("send of13 echo reply msg to switch");
        }
        else if (OFP10_VERSION == version)
        {
            COfMsgUtil::sendOfpMsg(sockfd, OFP10_VERSION, OFPT_ECHO_REPLY, sizeof(struct ofp_header), 0);
            LOG_DEBUG("send of10 echo reply msg to switch");
        }
        
    }
}

std::string COfEchoRequestHandler::toString()
{
    return "COfEchoRequestHandler";
}

CMsgHandler* COfEchoRequestHandler::clone()
{
    CMsgHandler* instance = new COfEchoRequestHandler();
    *instance = *this;
    return instance;
}
